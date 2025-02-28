import java.io.*;
import java.util.*;

class Sequence(val size: Int) {
  public lateinit var seq: IntArray

  constructor(size: Int, input: String): this(size) {
    seq = input.trim().split(" ").map { it.toInt() }.toIntArray()
  }

// Sliding Window
  fun process(): Long {
    var ans: Long = 0L
    val lastSeen = HashMap<Int, Int>() 
    var start = 0
    
    for (end in 0 until size) {
      val currentNum = seq[end]
      
      if (lastSeen.containsKey(currentNum) && lastSeen[currentNum]!! >= start) {
        start = lastSeen[currentNum]!! + 1 
      }
      
      ans += (end - start + 1) // The all possible set in unique set is unique
       
      lastSeen[currentNum] = end
    }
    
    return ans
  }
}

fun main() {
  val br = BufferedReader(InputStreamReader(System.`in`))
  val size = br.readLine().toInt()
  val list = br.readLine()

  val sequence = Sequence(size, list)
  println(sequence.process())

  br.close()
}

