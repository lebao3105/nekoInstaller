#pragma once

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif

#ifndef __linux__
#define GDP_SecondArg
#define DoLowerStr
#define DefaultFalse
#else
#define GDP_SecondArg , bool useFlatpak
#define DoLowerStr .Lower()
#define DefaultFalse = false
#endif
