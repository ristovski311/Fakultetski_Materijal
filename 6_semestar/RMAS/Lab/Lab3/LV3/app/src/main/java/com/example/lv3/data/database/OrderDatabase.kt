package com.example.lv3.data.database

import android.content.Context
import androidx.room.Database
import androidx.room.Room
import androidx.room.RoomDatabase
import androidx.sqlite.db.SupportSQLiteDatabase
import com.example.lv3.data.daos.OrderDao
import com.example.lv3.data.entities.Order
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.launch

@Database(entities = [Order::class], version = 1, exportSchema = false)
abstract class OrderDatabase : RoomDatabase() {
    abstract fun orderDao(): OrderDao

    companion object {
        @Volatile
        private var INSTANCE: OrderDatabase? = null

        fun getDatabase(context: Context, scope: CoroutineScope) : OrderDatabase {
            return INSTANCE ?: synchronized(this) {
                val instance = Room.databaseBuilder(
                    context.applicationContext,
                    OrderDatabase::class.java,
                    "order_database"
                )
                    .addCallback(WordDatabaseCallback(scope))
                    .build()
                INSTANCE = instance
                instance
            }
        }
    }

    private class WordDatabaseCallback(
        private val scope: CoroutineScope
    ) : RoomDatabase.Callback() {

        override fun onCreate(db: SupportSQLiteDatabase) {
            super.onCreate(db)
            INSTANCE?.let { database ->
                scope.launch {
                    populateDatabase(database.orderDao())
                }
            }
        }

        suspend fun populateDatabase(orderDao: OrderDao) {
            orderDao.deleteAll()

            var o = Order(
                0,
                "Chocolate Cupcake",
                120,
                "Cupcake",
                "sprinkles"
            )
            orderDao.insert(o)
            o = Order(
                0,
                "Strawberry Cupcake",
                130,
                "Cupcake",
                "cream, chocolate sprinkles"
            )
            orderDao.insert(o)
        }
    }

}