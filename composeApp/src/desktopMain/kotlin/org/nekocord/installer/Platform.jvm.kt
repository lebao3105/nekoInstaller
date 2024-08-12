package org.nekocord.installer

class DesktopPlatform: Platform() {
    override val name: String = "${System.getProperty("os.name")} ${System.getProperty("os.version")}"

    override val asarRelativePath: String = ""

    override var generalDiscordPath: String = when (System.getProperty("os.name")) {
        /// FIXME: Verify that macOS ONLY use this
        "Mac OS X" -> "/Applications/Discord.app/"
        /// FIXME: Is this value right?
        "Windows" -> "${System.getProperty("user.home")}/AppData/Local/Discord"
        else -> "" // incomplete
    }
}

actual fun getPlatform(): Platform { return DesktopPlatform() }