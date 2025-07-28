package com.example.lv3.data.repositories

import androidx.annotation.WorkerThread
import com.example.lv3.data.daos.OrderDao
import com.example.lv3.data.entities.Order
import kotlinx.coroutines.flow.Flow

class OrderRepository(private val orderDao: OrderDao){
    val orders: Flow<List<Order>> = orderDao.getOrders()

    @WorkerThread
    suspend fun getOrder(orderId: Int) : Order? {
        return orderDao.getOrder(orderId)
    }

    @WorkerThread
    suspend fun insert(order: Order) {
        orderDao.insert(order)
    }

    // TODO: Implement delete

}