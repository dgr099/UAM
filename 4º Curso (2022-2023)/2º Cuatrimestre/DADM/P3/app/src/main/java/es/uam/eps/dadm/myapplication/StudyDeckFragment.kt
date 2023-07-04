package es.uam.eps.dadm.myapplication
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Toast
import androidx.core.view.get
import androidx.core.view.size
import androidx.databinding.DataBindingUtil
import androidx.fragment.app.Fragment
import es.uam.eps.dadm.myapplication.databinding.FragmentStudyDeckBinding
import java.time.LocalDateTime

class StudyDeckFragment
    :Fragment(){
    private lateinit var binding: FragmentStudyDeckBinding



    private lateinit var viewModel : MainViewModelDeck
    private var listener = View.OnClickListener { v ->
        // Asigna a quality el valor 0, 3 o 5,
        // dependiendo del botón que se haya pulsado
        val quality = when (v?.id) {
            binding.easyButton.id -> 5
            binding.doubtButton.id -> 3
            else-> 0 //boton hard
        }
        viewModel.update(quality)
        StatisticsViewModel.addReview(quality, requireContext())
        if(viewModel.card==null){
            Toast.makeText(activity, "No more cards to study", Toast.LENGTH_SHORT).show()
        }
        binding.invalidateAll()
    }


    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        binding = DataBindingUtil.inflate(
            inflater,
            R.layout.fragment_study_deck,
            container,
            false)

        val args = StudyDeckFragmentArgs.fromBundle(requireArguments())
        viewModel = MainViewModelDeck(args.deckId, requireActivity().application)
        binding.viewModel = viewModel
        viewModel.cardsLive.observe(viewLifecycleOwner){
            viewModel.cardsDeck.value = it.filter { it -> it.card.isDue(LocalDateTime.now())  && it.card.idDeck==args.deckId}
            viewModel.nDueCards.value = viewModel.cardsDeck.value!!.size
            viewModel.changeCard()
            binding.invalidateAll()
        }

        binding.apply {
            answerButton.setOnClickListener {
                viewModel?.card?.answered = true
                invalidateAll()
            }
        }
        if(SettingsActivity.getBoardActivation(requireContext()))
            binding.customViewContainer.addView(BoardView(requireContext()))
        else{
            binding.customViewContainer.visibility=View.INVISIBLE
        }

        for(button in 0 until binding.difficultyButtons.size){
            binding.difficultyButtons[button].setOnClickListener(
                listener
            )
        }


        return binding.root
    }

}