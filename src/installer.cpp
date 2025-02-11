#include "installer.h"
#include "main.h"

#include <memory>

#include <wx/filefn.h>
#include <wx/dir.h>

const wxString PKG_LINK = "https://nekocord.dev/uploads/nekocord/dev/423/nekocord.zip";

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

ProgressDlg::ProgressDlg(wxWindow* parent, bool uninstall, wxString zipPath)
    : wxProgressDialog("Processing...", wxEmptyString, 100, parent,
                       wxPD_APP_MODAL | wxPD_AUTO_HIDE | wxPD_SMOOTH | wxPD_CAN_ABORT)
{
    asarPath = GetDiscordPathWithVer(wxGetApp().GetSettings().discordBranch) \
                + wxFileName::GetPathSeparator() + "resources" \
                + wxFileName::GetPathSeparator() + "app.asar";

    if (!uninstall)
    {
        if (zipPath != wxEmptyString)
        {
            wxWebRequest request = wxWebSession::GetDefault().CreateRequest(this, PKG_LINK);

            Bind(wxEVT_WEBREQUEST_STATE, [this](wxWebRequestEvent& evt)
            {
                switch (evt.GetState())
                {
                    case wxWebRequest::State_Completed:
                    {
                        if (Pulse("Unpacking..."))
                        {
                            this->Hide();
                            break;
                        }

                        InstallFromStream(*evt.GetResponse().GetStream());
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
            wxFileInputStream stream(zipPath);
            InstallFromStream(stream);
        }
    }
    else {
        wxCopyFile(asarPath + ".backup", asarPath);
        wxRemoveFile(asarPath + ".backup");
        Update(100, "Uninstalled.");
    }
}

void ProgressDlg::InstallFromStream(wxInputStream& stream)
{
    std::unique_ptr<wxZipEntry> entry;
    wxZipInputStream zip(stream);

    while (entry.reset(zip.GetNextEntry()), entry.get() != nullptr)
    {
        wxString name = entry->GetName();
        if (name == "app.asar")
        {
            if (Pulse("Installing... this is done quickly."))
            {
                this->Hide();
                break;
            }
            wxCopyFile(asarPath, asarPath + ".backup");
            
            zip.OpenEntry(*entry.get());

            wxFileOutputStream outF(asarPath);
            
            zip.Read(outF);
            Update(100);
            wxMessageBox("Done.");
        }
    }
}