import java.io.*;
import java.util.*;
import kotlin.Int

class GoodNumbers(val size: Int){
    private val numbers: MutableList<Long> = MutableList(size) { 0L }

    constructor(size: Int, list: List<String>) : this(size) {
        for (i in 0 until numbers.size) {
            numbers[i] = list[i].toLong()
        }
        
        numbers.sort()
    }


    fun countGoodNumbers(): Int {
      var ans: Int = 0

      for(i in 0 until numbers.size){
        val tgt = numbers[i]

        var s = 0
        var e = numbers.size - 1

        while(s != e){
          if(s == i) {
            // Skip the same index
            s++
          }else if(e == i){
            e--
          }else {
            // Check
            val cand = numbers[s] + numbers[e]
            if(cand == tgt){
              // Found!
              ans++
              break
            }else if(cand > tgt){
              // Candidate is bigger, reduce the rear
              e--
            }else{
              // Candidate is smaller, increase the front
              s++
            }
          }
        }
      }

      return ans
    }

}

fun main() {
  val br = BufferedReader(InputStreamReader(System.`in`))
  val size = br.readLine().trim().toInt()
  val list = br.readLine().trim().split(" ")

  val goodNumbers = GoodNumbers(size, list)

  println(goodNumbers.countGoodNumbers())
  br.close()
}
