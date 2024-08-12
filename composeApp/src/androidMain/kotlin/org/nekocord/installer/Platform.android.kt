package org.nekocord.installer

import android.os.Build

class AndroidPlatform: Platform() {
    override val name: String = "Android ${Build.VERSION.RELEASE}"

    /// Incomplete
    override var generalDiscordPath: String = "/storage/emulated/0/Android/data/Discord"

    override val asarRelativePath: String = ""
}

actual fun getPlatform(): Platform { return AndroidPlatform() }