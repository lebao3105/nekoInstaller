#pragma once

#include "../pch/pch.h"

#include <wx/preferences.h>
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

extern std::map<DISCORD_BRANCH, std::string> discordBranches;
extern std::map<NEKO_BRANCH, std::string> nekoBranches;

struct AppSettings
{
    DISCORD_BRANCH discordBranch;
    NEKO_BRANCH nekoBranch = DEV;
    wxString discordPath;

    #ifdef __linux__
    bool useFlatpak = false;
    #endif
};

#pragma endregion

#pragma region Setting panes

class PrefsPageGeneralPanel: public wxPanel
{
public:
    explicit PrefsPageGeneralPanel(wxWindow* parent);

private:
    wxUI::RadioBox::Proxy discordBr;
    wxUI::RadioBox::Proxy nekoBr;
    wxUI::TextCtrl::Proxy discordPath;
    wxUI::CheckBox::Proxy useCustom;

    #ifdef __linux__
    wxUI::CheckBox::Proxy useFlatpak;
    #endif

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
