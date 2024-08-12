package org.nekocord.installer

import org.jetbrains.compose.resources.painterResource
import androidx.compose.ui.window.Window
import androidx.compose.ui.window.application
import org.nekocord.installer.resources.Res
import org.nekocord.installer.resources.ic_launcher

fun main() = application {
    Window(
        onCloseRequest = ::exitApplication,
        title = "NekoCord Installer",
        icon = painterResource(Res.drawable.ic_launcher)
    ) {
        App()
    }
}