package es.uam.eps.dadm.myapplication
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Toast
import androidx.databinding.DataBindingUtil
import androidx.fragment.app.Fragment
import androidx.navigation.NavOptions
import androidx.navigation.findNavController
import com.google.firebase.auth.FirebaseAuth
import es.uam.eps.dadm.myapplication.databinding.FragmentEmailPasswordFragmentBinding

class EmailPasswordFragment
    :Fragment(){
    var reg = false
    var loading = false
    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        val binding = DataBindingUtil.inflate<FragmentEmailPasswordFragmentBinding>(
            inflater,
            R.layout.fragment_email_password_fragment,
            container,
            false
        )
        binding.register = reg
        binding.loading = loading
        binding.registerText.setOnClickListener {
            reg = !reg
            binding.register = reg
            binding.invalidateAll()
        }
        binding.loginButton.setOnClickListener {
            loading = true
            binding.loading = loading
            binding.invalidateAll()
            val email :String= binding.emailEditText.text.toString()
            val pass :String= binding.passwordEditText.text.toString()
            if(email.isEmpty() || pass.isEmpty()){
                Toast.makeText(
                    requireActivity(),
                    R.string.no_eamil_or_pass,
                    Toast.LENGTH_LONG
                ).show()
            }else{
                val auth = FirebaseAuth.getInstance()
                auth.signInWithEmailAndPassword(email, pass)
                    .addOnCompleteListener(requireActivity()) { task ->
                        if (task.isSuccessful) {
                            val navOptions = NavOptions.Builder()
                                .setPopUpTo(it.findNavController().currentDestination?.id ?: -1, true)
                                .build()
                            it.findNavController()
                                .navigate(EmailPasswordFragmentDirections.actionEmailPasswordFragmentToFirebaseFragment(), navOptions)
                        } else {
                            Toast.makeText(requireActivity(), R.string.error_logIn,
                                Toast.LENGTH_SHORT).show()
                        }
                    }
            }
            loading = false
            binding.loading = loading
            binding.invalidateAll()

        }
        binding.registerButton.setOnClickListener {
            loading = true
            binding.loading = loading
            binding.invalidateAll()
            val email :String= binding.registerEmailEditText.text.toString()
            val pass :String= binding.passwordEditTextRegister.text.toString()
            val pass2 :String= binding.passwordEditTextRegisterConfirm.text.toString()
            if(email.isEmpty() || pass.isEmpty() || pass2.isEmpty()){
                Toast.makeText(
                    requireActivity(),
                    R.string.no_eamil_or_pass,
                    Toast.LENGTH_LONG
                ).show()
            }
            else if(pass!=pass2){
                Toast.makeText(
                    requireActivity(),
                    R.string.passwords_no_coincidence,
                    Toast.LENGTH_LONG
                ).show()

            }else{
                FirebaseAuth.getInstance().createUserWithEmailAndPassword(email, pass)
                    .addOnCompleteListener { task ->
                        if (task.isSuccessful) {
                            it.findNavController()
                                .navigate(EmailPasswordFragmentDirections.actionEmailPasswordFragmentToCardListFragment())
                        } else {
                            Toast.makeText(
                                requireActivity(),
                                R.string.error_register,
                                Toast.LENGTH_LONG
                            ).show()
                        }
                    }
            }
            loading = false
            binding.loading = loading
            binding.invalidateAll()
        }


        return binding.root
    }
    /*interface OnTitleFragmentInteractionListener {
        fun onStudy()
    }*/

    /*var listener: OnTitleFragmentInteractionListener? = null
    override fun onAttach(context: Context) {
        super.onAttach(context)
        listener = context as OnTitleFragmentInteractionListener?
    }
    override fun onDetach() {
        super.onDetach()
        listener = null
    }
    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        val binding = DataBindingUtil.inflate<FragmentTitleBinding>(
            inflater,
            R.layout.fragment_title,
            container,
            false)

        binding.cardsTitleTextView.setOnClickListener {
            //startActivity(Intent(activity, StudyActivity::class.java))
            this.listener?.onStudy()

        }

        return binding.root
    }*/

}