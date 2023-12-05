package albertgustavsson.adventofcode.y2023.d05

import java.io.File

fun main(args: Array<String>) {
    require(args.size == 2) { throw IllegalArgumentException("Required arguments: <part> <inputFileName>") }
    val part = args[0].toInt()
    val inputFileName = args[1]

    var seeds: List<Long> = emptyList()
    var maps: MutableList<MutableList<Triple<Long, Long, Long>>> = mutableListOf()
    File(inputFileName).bufferedReader().lines().filter(String::isNotBlank).forEach { line ->
        if (line.endsWith(':')) { // title line for a new map
            maps.add(mutableListOf())
        } else if (line.contains(':')) { // 'seeds:' line
            seeds = line.split(':')[1].trim().split(' ').map(String::toLong)
        } else {
            val numbers = line.split(' ').map(String::toLong)
            maps.last().add(Triple(numbers[0], numbers[1], numbers[2]))
        }
    }
    val locations = seeds.map { seed ->
        var tempSource: Long = seed
        var destination: Long = 0
        maps.forEach { map ->
            val triple = map.firstOrNull { (it.second..<(it.second + it.third)).contains(tempSource) }
            if (triple == null) {
                destination = tempSource
            } else {
                destination = tempSource - triple.second + triple.first
                tempSource = destination
            }
        }
        destination
    }

    println(locations.min())
}
