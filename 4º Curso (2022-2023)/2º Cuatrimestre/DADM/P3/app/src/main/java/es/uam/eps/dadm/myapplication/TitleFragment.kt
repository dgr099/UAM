package es.uam.eps.dadm.myapplication
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Toast
import androidx.databinding.DataBindingUtil
import androidx.fragment.app.Fragment
import androidx.navigation.findNavController
import es.uam.eps.dadm.myapplication.databinding.FragmentTitleBinding

class TitleFragment
    :Fragment(){
    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        val binding = DataBindingUtil.inflate<FragmentTitleBinding>(
            inflater,
            R.layout.fragment_title,
            container,
            false
        )

        binding.cardsTitleTextView.setOnClickListener { view ->
            //if (CardsApplication.numberOfDueCards() > 0)
            view.findNavController()
                    .navigate(R.id.action_titleFragment_to_studyFragment)
        }

        return binding.root
    }


}