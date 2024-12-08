package albertgustavsson.adventofcode.y2024.d08

import java.io.File

fun main(args:Array<String>) {
    require (args.size == 2) { throw IllegalArgumentException("Required arguments: <part> <inputFileName>") }
    val part = args[0].toInt()
    val inputFileName = args[1]

    val grid: List<List<Char>> = File(inputFileName).bufferedReader().lines().map { line -> line.toMutableList() }.toList()

    val antiNodes: MutableSet<Pair<Int, Int>> = mutableSetOf()

    grid.forEachIndexed { row, chars ->
        chars.forEachIndexed { column, char ->
            if (char.isLetterOrDigit()) {
                val thisAntenna = Pair(row, column)
                val otherAntennaPositions: List<Pair<Int, Int>> = grid.flatMapIndexed { r, chars ->
                    chars.mapIndexed { c, f -> if (f == char) Pair(r, c) else null } }.filterNotNull().filter { pos -> pos != thisAntenna }
                otherAntennaPositions.forEach { otherAntenna ->
                    val offset = otherAntenna.minus(thisAntenna)
                    if (part == 1) {
                        val antiNode = thisAntenna.plus(offset.times(2))
                        if (isInMap(grid, antiNode)) {
                            antiNodes.add(antiNode)
                        }
                    } else {
                        var antiNode = thisAntenna.plus(offset.times(1))
                        while (isInMap(grid, antiNode)) {
                            antiNodes.add(antiNode)
                            antiNode = antiNode.plus(offset)
                        }
                    }
                }
            }
        }
    }

    println(antiNodes.size)
}

private fun Pair<Int, Int>.minus(pair: Pair<Int, Int>): Pair<Int, Int> {
    return Pair(first - pair.first, second - pair.second)
}

private fun Pair<Int, Int>.plus(pair: Pair<Int, Int>): Pair<Int, Int> {
    return Pair(first + pair.first, second + pair.second)
}

private fun Pair<Int, Int>.times(scalar: Int): Pair<Int, Int> {
    return Pair(first *scalar, second * scalar)
}

fun isInMap(grid: List<List<Char>>, position: Pair<Int, Int>): Boolean {
    return position.first in grid.indices && position.second in grid.first().indices
}
