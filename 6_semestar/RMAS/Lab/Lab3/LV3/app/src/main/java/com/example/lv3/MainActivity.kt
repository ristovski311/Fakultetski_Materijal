package com.example.lv3

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.viewModels
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Add
import androidx.compose.material3.BottomAppBar
import androidx.compose.material3.CenterAlignedTopAppBar
import androidx.compose.material3.FloatingActionButton
import androidx.compose.material3.Icon
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.material3.TopAppBar
import androidx.compose.material3.TopAppBarDefaults.topAppBarColors
import androidx.compose.runtime.Composable
import androidx.compose.runtime.collectAsState
import androidx.compose.ui.Modifier
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewmodel.compose.viewModel
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import androidx.navigation.compose.rememberNavController
import com.example.lv3.ui.OrderViewModel
import com.example.lv3.ui.OrderViewModelFactory
import com.example.lv3.ui.screens.OrderListScreen
import com.example.lv3.ui.screens.ViewOrderScreen
import com.example.lv3.ui.screens.addorder.AddOrderScreen
import com.example.lv3.ui.screens.addorder.EditViewModel
import com.example.lv3.ui.theme.LV3Theme

class MainActivity : ComponentActivity() {
    private val orderViewModel: OrderViewModel by viewModels {
        OrderViewModelFactory((application as OrderApplication).repository)
    }
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            LV3Theme {
                // A surface container using the 'background' color from the theme
                Surface(
                    modifier = Modifier.fillMaxSize(),
                    color = MaterialTheme.colorScheme.background
                ) {
                    LV3App(orderViewModel)
                }
            }
        }
    }
}

@Composable
fun LV3App(viewModel: OrderViewModel) {
    val navController = rememberNavController()
    val editViewModel: EditViewModel = viewModel()
    Scaffold(
        floatingActionButton = {
            FloatingActionButton(onClick = { navController.navigate(Screens.AddOrder.name) }) {
                Icon(Icons.Default.Add, contentDescription = "Add")
            }
        }
    ) { innerPadding ->
        Surface(modifier = Modifier.padding(innerPadding)) {
            NavHost(navController = navController, startDestination = Screens.OrderList.name) {
                composable(Screens.OrderList.name) {
                    val orderList = viewModel.orders.collectAsState(initial = listOf())
                    OrderListScreen(list = orderList.value, navigateToViewOrder = {
                        navController.navigate(
                            Screens.ViewOrder.name
                        )},
                        setSelectedOrder = { viewModel.setCurrentOrder(it) })
                }
                composable(Screens.AddOrder.name) {
                    AddOrderScreen(
                        editViewModel = editViewModel,
                        orderViewModel = viewModel,
                        navigateToList = { navController.popBackStack() }
                    )
                }
                composable(Screens.ViewOrder.name) {
                    ViewOrderScreen(
                        orderViewModel = viewModel,
                        navigateToList = { navController.popBackStack() }
                    )
                }
            }
        }
    }
}

enum class Screens {
    OrderList,
    AddOrder,
    ViewOrder
}