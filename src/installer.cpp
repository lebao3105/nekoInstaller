#include "downloader.h"
#include "installer.h"
#include "main.h"

#include <memory>

#include <wx/zipstrm.h>
#include <wx/filefn.h>
#include <wx/dir.h>
#include <wx/wfstream.h>

wxString GetDiscordPath(DISCORD_BRANCH branch)
{
    wxString path = wxStandardPaths::Get().GetUserLocalDataDir().RemoveLast(13);
    
    switch (branch)
    {
        case DISCORD_BRANCH::FINAL:
            path += "Discord";
            break;

        case DISCORD_BRANCH::PTB:
            path += "DiscordPTB";
            break;

        case DISCORD_BRANCH::CANARY:
            path += "DiscordCanary";
            break;
    }
        
    return path + wxFileName::GetPathSeparator();
}

wxString GetDiscordPathWithVer(DISCORD_BRANCH branch)
{
    wxString path = GetDiscordPath(branch);
    wxDir dir(path);

    if (!dir.HasSubDirs())
    {
        dir.Close();
        wxMessageBox(path + " not found", "Error", wxICON_ERROR);
        return wxEmptyString;
    }

    wxString latestVersion;
    bool cont = dir.GetFirst(&latestVersion, "", wxDIR_DIRS);

    while (cont)
    {
        wxString crafted(path + wxFileName::GetPathSeparator() + latestVersion);
        wxDir subDir(crafted);

        // Older versions of Discord normally have their folder empty.
        // At least that is what I've found out.
        if (subDir.HasSubDirs("resources"))
        {
            subDir.Close();
            return crafted;
        }
        else
        {
            subDir.Close();
            cont = dir.GetNext(&latestVersion);
        }
    }

    dir.Close();
    wxMessageBox(path + ": No Discord installation found based on the selected branch", "Error", wxICON_ERROR);

    return wxEmptyString;
}

ProgressDlg::ProgressDlg(wxWindow* parent, bool uninstall)
    : wxProgressDialog("Processing...", wxEmptyString, 100, parent,
                       wxPD_APP_MODAL | wxPD_AUTO_HIDE | wxPD_SMOOTH | wxPD_CAN_ABORT)
{
    wxString asarPath = GetDiscordPathWithVer(wxGetApp().GetSettings().discordBranch) \
                            + wxFileName::GetPathSeparator() + "resources" \
                            + wxFileName::GetPathSeparator() + "app.asar";

    if (!uninstall)
    {
        request = wxWebSession::GetDefault().CreateRequest(this, PKG_LINK);

        Bind(wxEVT_WEBREQUEST_STATE, [this, asarPath](wxWebRequestEvent& evt)
        {
            switch (evt.GetState())
            {
                case wxWebRequest::State_Completed:
                {
                    Pulse("Unpacking...");
                    std::unique_ptr<wxZipEntry> entry;
                    wxZipInputStream zip(*evt.GetResponse().GetStream());

                    while (entry.reset(zip.GetNextEntry()), entry.get() != nullptr)
                    {
                        wxString name = entry->GetName();
                        if (name == "app.asar")
                        {
                            Pulse("Installing... this is done quickly.");
                            wxCopyFile(asarPath, asarPath + ".backup");
                            
                            zip.OpenEntry(*entry.get());

                            wxFileOutputStream outF(asarPath);
                            
                            zip.Read(outF);
                            Update(100, "Completed.");
                        }
                    }
                    break;
                }

                case wxWebRequest::State_Failed:
                    wxLogError("Unable to fetch!\n%s", evt.GetErrorDescription());
                    break;
                
                // TODO
                default: break;
            }
        });
        request.Start();
        Pulse("Downloading the original installer");
    }

    else {
        wxCopyFile(asarPath + ".backup", asarPath);
        wxRemoveFile(asarPath + ".backup");
        Update(100, "Uninstalled.");
    }
}