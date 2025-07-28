package com.example.lv3.data.entities

import androidx.room.ColumnInfo
import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity(tableName = "orders")
data class Order(
    @PrimaryKey(autoGenerate = true) val id: Int,
    val name: String? = null,
    val price: Int? = null,
    val type: String? = null,
    val toppings: String? = null)

enum class OrderType {
    Cupcake,
    Coffee,
    Smoothie,
    Pizza
}
