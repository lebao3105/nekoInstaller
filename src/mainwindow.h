#pragma once

#include "../pch/pch.h"
#include <wxUI/wxUI.h>

class MainWindow: public wxFrame {
private:
    wxUI::Text::Proxy discordBr;
    wxUI::Text::Proxy nekoBr;
    wxUI::Text::Proxy discordPt;

public:
    explicit MainWindow();

    void UpdateSettings();
};