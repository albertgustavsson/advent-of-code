package albertgustavsson.adventofcode.y2024.d06

import java.io.File

fun main(args:Array<String>) {
    require (args.size == 2) { throw IllegalArgumentException("Required arguments: <part> <inputFileName>") }
    val part = args[0].toInt()
    val inputFileName = args[1]

    val grid: List<List<Char>> = File(inputFileName).bufferedReader().lines().map { line -> line.toMutableList() }.toList()

    val startLine = grid.indexOfFirst { line -> line.contains('^') }
    val startColumn = grid[startLine].indexOf('^')
    var guardPosition: Pair<Int, Int> = Pair(startLine, startColumn)
    var guardDirection: Pair<Int, Int> = Pair(-1, 0)
    val visitedPositions: MutableSet<Pair<Int, Int>> = mutableSetOf()

    while (isInMap(grid, guardPosition)) {
        visitedPositions.add(guardPosition)
        if (isBlocked(grid, guardPosition, guardDirection))
            guardDirection = guardDirection.rotateClockWise()
        else
            guardPosition = guardPosition.plus(guardDirection)
    }

    val numberOfVisitedPositions: Int = visitedPositions.size
    println(numberOfVisitedPositions)

}

private fun Pair<Int, Int>.rotateClockWise(): Pair<Int, Int> {
    return when {
        this == Pair(-1, 0) -> return Pair( 0, 1)
        this == Pair( 0, 1) -> return Pair( 1, 0)
        this == Pair( 1, 0) -> return Pair( 0,-1)
        this == Pair( 0,-1) -> return Pair(-1, 0)
        else -> { Pair( 0, 0) }
    }
}

private fun Pair<Int, Int>.plus(other: Pair<Int, Int>): Pair<Int, Int> {
    return Pair(first+other.first, second+other.second)
}

fun isBlocked(grid: List<List<Char>>, position: Pair<Int, Int>, direction: Pair<Int, Int>): Boolean {
    val pos = position.plus(direction)
    return isInMap(grid, pos) && grid[pos.first][pos.second] == '#'
}

fun isInMap(grid: List<List<Char>>, position: Pair<Int, Int>): Boolean {
    return position.first in grid.indices && position.second in grid.first().indices
}
