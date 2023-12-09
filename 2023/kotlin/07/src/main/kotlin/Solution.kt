package albertgustavsson.adventofcode.y2023.d07

import java.io.File

// Index is card rank
val cardStrengths = listOf('2','3','4','5','6','7','8','9','T','J','Q','K','A')

fun main(args: Array<String>) {
    require(args.size == 2) { throw IllegalArgumentException("Required arguments: <part> <inputFileName>") }
    val part = args[0].toInt()
    val inputFileName = args[1]

    val hands: List<Pair<String, Int>> = File(inputFileName).bufferedReader().lines().map { line ->
        val handAndBid = line.split("\\s+".toRegex())
        val hand = handAndBid[0]
        val bid = handAndBid[1].toInt()
        Pair(hand, bid)
    }.toList()

    val handsSortedByRank = hands.sortedWith { h1, h2 ->
        val hand1CardFrequencies = h1.first.groupingBy { it }.eachCount().toList().sortedBy { (_, value) -> value}.reversed()
        val hand2CardFrequencies = h2.first.groupingBy { it }.eachCount().toList().sortedBy { (_, value) -> value}.reversed()
        val hand1MostFrequent = hand1CardFrequencies[0]
        val hand1SecondMostFrequent = hand1CardFrequencies.getOrNull(1)
        val hand2MostFrequent = hand2CardFrequencies[0]
        val hand2SecondMostFrequent = hand2CardFrequencies.getOrNull(1)
        if (hand1MostFrequent.second > hand2MostFrequent.second) { // Hand 1 is stronger (more equal cards)
            1
        } else if (hand1MostFrequent.second == hand2MostFrequent.second) {
            if (hand1SecondMostFrequent!!.second > hand2SecondMostFrequent!!.second) { // Hand 1 is stronger (more equal cards)
                1
            } else if (hand1SecondMostFrequent.second == hand2SecondMostFrequent.second) {
                // Find first different card
                var firstDifferentIndex = -1
                for (i in 0..4) {
                    if (h1.first[i] != h2.first[i]) {
                        firstDifferentIndex = i
                        break
                    }
                }
                val hand1Strengths = h1.first.map { cardStrengths.indexOf(it) }.toList()
                val hand2Strengths = h2.first.map { cardStrengths.indexOf(it) }.toList()
                if (hand1Strengths[firstDifferentIndex] > hand2Strengths[firstDifferentIndex]) { // Hand 1 is stronger
                    1
                } else { // Hand 2 must be stronger (they cannot be equal)
                    -1
                }
            } else { // Hand 2 is stronger
                -1
            }
        } else { // Hand 2 is stronger
            -1
        }
    }
    val winnings = handsSortedByRank.mapIndexed { index, handAndBid -> (index+1)*handAndBid.second }.reduce(Int::plus)

    println(winnings)
}
