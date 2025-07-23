package com.example.lab2zadatak.ui.screens

import android.content.res.Configuration
import android.view.Surface
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxHeight
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Button
import androidx.compose.material3.ButtonDefaults
import androidx.compose.material3.Card
import androidx.compose.material3.CardColors
import androidx.compose.material3.ElevatedButton
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.OutlinedTextField
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.material3.TextButton
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.platform.LocalConfiguration
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.example.lab2zadatak.data.Calculation
import com.example.lab2zadatak.data.Operation

@Composable
fun CalculatorUI(onNavigateToHistory: () -> Unit,
                 setCurCalValue: (first: Int?, second: Int?, operation: Operation, result: Int) -> Unit,
                 doCalc: () -> Unit,
                 setDisplayValue: (value: String) -> Unit,
                 displayVal: String) {
    val configuration = LocalConfiguration.current
    if(configuration.orientation == Configuration.ORIENTATION_PORTRAIT) {
        CalculatorPortaitUI(onNavigateToHistory, setCurCalValue, doCalc, setDisplayValue, displayVal)
    }
    else {
        CalculatorLandscapeUI(onNavigateToHistory, setCurCalValue, doCalc, setDisplayValue, displayVal)
    }
}

@Composable
fun CalculatorPortaitUI(onNavigateToHistory: () -> Unit,
                        setCurCalValue: (first: Int?, second: Int?, operation: Operation, result: Int) -> Unit,
                        doCalc: () -> Unit,
                        setDisplayValue: (value: String) -> Unit ,
                        displayVal: String )
{
    Surface {
        Column(modifier = Modifier.fillMaxSize(),
            verticalArrangement = Arrangement.Center,
            horizontalAlignment = Alignment.CenterHorizontally) {
            Spacer(modifier = Modifier.weight(1f))
            CalculatorDisplay(modifier = Modifier.fillMaxWidth().weight(1f), displayVal)
            CalculatorKeyboard(modifier = Modifier.weight(5f), setDisplayValue, doCalc)
            Spacer(modifier = Modifier.weight(1f))
            ElevatedButton(onClick = { onNavigateToHistory()}, modifier = Modifier
                .padding(24.dp)
                .weight(1f)) {
                Text(text = "Go to history")
            }
        }
    }
}

@Composable
fun CalculatorLandscapeUI(onNavigateToHistory: () -> Unit,
                          setCurCalValue: (first: Int?, second: Int?, operation: Operation, result: Int) -> Unit,
                          doCalc: () -> Unit,
                          setDisplayValue: (value: String) -> Unit,
                          displayVal: String )
{
    Surface {
        Row(modifier = Modifier.fillMaxSize()) {
            Column (modifier = Modifier.weight(1f),
                horizontalAlignment = Alignment.CenterHorizontally) {
                CalculatorDisplay(modifier = Modifier.fillMaxWidth().weight(2f), displayVal)
                Spacer(modifier = Modifier.weight(1f))
                ElevatedButton(onClick = { onNavigateToHistory() },
                    modifier = Modifier
                    .padding(24.dp)
                    .weight(1f)) {
                    Text(text = "Go to history")
                }
            }
            Surface (modifier = Modifier.weight(1f)) {
                CalculatorKeyboard(modifier = Modifier.weight(5f), setDisplayValue, doCalc)
            }
        }
    }
}


@Composable
fun CalculatorDisplay(modifier: Modifier, displayVal: String) {
    Card(shape = MaterialTheme.shapes.large, modifier = Modifier
        .fillMaxWidth()
        .padding(24.dp)) {
        Text(text = displayVal, // viewModel.displayValue je namenjen za ovo
            modifier = Modifier.padding(24.dp).align(Alignment.CenterHorizontally).fillMaxWidth(),
            textAlign = TextAlign.End,
            style = MaterialTheme.typography.displaySmall)
    }
}

val symbolString = "7 8 9 + 4 5 6 - 1 2 3 * C 0 = /";
val buttonSymbols = symbolString.split(" ").toTypedArray();

@Composable
fun CalculatorKeyboard(modifier: Modifier, setDisplayValue: (value:String) -> Unit, doCalc: () -> Unit) {
    Surface(modifier = modifier
            .padding(24.dp)) {

        Column(modifier = Modifier
            .fillMaxSize()) {

            for(i in 0 until 4)
            {
                Row(modifier = Modifier
                    .weight(0.5f)) {

                    for(j in 0 until 4)
                    {
                        val index = i*4 + j;
                        ElevatedButton(onClick = {
                            when(buttonSymbols[index]) {
                                "+" -> setDisplayValue("+")
                                "-" -> setDisplayValue("-")
                                "*" -> setDisplayValue("*")
                                "/" -> setDisplayValue("/")
                                "C" -> setDisplayValue("C")
                                "=" -> doCalc()
                                else -> setDisplayValue(buttonSymbols[index])
                            } },
                            colors = ButtonDefaults.elevatedButtonColors(
                                containerColor = when(buttonSymbols[index]){
                                    "=" -> Color.Transparent
                                    "C" -> Color.Transparent
                                    else -> Color.DarkGray
                                },
                                contentColor = when(buttonSymbols[index]){
                                    "=" -> Color.Cyan
                                    "C" -> Color.Red
                                    else -> Color.White
                                }
                            ),
                            modifier = Modifier.weight(1f).fillMaxHeight().padding(4.dp)) {
                            Text(text = "${buttonSymbols[index]}", fontSize = 22.sp)
                        }
                    }
                }
            }
        }
    }
}