package com.example.lv3.ui

import android.util.Log
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableIntStateOf
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.setValue
import androidx.lifecycle.ViewModel
import androidx.lifecycle.ViewModelProvider
import androidx.lifecycle.viewModelScope
import com.example.lv3.data.entities.Order
import com.example.lv3.data.entities.OrderType
import com.example.lv3.data.repositories.OrderRepository
import kotlinx.coroutines.async
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.launch

class OrderViewModel(private val repository: OrderRepository): ViewModel() {
    var selectedOrder: Order by mutableStateOf(Order(0))
        private set
    val orders: Flow<List<Order>> = repository.orders

    fun setCurrentOrder(order: Order) {
        selectedOrder = order
    }

    fun addOrder(name: String, price: Int, type: OrderType, toppings: String) {
        val o = Order(0, name, price, type.name, toppings)
        // TODO: Call insert() from repository

    }

    fun deleteOrder(orderId: Int) {
        viewModelScope.launch {
            var o: Order? = null
            val coroutine = viewModelScope.async {
                return@async repository.getOrder(orderId)
            }
            o = coroutine.await()
            if (o != null) {
                viewModelScope.launch {
                    // TODO: Call delete() from repository

                }
            }
        }
    }
}

class OrderViewModelFactory(private val repository: OrderRepository) : ViewModelProvider.Factory {
    override fun <T : ViewModel> create(modelClass: Class<T>): T {
        if (modelClass.isAssignableFrom(OrderViewModel::class.java)) {
            return OrderViewModel(repository) as T
        }
        throw IllegalArgumentException("Unknown ViewModel class")
    }
}