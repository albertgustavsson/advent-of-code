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
    val times: List<Int> = timeLineSplit.subList(1, timeLineSplit.size).map(String::toInt)
    val distances: List<Int> = distanceLineSplit.subList(1, distanceLineSplit.size).map(String::toInt)
    val timesAndDistances = times.zip(distances)

    val product = timesAndDistances.map {
        val time = it.first
        val distance = it.second
        IntRange(0, time).filter {
            // Distance as a function of Time: d=t(time-t)
            val d = it*(time-it)
            d > distance
        }.count()
    }.reduce(Int::times)

    println(product)
}
