package es.uam.eps.dadm.myapplication

import android.annotation.SuppressLint
import android.app.Application
import android.content.Context
import androidx.lifecycle.*
import androidx.preference.PreferenceManager
import es.uam.eps.dadm.myapplication.database.CardDatabase
import timber.log.Timber
import java.time.LocalDateTime


class StatisticsViewModel(application: Application) : AndroidViewModel(application) {
    @SuppressLint("StaticFieldLeak")
    private val context = getApplication<Application>().applicationContext
    val decks: LiveData<List<DeckWithCards>> =
        CardDatabase.getInstance(context).cardDao.getDecksWithCards()

    //private val deckId = MutableLiveData<String>()
    /*val deckWithCards: LiveData<List<DeckWithCards>> = Transformations.switchMap(deckId) {
        CardDatabase.getInstance(context).cardDao.getDeckWithCards(it)
    }*/
    /*fun loadDeckId(id: String) {
        deckId.value = id
    }*/


    var viewGrap1 : Boolean?=null
    init {
        viewGrap1 = true
        Timber.i("MainViewModel created")
    }

    override fun onCleared() {
        super.onCleared()
        Timber.i("MainViewModel destroyed")
    }
    val totalReviewCards: LiveData<Int>
        get() = _cReviews

    /*val cardsToReview: MutableList<LiveData<Int>> = ArrayList()

    val cardsToReviewWeek: MutableList<LiveData<Int>> = ArrayList()*/

    val nDifficult: LiveData<Int>
        get() =  _difficult
    val nDoubt: LiveData<Int>
        get() =  _doubt
    val nEassy: LiveData<Int>
        get() =  _easy

    companion object :ViewModel(){
        private val _difficult = MutableLiveData<Int>()
        private val _doubt = MutableLiveData<Int>()
        private val _easy = MutableLiveData<Int>()
        private val _cReviews = MutableLiveData<Int>()
        val cardsToReview = mutableListOf<Float>()
        val cardsToReviewWeek = mutableListOf<Float>()


        fun updCardsToReview(cards: List<Card>) {
            cardsToReview.clear()
            cardsToReviewWeek.clear()
            for (i in 0..6) {
                cardsToReview.add(
                    cards.filter { card ->
                        card.isDue(
                            LocalDateTime.now().plusDays(i.toLong())
                        )
                    }.size.toFloat()
                )
            }
            for (i in 0..3) {
                cardsToReviewWeek.add(
                    cards.filter { card ->
                        card.isDue(
                            LocalDateTime.now().plusWeeks(i.toLong())
                        )
                    }.size.toFloat()
                )
            }
        }

        fun initValues(context: Context){
            _easy.value = PreferenceManager
                .getDefaultSharedPreferences(context)
                .getInt("easy", 0)
            _doubt.value = PreferenceManager
                .getDefaultSharedPreferences(context)
                .getInt("doubt", 0)
            _difficult.value = PreferenceManager
                .getDefaultSharedPreferences(context)
                .getInt("difficult", 0)
            _cReviews.value = PreferenceManager
                .getDefaultSharedPreferences(context)
                .getInt("total", 0)
        }


        fun addReview(quality: Int, context: Context){
            val sharedPreferences = PreferenceManager.getDefaultSharedPreferences(context)
            val editor = sharedPreferences.edit()
            when (quality) {
                5 -> {
                    _easy.value = (_easy.value?:0)+1
                    editor.putInt("easy", _easy.value!!)
                }
                3 ->  {
                    _doubt.value = (_doubt.value?:0)+1
                    editor.putInt("doubt", _doubt.value!!)
                }
                else->  {
                    _difficult.value = (_difficult.value?:0)+1
                    editor.putInt("difficult", _difficult.value!!)
                }
            }
            _cReviews.value = (_cReviews.value?:0)+1
            editor.putInt("total", _cReviews.value!!)
            editor.apply()

        }
    }
}
