package albertgustavsson.adventofcode.y2024.d03

import java.io.File

fun main(args:Array<String>) {
    require (args.size == 2) { throw IllegalArgumentException("Required arguments: <part> <inputFileName>") }
    val part = args[0].toInt()
    val inputFileName = args[1]

    val fileContents: String = File(inputFileName).bufferedReader().readText()
    val mulMatches = "mul\\([0-9]+,[0-9]+\\)".toRegex().findAll(fileContents)

    val dosAndDonts: Sequence<MatchResult> = "do(n't)?\\(\\)".toRegex().findAll(fileContents)
    println("dosAndDonts: ${dosAndDonts.map { match -> match.value }.toList()}")

    val enabledMulMatches = mulMatches.filter { match ->
        val lastDoOrDont = dosAndDonts.lastOrNull { doOrDont -> doOrDont.range.last < match.range.first }
        val enabled: Boolean = lastDoOrDont?.value?.equals("do()")?:true
        enabled
    }

    println("Enabled muls: ${enabledMulMatches.map { match -> match.value }.toList()}")

    val mulInstructions: List<String> = (if (part == 1) mulMatches else enabledMulMatches).map { match -> match.value }.toList()

    val multiplicationResults: List<Int> = mulInstructions.map { mulInstruction ->
        val firstMatch = "[0-9]+".toRegex().find(mulInstruction, 0)
        val secondMatch = firstMatch!!.next()
        val firstNumber: Int = firstMatch.value.toInt()
        val secondNumber: Int = secondMatch!!.value.toInt()
        firstNumber * secondNumber
    }

    println(multiplicationResults.sum())
}
