package es.uam.eps.dadm.myapplication

import DeckAdapter
import android.annotation.SuppressLint
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Toast
import androidx.databinding.DataBindingUtil
import androidx.fragment.app.Fragment
import androidx.lifecycle.ViewModelProvider
import androidx.navigation.findNavController
import es.uam.eps.dadm.myapplication.databinding.FragmentDeckListBinding
import java.util.concurrent.Executors

class DeckListFragment: Fragment(){
    private val deckListViewModel by lazy {
        ViewModelProvider(this)[DeckListViewModel::class.java]
    }

    private lateinit var adapter: DeckAdapter

    @SuppressLint("NotifyDataSetChanged")
    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        Executors.newSingleThreadExecutor()
        val binding = DataBindingUtil.inflate<FragmentDeckListBinding>(
            inflater,
            R.layout.fragment_deck_list,
            container,
            false
        )
        adapter = DeckAdapter()
        adapter.data = emptyList()
        binding.deckListRecyclerView.adapter = adapter
        binding.newDeckFab.setOnClickListener{
            if((SettingsActivity.getMaximumNumberOfDecks(requireContext())?.toIntOrNull()
                    ?: 0) <= adapter.data.size
            ){
            Toast.makeText(
                requireActivity(),
                R.string.maxNumDecksReached,
                Toast.LENGTH_LONG
            ).show()
        }else{
                it.findNavController()
                    .navigate(DeckListFragmentDirections.actionDeckListFragmentToCreateDeckFragment("0"))
            }

        }
        deckListViewModel.decks.observe(viewLifecycleOwner) {
            adapter.data = it
            adapter.notifyDataSetChanged()
        }

        return binding.root
    }
}