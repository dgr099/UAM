package es.uam.eps.dadm.myapplication
import android.os.Bundle
import android.text.Editable
import android.text.TextWatcher
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.databinding.DataBindingUtil
import androidx.fragment.app.Fragment
import androidx.navigation.findNavController
import es.uam.eps.dadm.myapplication.database.CardDatabase
import es.uam.eps.dadm.myapplication.databinding.FragmentCreateDeckBinding
import java.util.concurrent.Executors

class CreateDeckFragment
    :Fragment(){
    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        val executor = Executors.newSingleThreadExecutor()
        val binding = DataBindingUtil.inflate<FragmentCreateDeckBinding>(
            inflater,
            R.layout.fragment_create_deck,
            container,
            false
        )
        val deck = Deck("")
        val nameTextWatcher = object : TextWatcher {
            override fun beforeTextChanged(s: CharSequence?, start: Int, count: Int, after: Int) {

            }

            override fun onTextChanged(s: CharSequence?, start: Int, before: Int, count: Int) {
                deck.name = s.toString()
            }

            override fun afterTextChanged(s: Editable?) {

            }
        }
        binding.nameEditText.addTextChangedListener(nameTextWatcher)

        binding.acceptEditButtom.setOnClickListener { view ->
            executor.execute{
                CardDatabase.getInstance(requireContext()).cardDao.addDeck(deck)
            }
            view.findNavController()
                .navigate(R.id.action_createDeckFragment_to_deckListFragment)
        }
        return binding.root
    }

}