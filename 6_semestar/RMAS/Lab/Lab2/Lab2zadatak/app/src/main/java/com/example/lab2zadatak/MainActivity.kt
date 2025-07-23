package com.example.lab2zadatak

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.viewModels
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import androidx.navigation.compose.rememberNavController
import com.example.lab2zadatak.ui.CalculatorViewModel
import com.example.lab2zadatak.ui.screens.CalculatorUI
import com.example.lab2zadatak.ui.screens.CalculatorHisoryUI
import com.example.lab2zadatak.ui.theme.Lab2zadatakTheme

class MainActivity : ComponentActivity() {
    private val viewModel: CalculatorViewModel by viewModels()
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            Lab2zadatakTheme {
                // A surface container using the 'background' color from the theme
                CalculatorApp(viewModel)
            }
        }
    }
}

@Composable
fun CalculatorApp(viewModel: CalculatorViewModel) {
    val navController = rememberNavController()
    Surface {
        NavHost(navController = navController, startDestination = Screens.CalculatorUI.name) {
            composable(Screens.CalculatorUI.name) {
                CalculatorUI(onNavigateToHistory = {navController.navigate(Screens.History.name)},
                            setCurCalValue = {f,s,o,r -> viewModel.setCurrentCalculationComponents(f,s,o,r)},
                            doCalc = { viewModel.doCalculation() },
                            setDisplayValue = { v -> viewModel.setDisplayValue(v)},
                            displayVal = viewModel.displayValue.value)
            }
            composable(Screens.History.name) {
                CalculatorHisoryUI(ch = viewModel.calculationHistory.value, onNavigateToCalculatorUI = {navController.navigate(Screens.CalculatorUI.name)})
            }
        }
    }
}

enum class Screens {
    CalculatorUI,
    History
}