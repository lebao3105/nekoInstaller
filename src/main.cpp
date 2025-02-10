#include "main.h"
#include "mainwindow.h"
#include "installer.h"

#include <wx/filesys.h>
#include <wx/fs_arc.h>
#include <wx/artprov.h>
#include <wxMaterialDesignArtProvider.hpp>
#include <wx/stdpaths.h>

wxIMPLEMENT_APP(nekoApp);

	std::map<DISCORD_BRANCH, std::string> discordBranches = {
		std::make_pair(FINAL, "Stable"),
		std::make_pair(PTB, "PTB"),
		std::make_pair(CANARY, "Canary")
	};
	
	std::map<NEKO_BRANCH, std::string> nekoBranches = {
		std::make_pair(STABLE, "Stable"),
		std::make_pair(DEV, "Dev"),
		std::make_pair(FROM_ZIP, "From a zip file")
	};

bool nekoApp::OnInit()
{
	if (!wxApp::OnInit())
		return false;

	wxImage::AddHandler(new wxPNGHandler());
	wxFileSystem::AddHandler(new wxArchiveFSHandler());
	wxArtProvider::Push(new wxMaterialDesignArtProvider);

	SetAppDisplayName("NekoCord Installer");

	MainWindow* wind = new MainWindow();
	wind->Show();

	settings.discordPath = GetDiscordPath(settings.discordBranch);
	
	return true;
}

void nekoApp::ShowPreferencesEditor(wxWindow* parent)
{
	if (!prefEditor)
	{
		prefEditor.reset(new wxPreferencesEditor);
		prefEditor->AddPage(new PrefsPageGeneral());
		prefEditor->AddPage(new PrefsPageAbout());
		prefEditor->AddPage(new PrefsPageFAQ());
	}
	prefEditor->Show(parent);
}

void nekoApp::DismissPreferencesEditor()
{
	if (prefEditor)
		prefEditor->Dismiss();
}

void nekoApp::SetSettings(const AppSettings& newSettings)
{
	settings = newSettings;
}