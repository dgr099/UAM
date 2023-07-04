package es.uam.eps.dadm.myapplication

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import androidx.databinding.DataBindingUtil
import es.uam.eps.dadm.myapplication.databinding.StudyActivityBinding
import timber.log.Timber
class StudyActivity : AppCompatActivity() {
    lateinit var binding: StudyActivityBinding


    /*private lateinit var binding: StudyActivityBinding
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
        viewModel.update(quality)

        if(viewModel.card==null){
            Toast.makeText(this, "No more cards to study", Toast.LENGTH_SHORT).show()
        }


        binding.invalidateAll()
    }*/

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = DataBindingUtil.setContentView(this, R.layout.study_activity)


        //setContentView(R.layout.activity_main)
        /*binding = DataBindingUtil.setContentView(this, R.layout.study_activity)
        binding.viewModel = viewModel
        binding.apply {
            answerButton.setOnClickListener {
                viewModel?.card?.answered = true
                invalidateAll()
            }
        }
        for(button in 0 until binding.difficultyButtons.size){
            binding.difficultyButtons[button].setOnClickListener(
                listener
            )
        }*/

        Timber.i("onCreate called")

    }


    override fun onStart() {
        super.onStart()
        Timber.i("onStart called")
    }

    override fun onRestoreInstanceState(savedInstanceState: Bundle) {
        super.onRestoreInstanceState(savedInstanceState)
        Timber.i("onRestoreInstanceState called")

    }



    override fun onResume() {
        super.onResume()
        Timber.i("onResume called")
    }

    override fun onPause() {
        super.onPause()
        Timber.i("onPause called")
    }

    override fun onStop() {
        super.onStop()
        Timber.i("onStop called")

    }

    override fun onSaveInstanceState(outState: Bundle) {
        super.onSaveInstanceState(outState)
        Timber.i("onSaveInstanceState called")
    }

    override fun onDestroy() {
        super.onDestroy()
        Timber.i("onDestroy called")
    }


}