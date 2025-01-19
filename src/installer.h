#pragma once

#include "../pch/pch.h"
#include"settings.h"
#include <wx/zipstrm.h>
#include <wx/progdlg.h>



class ProgressDlg: public wxProgressDialog
{
public:
    explicit ProgressDlg(wxWindow* parent);
};