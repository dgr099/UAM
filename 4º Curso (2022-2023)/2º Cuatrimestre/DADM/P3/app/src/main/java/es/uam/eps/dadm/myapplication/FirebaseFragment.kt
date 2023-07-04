package es.uam.eps.dadm.myapplication
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Toast
import androidx.fragment.app.Fragment
import com.google.firebase.auth.FirebaseAuth
import com.google.firebase.database.DataSnapshot
import com.google.firebase.database.DatabaseError
import com.google.firebase.database.FirebaseDatabase
import com.google.firebase.database.ValueEventListener
import es.uam.eps.dadm.myapplication.database.CardDatabase
import es.uam.eps.dadm.myapplication.databinding.FragmentFirebaseBinding
import java.util.concurrent.Executors

@Suppress("DEPRECATION", "UNCHECKED_CAST")
class FirebaseFragment
    :Fragment(){
    private val executor = Executors.newSingleThreadExecutor()
    val database = FirebaseDatabase.getInstance()
    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        val binding = FragmentFirebaseBinding.inflate(
            inflater,
            container,
            false
        )
        binding.signOutButton.setOnClickListener {
            FirebaseAuth.getInstance().signOut()
            requireActivity().onBackPressed()
        }
        binding.uploadButton.setOnClickListener {
            executor.execute{
                val user = FirebaseAuth.getInstance().currentUser?.uid
                val userRef = database.getReference(user.toString())
                var cards = CardDatabase.getInstance(requireContext()).cardDao.getCardsToUpload()
                var cardsMap = HashMap<String, Any>()
                for (item in cards) {
                    cardsMap[item.id] = item
                }
                userRef.child("Cards").setValue(cardsMap)
                cards = CardDatabase.getInstance(requireContext()).cardDao.getCardsToUploadMult()
                cardsMap = HashMap<String, Any>()
                for (item in cards) {
                    cardsMap[item.id] = item
                }
                userRef.child("CardsMult").setValue(cardsMap)
                val decks = CardDatabase.getInstance(requireContext()).cardDao.getDecksToUpload()
                val decksMap = HashMap<String, Any>()
                for (item in decks) {
                    decksMap[item.id] = item
                }
                userRef.child("Decks").setValue(decksMap)
            }
            Toast.makeText(it.context, "Finish Upload", Toast.LENGTH_SHORT).show()
        }

        binding.downloadButton.setOnClickListener {

                val user = FirebaseAuth.getInstance().currentUser?.uid
                val cardsRef = database.getReference(user.toString()).child("Cards")
            val cardsMultRef = database.getReference(user.toString()).child("CardsMult")
            val decksRef = database.getReference(user.toString()).child("Decks")
            decksRef.addValueEventListener(object : ValueEventListener {
                override fun onDataChange(dataSnapshot: DataSnapshot) {
                    for (childSnapshot in dataSnapshot.children) {
                        val value = childSnapshot.value as Map<String, Any>
                        val aux = Deck(
                            id = value["id"].toString(),
                            name = value["name"].toString()
                        )
                        executor.execute{
                            CardDatabase.getInstance(requireContext()).cardDao.addDeck(aux)
                        }
                    }
                    Toast.makeText(it.context, "Finish Download", Toast.LENGTH_SHORT).show()
                }
                override fun onCancelled(error: DatabaseError) {
                }
            })
            cardsRef.addValueEventListener(object : ValueEventListener {
                override fun onDataChange(dataSnapshot: DataSnapshot) {
                    for (childSnapshot in dataSnapshot.children) {
                        val value = childSnapshot.value as Map<String, Any>
                        val aux = Card(
                            question =  value["question"].toString(),
                            answer =  value["answer"].toString(),
                            idDeck = value["idDeck"].toString(),
                            date = value["date"].toString(),
                            id = value["id"].toString(),
                            quality = value["quality"].toString().toInt(),
                            repetitions = value["repetitions"].toString().toInt(),
                            interval = value["interval"].toString().toLong(),
                            nextPracticeDate = value["nextPracticeDate"].toString(),
                            easiness = value["easiness"].toString().toDouble(),
                        )
                        executor.execute{
                            CardDatabase.getInstance(requireContext()).cardDao.addCard(aux)
                        }
                    }
                    Toast.makeText(it.context, "Finish Download", Toast.LENGTH_SHORT).show()
                }
                override fun onCancelled(error: DatabaseError) {
                }
            })
            cardsMultRef.addValueEventListener(object : ValueEventListener {
                    override fun onDataChange(dataSnapshot: DataSnapshot) {
                        for (childSnapshot in dataSnapshot.children) {
                            val value = childSnapshot.value as Map<String, Any>
                            val aux = MultipleOption(
                                question =  value["question"].toString(),
                                answer =  value["answer"].toString(),
                                idDeck = value["idDeck"].toString(),
                                date = value["date"].toString(),
                                id = value["id"].toString(),
                                quality = value["quality"].toString().toInt(),
                                repetitions = value["repetitions"].toString().toInt(),
                                interval = value["interval"].toString().toLong(),
                                nextPracticeDate = value["nextPracticeDate"].toString(),
                                easiness = value["easiness"].toString().toDouble(),
                                options = value["options"] as List<String>
                                )
                            executor.execute{
                                CardDatabase.getInstance(requireContext()).cardDao.addMult(aux)
                                CardDatabase.getInstance(requireContext()).cardDao.addCard(aux)
                            }
                        }
                        Toast.makeText(it.context, "Finish Download", Toast.LENGTH_SHORT).show()
                    }
                    override fun onCancelled(error: DatabaseError) {
                    }
            })

        }
        return binding.root
    }

}