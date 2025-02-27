import java.io.*;
import java.util.*;
import kotlin.Int

class World(
  val height: Int,
  val width: Int
) {
  val road = IntArray(width)
  
  fun initRoad(input: List<String>){
    for(i in 0 until input.size){
      road[i] = input[i].toInt()
    }
  }

  fun rain(): Int {
    var drops = 0

    // Strategy:
    // Rain till the left.
    // Raindrops increase if the left block is 'higher'
      // Higher left block -> The drop is need to be pooled or already pooled in the same level
        // Need to check if there are higher block on the right

    for(i in 0 until height){
      // Maximum rain level: height

      for(j in 1 until width -1) {
          // Ignore the first and last level
          if(road[j - 1] > road[j]){
          // pooled

          // Naive approach: check if there is a higher right block
          for(k in j until width){
            if(road[k] > road[j]){
              road[j] += 1
              drops += 1
              break;
            }
          }
        }
      }
    }

    return drops
  }
}

fun main() {
  val br = BufferedReader(InputStreamReader(System.`in`))

  val line = br.readLine().trim().split(" ")
  val height = line[0].toInt()
  val width = line[1].toInt()

  val world = World(height, width)

  val road = br.readLine().trim().split(" ")
  world.initRoad(road)

  val drops = world.rain()

  println(drops)
  br.close()
}
