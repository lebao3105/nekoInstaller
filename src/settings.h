#pragma once

#include "../pch/pch.h"

#include <wx/preferences.h>
#include <wx/fileconf.h>
#include <wxMaterialDesignArtProvider.hpp>

#include <memory>
#include <wxUI/wxUI.h>
#include <map>
#include <string>

#pragma region Enumerations and structs and variables

enum DISCORD_BRANCH
{
    FINAL,
    PTB,
    CANARY
};

enum NEKO_BRANCH
{
    STABLE,
    DEV,
    FROM_ZIP
};

// std::map<DISCORD_BRANCH, std::string> discordBranches
// {
//     std::make_pair(FINAL, "Stable"),
//     std::make_pair(PTB, "PTB"),
//     std::make_pair(CANARY, "Canary")
// };

// std::map<NEKO_BRANCH, std::string> nekoBranches
// {
//     std::make_pair(STABLE, "Stable"),
//     std::make_pair(DEV, "Dev"),
//     std::make_pair(FROM_ZIP, "From a zip file")
// };

class AppSettings: public wxFileConfig
{
public:
    DISCORD_BRANCH discordBranch;
    NEKO_BRANCH nekoBranch;

    wxString discordPath;

    explicit AppSettings()
        : wxFileConfig("nekoInstaller", "NekoCord Team", "settings", "", wxCONFIG_USE_LOCAL_FILE)
        {
            EnableAutoSave();
            // Read<DISCORD_BRANCH>("discordBranch", &discordBranch, FINAL);
            // Read<NEKO_BRANCH>("nekoBranch", &nekoBranch, STABLE);
            Read("discordPath", &discordPath);
        }
};

#pragma endregion

#pragma region Setting panes

class PrefsPageGeneralPanel: public wxPanel
{
public:
    explicit PrefsPageGeneralPanel(wxWindow* parent);

private:
    wxUI::Choice::Proxy discordBr;
    wxUI::Choice::Proxy nekoBr;
    wxUI::TextCtrl::Proxy discordPath;

    virtual bool TransferDataToWindow() override;
    virtual bool TransferDataFromWindow() override;
};

class PrefsPageAboutPanel: public wxPanel
{
public:
    explicit PrefsPageAboutPanel(wxWindow* parent);
};

class PrefsPageFAQPanel: public wxPanel
{
public:
    explicit PrefsPageFAQPanel(wxWindow* parent);
};

#pragma endregion

#pragma region wxStockPreferencesPages

// Reminder:
// wx/preferences.h has 2 stock pages type:
// One is General, one is Advanced.
// Just for anyone who wondering about PrefsPageGeneral's constructor.
// We only use Kind_General for now.

class PrefsPageGeneral: public wxStockPreferencesPage
{
public:
    explicit PrefsPageGeneral(): wxStockPreferencesPage(Kind_General) {}
    virtual wxWindow* CreateWindow(wxWindow* parent) override {
        return new PrefsPageGeneralPanel(parent);
    }
};

class PrefsPageAbout: public wxPreferencesPage
{
public:
    virtual wxString GetName() const override { return "About"; }
    virtual wxBitmapBundle GetIcon() const override {
        return wxMaterialDesignArtProvider::GetBitmap(wxART_INFO, wxART_CLIENT_FLUENTUI_REGULAR, wxDefaultSize);
    }
    virtual wxWindow* CreateWindow(wxWindow* parent) override {
        return new PrefsPageAboutPanel(parent);
    }
};

class PrefsPageFAQ: public wxPreferencesPage
{
public:
    virtual wxString GetName() const override { return "FAQ"; }
    virtual wxBitmapBundle GetIcon() const override {
        return wxMaterialDesignArtProvider::GetBitmap(wxART_INFO, wxART_CLIENT_FLUENTUI_REGULAR, wxDefaultSize);
    }
    virtual wxWindow* CreateWindow(wxWindow* parent) override {
        return new PrefsPageFAQPanel(parent);
    }
};

#pragma endregion
