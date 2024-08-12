package org.nekocord.installer

abstract class Platform {
    /// The current platform information.
    /// Follow *name* *version* format.
    abstract val name: String

    /// Where Discord normally gets installed.
    /// You should make this method, as good as possible,
    /// be compatible with kinds of installations
    /// (e.g Flatpak/Snap).
    /// Only use this for normal, stable variant. We'll handle the rest.
    abstract var generalDiscordPath: String

    /// The path to app.asar. Relative to the Discord installation.
    abstract val asarRelativePath: String

    /// Discord branches
    enum class DiscordBranch {
        Stable, PTB, Canary
    }

    var branch: DiscordBranch = DiscordBranch.Stable
}

expect fun getPlatform(): Platform