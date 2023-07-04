

import android.content.Context
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.navigation.findNavController
import androidx.recyclerview.widget.RecyclerView
import es.uam.eps.dadm.myapplication.*
import es.uam.eps.dadm.myapplication.database.CardDatabase
import es.uam.eps.dadm.myapplication.databinding.ListItemDeckBinding
import java.time.LocalDateTime
import java.util.concurrent.Executors

class DeckAdapter : RecyclerView.Adapter<DeckAdapter.CardHolder>() {

    var data =  listOf<DeckWithCards>()
    lateinit var binding: ListItemDeckBinding
    lateinit var context: Context
    private val executor = Executors.newSingleThreadExecutor()

    inner class CardHolder(view: View) : RecyclerView.ViewHolder(view){
        private var local = binding
        fun bind(deck: DeckWithCards) {
            local.deck=deck.deck
            val aux: List<Card> = deck.cards
            local.totalCards = aux.size

            local.dueCards=aux.filter{card ->  card.idDeck==deck.deck.id && card.isDue(LocalDateTime.now())}.size

            itemView.setOnClickListener {
                it.findNavController()
                    .navigate(DeckListFragmentDirections.actionDeckListFragmentToStudyDeckFragment(deck.deck.id))
            }

            local.removeButton.setOnClickListener {
                executor.execute {
                    CardDatabase.getInstance(context).cardDao.deleteDecksAndCards(deck.deck)
                    //CardDatabase.getInstance(context).cardDao.deleteDecksAndCards(deck)
                }
                //data.removeAt(absoluteAdapterPosition)
                notifyItemRemoved(absoluteAdapterPosition)
            }
        }

    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): CardHolder {
        val layoutInflater = LayoutInflater.from(parent.context)
        binding = ListItemDeckBinding.inflate(layoutInflater, parent, false)
        context = parent.context
        return CardHolder(binding.root)
    }

    override fun getItemCount() = data.size

    override fun onBindViewHolder(holder: CardHolder, position: Int) {
        holder.apply {
            this.bind(data[position])
        }
    }
}
