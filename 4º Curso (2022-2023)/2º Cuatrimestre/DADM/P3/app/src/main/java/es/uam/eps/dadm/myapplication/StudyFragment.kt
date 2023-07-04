package es.uam.eps.dadm.myapplication
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ArrayAdapter
import android.widget.Toast
import androidx.core.view.get
import androidx.core.view.size
import androidx.databinding.DataBindingUtil
import androidx.fragment.app.Fragment
import androidx.lifecycle.Observer
import androidx.lifecycle.ViewModelProvider
import es.uam.eps.dadm.myapplication.databinding.FragmentStudyBinding

class StudyFragment
    :Fragment(){
    private lateinit var binding: FragmentStudyBinding
    private val viewModel: MainViewModel by lazy {
        ViewModelProvider(this)[MainViewModel::class.java]
    }

    private var listener = View.OnClickListener { v ->
        // Asigna a quality el valor 0, 3 o 5,
        // dependiendo del botón que se haya pulsado
        val quality = when (v?.id) {
            binding.easyButton.id -> 5
            binding.doubtButton.id -> 3
            else-> 0 //boton hard
        }
        val card = viewModel.card
        viewModel.update(quality)
        StatisticsViewModel.addReview(quality, requireContext())
        if(viewModel.mult!=null){
            binding.spinner.visibility=View.VISIBLE
            binding.spinner.adapter = ArrayAdapter(requireContext(), R.layout.spinner_item, viewModel.mult!!.options.toMutableList())
        }else{
            binding.spinner.visibility=View.INVISIBLE
        }

        binding.invalidateAll()
    }

    override fun onResume() {
        super.onResume()
        if(!SettingsActivity.getLimitCards(requireContext())){
            if(SettingsActivity.getUpdSession(requireContext())){
                viewModel.finish= viewModel.card==null
                viewModel.stCards=0
            }
        }
        viewModel.updDueCard(binding)

    }

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        val board = BoardView(requireContext())
        binding = DataBindingUtil.inflate(
            inflater,
            R.layout.fragment_study,
            container,
            false)

        binding.viewModel = viewModel
        binding.apply {
            answerButton.setOnClickListener {
                viewModel?.card?.answered = true
                invalidateAll()
            }
        }
        if(SettingsActivity.getBoardActivation(requireContext()))
            binding.customViewContainer.addView(board)
        else{
            binding.customViewContainer.visibility=View.INVISIBLE
        }
        for(button in 0 until binding.difficultyButtons.size){
            binding.difficultyButtons.get(button).setOnClickListener(
                listener
            )
        }
        binding.lifecycleOwner = viewLifecycleOwner
        viewModel.dueCard.observe(viewLifecycleOwner, Observer {
            if(SettingsActivity.getMaximumNumberOfCardsStudy(requireContext()) !=viewModel.maxCardsStudy){
                viewModel.maxCardsStudy = SettingsActivity.getMaximumNumberOfCardsStudy(requireContext())
                viewModel.updDueCard(binding)
            }
            board.onClear()
            viewModel.card = it?.card
            viewModel.mult = it?.mult
            if(viewModel.mult!=null){
                binding.spinner.visibility=View.VISIBLE
                binding.spinner.adapter = ArrayAdapter(requireContext(), R.layout.spinner_item, viewModel.mult!!.options.toMutableList())
            }
            else{
                binding.spinner.visibility=View.INVISIBLE
            }
            binding.invalidateAll()
            if(viewModel.card==null){
                Toast.makeText(activity, "No more cards to study", Toast.LENGTH_SHORT).show()
            }

        })
        return binding.root
    }

}