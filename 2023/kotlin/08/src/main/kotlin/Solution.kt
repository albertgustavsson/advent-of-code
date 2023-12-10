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
    var steps = 0L
    if (part == 1) {
        var nextNode = "AAA"
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
    } else {
        // Find the LCM of all cycle lengths, which works because the graph seems to end in cycles for all starting
        // points. Maybe this is not the case for all possible inputs though...
        val periods = mutableListOf<Long>()
        var nextNodes = networkMap.keys.filter { it.endsWith('A') }
        while (!done) {
            instructionsLine.forEach { instruction ->
                if (!done) {
                    if (instruction == 'L') {
                        nextNodes = nextNodes.map { node -> networkMap.getValue(node).first }
                    } else if (instruction == 'R') {
                        nextNodes = nextNodes.map { node -> networkMap.getValue(node).second }
                    }
                    steps++
                    if (nextNodes.filter { node -> node.endsWith('Z') }.isNotEmpty()) {
                        periods.add(steps)
                    }
                    nextNodes = nextNodes.filter { node -> !node.endsWith('Z') }
                    if (nextNodes.all { node -> node.endsWith('Z') }) {
                        done = true
                    }
                }
            }
        }
        steps = lcm(periods)
    }

    println(steps)
}

fun lcm(periods: List<Long>): Long {
    var lcm = periods[0]
    periods.subList(1, periods.size).forEach { lcm = lcm(lcm, it) }
    return lcm
}

fun lcm(a: Long, b: Long): Long {
    return a*b/gcd(a,b)
}

fun gcd(a: Long, b: Long): Long {
    val (smaller, larger) = Pair(minOf(a,b), maxOf(a,b))
    if (smaller == 0L) return larger
    return gcd(smaller, larger % smaller)
}
