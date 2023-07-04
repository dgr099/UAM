package es.uam.eps.dadm.myapplication.database

import androidx.lifecycle.LiveData
import androidx.room.*
import es.uam.eps.dadm.myapplication.*

@Dao
interface CardDao {
    @Query("SELECT * FROM cards_table")
    fun getCards(): LiveData<List<Card>>

    // Añade la función getCard
    @Query("SELECT * FROM cards_table WHERE id=:id_Card")
    fun getCard(id_Card: String): LiveData<Card?>
    @Insert(onConflict = OnConflictStrategy.REPLACE)
    fun addCard(card: Card)
    @Delete
    fun delCard(card: Card)

    @Update
    fun updateCard(card: Card)

    @Query("SELECT * FROM mult_option")
    fun getMultOptions(): LiveData<List<MultipleOption>>

    // Añade la función getCard
    @Query("SELECT * FROM mult_option WHERE id=:id_Card")
    fun getMultOptions(id_Card: String): LiveData<Card?>
    @Insert(onConflict = OnConflictStrategy.REPLACE)
    fun addMult(multipleOption: MultipleOption)
    @Delete
    fun delMult(multipleOption: MultipleOption)
    @Update
    fun updateMult(multipleOption: MultipleOption)


    @Query("DELETE FROM cards_table")
    fun nukeCards()

    @Query("DELETE FROM decks_table")
    fun nukeDecks()

    @Query("DELETE FROM mult_option")
    fun nukeMults()

    fun nukeTable(){
        nukeCards()
        nukeMults()
        nukeDecks()
    }

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    fun addDeck(deck: Deck)

    @Delete
    fun delDeck(deck: Deck)

    @Query("SELECT * FROM decks_table")
    fun getDecks(): LiveData<List<Deck>>

    @Transaction
    @Query("SELECT * FROM decks_table")
    fun getDecksWithCards(): LiveData<List<DeckWithCards>>

    @Transaction
    @Query("SELECT * FROM cards_table")
    fun getCardsWithMult(): LiveData<List<CardsWithMultiple>>

    @Query("SELECT * FROM mult_option WHERE id=:id_Card")
    fun getMultCard(id_Card: String): LiveData<MultipleOption?>


    @Transaction
    @Query("DELETE FROM cards_table where idDeck=:deckID")
    fun delCardsDeck(deckID: String);
    @Transaction
    @Query("DELETE FROM mult_option where idDeck=:deckID")
    fun delMultCardsDeck(deckID: String);

    @Transaction
    fun deleteDecksAndCards(deck: Deck) {
        delDeck(deck)
        delMultCardsDeck(deck.id)
        delCardsDeck(deck.id)
    }

    @Transaction
    @Query("SELECT * FROM decks_table WHERE id = :deckId")
    fun getDeckWithCards(deckId: String): LiveData<List<DeckWithCards>>



    @Query("SELECT * FROM cards_table WHERE id NOT IN (SELECT id FROM mult_option)")
    fun getCardsToUpload(): List<Card>

    @Query("SELECT * FROM mult_option")
    fun getCardsToUploadMult(): List<MultipleOption>

    @Query("SELECT * FROM decks_table")
    fun getDecksToUpload(): List<Deck>

    @Query("SELECT * FROM decks_table WHERE id=:id_deck")
    fun getDeck(id_deck: String): LiveData<Deck?>






}
