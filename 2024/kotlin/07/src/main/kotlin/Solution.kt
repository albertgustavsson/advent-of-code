package albertgustavsson.adventofcode.y2024.d07

import java.io.File

fun main(args:Array<String>) {
    require (args.size == 2) { throw IllegalArgumentException("Required arguments: <part> <inputFileName>") }
    val part = args[0].toInt()
    val inputFileName = args[1]

    val equations: List<Pair<Long, List<Long>>> = File(inputFileName).bufferedReader().lines().map { line ->
        val s = line.split(":\\s*".toRegex())
        val split = s.get(1).split("\\s+".toRegex())
        val numbers = split.map { i -> i.toLong() }.toList()
        val testValue = s.first().toLong()
        Pair(testValue, numbers)
    }.toList()

    val canBeMadeTrue = equations.filter { eq ->
        val testValue = eq.first
        val numbers = eq.second

        val possibleOperatorSequences: List<List<Char>> = generatePossibleSequences(numbers.size - 1)

        possibleOperatorSequences.any { seq -> evaluateEquation(numbers, seq) == testValue }
    }
    println(canBeMadeTrue.map { eq -> eq.first }.sum())
}

fun evaluateEquation(numbers: List<Long>, seq: List<Char>): Long {
    var result = numbers.first()

    seq.forEachIndexed { index, c ->
        if (c == '+') result += numbers[index + 1]
        else if (c == '*') result *= numbers[index + 1]
    }

    return result
}

fun generatePossibleSequences(length: Int): List<List<Char>> {
    val permutations: MutableList<List<Char>> = mutableListOf()
    val operators = listOf('+', '*')

    if (length == 0)
        return listOf(listOf())

    operators.forEach { c ->
        val possibleShorterSequences = generatePossibleSequences(length-1)
        possibleShorterSequences.forEach { seq ->
            permutations.add(listOf(c) + seq) }
        }

    return permutations
}
