package albertgustavsson.adventofcode

import java.io.FileReader

fun main(args:Array<String>) {
    val part = args[0].toInt()
    val inputFileName = args[1]
    val fr = FileReader(inputFileName)
    val lines = fr.readLines()
    val validDigits: List<String> = if (part == 1) {
        listOf("1", "2", "3", "4", "5", "6", "7", "8", "9")
    } else if (part == 2) {
        listOf("1", "2", "3", "4", "5", "6", "7", "8", "9", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine")
    } else {
        throw IllegalArgumentException("Part 1 or 2?")
    }
    val digitsTranslation = mapOf(Pair("one", "1"), Pair("two", "2"), Pair("three", "3"), Pair("four", "4"), Pair("five", "5"), Pair("six", "6"), Pair("seven", "7"), Pair("eight", "8"), Pair("nine", "9"))
    val numbers = mutableListOf<Int>()
    for (line in lines) {
        var tempLine = line
        var firstDigit = ""
        while (tempLine.isNotEmpty()) {
            var foundDigit = false
            for (validDigit in validDigits) {
                if (tempLine.startsWith(validDigit)) {
                    foundDigit = true
                    firstDigit = digitsTranslation.getOrElse(validDigit) { validDigit }
                    break
                }
            }
            if (foundDigit) {
                break
            } else {
                tempLine = tempLine.substring(1)
            }
        }
        tempLine = line
        var lastDigit = ""
        while (tempLine.isNotEmpty()) {
            var foundDigit = false
            for (validDigit in validDigits) {
                if (tempLine.endsWith(validDigit)) {
                    foundDigit = true
                    lastDigit = digitsTranslation.getOrElse(validDigit) { validDigit }
                    break
                }
            }
            if (foundDigit) {
                break
            } else {
                tempLine = tempLine.substring(0,tempLine.length-1)
            }
        }
        val number = (firstDigit + lastDigit).toInt()
        numbers.add(number)
    }
    val sum: Int = numbers.stream().reduce { i: Int, j: Int -> i + j }.get()
    println(sum)
}
