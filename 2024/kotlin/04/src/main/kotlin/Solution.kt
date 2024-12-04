package albertgustavsson.adventofcode.y2024.d04

import java.io.File
import java.util.stream.Stream

fun main(args:Array<String>) {
    require (args.size == 2) { throw IllegalArgumentException("Required arguments: <part> <inputFileName>") }
    val part = args[0].toInt()
    val inputFileName = args[1]

    val grid: List<List<Char>> = File(inputFileName).bufferedReader().lines().map { line -> line.toList() }.toList()

    if (part == 1) {
        val xPositions: List<Pair<Int, Int>> = grid.flatMapIndexed { row: Int, line: List<Char> ->
            line.mapIndexed { column, c -> Pair(column, c) }.filter { pair -> pair.second == 'X' }.map { pair -> Pair(row, pair.first) }
        }

        val xmPositions = xPositions.map { xPos -> Pair(xPos, findNeighbors(grid, xPos, 'M')) }
            .flatMap { xPosAndDirs -> xPosAndDirs.second.map { dir -> Pair(xPosAndDirs.first, dir) } }

        val xmaPositions = xmPositions.filter { pair ->
            val mPosition = pair.first.plus(pair.second)
            hasNeighbor(grid, mPosition, pair.second, 'A')
        }

        val xmasPositions = xmaPositions.filter { pair ->
            val aPosition = pair.first.plus(pair.second).plus(pair.second)
            hasNeighbor(grid, aPosition, pair.second, 'S')
        }

        val fullMatches: Int = xmasPositions.size

        println(fullMatches)
    } else {
        val aPositions: List<Pair<Int, Int>> = grid.flatMapIndexed { row: Int, line: List<Char> ->
            line.mapIndexed { column, c -> Pair(column, c) }.filter { pair -> pair.second == 'A' }.map { pair -> Pair(row, pair.first) }
        }

        val maPositions = aPositions.map { aPos -> Pair(aPos, findDiagonalNeighbors(grid, aPos, 'M')) }
            .flatMap { aPosAndDirs -> aPosAndDirs.second.map { dir -> Pair(aPosAndDirs.first, dir) } }

        val masPositions = maPositions.filter { pair ->
            hasNeighbor(grid, pair.first, pair.second.flip(), 'S')
        }

        val xmasPositions = masPositions.groupBy { pair -> pair.first }
            .filter { entry -> entry.value.size >= 2}
            .map { entry ->
                val dirs = entry.value.map { pair -> pair.second }
                Pair(entry.key, dirs.filter { dir -> dirs.contains(dir.rotateClockWise()) || dirs.contains(dir.rotateCounterClockWise()) }.size/2)
            }

        println(xmasPositions.map { pair -> pair.second }.sum())
    }
}

private fun Pair<Int, Int>.flip(): Pair<Int, Int> {
    return Pair(-first, -second)
}
private fun Pair<Int, Int>.rotateClockWise(): Pair<Int, Int> {
    return when {
        first == -1 && second == -1 -> return Pair(-1,  1)
        first == -1 && second ==  0 -> return Pair( 0,  1)
        first == -1 && second ==  1 -> return Pair( 1,  1)
        first ==  0 && second == -1 -> return Pair(-1,  0)
        first ==  0 && second ==  1 -> return Pair( 1,  0)
        first ==  1 && second == -1 -> return Pair(-1, -1)
        first ==  1 && second ==  0 -> return Pair( 0, -1)
        first ==  1 && second ==  1 -> return Pair( 1, -1)
        else -> { Pair( 0,  0) }
    }
}
private fun Pair<Int, Int>.rotateCounterClockWise(): Pair<Int, Int> {
    return this.rotateClockWise().rotateClockWise().rotateClockWise()
}

private fun Pair<Int, Int>.plus(other: Pair<Int, Int>): Pair<Int, Int> {
    return Pair(first+other.first, second+other.second)
}

fun hasNeighbor(grid: List<List<Char>>, start: Pair<Int, Int>, direction: Pair<Int, Int>, c: Char): Boolean {
    val pos = start.plus(direction)
    return pos.first in grid.indices && pos.second in grid.first().indices && grid[pos.first][pos.second] == c
}

fun findNeighbors(grid: List<List<Char>>, position: Pair<Int, Int>, c: Char): List<Pair<Int, Int>> {
    return Stream.of(
        Pair(-1, -1), Pair(-1, 0), Pair(-1, +1),
        Pair( 0, -1),              Pair( 0, +1),
        Pair(+1, -1), Pair(+1, 0), Pair(+1, +1))
        .filter { dir ->
            hasNeighbor(grid, position, dir, c)
        }
        .toList()
}

fun findDiagonalNeighbors(grid: List<List<Char>>, position: Pair<Int, Int>, c: Char): List<Pair<Int, Int>> {
    return Stream.of(
        Pair(-1, -1), Pair(-1, +1),
        Pair(+1, -1), Pair(+1, +1))
        .filter { dir ->
            hasNeighbor(grid, position, dir, c)
        }
        .toList()
}
