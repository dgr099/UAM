package es.uam.eps.dadm.myapplication

import androidx.room.Embedded
import androidx.room.Entity
import androidx.room.PrimaryKey
import androidx.room.Relation
import java.io.File
import java.time.LocalDateTime
import java.time.format.DateTimeFormatter
import java.util.*

data class DeckWithCards(
    @Embedded
    val deck: Deck,
    @Relation(parentColumn = "id", entityColumn = "idDeck")
    val cards: List<Card>,
    @Relation(parentColumn = "id", entityColumn = "idDeck")
    val cardsMult: List<MultipleOption>
    )

data class CardsWithMultiple(
    @Embedded val card: Card,
    @Relation(
        parentColumn = "id",
        entityColumn = "id"
    )
    val mult: MultipleOption?
)

@Entity(tableName = "decks_table")
data class Deck(
    var name: String,
    @PrimaryKey
    var id: String = UUID.randomUUID().toString()
){
    /*fun writeCards(){
        //escribimos primero las cartas
        Data.cards.filter {card ->  card.idDeck==this.id}.forEach {
            File("data/Cards.txt").appendText(it.toString() + "\n")
        }
        //luego escribimos el propio mazo
        File("data/Decks.txt").appendText(this.toString() + "\n")
    }*/

    override fun toString() :String{
        var ret =  ""
        for (property in Deck::class.java.declaredFields.filter { field ->  field.name!="Companion"}) {
            ret += "${property.get(this)} | "
        }
        return ret
    }

    /*fun simulate(period: Long, modFactor: Int = 1) {
        println("Simulación del mazo: $name:")
        var now = LocalDateTime.now()
        //ponemos para que todas las tarjetas se pregunten desde el primer día
        Data.cards.filter {card ->  card.idDeck==this.id}.forEach{
            it.nextPracticeDate=now.toString()
            it.quality=0
            it.repetitions=0
            it.interval=1L
            it.easiness = 2.5
        }

        for(day in 0.rangeTo(period)){
            println("Fecha: ${now.format(DateTimeFormatter.ofPattern("yyyy-MM-dd"))}")
            Data.cards.filter {card ->  card.idDeck==this.id}.forEach {
                if(now.format(DateTimeFormatter.ofPattern("yyyy-MM-dd")).equals(it.nextPracticeDate.format((DateTimeFormatter.ofPattern("yyyy-MM-dd"))))){
                    it.show()
                    it.update(now, modFactor)
                    it.details()
                }
            }
            now = now.plusDays(1)
        }
    }*/

    /*fun addCard(){
        println("Añadiendo tarjeta al mazo $name")
        var tipo: Int?
        do{print("Teclea el tipo (0->Card, 1->Cloze, 2->TextCard): ")
        tipo = readln().toIntOrNull() ?: 0}while((tipo == null) || (tipo !in (0..2)))
        print("  Teclea la pregunta: ")
        val quest = readln()
        print("  Teclea la respuesta: ")
        val awns = readln()
        lateinit var card : Card
        //creamos y añadimos la tarjeta
        when(tipo){
            2 -> {
                //compruebo que la pregunta tenga el espacio para colocar la respuesta
                if(quest.count{it =='*'}==2){
                    card = TextCard(question=quest, answer=awns)
                    card.idDeck=this.id

                }else{
                    println("Sorry malformed question")
                    return
                }
            }
            1 -> {
                //compruebo que la pregunta tenga el espacio para colocar la respuesta
                if(quest.count{it =='*'}==2){
                    card = Cloze(question=quest, answer=awns)
                    card.idDeck=this.id

                }else{
                    println("Sorry malformed question")
                    return
                }
            }
            0 -> {
                card = (Card(question=quest, answer=awns))
                card.idDeck=this.id
            }
            else -> {
                println("Error no type $tipo")
                return
            }
        }
        //con la tarjeta añadida, la añadimos al colection
        Data.cards.add(card)

        println("Tarjeta añadida correctamente")
    }*/

    /*fun listCards(){
        CardsApplication.cards.filter {card ->  card.idDeck==this.id}.forEach {
           println(it.question + " -> " + it.answer)
        }
    }

    fun numlistCards(): Int{

        return CardsApplication.cards.filter {card ->  card.idDeck==this.id}.size
    }

    fun dueCards(): Int{
        return CardsApplication.cards.filter {card ->  card.idDeck==this.id && card.isDue(LocalDateTime.now())}.size
    }*/


    companion object{
        fun fromString(deck: String) : Deck{
            val atr: List<String> = deck.split(" | ")
            return Deck(atr[0], atr[1])
        }
    }

}