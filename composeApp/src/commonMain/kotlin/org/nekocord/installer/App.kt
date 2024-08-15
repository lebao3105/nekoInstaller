package org.nekocord.installer

import androidx.compose.foundation.Image
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxHeight
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.rounded.Edit
import androidx.compose.material.icons.rounded.Settings
import androidx.compose.material3.Button
import androidx.compose.material3.DropdownMenu
import androidx.compose.material3.DropdownMenuItem
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.Icon
import androidx.compose.material3.IconButton
import androidx.compose.material3.LargeFloatingActionButton
import androidx.compose.material3.ModalBottomSheet
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.material3.TextField
import androidx.compose.material3.TopAppBar
import androidx.compose.material3.TopAppBarDefaults
import androidx.compose.material3.rememberModalBottomSheetState
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.scale
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.unit.dp
import org.jetbrains.compose.resources.painterResource
import org.jetbrains.compose.ui.tooling.preview.Preview
import org.nekocord.installer.resources.Res
import org.nekocord.installer.resources.nekocord_logo_512
import org.nekocord.installer.resources.nekocord_wordmark

@OptIn(ExperimentalMaterial3Api::class)
@Composable
@Preview
fun App() {
    val greeting = remember { Greeting() }
    var showSettings by remember { mutableStateOf(false) }
    var comboboxExpanded by remember { mutableStateOf(false) }
    val sheetState = rememberModalBottomSheetState()

    ApplicationTheme {
        Scaffold(
            topBar = {
                TopAppBar(
                    title = {
                        Image(
                            painterResource(Res.drawable.nekocord_wordmark),
                            null,
                            modifier = Modifier.scale(0.5f, 0.5f)
                        )
                    },
                    colors = TopAppBarDefaults.topAppBarColors(
                        containerColor = Color(0xFFACD28F)
                    ),
                    modifier = Modifier.fillMaxWidth()
                )
            },
            floatingActionButton = {
                LargeFloatingActionButton(
                    { showSettings = true }
                ) {
                    Icon(Icons.Rounded.Settings, null)
                }
            }
        ){
            Column(
                verticalArrangement = Arrangement.Center,
                horizontalAlignment = Alignment.CenterHorizontally,
                modifier = Modifier.fillMaxWidth()//.fillMaxHeight()
            ) {
                Image(
                    painterResource(Res.drawable.nekocord_logo_512),
                    null,
                    modifier = Modifier.scale(0.5f, 0.5f)
                )

                Text(greeting.greet(), textAlign = TextAlign.Center)

                Text(
                    "Discord is installed in ${greeting.getDiscordPath()}",
                    textAlign = TextAlign.Center
                )

                Spacer(modifier = Modifier.height(height = 8.dp))

                Button(onClick = {}) {
                    Text("Click me!")
                }

//                Button(onClick = { showSettings = true }) {
//                    Text("Me too!")
//                }
            }
        }

        if (showSettings) {
            ModalBottomSheet(
                onDismissRequest = { showSettings = false },
                sheetState = sheetState,
                modifier = Modifier.fillMaxHeight()
            ) {
                Column(
                    verticalArrangement = Arrangement.Center,
                    horizontalAlignment = Alignment.CenterHorizontally,
                    modifier = Modifier.fillMaxWidth()
                ) {
                    TextField(
                        value = greeting.getDiscordPath(),
                        onValueChange = { greeting.setDiscordPath(it) },
                        singleLine = true, label = { Text("Custom Discord path") }
                    )

                    Row {
                        Text(
                            "Discord branch: ${greeting.getDiscordBranchAsString()}",
                            modifier = Modifier.align(Alignment.CenterVertically)
                        )
                        IconButton(
                            onClick = { comboboxExpanded = true },
                            modifier = Modifier.align(Alignment.CenterVertically)
                        ) {
                            Icon(Icons.Rounded.Edit, null)
                        }
                        DropdownMenu(comboboxExpanded, { comboboxExpanded = false }) {
                            Platform.DiscordBranch.entries.forEach {
                                DropdownMenuItem(
                                    { Text(it.toString()) },
                                    { greeting.setDiscordBranch(it) }
                                )
                            }
                        }

                    }
                }
            }

        }
    }
}