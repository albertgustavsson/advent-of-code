package albertgustavsson.adventofcode.y2023.d03

import java.io.FileReader
import kotlin.math.max
import kotlin.math.min

fun main(args:Array<String>) {
    require (args.size == 2) { throw IllegalArgumentException("Required arguments: <part> <inputFileName>") }
    val part = args[0].toInt()
    val inputFileName = args[1]

    val lines = FileReader(inputFileName).readLines()
    val sum: Int
    if (part == 1) {
        val partNumbers = mutableListOf<Int>()
        for ((row, s) in lines.withIndex()) {
            var parsingNumber = false
            var parsingStart = 0
            var parsingEnd: Int
            var isPartNumber = false
            for ((column, c) in s.withIndex()) {
                if (c.isDigit() && !parsingNumber) {
                    parsingNumber = true // the start of a number
                    parsingStart = column
                } else if (parsingNumber && (!c.isDigit() || column == s.length - 1)) {
                    parsingNumber = false // end of a number
                    if (c.isDigit()) {
                        parsingEnd = column
                    } else {
                        parsingEnd = column - 1
                    }

                    val first = max(parsingStart - 1, 0)
                    val last = min(parsingEnd + 1, s.length - 1)
                    var above = ""
                    if (row > 0) {
                        above = lines[row - 1].substring(first, last + 1)
                    }
                    var below = ""
                    if (row < lines.size - 1) {
                        below = lines[row + 1].substring(first, last + 1)
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
                        val number = s.substring(parsingStart, parsingEnd + 1)
                        partNumbers.add(number.toInt())
                    }
                    isPartNumber = false
                }
            }
        }
        sum = partNumbers.reduce(Int::plus)
    } else {
        val gearRatios = mutableListOf<Int>()
        for ((row, line) in lines.withIndex()) {
            for ((column, char) in line.withIndex()) {
                if (char == '*') {
                    val topLeft = Pair(max(row-1, 0), max(column-1, 0))
                    val bottomRight = Pair(min(row+1, lines.size-1), min(column+1, line.length-1))

                    var above = ""
                    if (topLeft.first < row) {
                        above = lines[topLeft.first].substring(topLeft.second, bottomRight.second+1)
                    }
                    var middle = line.substring(topLeft.second, bottomRight.second+1)
                    var below = ""
                    if (bottomRight.first > row) {
                        below = lines[bottomRight.first].substring(topLeft.second, bottomRight.second+1)
                    }

                    var numbersAbove = above.count { it.isDigit() }
                    var numbersMiddle = middle.count { it.isDigit() }
                    var numbersBelow = below.count { it.isDigit() }
                    if ((numbersAbove == 2 && above[1].isDigit()) || numbersAbove == 3) {
                        numbersAbove = 1
                    }
                    if ((numbersBelow == 2 && below[1].isDigit()) || numbersBelow == 3) {
                        numbersBelow = 1
                    }
                    val totalNumbers = numbersAbove + numbersMiddle + numbersBelow

                    if (totalNumbers == 2) { // Is a gear
                        var number1: Int? = null
                        var number2: Int? = null

                        findNumbers@ for (r in topLeft.first..bottomRight.first) {
                            var skip = 0
                            for (c in topLeft.second..bottomRight.second) {
                                if (skip > 0) {
                                    skip--
                                    continue
                                }
                                if (lines[r][c].isDigit()) {
                                    var offset = 0
                                    while (c+offset >= 0 && lines[r][c+offset].isDigit()) offset--
                                    val numberStart = c+offset+1
                                    offset = 0
                                    while (c+offset < lines[r].length && lines[r][c+offset].isDigit()) offset++
                                    val numberEnd = c+offset-1
                                    val number = lines[r].substring(numberStart, numberEnd+1).toInt()
                                    if (number1 == null) {
                                        number1 = number
                                        if (numberEnd > c) {
                                            skip = numberEnd-c
                                        }
                                    } else {
                                        number2 = number
                                        break@findNumbers
                                    }
                                }
                            }
                        }

                        val gearRatio = number1!! * number2!!
                        gearRatios.add(gearRatio)
                    }
                }
            }
        }
        sum = gearRatios.reduce(Int::plus)
    }

    println(sum)
}
