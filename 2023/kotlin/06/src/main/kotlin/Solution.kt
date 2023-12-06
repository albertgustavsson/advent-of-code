package albertgustavsson.adventofcode.y2023.d06

import java.io.File

fun main(args: Array<String>) {
    require(args.size == 2) { throw IllegalArgumentException("Required arguments: <part> <inputFileName>") }
    val part = args[0].toInt()
    val inputFileName = args[1]

    val reader = File(inputFileName).bufferedReader()
    val timeLine = reader.readLine()
    val distanceLine = reader.readLine()

    val timeLineSplit = timeLine.split("\\s+".toRegex())
    val distanceLineSplit = distanceLine.split("\\s+".toRegex())
    val times: List<Long>
    val distances: List<Long>
    if (part == 1) {
        times = timeLineSplit.subList(1, timeLineSplit.size).map(String::toLong)
        distances = distanceLineSplit.subList(1, distanceLineSplit.size).map(String::toLong)
    } else {
        times = listOf(timeLineSplit.subList(1, timeLineSplit.size).reduce(String::plus).toLong())
        distances = listOf(distanceLineSplit.subList(1, distanceLineSplit.size).reduce(String::plus).toLong())
    }
    val timesAndDistances = times.zip(distances)

    val product = timesAndDistances.map {
        val time = it.first
        val distance = it.second
        LongRange(0, time).filter {
            // Distance as a function of Time: d=t(time-t)
            val d = it*(time-it)
            d > distance
        }.count().toLong()
    }.reduce(Long::times)

    println(product)
}
