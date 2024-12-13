package albertgustavsson.adventofcode.y2024.d13

import java.io.File

fun main(args:Array<String>) {
    require (args.size == 2) { throw IllegalArgumentException("Required arguments: <part> <inputFileName>") }
    val part = args[0].toInt()
    val inputFileName = args[1]

    val fileContents: String = File(inputFileName).bufferedReader().readText()
    val machines = fileContents.split("\r?\n\\s*\r?\n".toRegex())
    val pressCounts = machines.map { machine ->
        val lines = machine.split("\r?\n".toRegex())
        val buttonA: Pair<Long, Long> = lines[0].split(':')[1].split(',').map { s -> s.trim().split('+')[1].toLong() }.zipWithNext().first()
        val buttonB: Pair<Long, Long> = lines[1].split(':')[1].split(',').map { s -> s.trim().split('+')[1].toLong() }.zipWithNext().first()
        val prize: Pair<Long, Long> = lines[2].split(':')[1].split(',').map { s -> s.trim().split('=')[1].toLong() }
            .map { s ->
                if (part == 1) {
                    s
                } else {
                    s + 10000000000000L
                }
            }.zipWithNext().first()

        val aPresses = (buttonB.second * prize.first - buttonB.first * prize.second) / (buttonA.first * buttonB.second - buttonA.second * buttonB.first)
        val bPresses = (-buttonA.second * prize.first + buttonA.first * prize.second) / (buttonA.first * buttonB.second - buttonA.second * buttonB.first)

        val endpoint = buttonA.multiplyBy(aPresses).plus(buttonB.multiplyBy(bPresses))
        val solution = if (endpoint == prize) Pair(aPresses, bPresses) else null

        if (solution != null && (part != 1 || (solution.first in 0..100 && solution.second in 0..100))) {
            println("A: ${solution.first} presses, B: ${solution.second} presses")
            solution
        } else {
            println("No solution")
            null
        }
    }.filterNotNull()

    val result = pressCounts.map { pair -> pair.first * 3 + pair.second * 1 }.sum()

    println(result)
}

private fun Pair<Long, Long>.plus(pair: Pair<Long, Long>): Pair<Long, Long> {
    return Pair(first + pair.first, second + pair.second)
}

private fun Pair<Long, Long>.multiplyBy(scalar: Long): Pair<Long, Long> {
    return Pair(first * scalar, second * scalar)
}
