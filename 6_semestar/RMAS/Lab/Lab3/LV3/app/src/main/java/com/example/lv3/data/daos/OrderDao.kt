package com.example.lv3.data.daos

import androidx.room.Dao
import androidx.room.Delete
import androidx.room.Insert
import androidx.room.OnConflictStrategy
import androidx.room.Query
import androidx.room.Update
import com.example.lv3.data.entities.Order
import kotlinx.coroutines.flow.Flow

@Dao
interface OrderDao {
    @Query("SELECT * FROM orders ORDER BY id ASC")
    fun getOrders(): Flow<List<Order>>

    @Query("SELECT * FROM orders WHERE id=:id")
    suspend fun getOrder(id: Int): Order?

    @Insert(onConflict = OnConflictStrategy.IGNORE)
    suspend fun insert(order: Order)

    // TODO: Implement delete order


    @Query("DELETE FROM orders")
    suspend fun deleteAll()
}