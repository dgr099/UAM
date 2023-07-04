package es.uam.eps.dadm.myapplication

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import androidx.databinding.DataBindingUtil
import es.uam.eps.dadm.myapplication.databinding.ActivityAboutBinding

class AboutActivity : AppCompatActivity()/*,TitleFragment.OnTitleFragmentInteractionListener */{
    lateinit var binding: ActivityAboutBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = DataBindingUtil.setContentView(this, R.layout.activity_about)
    }
}

