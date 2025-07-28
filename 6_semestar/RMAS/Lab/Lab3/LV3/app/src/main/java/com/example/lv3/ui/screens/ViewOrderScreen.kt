package com.example.lv3.ui.screens

import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxHeight
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Button
import androidx.compose.material3.Card
import androidx.compose.material3.ElevatedButton
import androidx.compose.material3.ElevatedCard
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.saveable.rememberSaveable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.unit.TextUnit
import androidx.compose.ui.unit.dp
import androidx.lifecycle.viewmodel.compose.viewModel
import com.example.lv3.data.entities.Order
import com.example.lv3.ui.OrderViewModel
import com.example.lv3.ui.screens.addorder.EditViewModel

@Composable
fun ViewOrderScreen(orderViewModel: OrderViewModel,
                    navigateToList: () -> Unit) {
    Column(
        modifier = Modifier.fillMaxWidth(),
        horizontalAlignment = Alignment.CenterHorizontally)
    {
        OrderCard(order = orderViewModel.selectedOrder)
        Button(modifier = Modifier.padding(12.dp),
            onClick = {
                orderViewModel.deleteOrder(orderViewModel.selectedOrder.id)
                navigateToList()
            }) {
            Text(text = "Delete Order")
        }
    }
}

@Composable
fun OrderCard(order: Order) {
    ElevatedCard(modifier = Modifier
        .padding(12.dp)
        .fillMaxWidth()) {
        Column() {
            Text(
                modifier = Modifier.padding(6.dp),
                text = order.name!!,
                fontSize = MaterialTheme.typography.headlineLarge.fontSize
            )
            Text(modifier = Modifier.padding(6.dp), text = "ID: ${order.id}")
            Text(modifier = Modifier.padding(6.dp), text = "Price: ${order.price}")
            Text(modifier = Modifier.padding(6.dp), text = "Type: ${order.type}")
            Text(modifier = Modifier.padding(6.dp), text = "Toppings: ${order.toppings}")
        }
    }
}