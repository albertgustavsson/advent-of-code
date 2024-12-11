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

    val startTime = System.currentTimeMillis()
    val numberOfBLinks = if (part == 1) 25 else 40

    val newStones = stonesAfterBlinks(stones, numberOfBLinks)

    println("Took ${System.currentTimeMillis() - startTime} ms")

    println(newStones.size)
}

fun stonesAfterBlinks(stones: List<Long>, blinks: Int): List<Long> {
    return if (blinks >= 1) {
        stonesAfterBlinks(stones.flatMap { stone ->
            if (stone == 0L ) {
                listOf(1)
            } else if (stone.toString().length % 2 == 0) {
                val firstHalf = stone.toString().substring(0, stone.toString().length/2).toLong()
                val secondHalf = stone.toString().substring(stone.toString().length/2).toLong()
                listOf(firstHalf, secondHalf)
            } else {
                listOf(stone * 2024)
            }
        }, blinks-1)
    } else {
        stones
    }
}
