package com.example.lv3.ui.screens.addorder

import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableIntStateOf
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.setValue
import androidx.lifecycle.ViewModel
import com.example.lv3.data.entities.OrderType

class EditViewModel : ViewModel() {

    var name: String by mutableStateOf("")
    var price: Int by mutableIntStateOf(0)
    var type: OrderType by mutableStateOf(OrderType.Cupcake)
    var toppings: List<String> by mutableStateOf(listOf())

    fun addTopping(t: String) {
        toppings += t
    }
    fun removeTopping(t: String) {
        toppings = toppings.filter { it != t }
    }
    fun reset() {
        name = ""
        price = 0
        type = OrderType.Cupcake
        toppings = listOf()
    }
}