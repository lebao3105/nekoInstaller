package org.nekocord.installer

class Greeting {
    private val platform = getPlatform()

    fun greet(): String {
        return "Hello, ${platform.name}!"
    }

    fun setDiscordBranch(branch: Platform.DiscordBranch) {
        platform.branch = branch
    }

    fun setDiscordPath(path: String) {
        platform.generalDiscordPath = path
    }

    fun getDiscordPath(): String {
        return platform.generalDiscordPath
    }

    fun getDiscordBranchAsString(): String {
        return platform.branch.toString()
    }
}