package com.example.lv3

import android.app.Application
import com.example.lv3.data.database.OrderDatabase
import com.example.lv3.data.repositories.OrderRepository
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.SupervisorJob

class OrderApplication : Application() {
    val applicationScope = CoroutineScope(SupervisorJob())

    val database by lazy { OrderDatabase.getDatabase(this, applicationScope) }
    val repository by lazy { OrderRepository(database.orderDao()) }
}