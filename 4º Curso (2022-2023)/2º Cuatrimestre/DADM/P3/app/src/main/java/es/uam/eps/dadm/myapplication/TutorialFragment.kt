package es.uam.eps.dadm.myapplication
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Toast
import androidx.databinding.DataBindingUtil
import androidx.fragment.app.Fragment
import es.uam.eps.dadm.myapplication.database.CardDatabase
import es.uam.eps.dadm.myapplication.databinding.FragmentTutorialBinding
import java.util.concurrent.Executors

class TutorialFragment
    :Fragment(){
    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        val executor = Executors.newSingleThreadExecutor()
        val cardDatabase = CardDatabase.getInstance(requireContext())
        val binding = DataBindingUtil.inflate<FragmentTutorialBinding>(
            inflater,
            R.layout.fragment_tutorial,
            container,
            false
        )
        binding.debugButton.setOnClickListener {
            executor.execute {
                cardDatabase.cardDao.nukeTable()
                cardDatabase.cardDao.addDeck(Deck("English", "1"))
                cardDatabase.cardDao.addDeck(Deck("Frech", "2"))
                var aux = Card("To wake up", "Despertarse", idDeck = "1")
                aux.toString()
                cardDatabase.cardDao.addCard(
                    aux
                )
                cardDatabase.cardDao.addCard(
                    Card("To rule out", "Descartar", idDeck = "1")
                )
                cardDatabase.cardDao.addCard(
                    Card("To turn down", "Rechazar", idDeck = "1")
                )
                cardDatabase.cardDao.addCard(
                    Card("La voiture", "El coche", idDeck = "2")
                )
                var aux2 = MultipleOption("multiple options", "El coche", idDeck = "2", options = listOf("value1", "value2", "value3"))

                cardDatabase.cardDao.addMult(aux2
                )
                cardDatabase.cardDao.addCard(aux2
                )
            }

            //StatisticsViewModel.update()
            Toast.makeText(
                requireActivity(),
                R.string.added_debug_values,
                Toast.LENGTH_LONG
            ).show()
        }

        return binding.root
    }

}