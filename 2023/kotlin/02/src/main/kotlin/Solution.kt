package albertgustavsson.adventofcode.y2023.d02

import java.io.File

val maxNumberPerColor = mapOf(Pair("red", 12), Pair("green", 13), Pair("blue", 14))

fun main(args:Array<String>) {
    if (args.size != 2) throw IllegalArgumentException("Required arguments: <part> <inputFileName>")
    val part = args[0].toInt()
    val inputFileName = args[1]

    val sum = File(inputFileName).bufferedReader().lines().map { line ->
        val parts = line.split(": ")
        val gameId = parts[0].split(" ")[1].toInt()
        val revealings = parts[1].split("; ")
        var gameValid = true
        for (revealing in revealings) {
            val cubes = revealing.split(", ")
            for (cube in cubes) {
                val x = cube.split(" ")
                val color = x[1]
                val number = x[0].toInt()
                if (number > maxNumberPerColor.getValue(color)) gameValid = false
            }
        }
        if (gameValid) {
            gameId
        } else {
            0
        }
    }.reduce { i, j -> i + j }.get()

    println(sum)
}
