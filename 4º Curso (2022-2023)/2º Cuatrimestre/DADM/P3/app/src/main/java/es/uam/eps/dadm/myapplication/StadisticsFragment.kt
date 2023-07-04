package es.uam.eps.dadm.myapplication

import android.graphics.Color
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.databinding.DataBindingUtil
import androidx.fragment.app.Fragment
import androidx.lifecycle.LiveData
import androidx.lifecycle.ViewModelProvider
import com.github.mikephil.charting.animation.Easing
import com.github.mikephil.charting.data.*
import com.google.android.material.snackbar.Snackbar
import es.uam.eps.dadm.myapplication.database.CardDatabase
import es.uam.eps.dadm.myapplication.databinding.FragmentStatisticsBinding


class StatisticsFragment
    :Fragment(){
    private val viewModel: StatisticsViewModel by lazy {
        ViewModelProvider(this)[StatisticsViewModel::class.java]
    }

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        val binding = DataBindingUtil.inflate<FragmentStatisticsBinding>(
            inflater,
            R.layout.fragment_statistics,
            container,
            false
        )
        binding.viewModel = viewModel
        val barEntriesList = ArrayList<BarEntry>()
        val barEntriesList2 = ArrayList<BarEntry>()
        val cards: LiveData<List<Card>> =CardDatabase.getInstance(context = requireContext()).cardDao.getCards()
        var barDataSet2 = BarDataSet(barEntriesList2, "Cards to Review")
        var barDataSet = BarDataSet(barEntriesList2, "Cards to Review")
        cards.observe(viewLifecycleOwner) {
            StatisticsViewModel.updCardsToReview(it)
            for(i in 0..6) {
                if(StatisticsViewModel.cardsToReview.size>i)
                    barEntriesList.add(BarEntry(i.toFloat(),   StatisticsViewModel.cardsToReview[i]))
            }
            for(i in 0..3) {
                if(StatisticsViewModel.cardsToReviewWeek.size>i)
                    barEntriesList2.add(BarEntry(i.toFloat(),   StatisticsViewModel.cardsToReviewWeek[i]))
            }
            barDataSet2 = BarDataSet(barEntriesList2, "Cards to Review")
            barDataSet = BarDataSet(barEntriesList, "Cards to Review")
            barDataSet.colors = mutableListOf(Color.parseColor("#ff99cc00"))
            barDataSet2.colors = mutableListOf(Color.parseColor("#ffff4444"))
            binding.chart2.data=BarData(barDataSet2)
            binding.chart.data = BarData(barDataSet)

            binding.chart.data.setValueTextSize(15f)
            binding.chart2.data.setValueTextSize(15f)
            binding.chart.legend.isEnabled = false
            binding.chart2.legend.isEnabled = false
            binding.chart.description.isEnabled = false
            binding.chart2.description.isEnabled=false
            binding.chart.xAxis.setDrawGridLines(false)
            binding.chart2.xAxis.setDrawGridLines(false)
            binding.chart.xAxis.setDrawLabels(false)
            binding.chart2.xAxis.setDrawLabels(false)
            binding.chart.xAxis.setDrawLimitLinesBehindData(false)
            binding.chart2.xAxis.setDrawLimitLinesBehindData(false)

            binding.chart.notifyDataSetChanged()
            binding.chart2.notifyDataSetChanged()
            binding.chart.invalidate()
            binding.chart2.invalidate()
        }
        // on belong line we are adding data
        // to our bar entries list
        binding.chart2.data=BarData(barDataSet2)
        binding.chart.data = BarData(barDataSet)
        val pieEntriesList = ArrayList<PieEntry>()
        pieEntriesList.add(PieEntry( viewModel.nEassy.value?.toFloat()?:0f, context?.getString(R.string.easy_button_title)))
        pieEntriesList.add(PieEntry( viewModel.nDoubt.value?.toFloat()?:0f, context?.getString(R.string.doubt_button_title)))
        pieEntriesList.add(PieEntry( viewModel.nDifficult.value?.toFloat()?:0f, context?.getString(R.string.difficult_button_title)))
        val pieDataSet = PieDataSet(pieEntriesList, "")

        val colors =
            mutableListOf( Color.parseColor("#ff99cc00"), Color.parseColor("#ffffbb33"), Color.parseColor("#ffff4444"))

        pieDataSet.colors = colors
        pieDataSet.setValueTextColors(mutableListOf(Color.WHITE))
        /*for(i in 0..6) {
            if(StatisticsViewModel.cardsToReview.size>i)
                barEntriesList.add(BarEntry(i.toFloat(),   StatisticsViewModel.cardsToReview[i]))
        }
        for(i in 0..3) {
            if(StatisticsViewModel.cardsToReviewWeek.size>i)
                barEntriesList2.add(BarEntry(i.toFloat(),   StatisticsViewModel.cardsToReviewWeek[i]))
        }*/



        binding.pieChart.data = PieData(pieDataSet)
        binding.pieChart.data.setValueTextSize(15f)
        binding.pieChart.legend.textSize = 15f
        binding.pieChart.setEntryLabelTextSize(0f)
        binding.pieChart.animateY(1400, Easing.EaseInOutQuad)
        binding.invalidateAll()
        binding.apply { changeView.setOnClickListener {
            viewModel?.viewGrap1 = !((viewModel?.viewGrap1)?:false)
            invalidateAll()
        } }

        viewModel.decks.observe(viewLifecycleOwner){
            var mess = ""
            for(aux in it){
                mess+="The deck: " + aux.deck.name + ", has " + aux.cards.size + " cards\n"
            }
            val aux = Snackbar.make(requireView(),mess,Snackbar.LENGTH_LONG)
            aux.show()

        }


        return binding.root
    }

}