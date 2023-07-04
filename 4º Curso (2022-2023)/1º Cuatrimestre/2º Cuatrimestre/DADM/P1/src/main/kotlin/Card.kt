import java.time.*
import java.util.UUID
import java.util.Date
import kotlin.math.roundToLong
import java.time.format.DateTimeFormatter;
open class Card(
    var question: String,
    var answer: String,
    var date: String = LocalDateTime.now().toString(),
    var id: String = UUID.randomUUID().toString(),
    var quality: Int = 0,
    var repetitions: Int = 0,
    var interval: Long = 1L,
    var nextPracticeDate: LocalDateTime = LocalDateTime.now(),
    var easiness: Double = 2.5,
    var id_deck: String? = null,
){

    override fun toString() :String{
        var ret =  "card" //| $question | $answer | $date | $id | $quality | $re"
        for (property in Card::class.java.declaredFields.filter { field ->  field.name!="Companion"}) {
            //println("${field.name} = ${field.get(this)}")
            ret += " | ${property.get(this)}"
        }
        return ret;
    }
    open fun show(){
        print("$question (INTRO para ver respuesta)")
        readln();
        print("$answer\n (Teclea 0->Difícil 3->Dudo 5->Fácil): ")
        quality = readln().toIntOrNull() ?: 0
    }

    fun update(currentDate: LocalDateTime, modFactor: Int=1){
        easiness = max(1.3, (easiness + 0.1 - (5 - quality) * (0.08 + (5 - quality) * 0.02)))
        if(quality<3) repetitions=0 else repetitions++
        if(repetitions<=1) interval = 1
        else if(repetitions==2) interval=6
        else{
            interval=(interval*easiness*modFactor).roundToLong()
        }
        nextPracticeDate = currentDate.plusDays(interval)
    }

    fun details(){
        println("eas = $easiness rep = $repetitions int = $interval next=${nextPracticeDate.format(DateTimeFormatter.ofPattern("yyyy-MM-dd"))}")
    }

    fun simulate(period: Long) {
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
    }

    companion object{
        fun fromString(cad: String) : Card{
            var atr: List<String>

            atr = cad.split(" | ")
            return Card(question = atr[0], answer=atr[1], date=atr[2], id=atr[3], quality=atr[4].toIntOrNull()?:0, repetitions=atr[5].toIntOrNull()?:0, interval=atr[6].toLongOrNull()?:0, nextPracticeDate=LocalDateTime.parse(atr[7]), easiness=atr[8].toDoubleOrNull()?:0.0, id_deck=atr[9])

        }
    }
}

/*fun Card.fromString(cad: String) : Card{
    var atr: List<String>

    atr = cad.split("|")
    return Card(question = atr[0], answer=atr[1], date=atr[2], id=atr[3], quality=atr[4].toIntOrNull()?:0, repetitions=atr[5].toIntOrNull()?:0, interval=atr[6].toLongOrNull()?:0, nextPracticeDate=LocalDateTime.parse(atr[7]), easiness=atr[8].toDoubleOrNull()?:0.0, id_deck=atr[9])

}*/