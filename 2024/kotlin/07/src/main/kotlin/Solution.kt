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

        val operators = if (part == 1) { listOf("+", "*") } else { listOf("+", "*", "||") }
        val possibleOperatorSequences: List<List<String>> = generatePossibleSequences(numbers.size - 1, operators)
        possibleOperatorSequences.any { seq -> evaluateEquation(numbers, seq) == testValue }
    }
    println(canBeMadeTrue.map { eq -> eq.first }.sum())
}

fun evaluateEquation(numbers: List<Long>, seq: List<String>): Long {
    var result = numbers.first()

    seq.forEachIndexed { index, op ->
        if (op == "+") result += numbers[index + 1]
        else if (op == "*") result *= numbers[index + 1]
        else if (op == "||") result = (result.toString()+numbers[index + 1].toString()).toLong()
    }

    return result
}

fun generatePossibleSequences(length: Int, operators: List<String>): List<List<String>> {
    val permutations: MutableList<List<String>> = mutableListOf()

    if (length == 0)
        return listOf(listOf())

    operators.forEach { op ->
        val possibleShorterSequences = generatePossibleSequences(length-1, operators)
        possibleShorterSequences.forEach { seq ->
            permutations.add(listOf(op) + seq) }
        }

    return permutations
}
