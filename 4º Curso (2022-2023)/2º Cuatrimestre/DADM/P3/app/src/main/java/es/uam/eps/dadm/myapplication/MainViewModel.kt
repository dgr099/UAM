package es.uam.eps.dadm.myapplication

import android.annotation.SuppressLint
import android.app.Application
import androidx.lifecycle.AndroidViewModel
import androidx.lifecycle.LiveData
import androidx.lifecycle.Transformations
import es.uam.eps.dadm.myapplication.database.CardDatabase
import es.uam.eps.dadm.myapplication.databinding.FragmentStudyBinding
import timber.log.Timber
import java.lang.Integer.min
import java.time.LocalDateTime
import java.util.concurrent.Executors

class MainViewModel(application: Application)  : AndroidViewModel(application) {
    private val executor = Executors.newSingleThreadExecutor()
    @SuppressLint("StaticFieldLeak")
    private val context = getApplication<Application>().applicationContext
    var cards: LiveData<List<CardsWithMultiple>> = CardDatabase.getInstance(context = context).cardDao.getCardsWithMult()
    var stCards = 0
    var finish: Boolean = false
    var maxCardsStudy = SettingsActivity.getMaximumNumberOfCardsStudy(context)

    var dueCard: LiveData<CardsWithMultiple?> = Transformations.map(cards) { it ->
        it.filter {it.card.isDue(LocalDateTime.now()) }.run {
            if (any()) random() else null
        }
    }

    var nDueCards : LiveData<Int>
    = Transformations.map(cards) { it ->
        var aux=it.filter{it.card.isDue(LocalDateTime.now())}.size
        if(!SettingsActivity.getLimitCards(context)){
            val maxCardsStudy = SettingsActivity.getMaximumNumberOfCardsStudy(context)?.toInt()?:0
            val cardsStudy = this.stCards
            aux=min(aux,  (maxCardsStudy - cardsStudy))
        }
        if(aux<=0){
            finish=true
        }else{
            finish=false
        }
        aux
    }

    fun updDueCard(binding: FragmentStudyBinding) {
        nDueCards = Transformations.map(cards) { it ->
            var aux=it.filter{it.card.isDue(LocalDateTime.now())}.size
            if(!SettingsActivity.getLimitCards(context)){
                val maxCardsStudy = SettingsActivity.getMaximumNumberOfCardsStudy(context)?.toInt()?:0
                val cardsStudy = this.stCards
                aux=min(aux,  (maxCardsStudy - cardsStudy))
            }
            if(aux<=0){
                finish=true
            }else{
                finish=false
            }
            binding.invalidateAll()
            aux
        }

    }









    var card: Card? = null
    var mult: MultipleOption? = null


    /*private fun randomCard(): CardsWithMultiple? {
        val aux = dueCards()
        if(aux.isEmpty()){
            return null
        }
        return aux.random()
    }*/

    /*private fun dueCards(): List<CardsWithMultiple> {
        return cards.value!!.filter {it.card.isDue(LocalDateTime.now())}
    }*/

    init {
        Timber.i("MainViewModel created")
        //card = random_card()
        //card = dueCard.value
        Timber.i((card!=null).toString())

    }

    override fun onCleared() {
        super.onCleared()
        Timber.i("MainViewModel destroyed")
    }




    fun update(quality: Int) {
        this.stCards++
        val auxCard: Card? = if(mult!=null){
            mult
        }else{
            card
        }
        auxCard?.quality =  quality
        auxCard?.update(LocalDateTime.now())
        //_nDueCards.value = _nDueCards.value?.minus(1)
        //guardamos cambios en la base de datos
        executor.execute{

            CardDatabase.getInstance(context).cardDao.updateCard(
                card = auxCard!!
            )
            if(auxCard is MultipleOption){
                CardDatabase.getInstance(context).cardDao.updateMult(
                    multipleOption = auxCard
                )
            }

        }
        /*
        var aux: CardsWithMultiple? = null
        val maxCardsStudy = SettingsActivity.getMaximumNumberOfCardsStudy(context)?.toInt()?:0
        val cardsStudy = this.stCards

        if(maxCardsStudy-cardsStudy>0){
            aux = randomCard()
        }
        card = aux?.card
        mult = aux?.mult*/
    }
}