#include "installer.h"
#include "main.h"

#include <memory>

#include <wx/filefn.h>
#include <wx/dir.h>

const wxString PKG_LINK = "https://nekocord.dev/uploads/nekocord/dev/423/nekocord.zip";

wxString GetDiscordPath(DISCORD_BRANCH branch GDP_SecondArg)
{
    #ifdef _WIN32
    wxString path = wxStandardPaths::Get().GetUserLocalDataDir().RemoveLast(13) + '\\';
    #else

    #ifdef __APPLE__
    wxString path = "/Applications/";
    #else
    wxString path = useFlatpak ? "/var/lib/flatpak/app/com.discordapp." :"/usr/share/";
    #endif

    #endif
    
    switch (branch)
    {
        case DISCORD_BRANCH::FINAL:
            path += wxString("Discord")DoLowerStr;
            break;

        case DISCORD_BRANCH::PTB:
            path += wxString("DiscordPTB")DoLowerStr;
            break;

        case DISCORD_BRANCH::CANARY:
            path += wxString("DiscordCanary")DoLowerStr;
            break;
    }

    #ifdef __APPLE__
    path += ".app"
    #endif
        
    return path + wxFileName::GetPathSeparator();
}

wxString GetDiscordPathWithVer(DISCORD_BRANCH branch GDP_SecondArg)
{
    #ifndef __linux__
    wxString path = GetDiscordPath(branch);
    #else
    wxString path = GetDiscordPath(branch, useFlatpak);
    #endif

    #ifdef __APPLE__
    path += "Contents"
    return path;
    #else

    wxDir dir(path);

    if (!dir.HasSubDirs())
    {
        dir.Close();
        wxMessageBox(path + " not found", "Error", wxICON_ERROR);
        return wxEmptyString;
    }

    #ifdef _WIN32
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
    #else
    if (dir.HasSubDirs("resources"))
    {
        dir.Close();
        return path;
    }
    #endif
    dir.Close();
    wxMessageBox(path + ": No Discord installation found based on the selected branch", "Error", wxICON_ERROR);
    return wxEmptyString;

    #endif
}

ProgressDlg::ProgressDlg(wxWindow* parent, bool uninstall, wxString zipPath GDP_SecondArg)
    : wxProgressDialog("Processing...", wxEmptyString, 100, parent,
                       wxPD_APP_MODAL | wxPD_AUTO_HIDE | wxPD_SMOOTH | wxPD_CAN_ABORT)
{
    #ifndef __linux__
    asarPath = GetDiscordPathWithVer(wxGetApp().GetSettings().discordBranch) \
                + wxFileName::GetPathSeparator() + "resources" \
                + wxFileName::GetPathSeparator() + "app.asar";
    #else
    asarPath = GetDiscordPathWithVer(wxGetApp().GetSettings().discordBranch, useFlatpak) \
                + wxFileName::GetPathSeparator() + "resources" \
                + wxFileName::GetPathSeparator() + "app.asar";
    #endif

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