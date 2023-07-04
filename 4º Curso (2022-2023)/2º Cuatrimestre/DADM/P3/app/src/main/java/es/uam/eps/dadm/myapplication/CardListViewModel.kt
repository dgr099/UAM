package es.uam.eps.dadm.myapplication

import android.annotation.SuppressLint
import android.app.Application
import androidx.lifecycle.AndroidViewModel
import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import es.uam.eps.dadm.myapplication.database.CardDatabase

class CardListViewModel(application: Application)
    : AndroidViewModel(application) {

    @SuppressLint("StaticFieldLeak")
    private val context = getApplication<Application>().applicationContext
    // Completa la siguiente instrucción
    var filer = MutableLiveData<Int>()
    val cards: LiveData<List<Card>> = CardDatabase.getInstance(context).cardDao.getCards()
}