#include "main.h"
#include "mainwindow.h"
#include <wx/filesys.h>
#include <wx/fs_arc.h>
#include <wx/artprov.h>
#include <wxMaterialDesignArtProvider.hpp>

wxIMPLEMENT_APP(nekoApp);

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
	// settings = newSettings;
	settings.discordBranch = newSettings.discordBranch;
	// settings.Write<DISCORD_BRANCH>("discordBranch", &settings.discordBranch);
	// settings.Write<NEKO_BRANCH>("nekoBranch", &settings.nekoBranch);
	// settings.Write("discordPath", &settings.discordPath);
	// settings.Save(wxFileOutputStream("settings.ini"));
}