package albertgustavsson.adventofcode.y2024.d03

import java.io.File

fun main(args:Array<String>) {
    require (args.size == 2) { throw IllegalArgumentException("Required arguments: <part> <inputFileName>") }
    val part = args[0].toInt()
    val inputFileName = args[1]

    val fileContents: String = File(inputFileName).bufferedReader().readText()
    val mulInstructions: List<String> = "mul\\([0-9]+,[0-9]+\\)".toRegex().findAll(fileContents).map { match -> match.value }.toList()

    val multiplicationResults: List<Int> = mulInstructions.map { mulInstruction ->
        val firstMatch = "[0-9]+".toRegex().find(mulInstruction, 0)
        val secondMatch = firstMatch!!.next()
        val firstNumber: Int = firstMatch.value.toInt()
        val secondNumber: Int = secondMatch!!.value.toInt()
        firstNumber * secondNumber
    }

    println(multiplicationResults.sum())
}
