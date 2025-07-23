package com.example.lab2zadatak.ui

import androidx.compose.runtime.MutableState
import androidx.compose.runtime.mutableStateOf
import androidx.lifecycle.ViewModel
import com.example.lab2zadatak.data.Calculation
import com.example.lab2zadatak.data.Operation

class CalculatorViewModel : ViewModel()  {
    var calculationHistory = mutableStateOf(listOf<Calculation>())
        private set
    var currentCalculation = mutableStateOf(Calculation())
        private set
    var displayValue = mutableStateOf("0")
        private set

    var calculated = false

    private fun writeToHistory(calculation: Calculation) {
        calculationHistory.value += calculation
    }

    fun setCurrentCalculationComponents(first: Int?, second: Int?, operation: Operation?, result: Int = 0) {
        currentCalculation.value = Calculation(
            first ?: currentCalculation.value.firstOperand,
            second ?: currentCalculation.value.secondOperand,
            operation ?: currentCalculation.value.operation,
            result ?: 0)
    }

    fun doCalculation() {

        if(!(displayValue.value in listOf("+", "-", "*", "/")))
            setCurrentCalculationComponents(first = null, second = displayValue.value.toInt(), operation = null)

        var res = 0;
        val first = currentCalculation.value.firstOperand
        val second = currentCalculation.value.secondOperand
        when (currentCalculation.value.operation) {
            Operation.Add -> {
                res = first + second
            }
            Operation.Sub -> {
                res = first - second
            }
            Operation.Mul -> {
                res = first * second
            }
            Operation.Div -> {
                res = if (second == 0) {
                    0
                } else {
                    first / second
                }
            }
        }
        writeToHistory(Calculation(
            first,
            second,
            currentCalculation.value.operation,
            res))
        currentCalculation.value = Calculation()
        displayValue.value = res.toString()
        calculated = true;
    }

    fun setDisplayValue(value: String) {
        when(value)
        {
            "C" -> {
                currentCalculation.value = Calculation()
                displayValue.value = currentCalculation.value.firstOperand.toString()
            }
            "*" -> {
                if(displayValue.value in listOf("+", "-", "*", "/")) {}
                else
                    setCurrentCalculationComponents(first = displayValue.value.toInt(), second = null, operation = null)
                if(currentCalculation.value.firstOperand != 0)
                    displayValue.value = "*"

            }
            "+" -> {
                if(displayValue.value in listOf("+", "-", "*", "/")) {}
                else
                    setCurrentCalculationComponents(first = displayValue.value.toInt(), second = null, operation = null)
                if(currentCalculation.value.firstOperand != 0)
                    displayValue.value = "+"

            }
            "-" -> {
                if(displayValue.value in listOf("+", "-", "*", "/")) {}
                else
                    setCurrentCalculationComponents(first = displayValue.value.toInt(), second = null, operation = null)
                if(currentCalculation.value.firstOperand != 0)
                    displayValue.value = "-"

            }
            "/" -> {
                if(displayValue.value in listOf("+", "-", "*", "/")) {}
                else
                    setCurrentCalculationComponents(first = displayValue.value.toInt(), second = null, operation = null)
                if(currentCalculation.value.firstOperand != 0)
                    displayValue.value = "/"

            }
            else -> {
                if(displayValue.value.length > 8)
                    return
                else if(displayValue.value in listOf("+", "-", "*", "/") || calculated) {
                    setCurrentCalculationComponents(first = null,
                        second = null,
                        operation = when(displayValue.value)
                        {
                            "+" -> Operation.Add
                            "-" -> Operation.Sub
                            "*" -> Operation.Mul
                            "/" -> Operation.Div
                            else -> Operation.Add
                        }
                    )
                    calculated = false;
                    displayValue.value = (0 * 10 + value.toInt()).toString()
                }
                else
                    displayValue.value = (displayValue.value.toInt() * 10 + value.toInt()).toString()
            }
        }
    }

}