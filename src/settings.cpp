#include "main.h"
#include "settings.h"
#include <wxUI/wxUI.h>

using namespace wxUI;

PrefsPageGeneralPanel::PrefsPageGeneralPanel(wxWindow* parent)
    : wxPanel(parent)
{
    VSizer {
        HSizer {
            Text { "Discord branch" },

            discordBr = Choice { {"Stable", "PTB", "Canary"} }
        },

        HSizer {
            Text { "NekoCord branch" },

            nekoBr = Choice { {"Stable", "Dev", "From zip"} }
        },

        HSizer {
            Text { "Discord path" },
            discordPath = TextCtrl {  }
        }
    }
        .attachTo(this);
}

bool PrefsPageGeneralPanel::TransferDataToWindow()
{
    // AppSettings st = wxGetApp().GetSettings();

    // discordPath->DiscardEdits();
    // discordPath->AppendText(st.discordPath);

    // discordBr->SetStringSelection(discordBranches[st.discordBranch]);
    // nekoBr->SetStringSelection(nekoBranches[st.nekoBranch]);
    return true;
}

bool PrefsPageGeneralPanel::TransferDataFromWindow()
{
    // AppSettings st = wxGetApp().GetSettings();

    // switch (discordBr->GetSelection())
    // {
    //     case 0:
    //         st.discordBranch = FINAL;
    //         break;
        
    //     case 1:
    //         st.discordBranch = PTB;
    //         break;
        
    //     case 2:
    //         st.discordBranch = CANARY;
    // }

    return true;
}

PrefsPageAboutPanel::PrefsPageAboutPanel(wxWindow* parent)
    : wxPanel(parent)
{
    VSizer {
        wxSizerFlags().Center(),
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
            "A: Yes. The source code is private due to hardcoded nekocord link. "
            "And since joining in its beta requires permission, I will just keep the source code private for now.\n"
            "This installer only fetch the archive, backup your current Discord's app.asar, install nekocord one there, and done."
        },

        Text {
            wxSizerFlags().Border(wxBOTTOM, 10),
            "Q: Why this? Why C++? Why not Flutter (which the original installer uses)?\n"
            "A: Flutter dropped support for non-Metal Macs. Discord still works there.\n"
            "As long as there is no problem about the computer being non-Metal-d, which is probably not gonna happen, "
            "there is no reason to abandon this platform, especially when OpenCore Legacy Patcher and DosDude's tools exist.\n"
            "As for the programming language and GUI toolkit used: Idk why and wxWidgets is good :thumbsup~1:"
        }

    }
        .attachTo(this);
}