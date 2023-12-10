package albertgustavsson.adventofcode.y2023.d08

import java.io.FileReader

fun main(args: Array<String>) {
    require(args.size == 2) { throw IllegalArgumentException("Required arguments: <part> <inputFileName>") }
    val part = args[0].toInt()
    val inputFileName = args[1]

    val lines = FileReader(inputFileName).readLines().filter { it.isNotBlank() }
    val instructionsLine = lines[0]
    val networkLines = lines.subList(1, lines.size)

    val networkMap: MutableMap<String, Pair<String, String>> = mutableMapOf()

    networkLines.forEach {
        val nodeAndNeighbors = it.replace("[\\s()]".toRegex(), "").split("=")
        val node = nodeAndNeighbors[0]
        val neighbors = nodeAndNeighbors[1].split(",")
        networkMap.put(node, Pair(neighbors[0], neighbors[1]))
    }

    var done = false
    var nextNode = "AAA"
    var steps = 0
    while (!done) {
        instructionsLine.forEach {
            if (!done) {
                if (it == 'L') {
                    nextNode = networkMap.getValue(nextNode).first
                } else if (it == 'R') {
                    nextNode = networkMap.getValue(nextNode).second
                }
                steps++
                if (nextNode == "ZZZ") {
                    done = true
                }
            }
        }
    }

    println(steps)
}
