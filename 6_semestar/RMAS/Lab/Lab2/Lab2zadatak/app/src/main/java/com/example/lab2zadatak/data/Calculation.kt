package com.example.lab2zadatak.data

data class Calculation(
    val firstOperand: Int = 0,
    val secondOperand: Int = 0,
    val operation: Operation = Operation.Add,
    val result: Int = 0
)

enum class Operation {
    Add,
    Sub,
    Mul,
    Div
}
