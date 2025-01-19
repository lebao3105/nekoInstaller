#pragma once

#include "../pch/pch.h"
#include "settings.h"
#include <memory>
#include <wx/wfstream.h>

class nekoApp: public wxApp
{
public:
	void ShowPreferencesEditor(wxWindow* parent);
	void DismissPreferencesEditor();

	const AppSettings& GetSettings() const { return settings; }
	void SetSettings(const AppSettings& newSettings);

protected:
	bool OnInit();

private:
	AppSettings settings;
	std::unique_ptr<wxPreferencesEditor> prefEditor;
};

wxDECLARE_APP(nekoApp);