package com.arcanenibble.demodice

import android.annotation.SuppressLint
import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.foundation.text.KeyboardOptions
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.outlined.Settings
import androidx.compose.material3.BasicAlertDialog
import androidx.compose.material3.Button
import androidx.compose.material3.Card
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.Icon
import androidx.compose.material3.IconButton
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.OutlinedTextField
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.material3.TextButton
import androidx.compose.material3.TopAppBar
import androidx.compose.material3.TopAppBarDefaults
import androidx.compose.runtime.Composable
import androidx.compose.runtime.derivedStateOf
import androidx.compose.runtime.mutableIntStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.text.input.KeyboardType
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
    var maxRoll by remember { mutableIntStateOf(20) }

    if (!showSettings) {
        DiceMainApp(
            showSettings = {
                showSettings = true
            },
            maxRoll = {maxRoll},
        )
    } else {
        SettingsDialog(
            hideSettings = {
                showSettings = false
            },
            setNewMaxRoll = {
                maxRoll = it
            }
        )
    }
}

@Composable
@OptIn(ExperimentalMaterial3Api::class)
fun DiceMainApp(
    modifier: Modifier = Modifier,
    showSettings: () -> Unit,
    maxRoll: () -> Int = {20},
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
fun DiceButton(
    modifier: Modifier = Modifier,
    maxRoll: () -> Int = {20}
) {
    var diceRoll by remember { mutableIntStateOf(0) }

    Column(
        modifier = modifier.fillMaxSize(),
        horizontalAlignment = Alignment.CenterHorizontally,
        verticalArrangement = Arrangement.Center
    ) {
        Button(
            modifier = Modifier.size(width = 200.dp, height = 200.dp),
            onClick = {
                diceRoll = (1..maxRoll()).random()
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
fun SettingsDialog(
    modifier: Modifier = Modifier,
    hideSettings: () -> Unit,
    setNewMaxRoll: (Int) -> Unit,
) {
    var maxRollStr by remember { mutableStateOf("") }
    val maxRollIsValid by derivedStateOf {
        val num = maxRollStr.toIntOrNull()
        if (num == null) {
            false
        } else {
            num > 0
        }
    }

    BasicAlertDialog(
        onDismissRequest = hideSettings,
        content = {
            Card(
                modifier = Modifier
                    .fillMaxWidth()
                    .height(200.dp)
                    .padding(16.dp),
                shape = RoundedCornerShape(16.dp)
            ) {
                Column(
                    modifier = Modifier.fillMaxSize(),
                    verticalArrangement = Arrangement.Center,
                    horizontalAlignment = Alignment.CenterHorizontally,
                ) {
                    OutlinedTextField(
                        value = maxRollStr,
                        onValueChange = { maxRollStr = it },
                        keyboardOptions = KeyboardOptions(keyboardType = KeyboardType.Number),
                        label = { Text(stringResource(R.string.set_max)) },
                        modifier = Modifier.padding(16.dp),
                        isError = !maxRollIsValid,
                        supportingText = {
                            if (!maxRollIsValid) {
                                Text(stringResource(R.string.must_be_num))
                            }
                        }
                    )
                    Row(
                        modifier = Modifier.fillMaxWidth(),
                        horizontalArrangement = Arrangement.Center
                    ) {
                        TextButton(
                            onClick = hideSettings,
                            modifier = Modifier.padding(8.dp),
                        ) {
                            Text(stringResource(R.string.cancel))
                        }
                        TextButton(
                            onClick = {
                                if (maxRollIsValid) {
                                    setNewMaxRoll(maxRollStr.toInt())
                                    hideSettings()
                                }
                            },
                            enabled = maxRollIsValid,
                            modifier = Modifier.padding(8.dp),
                        ) {
                            Text(stringResource(R.string.ok))
                        }
                    }
                }
            }
        }
    )
}
@Preview(showBackground = true)
@Composable
fun SettingsPreview() {
    DemoDiceTheme {
        SettingsDialog(
            hideSettings = {},
            setNewMaxRoll = {},
        )
    }
}
