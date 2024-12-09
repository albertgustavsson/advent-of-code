package albertgustavsson.adventofcode.y2024.d09

import java.io.File
import java.util.Collections

fun main(args:Array<String>) {
    require (args.size == 2) { throw IllegalArgumentException("Required arguments: <part> <inputFileName>") }
    val part = args[0].toInt()
    val inputFileName = args[1]

    val diskMap: List<Char> = File(inputFileName).bufferedReader().lines().flatMap { line -> line.toList().stream() }.toList()

    val diskBlocks: List<String> = if (part == 1) {
        val diskBlocks: List<String> = createDiskBlocks(diskMap.mapIndexed { index, c -> Pair(if (index % 2 == 0) index / 2 else null, c.digitToInt()) })

        println(diskBlocks)

        for ((index, s) in diskBlocks.withIndex()) {
            if (s == ".") {
                val fileIndex = diskBlocks.indexOfLast { id -> id != "." }
                if (index < fileIndex)
                    Collections.swap(diskBlocks, index, fileIndex)
            }
        }
        diskBlocks
    } else {
        val reorderedDiskMap: MutableList<Pair<Int?, Int>> = diskMap.mapIndexed { index, c -> Pair(if (index % 2 == 0) index / 2 else null, c.digitToInt()) }.toMutableList()

        // For each hole, pick the right-most file that fits
        var index = reorderedDiskMap.size - 1
        while (index in reorderedDiskMap.indices) {
            val file = reorderedDiskMap[index]

            if (file.first != null) { // Is file space
                // Find first empty space that fits file
                val gapIndex = reorderedDiskMap.indexOfFirst { p -> p.first == null && p.second >= file.second }
                if (gapIndex in 0..index) {
                    val gap = reorderedDiskMap[gapIndex]
                    reorderedDiskMap[gapIndex] = file

                    if (file.second != gap.second) {
                        if (gapIndex+1 in reorderedDiskMap.indices && reorderedDiskMap[gapIndex+1].first == null) {
                            reorderedDiskMap[gapIndex+1] = reorderedDiskMap[gapIndex+1].copy(second = reorderedDiskMap[gapIndex+1].second + (gap.second - file.second))
                        } else {
                            reorderedDiskMap.add(gapIndex+1, Pair(null, gap.second - file.second))
                            index++
                        }
                    }

                    reorderedDiskMap[index] = Pair(null, file.second)

                    // Combine any consecutive gaps
                    var tempIndex = 0
                    while (tempIndex+1 in reorderedDiskMap.indices) {
                        if (reorderedDiskMap[tempIndex].first == null && reorderedDiskMap[tempIndex+1].first == null) {
                            reorderedDiskMap[tempIndex] = reorderedDiskMap[tempIndex].copy(second = reorderedDiskMap[tempIndex].second + reorderedDiskMap[tempIndex+1].second)
                            reorderedDiskMap.removeAt(tempIndex+1)
                            if (tempIndex+1 <= index) {
                                index--
                            }
                        }
                        tempIndex++
                    }
                }
            }
            index--
        }

        val diskBlocks: List<String> = createDiskBlocks(reorderedDiskMap)
        diskBlocks
    }

    val checksum: Long = diskBlocks.mapIndexed { index, block -> if (block == ".") 0 else block.toLong()*index }.sum()

    println(checksum)
}

private fun createDiskBlocks(diskMap: List<Pair<Int?, Int>>): List<String> {
    val diskBlocks: MutableList<String> = mutableListOf()
    diskMap.forEach { p ->
        val fileId = p.first
        val size = p.second
        if (fileId != null) {
            diskBlocks.addAll(List(size) { fileId.toString() })
        } else {
            diskBlocks.addAll(List(size) { "." })
        }
    }
    return diskBlocks
}
