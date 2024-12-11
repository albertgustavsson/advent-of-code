package albertgustavsson.adventofcode.y2024.d11

import java.io.File

fun main(args:Array<String>) {
    require (args.size == 2) { throw IllegalArgumentException("Required arguments: <part> <inputFileName>") }
    val part = args[0].toInt()
    val inputFileName = args[1]

    val stones: MutableList<Long> = File(inputFileName)
        .bufferedReader()
        .readText()
        .split("\\s+".toRegex())
        .filter { s -> s.isNotBlank() }
        .map { s -> s.toLong() }
        .toMutableList()

    for (i in 0..<25) {
        var index = 0
        while (index in stones.indices) {
            if (stones[index] == 0L ) {
                stones[index] = 1
            } else if (stones[index].toString().length % 2 == 0) {
                val firstHalf = stones[index].toString().substring(0, stones[index].toString().length/2).toLong()
                val secondHalf = stones[index].toString().substring(stones[index].toString().length/2).toLong()
                stones[index] = firstHalf
                stones.add(index+1, secondHalf)
                index++
            } else {
                stones[index] = stones[index] * 2024
            }
            index++
        }
    }

    println(stones.size)
}
