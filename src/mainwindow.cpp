#include "main.h"
#include "mainwindow.h"
#include "installer.h"
#include <wxUI/wxUI.h>
#include <wxMaterialDesignArtProvider.hpp>
#include <wx/stdpaths.h>
#include <wx/filefn.h>

using namespace wxUI;

MainWindow::MainWindow()
    : wxFrame(NULL, wxID_ANY, "NekoCord Installer")
{
    wxString exeDir = wxPathOnly(wxStandardPaths::Get().GetExecutablePath());
    wxBitmap wordmark(exeDir + "/nekocord_wordmark.png", wxBITMAP_TYPE_PNG);
    wxBitmap logo(exeDir + "/nekocord_logo_512.png", wxBITMAP_TYPE_PNG);

    bool canUninstall = wxFileExists(GetDiscordPathWithVer(wxGetApp().GetSettings().discordBranch) \
        + wxFileName::GetPathSeparator() + "resources" \
        + wxFileName::GetPathSeparator() + "app.asar.backup");

    wxUI::Button::Proxy doItBtn;
    wxUI::Button::Proxy settingsBtn;

    wxBitmap::Rescale(wordmark, wxSize(521 / 3, 118 / 3));
    wxBitmap::Rescale(logo, wxSize(256 * 0.75, 256 * 0.75));

    VSizer {
        wxSizerFlags().Expand(),

        Generic {
            wxSizerFlags().Expand().Top(),
            [wordmark](wxWindow* window)
            {
                wxPanel* wordmarkPanel = new wxPanel(window, wxID_ANY);
                wordmarkPanel->SetBackgroundColour(wxColour(172, 210, 143));

                wxBoxSizer* sz = new wxBoxSizer(wxHORIZONTAL);
                wxStaticBitmap* bmp = new wxStaticBitmap(wordmarkPanel, wxID_ANY, wxBitmap(wordmark));
                sz->Add(bmp, 0, wxALL, 5);

                wordmarkPanel->SetSizer(sz);
                wordmarkPanel->Layout();
                
                return wordmarkPanel;
            }
        },

        VSizer {
            wxSizerFlags().CenterHorizontal().CenterVertical(),
            Bitmap(wxSizerFlags().Border(wxBOTTOM, 40).Border(wxTOP, 50), logo),

            Text { wxSizerFlags().Border(wxBOTTOM, 15), "Current Discord channel: " },

            Text { wxSizerFlags().Border(wxBOTTOM, 35), wxString::Format("Current Discord path:\n%s", wxGetApp().GetSettings().discordPath ).utf8_string() },

            doItBtn = Button {
                canUninstall ? "Uninstall" : "Install / Update"
            }
                .bind([this, canUninstall]() {
                    ProgressDlg* dlg = new ProgressDlg(this, canUninstall);
                    dlg->Show(true);
                }),

            settingsBtn = Button {
                "Settings"
            }
                .bind([this]() {
                    wxGetApp().ShowPreferencesEditor(this);
                })
        },

    }
        .attachTo(this);
    
    doItBtn->SetBitmap(wxMaterialDesignArtProvider::GetBitmap(wxART_ARROW_SQUARE_DOWN, wxART_CLIENT_FLUENTUI_REGULAR, wxDefaultSize, wxColour(172, 210, 143)));
    settingsBtn->SetBitmap(wxMaterialDesignArtProvider::GetBitmap(wxART_SETTINGS, wxART_CLIENT_FLUENTUI_REGULAR, wxDefaultSize, wxColour(172, 210, 143)));

    this->SetSize(800, 680);
    this->SetBackgroundColour(wxColour(233, 250, 230));
}