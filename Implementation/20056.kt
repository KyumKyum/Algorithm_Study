import java.io.*
import java.util.*

class Fireball(
    var pos: Pair<Int, Int>,
    var mass: Int,
    var velocity: Int,
    var direction: Int
) {
    private val dx = listOf(-1, -1, 0, 1, 1, 1, 0, -1)
    private val dy = listOf(0, 1, 1, 1, 0, -1, -1, -1)
    
    // Move fireball according to its velocity and direction
    fun move(gridSize: Int) {
        // Calculate actual movement (considering the wrap-around)
        val moveAmount = velocity % gridSize
        
        var newRow = pos.first + dx[direction] * moveAmount
        var newCol = pos.second + dy[direction] * moveAmount
        
        // Handle wrapping around the grid
        // Adjust for modular arithmetic with negative numbers
        newRow = (newRow % gridSize + gridSize) % gridSize
        newCol = (newCol % gridSize + gridSize) % gridSize
        
        // Update position
        pos = Pair(newRow, newCol)
    }
}

class Magician(
    val size: Int,
    val fireballNum: Int,
    val commandNum: Int,
    val fireballsInput: MutableList<IntArray> 
) {
    // List to store all fireballs
    private var fireballs: MutableList<Fireball> = mutableListOf()
    
    init {
        // Initialize fireballs from input
        // Note: adjusting 1-based indexing to 0-based
        fireballsInput.forEach {
            val fireball = Fireball(
                Pair(it[0] - 1, it[1] - 1), // Convert to 0-indexed
                it[2], // mass
                it[3], // velocity
                it[4]  // direction
            )
            fireballs.add(fireball)
        }
    }
    
    // Execute one round of movement and merging
    private fun executeCommand() {
        // Move all fireballs
        fireballs.forEach { it.move(size) }
        
        // Group fireballs by position
        val positionMap = mutableMapOf<Pair<Int, Int>, MutableList<Fireball>>()
        
        fireballs.forEach { fireball ->
            val pos = fireball.pos
            if (!positionMap.containsKey(pos)) {
                positionMap[pos] = mutableListOf()
            }
            positionMap[pos]?.add(fireball)
        }
        
        // Clear current fireballs and process each position
        fireballs.clear()
        
        for ((pos, fireballsAtPos) in positionMap) {
            // If only one fireball, just keep it
            if (fireballsAtPos.size == 1) {
                fireballs.add(fireballsAtPos[0])
                continue
            }
            
            // Multiple fireballs at this position - merge and split
            var totalMass = 0
            var totalVelocity = 0
            var allEven = true
            var allOdd = true
            
            for (fb in fireballsAtPos) {
                totalMass += fb.mass
                totalVelocity += fb.velocity
                
                // Check if all directions are even or all are odd
                if (fb.direction % 2 == 0) {
                    allOdd = false
                } else {
                    allEven = false
                }
            }
            
            // Calculate new properties
            val newMass = totalMass / 5
            val newVelocity = totalVelocity / fireballsAtPos.size
            
            // If mass becomes 0, no new fireballs
            if (newMass == 0) continue
            
            // Determine directions based on original fireballs
            val directions = if (allEven || allOdd) {
                listOf(0, 2, 4, 6) // All even or all odd
            } else {
                listOf(1, 3, 5, 7) // Mixed
            }
            
            // Create 4 new fireballs
            for (dir in directions) {
                fireballs.add(Fireball(pos, newMass, newVelocity, dir))
            }
        }
    }
    
    // Execute all commands and return sum of masses
    fun executeAllCommands(): Int {
        // Perform K movements
        repeat(commandNum) {
            executeCommand()
        }
        
        // Calculate sum of masses
        return fireballs.sumOf { it.mass }
    }
}

fun main() {
    val br = BufferedReader(InputStreamReader(System.`in`))
    val (n, m, k) = br.readLine().trim().split(" ").map { it.toInt() }
    
    val fireballs: MutableList<IntArray> = mutableListOf()
    
    for(idx in 0 until m) {
        fireballs.add(br.readLine().trim().split(" ").map { it.toInt() }.toIntArray())
    }
    
    val magician = Magician(n, m, k, fireballs)
    val result = magician.executeAllCommands()
    
    println(result)
    
    br.close()
}