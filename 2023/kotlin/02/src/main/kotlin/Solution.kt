package albertgustavsson.adventofcode.y2023.d02

import java.io.File
import kotlin.math.max

val maxNumberPerColor = mapOf(Pair("red", 12), Pair("green", 13), Pair("blue", 14))

fun main(args:Array<String>) {
    if (args.size != 2) throw IllegalArgumentException("Required arguments: <part> <inputFileName>")
    val part = args[0].toInt()
    val inputFileName = args[1]

    val sum = File(inputFileName).bufferedReader().lines().map { line ->
        val parts = line.split(": ")
        val gameId = parts[0].split(" ")[1].toInt()
        val revealings = parts[1].split("; ")
        var minRequiredCubes = mutableMapOf(Pair("red", Int.MIN_VALUE), Pair("green", Int.MIN_VALUE), Pair("blue", Int.MIN_VALUE))
        for (revealing in revealings) {
            val cubes = revealing.split(", ")
            for (cube in cubes) {
                val x = cube.split(" ")
                val color = x[1]
                val number = x[0].toInt()
                minRequiredCubes.set(color, max(minRequiredCubes.getValue(color), number))
            }
        }
        if (part == 1) {
            var gameValid = true
            for (entry in maxNumberPerColor) {
                if (minRequiredCubes.getValue(entry.key) > entry.value) gameValid = false
            }
            if (gameValid) {
                gameId
            } else {
                0
            }
        } else {
            var power = 1
            for (value in minRequiredCubes.values) {
                power *= value
            }
            power
        }
    }.reduce { i, j -> i + j }.get()

    println(sum)
}
