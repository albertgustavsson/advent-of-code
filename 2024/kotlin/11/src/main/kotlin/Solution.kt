package albertgustavsson.adventofcode.y2024.d11

import java.io.File

val resultCache: MutableMap<Pair<Long, Int>, Long> = mutableMapOf()

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
    val numberOfBLinks = if (part == 1) 25 else 75

    val result = stones.map { stone -> stonesAfterBlinks(stone, numberOfBLinks) }.sum()

    println("Took ${System.currentTimeMillis() - startTime} ms")

    println(result)
}

fun stonesAfterBlinks(stone: Long, blinks: Int): Long {
    return resultCache.getOrPut(Pair(stone, blinks)) {
        if (blinks >= 1) {
            if (stone == 0L) {
                stonesAfterBlinks(1, blinks - 1)
            } else if (stone.toString().length % 2 == 0) {
                val firstHalf = stone.toString().substring(0, stone.toString().length / 2).toLong()
                val secondHalf = stone.toString().substring(stone.toString().length / 2).toLong()

                stonesAfterBlinks(firstHalf, blinks - 1) + stonesAfterBlinks(secondHalf, blinks - 1)
            } else {
                stonesAfterBlinks(stone * 2024, blinks - 1)
            }
        } else {
            1
        }
    }
}
