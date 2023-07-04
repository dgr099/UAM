package es.uam.eps.dadm.myapplication

import android.os.Bundle
import android.util.Log
import androidx.appcompat.app.AppCompatActivity
import androidx.databinding.DataBindingUtil
import androidx.navigation.fragment.NavHostFragment
import androidx.navigation.ui.setupWithNavController
import androidx.preference.PreferenceManager
import com.google.android.material.snackbar.Snackbar
import com.google.firebase.FirebaseApp
import com.google.firebase.database.DataSnapshot
import com.google.firebase.database.DatabaseError
import com.google.firebase.database.FirebaseDatabase
import com.google.firebase.database.ValueEventListener
import es.uam.eps.dadm.myapplication.database.CardDatabase
import es.uam.eps.dadm.myapplication.databinding.ActivityTitleBinding
import java.util.concurrent.Executors


class TitleActivity : AppCompatActivity()/*,TitleFragment.OnTitleFragmentInteractionListener */{
    lateinit var binding: ActivityTitleBinding
    private val executor = Executors.newSingleThreadExecutor()

    /* private fun setupMenu() {
        addMenuProvider(object : MenuProvider {
            override fun onCreateMenu(menu: Menu, menuInflater: MenuInflater) {
                menuInflater.inflate(R.menu.fragment_card_list, menu)
            }
            override fun onMenuItemSelected(menuItem: MenuItem): Boolean {
                when (menuItem.itemId) {
                    R.id.settings -> {
                        startActivity(Intent(this@TitleActivity, ComponentActivity))
                    }
                }
                return true
            }
        })
    }*/
    val context = this
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
       PreferenceManager.setDefaultValues(
           this,
           R.xml.root_preferences,
           false
       )
        //setupMenu()
        binding = DataBindingUtil.setContentView(this, R.layout.activity_title)
        FirebaseApp.initializeApp(this)

        val navHostFragment = supportFragmentManager.findFragmentById(R.id.navHostFragment) as NavHostFragment
        binding.navView.setupWithNavController(navHostFragment.navController)
    }
}

