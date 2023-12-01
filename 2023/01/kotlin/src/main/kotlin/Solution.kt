package albertgustavsson.adventofcode

import java.io.FileReader

fun main(args:Array<String>) {
    val inputFileName = args[0]
    val fr = FileReader(inputFileName)
    val lines = fr.readLines()
    val numbers = mutableListOf<Int>()
    for (line in lines) {
        val digits: String = line.filter { it.isDigit() }
        numbers.add((digits.substring(0,1) + digits.substring(digits.length-1,digits.length)).toInt())
    }
    val sum: Int = numbers.stream().reduce { i: Int, j: Int -> i + j }.get()
    println(sum)
}
