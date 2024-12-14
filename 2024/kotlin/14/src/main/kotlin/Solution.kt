package albertgustavsson.adventofcode.y2024.d14

import java.io.File

fun main(args:Array<String>) {
    require (args.size == 2) { throw IllegalArgumentException("Required arguments: <part> <inputFileName>") }
    val part = args[0].toInt()
    val inputFileName = args[1]

    val robots: List<Pair<Pair<Int, Int>, Pair<Int, Int>>> = File(inputFileName).bufferedReader().lines().map { line ->
        val parts = line.split("\\s+".toRegex())
        val position: Pair<Int, Int> = parts[0].split('=')[1].split(',').map { s -> s.trim().toInt() }.zipWithNext().first()
        val velocity: Pair<Int, Int> = parts[1].split('=')[1].split(',').map { s -> s.trim().toInt() }.zipWithNext().first()
        Pair(position, velocity)
    }.toList()

    val roomSize = Pair(101, 103)
    val border = Pair(roomSize.first / 2, roomSize.second / 2)
    val time = 100
    val endPositions = robots.map { robot ->
        robot.first.plus(robot.second.multiplyBy(time)).positiveModulo(roomSize)
    }.toList()

    val robotsByQuadrant = endPositions.groupBy { position ->
        if (position.first < border.first && position.second < border.second) 1
        else if (position.first > border.first && position.second < border.second) 2
        else if (position.first < border.first && position.second > border.second) 3
        else if (position.first > border.first && position.second > border.second) 4
        else 0
    }

    val result = robotsByQuadrant.filterNot { entry -> entry.key == 0 }.values.map { positions -> positions.size }.reduce { acc, i -> acc * i }

    println(result)
}

private fun Pair<Int, Int>.plus(pair: Pair<Int, Int>): Pair<Int, Int> {
    return Pair(first + pair.first, second + pair.second)
}

private fun Pair<Int, Int>.multiplyBy(scalar: Int): Pair<Int, Int> {
    return Pair(first * scalar, second * scalar)
}

private fun Pair<Int, Int>.positiveModulo(pair: Pair<Int, Int>): Pair<Int, Int> {
    return Pair((first % pair.first + pair.first) % pair.first, (second % pair.second + pair.second) % pair.second)
}
