package es.uam.eps.dadm.myapplication

import android.content.Context
import android.os.Bundle
import android.view.Menu
import android.view.MenuItem
import androidx.appcompat.app.AppCompatActivity
import androidx.preference.PreferenceFragmentCompat
import androidx.preference.PreferenceManager

@Suppress("DEPRECATION")
class SettingsActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.settings_activity)
        if (savedInstanceState == null) {
            supportFragmentManager
                .beginTransaction()
                .replace(R.id.settings, SettingsFragment())
                .commit()
        }
        supportActionBar?.setDisplayHomeAsUpEnabled(true)
    }
    override fun onCreateOptionsMenu(menu: Menu?): Boolean {
        return super.onCreateOptionsMenu(menu)
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        when (item.itemId) {
            android.R.id.home -> {
                onBackPressed()
                return true
            }
        }
        return super.onOptionsItemSelected(item)
    }

    class SettingsFragment : PreferenceFragmentCompat() {
        override fun onCreatePreferences(savedInstanceState: Bundle?, rootKey: String?) {
            setPreferencesFromResource(R.xml.root_preferences, rootKey)
        }
    }

    companion object {
        const val MAX_NUMBER_CARDS_KEY = "max_number_cards"
        const val MAX_NUMBER_CARDS_DEFAULT = "20"
        const val MAX_NUMBER_DECKS_KEY = "max_number_decks"
        const val MAX_NUMBER_DECKS_DEFAULT = "4"
        const val MAX_NUMBER_CARDS_STUDY_KEY = "max_number_cards_study"
        const val MAX_NUMBER_CARDS_STUDY_DEFAULT = "20"
        /*const val MAX_NUMBER_OPTIONS_KEY = "max_number_opts"
        const val MAX_NUMBER_OPTIONS_DEFAULT = 3*/
        const val BOARD_KEY = "showBoard"
        const val UPD_SESSIOM_KEY = "updateSession"
        const val LIMIT_CARDS_KEY = "limitCards"
        fun getMaximumNumberOfCardsStudy(context: Context): String? {
            return PreferenceManager
                .getDefaultSharedPreferences(context)
                .getString(MAX_NUMBER_CARDS_STUDY_KEY, MAX_NUMBER_CARDS_STUDY_DEFAULT)
        }
        fun getMaximumNumberOfCards(context: Context): String? {
            return PreferenceManager
                .getDefaultSharedPreferences(context)
                .getString(MAX_NUMBER_CARDS_KEY, MAX_NUMBER_CARDS_DEFAULT)
        }
        fun getMaximumNumberOfDecks(context: Context): String? {
            return PreferenceManager
                .getDefaultSharedPreferences(context)
                .getString(MAX_NUMBER_DECKS_KEY, MAX_NUMBER_DECKS_DEFAULT)
        }
        /*fun getMaxOpt(context: Context): Int? {
            return PreferenceManager
                .getDefaultSharedPreferences(context)
                .getInt(MAX_NUMBER_OPTIONS_KEY, MAX_NUMBER_OPTIONS_DEFAULT)
        }

        fun setMaxOpt(context: Context, int: Int) {
            val sharedPreferences = PreferenceManager
                .getDefaultSharedPreferences(context)
            val editor = sharedPreferences.edit()
            editor.putInt(LOGGED_IN_KEY, int)
            editor.apply()
        }*/

        fun getBoardActivation(context: Context): Boolean {
            return PreferenceManager
                .getDefaultSharedPreferences(context)
                .getBoolean(BOARD_KEY, false)
        }
        fun getUpdSession(context: Context): Boolean {
            return PreferenceManager
                .getDefaultSharedPreferences(context)
                .getBoolean(UPD_SESSIOM_KEY, false)
        }
        fun getLimitCards(context: Context): Boolean {
            return PreferenceManager
                .getDefaultSharedPreferences(context)
                .getBoolean(LIMIT_CARDS_KEY, false)
        }

    }
}