package es.uam.eps.dadm.myapplication

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.navigation.findNavController
import androidx.recyclerview.widget.RecyclerView
import es.uam.eps.dadm.myapplication.databinding.ListItemCardBinding

class CardAdapter : RecyclerView.Adapter<CardAdapter.CardHolder>() {

    var data =  listOf<Card>()
    lateinit var binding: ListItemCardBinding

    inner class CardHolder(view: View) : RecyclerView.ViewHolder(view){
        val local = binding

        fun bind(card: Card) {
            if(card is MultipleOption){
                print("jaja")
            }
            local.card=card
            itemView.setOnClickListener {
                it.findNavController()
                    .navigate(CardListFragmentDirections.actionCardListFragmentToCardEditFragment(card.id))

                //Toast.makeText(it.context, card.question, Toast.LENGTH_SHORT).show()
            }

        }


    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): CardHolder {

        val layoutInflater = LayoutInflater.from(parent.context)
        binding = ListItemCardBinding.inflate(layoutInflater, parent, false)
        //binding.expandedInfo.visibility = View.INVISIBLE

        return CardHolder(binding.root)
    }

    override fun getItemCount() = data.size

    override fun onBindViewHolder(holder: CardHolder, position: Int) {

        holder.local.expandButton.setOnClickListener {
            holder.local.card?.expanded = holder.local.card?.expanded==false
            holder.local.card?.question
            holder.local.card?.expanded
            /*if(isExpandable==true){
                holder.local.expandButton.text = "⬇️️"

            }else{
                holder.local.expandButton.text = "⬆️"
            }*/
            notifyItemChanged(position)
        }
        holder.apply {
            this.bind(data[position])
        }

    }
}
