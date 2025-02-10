#pragma once

#include "../pch/pch.h"
#include "settings.h"
#include <wx/zipstrm.h>
#include <wx/progdlg.h>
#include <wx/stdpaths.h>

wxString GetDiscordPath(DISCORD_BRANCH branch);
wxString GetDiscordPathWithVer(DISCORD_BRANCH branch);

class ProgressDlg: public wxProgressDialog
{
public:
    explicit ProgressDlg(wxWindow* parent, bool uninstall = false);
};