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
        val buttonA: Pair<Int, Int> = lines[0].split(':')[1].split(',').map { s -> s.trim().split('+')[1].toInt() }.zipWithNext().first()
        val buttonB: Pair<Int, Int> = lines[1].split(':')[1].split(',').map { s -> s.trim().split('+')[1].toInt() }.zipWithNext().first()
        val prize: Pair<Int, Int> = lines[2].split(':')[1].split(',').map { s -> s.trim().split('=')[1].toInt() }.zipWithNext().first()

        var solution: Pair<Int, Int>? = null
        for (a in 0..100) {
            for (b in 0..100) {
                if (buttonA.multiplyBy(a).plus(buttonB.multiplyBy(b)) == prize) {
                    solution = Pair(a, b)
                    break
                }
            }
            if(solution != null) break
        }

        if (solution != null) {
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

private fun Pair<Int, Int>.plus(pair: Pair<Int, Int>): Pair<Int, Int> {
    return Pair(first + pair.first, second + pair.second)
}

private fun Pair<Int, Int>.multiplyBy(scalar: Int): Pair<Int, Int> {
    return Pair(first * scalar, second * scalar)
}
