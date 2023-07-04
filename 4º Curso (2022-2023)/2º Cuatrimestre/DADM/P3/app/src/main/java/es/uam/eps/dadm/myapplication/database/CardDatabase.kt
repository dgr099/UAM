package es.uam.eps.dadm.myapplication.database

import android.content.Context
import androidx.room.Database
import androidx.room.Room
import androidx.room.RoomDatabase
import androidx.room.TypeConverters
import es.uam.eps.dadm.myapplication.Card
import es.uam.eps.dadm.myapplication.Deck
import es.uam.eps.dadm.myapplication.MultipleOption
import es.uam.eps.dadm.myapplication.StringListConverter

@Database(entities = [Card::class, Deck::class, MultipleOption::class], version = 4, exportSchema = false)
@TypeConverters(StringListConverter::class)
abstract class CardDatabase : RoomDatabase() {
    abstract val cardDao: CardDao
    companion object {
        @Volatile
        private var INSTANCE: CardDatabase? = null

        fun getInstance(context: Context): CardDatabase {
            var instance = INSTANCE

            if (instance == null) {
                instance = Room.databaseBuilder(
                    context.applicationContext,
                    CardDatabase::class.java,
                    "cards_database"
                )
                    .fallbackToDestructiveMigration()
                    .build()
                INSTANCE = instance
            }
            return instance
        }
    }
}
