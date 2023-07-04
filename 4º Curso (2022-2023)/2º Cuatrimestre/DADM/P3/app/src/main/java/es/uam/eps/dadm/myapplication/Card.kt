package es.uam.eps.dadm.myapplication

import android.annotation.SuppressLint
import android.content.Context
import android.graphics.Canvas
import android.graphics.Color
import android.graphics.Paint
import android.graphics.Path
import android.util.AttributeSet
import android.view.MotionEvent
import android.view.View
import androidx.room.ColumnInfo
import androidx.room.Entity
import androidx.room.PrimaryKey
import java.time.*
import java.time.format.DateTimeFormatter
import java.util.*
import kotlin.math.max
import kotlin.math.roundToLong

/*
object LocalDateTimeConverter {
    @TypeConverter
    fun toDate(dateString: String?): LocalDateTime? {
        return if (dateString == null) {
            null
        } else {
            LocalDateTime.parse(dateString)
        }
    }

    @TypeConverter
    fun toDateString(date: LocalDateTime?): String? {
        return date?.toString()
    }
}
*/

@Entity(tableName = "cards_table")
open class Card(
    @ColumnInfo(name = "card_question")
    var question: String,
    var answer: String,
    var date: String = LocalDateTime.now().toString(),
    @PrimaryKey
    open var id: String = UUID.randomUUID().toString(),
    var quality: Int = 0,
    var repetitions: Int = 0,
    var interval: Long = 1L,
    var nextPracticeDate: String = LocalDateTime.now().toString(),
    var easiness: Double = 2.5,
    var idDeck: String? = null,
    var answered: Boolean = false,
    var expanded: Boolean = false
) {

    constructor() : this(
        "question",
        "answer",
        LocalDateTime.now().toString(),
        UUID.randomUUID().toString(),
        0
    )

    /*fun update_card(quality: Int) {
        this.quality = quality
        update(LocalDateTime.now())
    }*/


    fun isDue(date: LocalDateTime): Boolean {
        return (date.isEqual(LocalDateTime.parse(nextPracticeDate)) || date.isAfter(LocalDateTime.parse(nextPracticeDate)))
    }

    override fun toString() :String{
        var ret =  "card" //| $question | $answer | $date | $id | $quality | $re"
        for (property in Card::class.java.declaredFields.filter { field ->  field.name!="Companion"}) {
            //println("${field.name} = ${field.get(this)}")
            ret += " | ${property.get(this)}"
        }
        return ret
    }
    open fun show(){
        print("$question (INTRO para ver respuesta)")
        readln()
        print("$answer\n (Teclea 0->Difícil 3->Dudo 5->Fácil): ")
        quality = readln().toIntOrNull() ?: 0
    }

    fun update(currentDate: LocalDateTime, modFactor: Int=1){

        val value: Double = easiness + 0.1 - (5 - quality) * (0.08 + (5 - quality) * 0.02)
        easiness = max(1.3, value)
        if(quality<3) repetitions=0 else repetitions++
        interval = if(repetitions<=1) 1
        else if(repetitions==2) 6
        else{
            (interval*easiness*modFactor).roundToLong()
        }
        nextPracticeDate = currentDate.plusDays(interval).toString()
    }

    fun details(){
        println("eas = $easiness rep = $repetitions int = $interval next=${nextPracticeDate.format(DateTimeFormatter.ofPattern("yyyy-MM-dd"))}")
    }

    /*fun simulate(period: Long) {
        println("Simulación de la tarjeta $question:")
        var now = LocalDateTime.now()
        for(day in 0.rangeTo(period)){
            println("Fecha: ${now.format(DateTimeFormatter.ofPattern("yyyy-MM-dd"))}")
            if(now.format(DateTimeFormatter.ofPattern("yyyy-MM-dd")).equals(nextPracticeDate.format((DateTimeFormatter.ofPattern("yyyy-MM-dd"))))){
                this.show()
                this.update(now)
                this.details()
            }
            
            now = now.plusDays(1)
        }
    }*/

    companion object{
        fun fromString(cad: String) : Card{
            val atr: List<String> = cad.split(" | ")
            return Card(question = atr[0], answer=atr[1], date=atr[2], id=atr[3], quality=atr[4].toIntOrNull()?:0, repetitions=atr[5].toIntOrNull()?:0, interval=atr[6].toLongOrNull()?:0, nextPracticeDate=
            atr[7], easiness=atr[8].toDoubleOrNull()?:0.0, idDeck=atr[9])
        }
    }
}

/*fun Card.fromString(cad: String) : Card{
    var atr: List<String>

    atr = cad.split("|")
    return Card(question = atr[0], answer=atr[1], date=atr[2], id=atr[3], quality=atr[4].toIntOrNull()?:0, repetitions=atr[5].toIntOrNull()?:0, interval=atr[6].toLongOrNull()?:0, nextPracticeDate=LocalDateTime.parse(atr[7]), easiness=atr[8].toDoubleOrNull()?:0.0, id_deck=atr[9])

}*/class BoardView(
    context: Context,
    attrs: AttributeSet? = null
) : View(context, attrs) {
    private val linePaint = Paint(Paint.ANTI_ALIAS_FLAG).apply {
        color = Color.BLACK
        strokeWidth = 2f
        setStyle(Paint.Style.STROKE)
    }
    private var path = Path()

    fun onClear() {
        path.reset()
        invalidate()
    }

    override fun onDraw(canvas: Canvas) {
        super.onDraw(canvas)
        canvas.drawPath(path, linePaint)
    }

    @SuppressLint("ClickableViewAccessibility")
    override fun onTouchEvent(event: MotionEvent): Boolean {
        val pointX = event.x
        val pointY = event.y

        when (event.action) {
            MotionEvent.ACTION_DOWN ->
                // Comienza una línea nueva
                path.moveTo(pointX, pointY)
            MotionEvent.ACTION_MOVE ->
                // Dibuja una línea entre el anterior punto y (pointX, pointY)
                path.lineTo(pointX, pointY)
            else -> return false
        }

        postInvalidate()
        return true
    }
}