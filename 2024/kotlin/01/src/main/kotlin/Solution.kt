package albertgustavsson.adventofcode.y2024.d01

import java.io.File
import kotlin.math.abs

fun main(args:Array<String>) {
    require (args.size == 2) { throw IllegalArgumentException("Required arguments: <part> <inputFileName>") }
    val part = args[0].toInt()
    val inputFileName = args[1]

    val leftList: MutableList<Int> = mutableListOf()
    val rightList: MutableList<Int> = mutableListOf()

    File(inputFileName).bufferedReader().lines().forEach { line ->
        val parts = line.split("\\s+".toRegex())
        leftList.add(parts[0].toInt())
        rightList.add(parts[1].toInt())
    }

    if (part == 1) {
        val rightListSorted = rightList.sorted()

        val totalDistances: Int = leftList.sorted().mapIndexed { index, i ->
            abs(i-rightListSorted[index])
        }.sum()
        println(totalDistances)
    } else {
        val similarityScore: Int = leftList.sumOf { i ->
            i * rightList.count { it == i }
        }
        println(similarityScore)
    }
}
