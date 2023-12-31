package albertgustavsson.adventofcode.y2023.d04

import java.io.File
import kotlin.math.max

fun main(args:Array<String>) {
    require (args.size == 2) { throw IllegalArgumentException("Required arguments: <part> <inputFileName>") }
    val part = args[0].toInt()
    val inputFileName = args[1]

    val futureCopies = mutableListOf<Int>()
    val sum = File(inputFileName).bufferedReader().lines().map { line ->
        val numberLists = line.split(':')[1].split('|')
        val winningNumbers = numberLists[0].trim().split("\\s+".toRegex()).map { it.toInt() }
        val numbersYouHave = numberLists[1].trim().split("\\s+".toRegex()).map { it.toInt() }
        val matches: Int = winningNumbers.toSet().intersect(numbersYouHave.toSet()).count()
        if (part == 1) {
            val points = Math.pow(2.0, (matches - 1).toDouble()).toInt()
            points
        } else {
            val additionalCopies: Int = futureCopies.removeFirstOrNull() ?: 0
            val totalCopies = 1 + additionalCopies
            futureCopies.addAll(List(max(matches - futureCopies.size, 0)) { 0 })
            for (i in 0..<matches) {
                futureCopies[i] += totalCopies
            }
            totalCopies
        }
    }.reduce(Int::plus).get()

    println(sum)
}
