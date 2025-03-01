import java.io.*
import java.util.*
import kotlin.math.abs

// To execute Kotlin code, please define a top level function named main

class Game(val r: Int, val c: Int, val range: Int){
  private val castle = MutableList(r) { IntArray(c) }
  private lateinit var temp: MutableList<IntArray>
  private var archers: MutableList<Pair<Int, Int>> = mutableListOf()
  private var monsters: MutableList<Pair<Int, Int>> = mutableListOf()
  private var maxKills = 0

  constructor(r: Int, c: Int, range: Int, input: MutableList<String>): this(r, c, range) {
    input.forEachIndexed { idx, list -> 
      castle[idx] = list.trim().split(" ").map { it.toInt()}.toIntArray()
    }

    reset()
  }

  fun reset(){
    temp = MutableList(r) {i -> castle[i].copyOf()}
    monsters.clear()
    archers.clear()
    
    // Find all monsters in the initial state
    for (i in 0 until r) {
      for (j in 0 until c) {
        if (temp[i][j] == 1) {
          monsters.add(Pair(i, j))
        }
      }
    }
  }

  fun checkFinished(): Boolean {
    return monsters.isEmpty()
  }

  fun moveMonster() {
    val intruderList: MutableList<Int> = mutableListOf()
    
    monsters.forEachIndexed { idx, monster -> 
      val (mr, mc) = monster
      if (mr + 1 >= r) {
        // This monster reached the castle row, it will be removed
        intruderList.add(idx)
      } else {
        val newPos = Pair(mr + 1, mc)
        monsters[idx] = newPos
      }
    }

    intruderList.sortedDescending().forEach { idx ->
      monsters.removeAt(idx)
    }
  }

  fun shoot(): Int {
    val monsterToKill = mutableSetOf<Int>() // Using a set to avoid duplicate kills
    
    archers.forEach { archer -> 
      val (ar, ac) = archer
      var closestDistance = Int.MAX_VALUE
      var closestMonsterIndex = -1
      var closestMonsterColumn = Int.MAX_VALUE
      
      monsters.forEachIndexed { idx, monster -> 
        val (mr, mc) = monster
        val distance = abs(ar - mr) + abs(ac - mc)
        
        if (distance <= range) {
          // If distance is smaller, update closest
          if (distance < closestDistance) {
            closestDistance = distance
            closestMonsterIndex = idx
            closestMonsterColumn = mc
          } 
          // If distances are equal, take the leftmost
          else if (distance == closestDistance && mc < closestMonsterColumn) {
            closestMonsterIndex = idx
            closestMonsterColumn = mc
          }
        }
      }
      
      if (closestMonsterIndex != -1) {
        monsterToKill.add(closestMonsterIndex)
      }
    }
    
    // Kill monsters (from highest index to lowest to avoid index shifting problems)
    val sortedIndices = monsterToKill.sortedDescending()
    sortedIndices.forEach { idx ->
      monsters.removeAt(idx)
    }
    
    return sortedIndices.size
  }

  fun simulate(): Int {
    var killCount = 0
    while (!checkFinished()) {
      killCount += shoot()
      moveMonster()
    }
    return killCount
  }

  fun placeArcher(positions: List<Int>): Int {
    reset()
    archers.clear()
    
    // Place archers at the castle row (r) at the specified columns
    positions.forEach { col ->
      archers.add(Pair(r, col))
    }
    
    return simulate()
  }
  
  fun findMaxKills(): Int {
    // Generate all combinations of 3 columns
    for (i in 0 until c) {
      for (j in i+1 until c) {
        for (k in j+1 until c) {
          val kills = placeArcher(listOf(i, j, k))
          maxKills = maxOf(maxKills, kills)
        }
      }
    }
    
    return maxKills
  }
}

fun main() {
  val br = BufferedReader(InputStreamReader(System.`in`))
  val (n, m, d) = br.readLine().split(" ").map { it.toInt() }
  
  val inputLines = mutableListOf<String>()
  for (i in 0 until n) {
    inputLines.add(br.readLine())
  }
  
  val game = Game(n, m, d, inputLines)
  val result = game.findMaxKills()
  println(result)
}
