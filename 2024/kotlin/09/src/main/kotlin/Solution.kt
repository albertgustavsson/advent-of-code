package albertgustavsson.adventofcode.y2024.d09

import java.io.File
import java.util.Collections

fun main(args:Array<String>) {
    require (args.size == 2) { throw IllegalArgumentException("Required arguments: <part> <inputFileName>") }
    val part = args[0].toInt()
    val inputFileName = args[1]

    val diskMap: List<Char> = File(inputFileName).bufferedReader().lines().flatMap { line -> line.toList().stream() }.toList()

    val diskBlocks: List<String> = createDiskBlocks(diskMap)

    for ((index, s) in diskBlocks.withIndex()) {
        if (s == ".") {
            val fileIndex = diskBlocks.indexOfLast { id -> id != "." }
            if (index < fileIndex)
                Collections.swap(diskBlocks, index, fileIndex)
        }
    }

    val checksum: Long = diskBlocks.mapIndexed { index, block -> if (block == ".") 0 else block.toLong()*index }.sum()

    println(checksum)
}

private fun createDiskBlocks(diskMap: List<Char>): List<String> {
    val diskBlocks: MutableList<String> = mutableListOf()
    diskMap.forEachIndexed { index, c ->
        if (index % 2 == 0) {
            val fileId = index / 2
            val size = c.code - '0'.code
            diskBlocks.addAll(List(size) { fileId.toString() })
        } else {
            val size = c.code - '0'.code
            diskBlocks.addAll(List(size) { "." })
        }
    }
    return diskBlocks
}
