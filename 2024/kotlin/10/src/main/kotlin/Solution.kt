package albertgustavsson.adventofcode.y2024.d10

import java.io.File

fun main(args:Array<String>) {
    require (args.size == 2) { throw IllegalArgumentException("Required arguments: <part> <inputFileName>") }
    val part = args[0].toInt()
    val inputFileName = args[1]

    val heightMap: List<List<Int>> = File(inputFileName).bufferedReader().lines().map { line -> line.toList().map { c -> c.digitToInt() } }.toList()

    val trailHeads: List<Pair<Int, Int>> = heightMap.flatMapIndexed { row, heights -> heights.mapIndexed { column, height -> if (height == 0) Pair(row, column) else null } }.filterNotNull()
    val totalScore = trailHeads.map { trailhead -> getReachable(heightMap, trailhead, 9).size }.sum()

    println(totalScore)
}

fun getReachable(heightMap: List<List<Int>>, position: Pair<Int, Int>, targetHeight: Int): Set<Pair<Int, Int>> {
    val startingHeight = heightMap[position.first][position.second]
    if (startingHeight == targetHeight) return setOf(position)

    val neighbors: Set<Pair<Int, Int>> = getNeighbors(heightMap, position, startingHeight+1)
    return neighbors.flatMap { n -> getReachable(heightMap, n, targetHeight) }.toSet()
}

fun getNeighbors(heightMap: List<List<Int>>, position: Pair<Int, Int>, neighborHeight: Int): Set<Pair<Int, Int>> {
    return position.upDownLeftRight()
        .filter { p -> p.isInMap(heightMap) }
        .filter { n -> heightMap[n.first][n.second] == neighborHeight }
        .toSet()
}

private fun Pair<Int, Int>.upDownLeftRight(): Set<Pair<Int, Int>> {
    return listOf(
        Pair(-1, 0),
        Pair(+1, 0),
        Pair(0, -1),
        Pair(0, +1))
        .map { dir ->
            this.plus(dir)
        }.toSet()
}

private fun Pair<Int, Int>.plus(other: Pair<Int, Int>): Pair<Int, Int> {
    return Pair(first+other.first, second+other.second)
}

private fun Pair<Int, Int>.isInMap(grid: List<List<Int>>): Boolean {
    return this.first in grid.indices && this.second in grid.first().indices
}
