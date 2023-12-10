package albertgustavsson.adventofcode.y2023.d09

import java.io.File

fun main(args: Array<String>) {
    require(args.size == 2) { throw IllegalArgumentException("Required arguments: <part> <inputFileName>") }
    val part = args[0].toInt()
    val inputFileName = args[1]

    val sum = File(inputFileName).bufferedReader().lines().map { line ->
        val numbers = line.split("\\s+".toRegex()).map(String::toInt).toMutableList()
        var steps: MutableList<MutableList<Int>> = mutableListOf(numbers)
        var temps = numbers
        while (!temps.all { it == 0 }) {
            temps = temps.windowed(size = 2, transform = { neighbors ->  neighbors[1] - neighbors[0]}).toMutableList()
            steps.add(temps)
        }
        // Temps is now all zeroes. Add one zero and extrapolate back
        var diff = 0
        if (part == 1) {
            for (i in steps.size-1 downTo  0) {
                diff = steps[i].last() + diff
                steps[i].add(diff)
            }
            steps.first().last()
        } else {
            for (i in steps.size-1 downTo  0) {
                diff = steps[i].first() - diff
                steps[i].add(0, diff)
            }
            steps.first().first()
        }
    }.reduce(Int::plus).get()

    println(sum)
}
