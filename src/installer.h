#pragma once

#include "../pch/pch.h"
#include "settings.h"

#include <wx/zipstrm.h>
#include <wx/progdlg.h>
#include <wx/stdpaths.h>
#include <wx/webrequest.h>
#include <wx/wfstream.h>

wxString GetDiscordPath(DISCORD_BRANCH branch GDP_SecondArg);
wxString GetDiscordPathWithVer(DISCORD_BRANCH branch GDP_SecondArg);

class ProgressDlg: public wxProgressDialog
{
public:
    explicit ProgressDlg(wxWindow* parent, bool uninstall = false, wxString zipPath = wxEmptyString GDP_SecondArg DefaultFalse);

private:
    void InstallFromStream(wxInputStream& stream);
    wxString asarPath;
};