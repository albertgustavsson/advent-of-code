package albertgustavsson.adventofcode.y2024.d05

import java.io.File

fun main(args:Array<String>) {
    require (args.size == 2) { throw IllegalArgumentException("Required arguments: <part> <inputFileName>") }
    val part = args[0].toInt()
    val inputFileName = args[1]

    val lines: List<String> = File(inputFileName).bufferedReader().lines().toList()
    val numberOfOrderingRuleLines = lines.indexOf("")
    val orderingRules = lines.take(numberOfOrderingRuleLines).map { s -> val parts = s.split("|")
        Pair(parts[0].toInt(), parts[1].toInt())
    }
    val updates: List<List<Int>> = lines.drop(numberOfOrderingRuleLines+1).map { line -> line.split(",").map { n -> n.toInt() } }

    val orderedUpdates = updates.filter { update -> checkOrder(update, orderingRules)}

    val middlePageNumbers = orderedUpdates.map { update -> update[update.size/2] }

    println("${middlePageNumbers.sum()}")
}

fun checkOrder(update: List<Int>, orderingRules: List<Pair<Int, Int>>): Boolean {
    val relevantOrderingRules = orderingRules.filter { pair -> (update.contains(pair.first) && update.contains(pair.second)) }
    for (i in update) {
        val relevantOrderingRulesForElement = relevantOrderingRules.filter { pair -> pair.first == i || pair.second == i }
        for (orderingRule in relevantOrderingRulesForElement) {
            val firstIndex = update.indexOf(orderingRule.first)
            val secondIndex = update.indexOf(orderingRule.second)
            if (firstIndex > secondIndex) {
                return false
            }
        }
    }
    return true
}
