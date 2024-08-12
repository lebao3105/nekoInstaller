package org.nekocord.installer

import platform.UIKit.UIDevice

class iOSPlatform: Platform() {
    override val name: String = UIDevice.currentDevice.systemName() + " " + UIDevice.currentDevice.systemVersion

    override var generalDiscordPath: String = "/Applications/Discord.app"

    override val asarRelativePath: String = "/Contents/Resources"
}

actual fun getPlatform(): Platform { return iOSPlatform() }