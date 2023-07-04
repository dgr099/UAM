import java.io.File
import java.nio.file.Files
import java.nio.file.Paths

object Data{
    var decks = mutableListOf<Deck>()
    var cards = mutableListOf<Card>()
    fun writeCards(){
        //creamos si no existe la carpeta
        try {
            Files.createDirectory((Paths.get("data/")))
        }catch (e :java.nio.file.FileAlreadyExistsException){
            print("Directory already created")
        }
        File("data/Cards.txt").writeText("") //vaciamos lo anterior
        File("data/Decks.txt").writeText("")
        this.decks.forEach { it.writeCards() } //escribimos las tarjetas de cada mazo
    }
    fun readCards(){
        val decksStrings: List<String> = File("data/Decks.txt").readLines()
        for(deckString in decksStrings){
            val aux:Deck = Deck.fromString(deckString)
            println(aux)
            this.decks.add(aux)
        }
        val cardStrings: List<String> = File("data/Cards.txt").readLines()
        for (cardString in cardStrings) {
            val cardType = cardString.substringBefore(" | ") //obtenemos el tipo de carta
            val infoCard = cardString.substringAfter(" | ")
            val aux:Card = if(cardType=="card"){
                Card.fromString(infoCard)
            }else if(cardType=="cloze"){
                Cloze.fromString(infoCard)

            }else{
                continue
            }
            println(aux)
            this.cards.add(aux)
        }
    }
    fun selectDeck() :Deck?{
        if(this.decks.isEmpty()){
            println("La lista de mazos está vacía")
            return null
        }
        println("List of Decks")
        var index=0
        this.decks.forEach {
            println("Deck $index: ${it.name}, ${it.id}")
            index++
        }
        print("Select Deck: ")
        val iDeck = readln().toIntOrNull()
        if(iDeck==null || iDeck !in 0 until index){
            println("Index out of range")
            return null
        }
        return this.decks[iDeck]
    }




}


fun main(){
    var opt : Int?
    var modFactor : Int? = null
    do {

        do {
            print(
                """    1. Añadir tarjeta
    2. Lista de tarjetas
    3. Simulación
    4. Leer tarjetas de fichero
    5. Escribir tarjetas en fichero
    6. Crear Mazo
    7. Eliminar Mazo
    8. Eliminar Tarjeta
    9. Modificar Factor de aprendizaje Anki
    10. Salir
    Elige una opción: """
            )
            opt = readln().toIntOrNull() ?: 0
        } while (opt == null || opt !in 1..10)
        when(opt){
            1-> {
                val deck : Deck? = Data.selectDeck()
                if(deck==null){
                    println("Error on deck select")
                }else{
                    deck.addCard()
                }
            }
            2 -> {
                val deck : Deck? = Data.selectDeck()
                if(deck==null){
                    println("Error on deck select")
                }else{
                    deck.listCards()
                }
            }
            3 ->{
                val deck : Deck? = Data.selectDeck()
                if(deck==null){
                    println("Error on deck select")
                }else{
                    print("Input days to simulate: ")
                    val days = readln().toLongOrNull()?:0
                    deck.simulate(days, modFactor?:1)
                }
            }
            4->{
                Data.readCards()
            }
            5 -> {
                Data.writeCards()
            }
            6 ->{
                print("Introduce el nombre del mazo: ")
                val nameDeck = readln()
                Data.decks.add(Deck(name = nameDeck))
            }
            7->{
                val deck : Deck? = Data.selectDeck()
                if(deck==null){
                    println("Error on deck select")
                }else{
                    //eliminamos las tarjetas de ese mazo
                    Data.cards.removeIf{card ->  card.id_deck==deck.id}
                    //eliminamos ese mazo
                    Data.decks.removeIf { it.id==deck.id}
                }
            }
            8->{
                val deck : Deck? =Data. selectDeck()
                if(deck==null){
                    println("Error on deck select")
                }else{
                    Data.cards.withIndex().filter { (_, value)->value.id_deck==deck.id }.forEach{
                        println(it.index.toString() +": " + it.value.question + " -> " + it.value.answer)
                    }
                    print("Select Index of the card: ")
                    val ind = readln().toIntOrNull()
                    if(ind!=null && ind in 0 until Data.cards.size){
                        Data.cards.removeAt(ind)
                    }else{
                        print("Error on card select")
                    }

                }
            }
            9->{
                print("Introduce el nuevo factor de aprendizaje: ")
                modFactor= readln().toIntOrNull()
            }
            else -> {
                opt = 10
            }
        }
    } while(opt!=10)
    println("Finalizando ejecución...")
}
