package es.uam.eps.dadm.myapplication
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import androidx.databinding.DataBindingUtil
import es.uam.eps.dadm.myapplication.databinding.CardListBinding

class CardListActivity : AppCompatActivity()/*,TitleFragment.OnTitleFragmentInteractionListener */{
    lateinit var binding: CardListBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = DataBindingUtil.setContentView(this, R.layout.card_list)
    }
}