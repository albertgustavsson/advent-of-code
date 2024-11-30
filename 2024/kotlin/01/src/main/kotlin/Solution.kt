package albertgustavsson.adventofcode.y2024.d01

import java.io.File
import kotlin.math.abs

fun main(args:Array<String>) {
    require (args.size == 2) { throw IllegalArgumentException("Required arguments: <part> <inputFileName>") }
    val part = args[0].toInt()
    val inputFileName = args[1]

    val leftList: MutableList<Int> = mutableListOf()
    val rightList: MutableList<Int> = mutableListOf()

    File(inputFileName).bufferedReader().lines().forEach {
        val parts = it.split(" ".toRegex()).filter { it.isNotBlank() }
        leftList.add(parts[0].toInt())
        rightList.add(parts[1].toInt())
    }

    val leftListSorted = leftList.sorted()
    val rightListSorted = rightList.sorted()

    val distances: MutableList<Int> = mutableListOf()

    leftListSorted.forEachIndexed { index, i ->
        distances.add(index, abs(i-rightListSorted[index]))
    }
    val totalDistances = distances.sum()
    println(totalDistances)
}
