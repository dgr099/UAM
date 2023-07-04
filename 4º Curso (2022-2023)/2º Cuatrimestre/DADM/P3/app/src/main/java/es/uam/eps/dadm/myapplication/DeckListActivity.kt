package es.uam.eps.dadm.myapplication

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import androidx.databinding.DataBindingUtil
import es.uam.eps.dadm.myapplication.databinding.DeckListBinding

class DeckListActivity : AppCompatActivity()/*,TitleFragment.OnTitleFragmentInteractionListener */{
    lateinit var binding: DeckListBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = DataBindingUtil.setContentView(this, R.layout.deck_list)
    }
}