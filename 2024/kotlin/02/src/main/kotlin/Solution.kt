package albertgustavsson.adventofcode.y2024.d02

import java.io.File
import kotlin.math.abs
import kotlin.math.max
import kotlin.math.min
import kotlin.math.sign

fun main(args:Array<String>) {
    require (args.size == 2) { throw IllegalArgumentException("Required arguments: <part> <inputFileName>") }
    val part = args[0].toInt()
    val inputFileName = args[1]

    val reports: List<List<Int>> = File(inputFileName).bufferedReader().lines().map { line ->
        line.split("\\s+".toRegex()).map { it.toInt() }
    }.toList()

    val safeReports: List<List<Int>> = reports.filter { report ->
        if (part == 1) {
            reportIsSafe(report)
        } else {
            reportIsSafe(report) || report.indices.any { indexToRemove ->
                val reportWithOneItemRemoved = report.filterIndexed { index, _ -> index != indexToRemove }
                reportIsSafe(reportWithOneItemRemoved)
            }
        }
    }
    println(safeReports.count())
}

private fun reportIsSafe(report: List<Int>): Boolean {
    val differences: List<Int> = report.mapIndexed { index, i -> report.getOrNull(index - 1)?.let { it1 -> i - it1 } }.filterNotNull()
    val minDiff: Int = differences.min()
    val maxDiff: Int = differences.max()
    return minDiff.sign == maxDiff.sign && (min(abs(minDiff), abs(maxDiff)) >= 1 && max(abs(minDiff), abs(maxDiff)) <= 3)
}
