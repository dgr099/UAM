package es.uam.eps.dadm.myapplication

import android.annotation.SuppressLint
import android.content.Intent
import android.os.Bundle
import android.view.*
import android.widget.Toast
import androidx.databinding.DataBindingUtil
import androidx.fragment.app.Fragment
import androidx.lifecycle.ViewModelProvider
import androidx.navigation.findNavController
import com.google.firebase.FirebaseApp
import com.google.firebase.auth.FirebaseAuth
import es.uam.eps.dadm.myapplication.database.CardDatabase
import es.uam.eps.dadm.myapplication.databinding.FragmentCardListBinding
import java.util.concurrent.Executors

@Suppress("DEPRECATION")
class CardListFragment: Fragment(){
    private val executor = Executors.newSingleThreadExecutor()
    private val cardListViewModel by lazy {
        ViewModelProvider(this)[CardListViewModel::class.java]
    }
    private lateinit var adapter: CardAdapter
    override fun onCreateOptionsMenu(menu: Menu, inflater: MenuInflater) {
        super.onCreateOptionsMenu(menu, inflater)
        inflater.inflate(R.menu.fragment_card_list, menu)
    }


    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        when (item.itemId) {
            R.id.settings -> {
                startActivity(Intent(requireContext(), SettingsActivity::class.java))
            }
            R.id.menu_item_1 -> {
                cardListViewModel.filer.value=1
            }
            R.id.menu_item_2 -> {
                cardListViewModel.filer.value=2
            }
            R.id.menu_item_3 -> {
                cardListViewModel.filer.value=3
            }


            R.id.log_out -> {
                //si está logeada
                if (FirebaseAuth.getInstance().currentUser != null) {
                    //FirebaseAuth.getInstance().signOut()
                    //startActivity(Intent(requireContext(), SettingsActivity::class.java))
                    requireView().findNavController().navigate(CardListFragmentDirections.actionCardListFragmentToFirebaseFragment())
                } else {

                    requireView().findNavController()
                        .navigate(CardListFragmentDirections.actionCardListFragmentToEmailPasswordFragment())

                }


            }
        }
        return true

    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setHasOptionsMenu(true)
        FirebaseApp.initializeApp(requireContext())
    }
    @SuppressLint("NotifyDataSetChanged")
    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {

        val binding = DataBindingUtil.inflate<FragmentCardListBinding>(
            inflater,
            R.layout.fragment_card_list,
            container,
            false
        )
        adapter = CardAdapter()
        adapter.data = emptyList()
        binding.cardListRecyclerView.adapter = adapter
        var sizeDecks = 0
        var idDeck = ""
        CardDatabase.getInstance(requireContext()).cardDao.getDecks().observe(viewLifecycleOwner){
            sizeDecks=it.size
            if(sizeDecks>0)
                idDeck=it.first().id
        }
        binding.newCardFab.setOnClickListener{
            if(sizeDecks<1){
                Toast.makeText(
                    requireActivity(),
                    R.string.no_decks,
                    Toast.LENGTH_LONG
                ).show()
            }
            else if((SettingsActivity.getMaximumNumberOfCards(requireContext())?.toIntOrNull()
                    ?: 0) <= adapter.data.size
            ){
                Toast.makeText(
                    requireActivity(),
                    R.string.maxNumCardsReached,
                    Toast.LENGTH_LONG
                ).show()
            }
                else{
                val card = Card("", "")
                card.idDeck=idDeck
                /*CardsApplication.addCard(card)
                MainViewModel.update()*/
                executor.execute{
                    CardDatabase.getInstance(requireContext()).cardDao.addCard(card)
                }

                it.findNavController()
                    .navigate(CardListFragmentDirections.actionCardListFragmentToCardEditFragment(card.id))
            }
        }
        cardListViewModel.filer.observe(viewLifecycleOwner) { it ->
            when (it) {
                1 -> {
                    adapter.data = adapter.data.sortedByDescending { it.easiness }
                    adapter.notifyDataSetChanged()
                }
                2 -> {
                    adapter.data = adapter.data.sortedByDescending { it.quality }
                    adapter.notifyDataSetChanged()
                }
                3 -> {
                    adapter.data = adapter.data.sortedByDescending { it.idDeck }
                    adapter.notifyDataSetChanged()
                }
                else -> {
                }
            }
            print(adapter.data)
        }
        cardListViewModel.cards.observe(viewLifecycleOwner) {
            adapter.data = it
            adapter.notifyDataSetChanged()
        }

        /*binding.reviewButton.setOnClickListener { view ->
            if (CardsApplication.numberOfDueCards() > 0)
                view.findNavController()
                    .navigate(R.id.action_cardListFragment_to_studyFragment)
            else
                Toast.makeText(
                    requireActivity(),
                    R.string.no_more_cards_toast_message,
                    Toast.LENGTH_LONG
                ).show()
        }*/

        return binding.root
    }
}