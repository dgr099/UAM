package es.uam.eps.dadm.myapplication

import android.os.Bundle
import android.text.Editable
import android.text.TextWatcher
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.AdapterView
import android.widget.ArrayAdapter
import androidx.databinding.DataBindingUtil
import androidx.lifecycle.ViewModelProvider
import androidx.navigation.findNavController
import androidx.navigation.fragment.findNavController
import es.uam.eps.dadm.myapplication.database.CardDatabase
import es.uam.eps.dadm.myapplication.databinding.FragmentCardEditBinding
import java.util.concurrent.Executors

class CardEditFragment : Fragment() {
    lateinit var card: Card
    var multipleOption: MultipleOption? = null
    lateinit var binding: FragmentCardEditBinding
    private val executor = Executors.newSingleThreadExecutor()
    lateinit var question: String
    lateinit var answer: String
    private lateinit var deckId: String
    var options= mutableListOf<String>()
    private val viewModel by lazy {
        ViewModelProvider(this)[CardEditViewModel::class.java]
    }
    @Suppress("UNCHECKED_CAST")
    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        binding = DataBindingUtil.inflate(
            inflater,
            R.layout.fragment_card_edit,
            container,
            false
        )
        val args = CardEditFragmentArgs.fromBundle(requireArguments())
        viewModel.loadCardId(args.cardId)
        val decksID = mutableListOf<String>()
        val decksName = mutableListOf<String>()
        viewModel.card.observe(viewLifecycleOwner) {
            card = it!!
            binding.card = card
            question = card.question
            answer = card.answer
            CardDatabase.getInstance(requireContext()).cardDao.getDecks().observe(viewLifecycleOwner){
                it.forEach {
                    decksName.add(it.name)
                    decksID.add(it.id)
                    if(card.idDeck==it.id){
                        deckId=it.id
                    }
                }
                binding.spinner.adapter = ArrayAdapter(requireContext(), R.layout.spinner_item, decksName)
                binding.spinner.setSelection(decksID.indexOf(deckId))
            }
        }
        options.add(0, "Select")
        binding.spinner2.adapter = ArrayAdapter(requireContext(), R.layout.spinner_item, options)

        viewModel.mult.observe(viewLifecycleOwner){
            multipleOption=it

            if(multipleOption!=null){
                options = multipleOption!!.options.toMutableList()
                options.add(0, "Select")
                binding.spinner2.adapter = ArrayAdapter(requireContext(), R.layout.spinner_item, options)
                binding.spinner2.setSelection(0)
            }

        }





        binding.spinner.onItemSelectedListener = object : AdapterView.OnItemSelectedListener{
            override fun onNothingSelected(parent: AdapterView<*>?) {

            }

            override fun onItemSelected(parent: AdapterView<*>?, view: View?, position: Int, id: Long) {
                card.idDeck=decksID[position]
            }

        }

        binding.spinner2.onItemSelectedListener = object : AdapterView.OnItemSelectedListener{
            override fun onNothingSelected(parent: AdapterView<*>?) {

            }
            override fun onItemSelected(parent: AdapterView<*>?, view: View?, position: Int, id: Long) {
                if(position!=0){
                    val aux = binding.spinner2.adapter as ArrayAdapter<String>
                    aux.remove(aux.getItem(position))
                    //options.removeAt(position)
                    aux.notifyDataSetChanged()
                    binding.spinner2.setSelection(0)
                }


            }

        }
        binding.optButtom.setOnClickListener {
            val aux = binding.spinner2.adapter as ArrayAdapter<String>
            aux.add(binding.optEditText.text.toString())
            aux.notifyDataSetChanged()
        }
        binding.removeEditButtom.setOnClickListener {
            executor.execute{
                if(multipleOption!=null){
                    CardDatabase.getInstance(requireContext()).cardDao.delMult(
                        multipleOption = multipleOption!!
                    )
                }

                CardDatabase.getInstance(requireContext()).cardDao.delCard(
                    card = card
                )
            }
            findNavController().popBackStack()
        }

        return binding.root
    }

    override fun onStart() {
        super.onStart()

        val questionTextWatcher = object : TextWatcher {
            override fun beforeTextChanged(s: CharSequence?, start: Int, count: Int, after: Int) {

            }

            override fun onTextChanged(s: CharSequence?, start: Int, before: Int, count: Int) {
                card.question = s.toString()
            }

            override fun afterTextChanged(s: Editable?) {

            }
        }
        binding.questionEditText.addTextChangedListener(questionTextWatcher)

        val answerTextWatcher = object : TextWatcher {
            override fun beforeTextChanged(s: CharSequence?, start: Int, count: Int, after: Int) {

            }

            override fun onTextChanged(s: CharSequence?, start: Int, before: Int, count: Int) {
                card.answer = s.toString()
            }

            override fun afterTextChanged(s: Editable?) {

            }
        }
        binding.answerEditText.addTextChangedListener(answerTextWatcher)

        binding.acceptEditButtom.setOnClickListener {
            executor.execute{
                    CardDatabase.getInstance(requireContext()).cardDao.updateCard(
                        card = card
                )
                if(options.size>1){
                    options.removeAt(0)
                    if(multipleOption==null){
                        val aux = MultipleOption(question =  card.question,
                            answer =  card.answer,
                            idDeck = card.idDeck,
                            date = card.date,
                            id = card.id,
                            quality = card.quality,
                            repetitions = card.repetitions,
                            interval = card.interval,
                            nextPracticeDate = card.nextPracticeDate,
                            easiness = card.easiness,
                            options = options
                        )
                        multipleOption=aux
                    }


                    CardDatabase.getInstance(requireContext()).cardDao.addMult(
                        multipleOption = multipleOption!!
                    )
                }else{
                    if(multipleOption!=null){
                        CardDatabase.getInstance(requireContext()).cardDao.delMult(
                            multipleOption = multipleOption!!
                        )
                    }
                }


            }
            it.findNavController()
                    .navigate(R.id.action_cardEditFragment_to_cardListFragment2)
        }
        binding.cancelEditButtom.setOnClickListener { view ->
            /*card.answer=this.answer
            card.question=this.question
            card.idDeck=this.deckId*/
            view.findNavController()
                .navigate(R.id.action_cardEditFragment_to_cardListFragment2)
        }
    }
}