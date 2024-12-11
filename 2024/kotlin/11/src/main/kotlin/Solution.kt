package albertgustavsson.adventofcode.y2024.d11

import java.io.File

fun main(args:Array<String>) {
    require (args.size == 2) { throw IllegalArgumentException("Required arguments: <part> <inputFileName>") }
    val part = args[0].toInt()
    val inputFileName = args[1]

    var stones: List<Long> = File(inputFileName)
        .bufferedReader()
        .readText()
        .split("\\s+".toRegex())
        .filter { s -> s.isNotBlank() }
        .map { s -> s.toLong() }
        .toMutableList()

    val numberOfBLinks = if (part == 1) 25 else 75
    for (i in 1..numberOfBLinks) {
        val newStones = stones.flatMap { stone ->
            if (stone == 0L ) {
                listOf(1)
            } else if (stone.toString().length % 2 == 0) {
                val firstHalf = stone.toString().substring(0, stone.toString().length/2).toLong()
                val secondHalf = stone.toString().substring(stone.toString().length/2).toLong()
                listOf(firstHalf, secondHalf)
            } else {
                listOf(stone * 2024)
            }
        }
        stones = newStones
    }

    println(stones.size)
}
