package albertgustavsson.adventofcode.y2023.d07

import java.io.File

fun main(args: Array<String>) {
    require(args.size == 2) { throw IllegalArgumentException("Required arguments: <part> <inputFileName>") }
    val part = args[0].toInt()
    val inputFileName = args[1]
    // Index is card rank
    val cardStrengths = if (part == 1)
        listOf('2','3','4','5','6','7','8','9','T','J','Q','K','A')
    else
        listOf('J','2','3','4','5','6','7','8','9','T','Q','K','A')

    val hands: List<Pair<String, Int>> = File(inputFileName).bufferedReader().lines().map { line ->
        val handAndBid = line.split("\\s+".toRegex())
        val hand = handAndBid[0]
        val bid = handAndBid[1].toInt()
        Pair(hand, bid)
    }.toList()

    val handsSortedByRank = hands.sortedWith { h1, h2 ->
        val hand1CardFrequencies: MutableList<Pair<Char, Int>> = h1.first.groupingBy { it }.eachCount().toList().sortedBy { (_, value) -> value}.reversed().toMutableList()
        val hand2CardFrequencies: MutableList<Pair<Char, Int>> = h2.first.groupingBy { it }.eachCount().toList().sortedBy { (_, value) -> value}.reversed().toMutableList()
        if (part == 2) {
            // Remove jokers from the cardFrequencies
            val hand1Jokers: Int = hand1CardFrequencies.firstOrNull { it.first == 'J' }?.second ?: 0
            hand1CardFrequencies.removeAll { it.first == 'J' } // Could make the list empty if the hand contains only jokers
            if (hand1CardFrequencies.isEmpty()) {
                hand1CardFrequencies.add(0, Pair('A', 0))
            }
            hand1CardFrequencies[0] = hand1CardFrequencies[0].copy(second = hand1CardFrequencies[0].second + hand1Jokers)
            val hand2Jokers: Int = hand2CardFrequencies.firstOrNull { it.first == 'J' }?.second ?: 0
            hand2CardFrequencies.removeAll { it.first == 'J' } // Could make the list empty if the hand contains only jokers
            if (hand2CardFrequencies.isEmpty()) {
                hand2CardFrequencies.add(0, Pair('A', 0))
            }
            hand2CardFrequencies[0] = hand2CardFrequencies[0].copy(second = hand2CardFrequencies[0].second + hand2Jokers)
        }
        val hand1MostFrequent = hand1CardFrequencies[0]
        val hand2MostFrequent = hand2CardFrequencies[0]
        val hand1SecondMostFrequent = hand1CardFrequencies.getOrNull(1)
        val hand2SecondMostFrequent = hand2CardFrequencies.getOrNull(1)
        if (hand1MostFrequent.second > hand2MostFrequent.second) { // Hand 1 is stronger (more equal cards)
            1
        } else if (hand1MostFrequent.second == hand2MostFrequent.second) {
            if (hand1SecondMostFrequent == null || hand2SecondMostFrequent == null) {
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
            } else {
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
            }
        } else { // Hand 2 is stronger
            -1
        }
    }
    val winnings = handsSortedByRank.mapIndexed { index, handAndBid -> (index+1)*handAndBid.second }.reduce(Int::plus)

    println(winnings)
}
