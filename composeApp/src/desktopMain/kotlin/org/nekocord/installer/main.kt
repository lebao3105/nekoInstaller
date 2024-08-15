package org.nekocord.installer

import androidx.compose.ui.unit.DpSize
import androidx.compose.ui.unit.dp
import org.jetbrains.compose.resources.painterResource
import androidx.compose.ui.window.Window
import androidx.compose.ui.window.WindowState
import androidx.compose.ui.window.application
import org.nekocord.installer.resources.Res
import org.nekocord.installer.resources.ic_launcher

fun main() = application {
    Window(
        onCloseRequest = ::exitApplication,
        title = "NekoCord Installer",
        icon = painterResource(Res.drawable.ic_launcher),
        state = WindowState(size = DpSize(width = 1000.dp, height = 650.dp))
    ) {
        App()
    }
}