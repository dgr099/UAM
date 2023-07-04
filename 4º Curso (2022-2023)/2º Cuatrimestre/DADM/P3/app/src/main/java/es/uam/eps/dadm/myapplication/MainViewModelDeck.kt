package es.uam.eps.dadm.myapplication

import android.app.Application
import androidx.lifecycle.*
import es.uam.eps.dadm.myapplication.database.CardDatabase
import timber.log.Timber
import java.time.LocalDateTime
import java.util.concurrent.Executors

class MainViewModelDeck(idDeck: String, application: Application) : AndroidViewModel(application)  {


    private val idDeck = idDeck
    private val executor = Executors.newSingleThreadExecutor()
    private val context = getApplication<Application>().applicationContext
    val cardsLive: LiveData<List<CardsWithMultiple>> = CardDatabase.getInstance(context = context).cardDao.getCardsWithMult()

    var cardsDeck = MutableLiveData<List<CardsWithMultiple>>()
    var card: Card? = null
    val nDueCards = MutableLiveData<Int>()


    init {
        Timber.i((card!=null).toString())
    }

    override fun onCleared() {
        super.onCleared()
        Timber.i("MainViewModel destroyed")
    }

    private fun random_card(): Card? {
        if(cardsDeck.value!!.isEmpty()){
            return null
        }
        return cardsDeck.value!!.random().card
    }

    fun changeCard(){
        card = random_card()
    }

    fun update(quality: Int) {
        card?.quality =  quality
        card?.update(LocalDateTime.now())
        //_nDueCards.value = _nDueCards.value?.minus(1)
        //guardamos cambios en la base de datos
        executor.execute{
            CardDatabase.getInstance(context).cardDao.updateCard(
                card = card!!
            )
        }
    }

}