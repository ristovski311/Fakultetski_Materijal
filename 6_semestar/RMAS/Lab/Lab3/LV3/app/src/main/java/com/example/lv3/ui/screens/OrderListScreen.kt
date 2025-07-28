package com.example.lv3.ui.screens

import android.util.Log
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxHeight
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.material3.Card
import androidx.compose.material3.ElevatedButton
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.unit.dp
import com.example.lv3.data.entities.Order

@Composable
fun OrderListScreen(list: List<Order>, navigateToViewOrder: () -> Unit, setSelectedOrder: (Order) -> Unit) {
    Log.i("LIST", list.joinToString())
    LazyColumn {
        items(list) {
            OrderPreview(order = it, navigateToViewOrder, setSelectedOrder)
        }
    }
}

@Composable
fun OrderPreview(
    order: Order,
    navigateToViewOrder: () -> Unit,
    setSelectedOrder: (Order) -> Unit =  {order: Order ->}
) {
    Card(modifier = Modifier
        .padding(12.dp)
        .fillMaxWidth()) {
        Row(verticalAlignment = Alignment.CenterVertically) {
            Text(
                modifier = Modifier.padding(6.dp),
                text = "${order.name}, ${order.type}, ${order.price}"
            )
            Spacer(Modifier.weight(1f).fillMaxHeight())
            ElevatedButton(modifier = Modifier.padding(6.dp) ,onClick = {
                setSelectedOrder(order)
                navigateToViewOrder()
            }) {
                Text(text = "View")
            }
        }
    }
}