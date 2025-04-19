package com.arcanenibble.demodice

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Button
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.getValue
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.tooling.preview.Preview
import com.arcanenibble.demodice.ui.theme.DemoDiceTheme

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            DemoDiceTheme {
                Scaffold(
                    modifier = Modifier.fillMaxSize()
                ) { innerPadding ->
                    DiceApp(modifier = Modifier.padding(innerPadding))
                }
            }
        }
    }
}

@Composable
fun DiceApp(modifier: Modifier = Modifier) {
    var diceRoll by remember { mutableStateOf(0) }

    Column(
        modifier = modifier.fillMaxSize(),
        horizontalAlignment = Alignment.CenterHorizontally,
        verticalArrangement = Arrangement.Center
    ) {
        Button(
            onClick = {
                diceRoll = (1..20).random()
            }
        ) {
            Text(
                if (diceRoll == 0) {
                    stringResource((R.string.roll))
                } else {
                    diceRoll.toString()
                }
            )
        }
    }
}
@Preview(showBackground = true)
@Composable
fun DiceAppPreview() {
    DemoDiceTheme {
        DiceApp()
    }
}
