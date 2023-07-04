package es.uam.eps.dadm.myapplication

import androidx.room.ColumnInfo
import androidx.room.Entity
import androidx.room.PrimaryKey
import androidx.room.TypeConverter
import java.time.LocalDateTime
import java.util.*
class StringListConverter {
    @TypeConverter
    fun fromList(list: List<String>): String {
        return list.joinToString(",")
    }

    @TypeConverter
    fun toList(string: String): List<String> {
        return string.split(",")
    }
}

@Entity(tableName = "mult_option")
class MultipleOption(question: String,
                     answer: String, date: String = LocalDateTime.now().toString(),
                     @PrimaryKey
                     override var id: String = UUID.randomUUID().toString(),
                     quality: Int = 0,
                     repetitions: Int = 0,
                     interval: Long = 1L,
                     nextPracticeDate: String = LocalDateTime.now().toString(),
                     easiness: Double = 2.5,
                     @ColumnInfo(name = "options")
                     var options: List<String> = emptyList(),
                     idDeck: String? = null,) :
    Card(question, answer, date, id, quality, repetitions, interval, nextPracticeDate, easiness, idDeck){



    override fun toString() :String{
        return "multOpt" + super.toString().substring("card".length)
    }
    companion object{
        /*fun fromString(cad: String) : Card{

            val atr: List<String> = cad.split(" | ")
            return MultipleOption(question = atr[0], answer=atr[1], date=atr[2], id=atr[3], quality=atr[4].toIntOrNull()?:0, repetitions=atr[5].toIntOrNull()?:0, interval=atr[6].toLongOrNull()?:0, nextPracticeDate= atr[7], easiness=atr[8].toDoubleOrNull()?:0.0, idDeck=atr[9])
        }*/
    }
}