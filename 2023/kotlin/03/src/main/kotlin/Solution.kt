package albertgustavsson.adventofcode.y2023.d03

import java.io.FileReader
import kotlin.math.max
import kotlin.math.min

fun main(args:Array<String>) {
    require (args.size == 2) { throw IllegalArgumentException("Required arguments: <part> <inputFileName>") }
    val part = args[0].toInt()
    val inputFileName = args[1]

    val lines = FileReader(inputFileName).readLines()

    var partNumbers = mutableListOf<Int>()
    for ((row, s) in lines.withIndex()) {
        var parsingNumber = false
        var parsingStart = 0
        var parsingEnd: Int
        var isPartNumber = false
        for ((column, c) in s.withIndex()) {
            if (c.isDigit() && !parsingNumber) {
                parsingNumber = true // the start of a number
                parsingStart = column
            } else if (parsingNumber && (!c.isDigit() || column == s.length-1)) {
                parsingNumber = false // end of a number
                if (c.isDigit()) {
                    parsingEnd = column
                } else {
                    parsingEnd = column-1
                }

                val first = max(parsingStart-1, 0)
                val last = min(parsingEnd+1, s.length-1)
                var above = ""
                if (row > 0) {
                    above = lines[row-1].substring(first, last+1)
                }
                var below = ""
                if (row < lines.size-1) {
                    below = lines[row+1].substring(first, last+1)
                }

                if (above.count { it != '.' } > 0) {
                    isPartNumber = true
                } else if (below.count { it != '.' } > 0) {
                    isPartNumber = true
                } else if (first < parsingStart && s[first] != '.') {
                    isPartNumber = true
                } else if (last > parsingEnd && s[last] != '.') {
                    isPartNumber = true
                }

                if (isPartNumber) {
                    val number = s.substring(parsingStart, parsingEnd+1)
                    partNumbers.add(number.toInt())
                }
                isPartNumber = false
            }
        }
    }
    
    val sum = partNumbers.reduce(Int::plus)
    println(sum)
}
