import java.time.LocalDateTime
import java.util.*

class TextCard(question: String,
            answer: String, date: String = LocalDateTime.now().toString(),
            id: String = UUID.randomUUID().toString(),
            quality: Int = 0,
            repetitions: Int = 0,
            interval: Long = 1L,
            nextPracticeDate: LocalDateTime = LocalDateTime.now(),
            easiness: Double = 2.5,
            id_deck: String? = null,) : Card(question, answer, date, id, quality, repetitions, interval, nextPracticeDate, easiness, id_deck){
                val fPart = question.subSequence(0, question.indexOf("*"))
                val sPart = question.subSequence(question.indexOf("*"), question.lastIndexOf("*"))
                override fun show(){
                    print("$question")
                    println("Introduce respuesta: ")
                    var respuesta = readln()
                    println("Respuesta Correcta: ")
                    print("${this.fPart}${answer}${this.sPart} (Teclea 0 -> Difícil 3 -> Dudo 5 -> Fácil): ")
                    quality = readln().toIntOrNull() ?: 0
                }
    override fun toString() :String{
        return "textCard" + super.toString().substring("card".length)
    }

    companion object{
        fun fromString(cad: String) : Card{
            var atr: List<String>

            atr = cad.split(" | ")
            return Cloze(question = atr[0], answer=atr[1], date=atr[2], id=atr[3], quality=atr[4].toIntOrNull()?:0, repetitions=atr[5].toIntOrNull()?:0, interval=atr[6].toLongOrNull()?:0, nextPracticeDate= LocalDateTime.parse(atr[7]), easiness=atr[8].toDoubleOrNull()?:0.0, id_deck=atr[9])
        }
    }
}
