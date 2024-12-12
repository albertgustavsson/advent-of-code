package albertgustavsson.adventofcode.y2024.d12

import java.io.File

val neighborDirections = listOf(Pair(-1, 0), Pair(1, 0), Pair(0, -1), Pair(0, 1))

fun main(args:Array<String>) {
    require (args.size == 2) { throw IllegalArgumentException("Required arguments: <part> <inputFileName>") }
    val part = args[0].toInt()
    val inputFileName = args[1]

    val grid: List<List<Char>> = File(inputFileName).bufferedReader().lines().map { line -> line.toList() }.toList()

    val regionGrid: List<MutableList<Pair<Char, Int>>> = grid.map { chars: List<Char> -> chars.map { c -> Pair(c, -1) }.toMutableList() }

    populateRegionIds(regionGrid)

    val positionsByRegionId = regionGrid
        .flatMapIndexed { row: Int, pairs: MutableList<Pair<Char, Int>> ->
            pairs.mapIndexed { column, pair -> Triple(Pair(row, column), pair.first, pair.second) }
        }
        .groupBy { triple -> triple.third }

    val areaAndPerimeterByRegion = positionsByRegionId.mapValues { entry ->
        val area = entry.value.size
        val positions = entry.value.map { triple -> triple.first }
        val perimeter = if (part == 1) {
            positions.map { pos -> 4 - neighborDirections.count { dir -> positions.contains(pos.plus(dir)) } }.sum()
        } else {
            val corners: MutableSet<Pair<Pair<Int, Int>, Pair<Int, Int>>> = mutableSetOf()
            positions.forEach { pos ->
                neighborDirections.forEach { dir ->
                    val cornerPos = pos.toCornerPosition(dir)
                    if (
                        !positions.contains(pos.plus(dir)) &&
                        !positions.contains(pos.plus(dir.rotateClockWise90()))
                        ) corners.add(Pair(cornerPos, dir))
                    else if (
                        positions.contains(pos.plus(dir)) &&
                        positions.contains(pos.plus(dir.rotateClockWise45())) &&
                        !positions.contains(pos.plus(dir.rotateClockWise90()))
                        ) corners.add(Pair(cornerPos, dir.rotateCounterClockWise90()))
                    else if (
                        positions.contains(pos.plus(dir)) &&
                        !positions.contains(pos.plus(dir.rotateClockWise45())) &&
                        positions.contains(pos.plus(dir.rotateClockWise90()))
                        ) corners.add(Pair(cornerPos, dir.rotate180()))
                    else if (
                        !positions.contains(pos.plus(dir)) &&
                        positions.contains(pos.plus(dir.rotateClockWise45())) &&
                        positions.contains(pos.plus(dir.rotateClockWise90()))
                        ) corners.add(Pair(cornerPos, dir.rotateClockWise90()))
                }
            }
            corners.size
        }
        Pair(area, perimeter)
    }
    val totalPrice = areaAndPerimeterByRegion.values.map { areaAndPerimeter -> areaAndPerimeter.first * areaAndPerimeter.second }.sum()

    println(totalPrice)
}

fun populateRegionIds(regions: List<MutableList<Pair<Char, Int>>>) {
    var nextId = 0
    for (r in regions.indices) {
        for (c in regions[r].indices) {
            if (regions[r][c].second == -1)
                populateDepthFirstSearch(regions, Pair(r, c), nextId)
            nextId++
        }
    }
}

fun populateDepthFirstSearch(regions: List<MutableList<Pair<Char, Int>>>, position: Pair<Int, Int>, id: Int) {
    regions[position.first][position.second] = regions[position.first][position.second].copy(second = id)
    neighborDirections
        .map { dir -> position.plus(dir) }
        .filter { pos -> isInMap(regions, pos) }
        .filter { pos -> regions[pos.first][pos.second].first == regions[position.first][position.second].first }
        .filter { pos -> regions[pos.first][pos.second].second == -1 }
        .forEach { pos -> populateDepthFirstSearch(regions, pos, id)}
}

fun <T> isInMap(grid: List<List<T>>, position: Pair<Int, Int>): Boolean {
    return position.first in grid.indices && position.second in grid.first().indices
}

private fun Pair<Int, Int>.toCornerPosition(dir: Pair<Int, Int>): Pair<Int, Int> {
    return this.plus(dir.toCornerOffset())
}

private fun Pair<Int, Int>.toCornerOffset(): Pair<Int, Int> {
    return when {
        this == Pair(-1, 0) -> return Pair( 0, 1)
        this == Pair( 0, 1) -> return Pair( 1, 1)
        this == Pair( 1, 0) -> return Pair( 1, 0)
        this == Pair( 0,-1) -> return Pair( 0, 0)
        else -> { Pair( 0, 0) }
    }
}

private fun Pair<Int, Int>.plus(other: Pair<Int, Int>): Pair<Int, Int> {
    return Pair(first+other.first, second+other.second)
}

private fun Pair<Int, Int>.rotate180(): Pair<Int, Int> {
    return this.rotateClockWise90().rotateClockWise90()
}

private fun Pair<Int, Int>.rotateCounterClockWise90(): Pair<Int, Int> {
    return this.rotateClockWise90().rotateClockWise90().rotateClockWise90()
}

private fun Pair<Int, Int>.rotateClockWise90(): Pair<Int, Int> {
    return when {
        this == Pair(-1, 0) -> return Pair( 0, 1)
        this == Pair( 0, 1) -> return Pair( 1, 0)
        this == Pair( 1, 0) -> return Pair( 0,-1)
        this == Pair( 0,-1) -> return Pair(-1, 0)
        else -> { Pair( 0, 0) }
    }
}

private fun Pair<Int, Int>.rotateClockWise45(): Pair<Int, Int> {
    return when {
        this == Pair(-1, 0) -> return Pair(-1, 1)
        this == Pair( 0, 1) -> return Pair( 1, 1)
        this == Pair( 1, 0) -> return Pair( 1,-1)
        this == Pair( 0,-1) -> return Pair(-1,-1)
        else -> { Pair( 0, 0) }
    }
}
