package com.example.lv3.ui.screens.addorder

import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.lazy.LazyRow
import androidx.compose.foundation.lazy.*
import androidx.compose.foundation.text.KeyboardActions
import androidx.compose.foundation.text.KeyboardOptions
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Close
import androidx.compose.material3.Button
import androidx.compose.material3.DropdownMenuItem
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.ExposedDropdownMenuBox
import androidx.compose.material3.ExposedDropdownMenuDefaults
import androidx.compose.material3.Icon
import androidx.compose.material3.InputChip
import androidx.compose.material3.InputChipDefaults
import androidx.compose.material3.OutlinedTextField
import androidx.compose.material3.Text
import androidx.compose.material3.TextField
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.saveable.rememberSaveable
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.ExperimentalComposeUiApi
import androidx.compose.ui.Modifier
import androidx.compose.ui.focus.FocusRequester
import androidx.compose.ui.focus.focusRequester
import androidx.compose.ui.input.key.Key
import androidx.compose.ui.input.key.KeyEvent
import androidx.compose.ui.input.key.KeyEventType
import androidx.compose.ui.input.key.key
import androidx.compose.ui.input.key.onKeyEvent
import androidx.compose.ui.text.input.ImeAction
import androidx.compose.ui.unit.dp
import androidx.core.text.isDigitsOnly
import androidx.lifecycle.viewmodel.compose.viewModel
import com.example.lv3.data.entities.OrderType
import com.example.lv3.ui.OrderViewModel

@Composable
fun AddOrderScreen(editViewModel: EditViewModel = viewModel(),
                   orderViewModel: OrderViewModel,
                   navigateToList: () -> Unit) {
    Column(
        modifier = Modifier.fillMaxWidth().padding(6.dp),
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        val modifier = Modifier.padding(6.dp)
        OutlinedTextField(
            modifier = modifier,
            value = editViewModel.name,
            onValueChange = { editViewModel.name = it },
            label = { Text("Name") })
        OutlinedTextField(
            modifier = modifier,
            value = editViewModel.price.toString(),
            onValueChange = {
                if (it.isDigitsOnly()) {
                    val number = it.toIntOrNull()
                    if (number != null)
                        editViewModel.price = it.toInt()
                }
            },
            label = { Text("Price") })
        OrderTypeDropdown(
            modifier = modifier,
            editViewModel)
        ToppingsChips(
            modifier = modifier,
            toppingList = editViewModel.toppings,
            addToList = { editViewModel.addTopping(it) } ,
            removeFromList = { editViewModel.removeTopping(it) })
        Button(modifier = modifier, onClick = {
            orderViewModel.addOrder(
                editViewModel.name,
                editViewModel.price,
                editViewModel.type,
                editViewModel.toppings.joinToString(", ")
            )
            editViewModel.reset()
            navigateToList()
        }) {
            Text(text = "Add Order")
        }
    }
}

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun OrderTypeDropdown(modifier: Modifier, editViewModel:EditViewModel) {
    var expanded by rememberSaveable { mutableStateOf(false) }
    ExposedDropdownMenuBox(
        expanded = expanded,
        onExpandedChange = {
            expanded = !expanded
        }
    ) {
        OutlinedTextField(
            value = editViewModel.type.name,
            onValueChange = { },
            readOnly = true,
            trailingIcon = { ExposedDropdownMenuDefaults.TrailingIcon(expanded = expanded) },
            modifier = Modifier.menuAnchor()
        )
        ExposedDropdownMenu(
            expanded = expanded,
            onDismissRequest = { expanded = false }
        ) {
            OrderType.entries.forEach { item ->
                DropdownMenuItem(
                    text = { Text(text = item.name) },
                    onClick = {
                        editViewModel.type = item
                        expanded = false
                    }
                )
            }
        }
    }
}

@Composable
fun ToppingsChips(
    modifier: Modifier,
    toppingList: List<String>,
    addToList: (String) -> Unit = { t: String ->},
    removeFromList: (String) -> Unit = { t: String ->})
{
    val focusRequester = remember { FocusRequester() }
    var text by rememberSaveable {
        mutableStateOf("")
    }
    Column(modifier = modifier) {
        OutlinedTextField(
            value = text,
            onValueChange = { text = it},
            keyboardOptions = KeyboardOptions(imeAction = ImeAction.Done),
            keyboardActions = KeyboardActions(
                onDone = {
                    focusRequester.requestFocus()
                    addToList(text)
                }
            ),
            modifier = Modifier.focusRequester(focusRequester).onKeyEvent {
                if (it.nativeKeyEvent.keyCode.toLong() == Key.Enter.keyCode){
                    focusRequester.requestFocus()
                    addToList(text)
                    true
                }
                false
            },
            label = { Text("Topping") })
        ChipRow(toppingList, removeFromList)
    }
}

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun ChipRow(
    toppingList: List<String>,
    removeFromList: (String) -> Unit) {
    Row {
        toppingList.forEach {
            InputChip(
                onClick = {
                    removeFromList(it)
                },
                selected = true,
                label = { Text(it) },
                trailingIcon = {
                    Icon(
                        Icons.Default.Close,
                        contentDescription = "Chip",
                        Modifier.size(InputChipDefaults.AvatarSize)
                    )
                },
            )
        }
    }
}
