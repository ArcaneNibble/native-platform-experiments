package com.arcanenibble.demodice

import android.annotation.SuppressLint
import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.automirrored.filled.ArrowBack
import androidx.compose.material.icons.outlined.Settings
import androidx.compose.material3.Button
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.Icon
import androidx.compose.material3.IconButton
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.material3.TopAppBar
import androidx.compose.material3.TopAppBarDefaults
import androidx.compose.runtime.Composable
import androidx.compose.runtime.mutableIntStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import com.arcanenibble.demodice.ui.theme.DemoDiceTheme

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            DemoDiceTheme {
                DiceToplevel()
            }
        }
    }
}

@Composable
fun DiceToplevel() {
    var showSettings by remember { mutableStateOf(false) }

    if (!showSettings) {
        DiceMainApp(showSettings = {
            showSettings = true
        })
    } else {
        Settings(hideSettings = {
            showSettings = false
        })
    }
}

@Composable
@OptIn(ExperimentalMaterial3Api::class)
fun DiceMainApp(
    modifier: Modifier = Modifier,
    showSettings: () -> Unit
) {
    Scaffold(
        modifier = modifier.fillMaxSize(),
        topBar = {
            TopAppBar(
                colors = TopAppBarDefaults.topAppBarColors(
                    containerColor = MaterialTheme.colorScheme.primaryContainer,
                    titleContentColor = MaterialTheme.colorScheme.primary,
                ),
                title = {
                    Text(stringResource(R.string.title))
                },
                actions = {
                    IconButton(onClick = showSettings) {
                        Icon(
                            imageVector = Icons.Outlined.Settings,
                            contentDescription = stringResource(R.string.settings)
                        )
                    }
                },
            )
        }
    ) { innerPadding ->
        DiceButton(modifier = Modifier.padding(innerPadding))
    }
}
@Preview(showBackground = true)
@Composable
fun DiceMainAppPreview() {
    DemoDiceTheme {
        DiceMainApp(showSettings = {})
    }
}

@Composable
fun DiceButton(modifier: Modifier = Modifier) {
    var diceRoll by remember { mutableIntStateOf(0) }

    Column(
        modifier = modifier.fillMaxSize(),
        horizontalAlignment = Alignment.CenterHorizontally,
        verticalArrangement = Arrangement.Center
    ) {
        Button(
            modifier = Modifier.size(width = 200.dp, height = 200.dp),
            onClick = {
                diceRoll = (1..20).random()
            }
        ) {
            Text(
                text = if (diceRoll == 0) {
                    stringResource(R.string.roll)
                } else {
                    diceRoll.toString()
                },
                style = MaterialTheme.typography.titleLarge
            )
        }
    }
}
@Preview(showBackground = true)
@Composable
fun DiceButtonPreview() {
    DemoDiceTheme {
        DiceButton()
    }
}

@Composable
@OptIn(ExperimentalMaterial3Api::class)
fun Settings(
    modifier: Modifier = Modifier,
    hideSettings: () -> Unit
) {
    Scaffold(
        modifier = modifier.fillMaxSize(),
        topBar = {
            TopAppBar(
                colors = TopAppBarDefaults.topAppBarColors(
                    containerColor = MaterialTheme.colorScheme.primaryContainer,
                    titleContentColor = MaterialTheme.colorScheme.primary,
                ),
                title = {
                    Text(stringResource(R.string.settings))
                },
                navigationIcon = {
                    IconButton(onClick = hideSettings) {
                        Icon(
                            imageVector = Icons.AutoMirrored.Filled.ArrowBack,
                            contentDescription = stringResource(R.string.back)
                        )
                    }
                },
            )
        }
    ) { innerPadding ->
        Text("ASDF!", modifier = Modifier.padding(innerPadding))
    }
}
@Preview(showBackground = true)
@Composable
fun SettingsPreview() {
    DemoDiceTheme {
        Settings(hideSettings = {})
    }
}
