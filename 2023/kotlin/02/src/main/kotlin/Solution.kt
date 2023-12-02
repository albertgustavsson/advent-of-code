package albertgustavsson.adventofcode.y2023.d02

import java.io.File
import kotlin.math.max

val maxNumberPerColor = mapOf(Pair("red", 12), Pair("green", 13), Pair("blue", 14))

fun main(args:Array<String>) {
    require (args.size == 2) { throw IllegalArgumentException("Required arguments: <part> <inputFileName>") }
    val part = args[0].toInt()
    val inputFileName = args[1]

    val sum = File(inputFileName).bufferedReader().lines().map { line ->
        val gameAndCubeSets = line.split(": ")
        val gameId = gameAndCubeSets[0].split(" ")[1].toInt()
        val minRequiredCubes = mutableMapOf(Pair("red", 0), Pair("green", 0), Pair("blue", 0))
        for (cubeSet in gameAndCubeSets[1].split("; ")) {
            for (cubeType in cubeSet.split(", ")) {
                val colorAndNumber = cubeType.split(" ")
                val color = colorAndNumber[1]
                val number = colorAndNumber[0].toInt()
                minRequiredCubes[color] = max(minRequiredCubes[color]!!, number)
            }
        }
        if (part == 1) {
            val gameValid = minRequiredCubes.entries.all { (key, value) -> value <= maxNumberPerColor[key]!! }
            if (gameValid) gameId else 0
        } else {
            minRequiredCubes.values.reduce(Int::times)
        }
    }.reduce(Int::plus).get()
    println(sum)
}
