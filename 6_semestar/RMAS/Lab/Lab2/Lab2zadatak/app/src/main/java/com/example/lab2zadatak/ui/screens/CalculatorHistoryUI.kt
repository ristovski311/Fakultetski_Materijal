package com.example.lab2zadatak.ui.screens

import android.content.res.Configuration
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.material3.Card
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.unit.dp
import com.example.lab2zadatak.data.Calculation
import com.example.lab2zadatak.data.Operation
import androidx.compose.foundation.lazy.items
import androidx.compose.material3.ElevatedButton
import androidx.compose.ui.platform.LocalConfiguration
import java.text.SimpleDateFormat
import java.util.Date
import java.util.Locale

val currentTime: String
    get() {
        val formatter = SimpleDateFormat("yyyy-MM-dd HH:mm:ss", Locale.getDefault())
        return formatter.format(Date())
    }

@Composable
fun CalculatorHisoryUI(ch: List<Calculation>, onNavigateToCalculatorUI: () -> Unit) {
    val configuration = LocalConfiguration.current
    Column(modifier = Modifier.fillMaxSize().padding(5.dp), horizontalAlignment = Alignment.CenterHorizontally) {
        Row(modifier = Modifier.weight(10f)) {
            LazyColumn(modifier = Modifier.fillMaxWidth(), horizontalAlignment = Alignment.CenterHorizontally) {
                items(ch) { item ->

                    val operationSymbol = when(item.operation)
                    {
                        Operation.Add -> "+"
                        Operation.Sub -> "-"
                        Operation.Div -> "/"
                        Operation.Mul -> "*"
                    }

                    Card(modifier = Modifier.fillMaxWidth().padding(12.dp)) {
                        Box(modifier = Modifier.fillMaxWidth().padding(12.dp), contentAlignment = Alignment.Center)
                        {
                            Text("${item.firstOperand} " + operationSymbol + " ${item.secondOperand} = ${item.result}")
                        }
                    }
                }
            }
        }

        val weightVal = when(configuration.orientation)
        {
            Configuration.ORIENTATION_PORTRAIT -> 1f
            Configuration.ORIENTATION_LANDSCAPE -> 2f
            else -> 0f
        }

        Row(modifier = Modifier.weight(weightVal).fillMaxWidth()) {
            Box(modifier = Modifier.fillMaxWidth(), contentAlignment = Alignment.Center) {
                ElevatedButton(onClick = {onNavigateToCalculatorUI()}, modifier = Modifier) {
                    Text("Go to calculator")
                }
            }
        }
    }
}
