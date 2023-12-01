package albertgustavsson.adventofcode.y2023.d01

import java.io.File

val digitsTranslation = mapOf(
        Pair("1", "1"), Pair("2", "2"), Pair("3", "3"), Pair("4", "4"), Pair("5", "5"), Pair("6", "6"), Pair("7", "7"), Pair("8", "8"), Pair("9", "9"),
        Pair("one", "1"), Pair("two", "2"), Pair("three", "3"), Pair("four", "4"), Pair("five", "5"), Pair("six", "6"), Pair("seven", "7"), Pair("eight", "8"), Pair("nine", "9"))

fun main(args:Array<String>) {
    if (args.size != 2) throw IllegalArgumentException("Required arguments: <part> <inputFileName>")
    val part = args[0].toInt()
    val inputFileName = args[1]

    val validDigits: List<String> = when (part) {
        1 -> digitsTranslation.keys.filter { it.length == 1 && it[0].isDigit() }
        2 -> digitsTranslation.keys.toList()
        else -> throw IllegalArgumentException("Part 1 or 2?")
    }

    val sum = File(inputFileName).bufferedReader().lines().map { line ->
        val firstDigit = digitsTranslation.getValue(line.findAnyOf(validDigits)!!.second)
        val lastDigit = digitsTranslation.getValue(line.findLastAnyOf(validDigits)!!.second)
        (firstDigit + lastDigit).toInt()
    }.reduce { i, j -> i + j }.get()
    println(sum)
}
