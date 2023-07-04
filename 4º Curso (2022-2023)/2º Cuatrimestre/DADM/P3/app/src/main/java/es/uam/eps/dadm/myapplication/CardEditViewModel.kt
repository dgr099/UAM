package es.uam.eps.dadm.myapplication

import android.annotation.SuppressLint
import android.app.Application
import androidx.lifecycle.AndroidViewModel
import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.Transformations
import es.uam.eps.dadm.myapplication.database.CardDatabase

class CardEditViewModel(application: Application): AndroidViewModel(application) {
    @SuppressLint("StaticFieldLeak")
    private val context = getApplication<Application>().applicationContext

    private val cardId = MutableLiveData<String>()

    val card: LiveData<Card?> = Transformations.switchMap(cardId) {
        CardDatabase.getInstance(context).cardDao.getCard(it)
    }

    val mult: LiveData<MultipleOption?> = Transformations.switchMap(cardId) {
        CardDatabase.getInstance(context).cardDao.getMultCard(it)
    }


    fun loadCardId(id: String) {
        cardId.value = id
    }
}
