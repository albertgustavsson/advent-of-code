package albertgustavsson.adventofcode.y2023.d04

import java.io.File

fun main(args:Array<String>) {
    require (args.size == 2) { throw IllegalArgumentException("Required arguments: <part> <inputFileName>") }
    val part = args[0].toInt()
    val inputFileName = args[1]

    val sum = File(inputFileName).bufferedReader().lines().map { line ->
        val cardAndNumbers = line.split(':')
        val numberLists = cardAndNumbers[1].trim().split('|')
        val winningNumbersList = numberLists[0].trim().replace("\\s+".toRegex(), " ").split(' ')
        val winningNumbers = winningNumbersList.map { it.trim().toInt() }
        val numbersYouHaveList = numberLists[1].trim().replace("\\s+".toRegex(), " ").split(' ')
        val numbersYouHave = numbersYouHaveList.map { it.trim().toInt() }
        val matches: Int = winningNumbers.toSet().intersect(numbersYouHave.toSet()).count()
        val points = Math.pow(2.0, (matches-1).toDouble()).toInt()
        points
    }.reduce(Int::plus).get()

    println(sum)
}
