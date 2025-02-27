import java.io.*;
import java.util.*;

// To execute Kotlin code, please define a top level function named main

class LightBulb(val size: Int){
  private lateinit var received: IntArray
  private lateinit var processed: IntArray
  private lateinit var desired: IntArray

  constructor(size: Int, fl: String, sl: String): this(size) {
    received = IntArray(size)
    desired = IntArray(size)

    fl.trim().forEachIndexed { idx, char -> received[idx] = Character.getNumericValue(char) }
    sl.trim().forEachIndexed { idx, char -> desired[idx] = Character.getNumericValue(char) }

    processed = received.copyOf()
  }

  fun toggle(idx: Int){
    if(processed[idx] == 1) processed[idx] = 0
    else processed[idx] = 1
  }

  fun click(idx: Int){
    if(idx - 1 >= 0){
      toggle(idx - 1)
    }
    toggle(idx)
    if(idx + 1 < size){
      toggle(idx + 1)
    }
  }

  fun greedy(clk: Int): Int{
    var ret = clk
    for(i in 1 until size){
      if(processed[i - 1] != desired[i - 1]){
        click(i)
        ret++
      }
    }

    return ret
  }

  fun compare(): Boolean {
    for(i in 0 until size){
      if(processed[i] != desired[i]) return false
    }
    return true
  }

  fun checkClickNum(): Int {
    
    // Case 1: First lightbulb clicked
    click(0)
    var firstAns = greedy(1)
    if(!compare()) firstAns = -1
    
    processed = received.copyOf() // Reset
    // Case 2: First lightbulb not clicked
    var secondAns = greedy(0)
    
    if(!compare()) secondAns = -1

    if(firstAns == -1) return secondAns
    if(secondAns == -1) return firstAns

    return minOf(firstAns, secondAns)
  }
}

fun main() {
  val br = BufferedReader(InputStreamReader(System.`in`))

  val size = br.readLine().toInt()
  val fl = br.readLine()
  val sl = br.readLine()

  val lb = LightBulb(size, fl, sl)

  println(lb.checkClickNum())
  br.close()
}
