package es.uam.eps.dadm.myapplication

import android.app.Application
import com.google.firebase.FirebaseApp
import timber.log.Timber

class CardsApplication: Application() {


    override fun onCreate() {
        super.onCreate()
        StatisticsViewModel.initValues(applicationContext)


        Timber.plant(Timber.DebugTree())

    }
    /*companion object {
        fun addDebugValues(){
            for(j in 0..4){
                val auxDeck = Deck("Deck $j")
                for(i in 0..4) {
                    val auxCard = Card(question = "preg tarj: $j $i", answer = "resp tarj: $j $i")
                    //auxCard.nextPracticeDate = currentDate.plusDays(i.toLong())
                    auxCard.idDeck = auxDeck.id
                    cards.add(auxCard)
                }
                for(i in 0..4) {
                    val auxCard = Card(question = "preg tarj: $j $i", answer = "resp tarj: $j $i")
                    val currentDate = LocalDateTime.now()
                    auxCard.nextPracticeDate = currentDate.plusDays(i.toLong()).toString()
                    auxCard.idDeck = auxDeck.id
                    cards.add(auxCard)
                }
                decks.add(auxDeck)
            }
        }
        fun numberOfDueCards(): Int {
            return cards.filter { it.isDue(LocalDateTime.now()) }.size
        }

        fun getCard(cardId: String): Card? {
            cards.forEach{
                if(it.id==cardId){
                    return it
                }
            }
            return null
        }
        fun getDeck(deckID: String): Deck? {
            decks.forEach{
                if(it.id==deckID){
                    return it
                }
            }
            return null
        }

        fun addCard(card: Card) {
            cards.add(card)
        }
        fun removeDeck(deck: Deck){
            cards.filter { it.idDeck==deck.id }.forEach {
                cards.remove(it)
            }
            decks.remove(deck)
        }
        fun addDeck(deck: Deck) {
            decks.add(deck)
        }
        fun listCards(idDeck: String): Int{
            return cards.filter { it.idDeck==idDeck }.size
        }

        var cards: MutableList<Card> = mutableListOf()
        var decks: MutableList<Deck> = mutableListOf()
    }*/
}