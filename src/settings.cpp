#include "main.h"
#include "settings.h"
#include "mainwindow.h"
#include <wxUI/wxUI.h>

using namespace wxUI;

PrefsPageGeneralPanel::PrefsPageGeneralPanel(wxWindow* parent)
    : wxPanel(parent)
{
    AppSettings st = wxGetApp().GetSettings();

    VSizer {
        wxSizerFlags().Expand().Border(),

        discordBr = RadioBox {
            wxSizerFlags().Expand().Border(wxBOTTOM, 15),
            "Discord branch",
            RadioBox::withChoices {},
            {"Stable", "PTB", "Canary"}
        }
            .withSelection(st.discordBranch)
            .setStyle(wxRA_SPECIFY_ROWS)
            .withMajorDim(1),

        nekoBr = RadioBox {
            wxSizerFlags().Expand().Border(wxBOTTOM, 15),
            "NekoCord branch",
            RadioBox::withChoices {},
            {"Stable", "Dev", "From zip"}
        }
            .withSelection(st.nekoBranch)
            .setStyle(wxRA_SPECIFY_ROWS)
            .withMajorDim(1),

        HSizer {
            "Discord path",
            wxSizerFlags(1).Expand().Border(wxBOTTOM, 15),
            discordPath = TextCtrl { st.discordPath }.withStyle(wxALIGN_LEFT)
        },

        CheckBox { "Dark Blockchain" },

        CheckBox { "Install McAfee" }
    }
        .attachTo(this);
}

bool PrefsPageGeneralPanel::TransferDataFromWindow()
{
    AppSettings st = wxGetApp().GetSettings();

    st.discordBranch = (DISCORD_BRANCH)discordBr->GetSelection();
    st.nekoBranch = (NEKO_BRANCH)nekoBr->GetSelection();
    st.discordPath = discordPath->GetValue();

    wxGetApp().SetSettings(st);
    wxDynamicCast(wxGetApp().GetTopWindow(), MainWindow)->UpdateSettings();

    return true;
}

PrefsPageAboutPanel::PrefsPageAboutPanel(wxWindow* parent)
    : wxPanel(parent)
{
    VSizer {
        wxSizerFlags().CenterHorizontal().CenterVertical(),
        Text { "NekoCord Installer" },
        Text { "-- Unofficial --" },
        Text { "Made by Le Bao Nguyen, using wxWidgets and C++" }
    }
        .attachTo(this);
}

PrefsPageFAQPanel::PrefsPageFAQPanel(wxWindow* parent)
    : wxPanel(parent)
{
    VSizer {
        Text {
            wxSizerFlags().Border(wxBOTTOM, 10),
            "Q: Discord got logged out!\n"
            "A: Just log back in. We've changed a file which has unmatch signature."
        },

        Text {
            wxSizerFlags().Border(wxBOTTOM, 10),
            "Q: Is this safe?\n"
            "A: Yes. The source code is private due to hardcoded nekocord link.\n"
            "And since joining in its beta requires permission, I will just keep the source code private for now.\n"
            "This installer fetches the archive, backups your current Discord's app.asar, installs/uninstalls/updates nekocord there."
        },

        Text {
            wxSizerFlags().Border(wxBOTTOM, 10),
            "Q: Why this? Why C++? Why not Flutter (which the original installer uses)?\n"
            "A: Flutter dropped support for non-Metal Macs. Discord still works there.\n"
            "As long as there is no problem about the computer being non-Metal-d, which is probably not gonna happen,\n"
            "there is no reason to abandon this platform, especially when OpenCore Legacy Patcher and DosDude's tools exist.\n"
            "As for the programming language and GUI toolkit used: Idk why and wxWidgets is good :thumbsup~1:"
        }
    }
        .attachTo(this);
}