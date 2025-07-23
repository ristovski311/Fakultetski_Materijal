package com.example.lifecycle19347

import android.os.Bundle
import android.widget.Toast
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import com.example.lifecycle19347.ui.theme.Lifecycle19347Theme
import android.util.Log

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        Log.i("testiranjeOverrideova", "Trenutno se izvrsila onCreate metoda!")
        Toast.makeText(this, "Trenutno se izvrsila onCreate metoda!", Toast.LENGTH_LONG).show()
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            Lifecycle19347Theme {
                Scaffold(modifier = Modifier.fillMaxSize()) { innerPadding ->
                    Greeting(
                        name = "Android",
                        modifier = Modifier.padding(innerPadding)
                    )
                }
            }
        }
    }

    override fun onStart() {
        Log.i("testiranjeOverrideova", "Trenutno se izvrsila onStart metoda!")
        Toast.makeText(this, "Trenutno se izvrsila onStart metoda!", Toast.LENGTH_LONG).show()
        super.onStart()
    }

    override fun onResume() {
        Log.i("testiranjeOverrideova", "Trenutno se izvrsila onResume metoda!")
        Toast.makeText(this, "Trenutno se izvrsila onResume metoda!", Toast.LENGTH_LONG).show()
        super.onResume()
    }

    override fun onPause() {
        Log.i("testiranjeOverrideova", "Trenutno se izvrsila onPause metoda!")
        Toast.makeText(this, "Trenutno se izvrsila onPause metoda!", Toast.LENGTH_LONG).show()
        super.onPause()
    }

    override fun onStop() {
        Log.i("testiranjeOverrideova", "Trenutno se izvrsila onStop metoda!")
        Toast.makeText(this, "Trenutno se izvrsila onStop metoda!", Toast.LENGTH_LONG).show()
        super.onStop()
    }

    override fun onRestart() {
        Log.i("testiranjeOverrideova", "Trenutno se izvrsila onRestart metoda!")
        Toast.makeText(this, "Trenutno se izvrsila onRestart metoda!", Toast.LENGTH_LONG).show()
        super.onRestart()
    }

    override fun onDestroy() {
        Log.i("testiranjeOverrideova", "Trenutno se izvrsila onDestroy metoda!")
        Toast.makeText(this, "Trenutno se izvrsila onDestroy metoda!", Toast.LENGTH_LONG).show()
        super.onDestroy()
    }

}

@Composable
fun Greeting(name: String, modifier: Modifier = Modifier) {
    Text(
        text = "Hello $name!",
        modifier = modifier
    )
}

@Preview(showBackground = true)
@Composable
fun GreetingPreview() {
    Lifecycle19347Theme {
        Greeting("Android")
    }
}
