package albertgustavsson.adventofcode.y2024.d15

import java.io.File

fun main(args:Array<String>) {
    require (args.size == 2) { throw IllegalArgumentException("Required arguments: <part> <inputFileName>") }
    val part = args[0].toInt()
    val inputFileName = args[1]

    val fileContents: String = File(inputFileName).bufferedReader().readText()
    val parts = fileContents.split("\r?\n\\s*\r?\n".toRegex())

    val map: List<MutableList<Char>> = parts[0].split("\r?\n".toRegex()).map { line -> line.toList().flatMap { c ->
            if (part == 1) {
                listOf(c)
            } else {
                when(c) {
                    '#' -> "##"
                    'O' -> "[]"
                    '.' -> ".."
                    '@' -> "@."
                    else -> ""
                }.toList()
            }
        }.toMutableList()
    }
    val movements: List<Char> = parts[1].toList().filterNot { c -> c.isWhitespace() }

    movements.forEach { c ->
        val dir: Pair<Int, Int> = when(c) {
            '^' -> Pair(-1, 0)
            'v' -> Pair( 1, 0)
            '<' -> Pair( 0,-1)
            '>' -> Pair( 0, 1)
            else-> Pair( 0, 0)
        }
        moveIfPossible(map, dir)
    }

    val gpsCoordinates = map.flatMapIndexed { row: Int, chars: List<Char> -> chars.mapIndexed { column, c -> Pair(Pair(row, column), c) } }.filter { pair -> pair.second == 'O' || pair.second == '[' }.map { pair -> pair.first.first * 100 + pair.first.second }

    println(gpsCoordinates.sum())
}

fun moveIfPossible(map: List<MutableList<Char>>, dir: Pair<Int, Int>) {
    val robotRow = map.indexOfFirst { row -> row.contains('@') }
    val robotColumn = map[robotRow].indexOfFirst { c -> c == '@' }
    val robotPosition = Pair(robotRow, robotColumn)
    moveIfPossible(map, dir, robotPosition)
}

fun moveIfPossible(map: List<MutableList<Char>>, dir: Pair<Int, Int>, position: Pair<Int, Int>): Boolean {
    if (map[position.first][position.second] == '#') return false
    if (map[position.first][position.second] == '.') return true
    return if (canMove(map, dir, position)) {
        val newPosition = position.plus(dir)
        if (map[position.first][position.second] == 'O') {
            val possible = moveIfPossible(map, dir, newPosition)
            if (possible) {
                map[newPosition.first][newPosition.second] = map[position.first][position.second]
                map[position.first][position.second] = '.'
                true
            } else {
                false
            }
        } else if (map[position.first][position.second] == '[') {
            if (dir != Pair(0, 1)) {
                moveIfPossible(map, dir, newPosition)
                map[newPosition.first][newPosition.second] = '['
                map[position.first][position.second] = '.'
                moveIfPossible(map, dir, newPosition.plus(Pair(0, 1)))
                map[newPosition.plus(Pair(0, 1)).first][newPosition.plus(Pair(0, 1)).second] = ']'
                map[position.plus(Pair(0, 1)).first][position.plus(Pair(0, 1)).second] = '.'
                true
            } else if (dir == Pair(0, 1)) {
                moveIfPossible(map, dir, newPosition.plus(Pair(0, 1)))
                map[newPosition.plus(Pair(0, 1)).first][newPosition.plus(Pair(0, 1)).second] = ']'
                map[position.plus(Pair(0, 1)).first][position.plus(Pair(0, 1)).second] = '.'
                moveIfPossible(map, dir, newPosition)
                map[newPosition.first][newPosition.second] = '['
                map[position.first][position.second] = '.'
                true
            } else false
        } else if (map[position.first][position.second] == ']') {
            if (dir != Pair(0,-1)) {
                moveIfPossible(map, dir, newPosition)
                map[newPosition.first][newPosition.second] = ']'
                map[position.first][position.second] = '.'
                moveIfPossible(map, dir, newPosition.plus(Pair(0,-1)))
                map[newPosition.plus(Pair(0,-1)).first][newPosition.plus(Pair(0,-1)).second] = '['
                map[position.plus(Pair(0,-1)).first][position.plus(Pair(0,-1)).second] = '.'
                true
            } else if (dir == Pair(0,-1)) {
                moveIfPossible(map, dir, newPosition.plus(Pair(0,-1)))
                map[newPosition.plus(Pair(0,-1)).first][newPosition.plus(Pair(0,-1)).second] = '['
                map[position.plus(Pair(0,-1)).first][position.plus(Pair(0,-1)).second] = '.'
                moveIfPossible(map, dir, newPosition)
                map[newPosition.first][newPosition.second] = ']'
                map[position.first][position.second] = '.'
                true
            } else false
        } else if (map[position.first][position.second] == '@') {
            val possible = moveIfPossible(map, dir, newPosition)
            if (possible) {
                map[newPosition.first][newPosition.second] = map[position.first][position.second]
                map[position.first][position.second] = '.'
                true
            } else false
        } else {
            false
        }
    } else {
        false
    }
}

fun canMove(map: List<MutableList<Char>>, dir: Pair<Int, Int>, position: Pair<Int, Int>): Boolean {
    val newPosition = position.plus(dir)
    return when(map[newPosition.first][newPosition.second]) {
        '#' -> false
        '.' -> true
        'O' -> canMove(map, dir, newPosition)
        '[' -> canMove(map, dir, newPosition) && (dir == Pair(0,-1) || canMove(map, dir, newPosition.plus(Pair(0,1))))
        ']' -> canMove(map, dir, newPosition) && (dir == Pair(0,1) || canMove(map, dir, newPosition.plus(Pair(0,-1))))
        else -> false
    }
}

private fun Pair<Int, Int>.plus(pair: Pair<Int, Int>): Pair<Int, Int> {
    return Pair(first + pair.first, second + pair.second)
}
