import java.io.*;
import java.util.*;
import kotlin.Int

class Road(val num: Int) {
  private val graph = Array(num) {ArrayList<Pair<Int, Int>>()}

  fun add(src: Int, dest: Int, value: Int){
    graph[src].add(Pair(dest, value))
  }

  fun process(start: Int): IntArray{ // Djkstra
    val distance = IntArray(num) { Int.MAX_VALUE }
    distance[start] = 0 // start
    val pq = PriorityQueue<Pair<Int, Int>>(compareBy { it.second })

    pq.add(Pair(start, 0))

    while(pq.isNotEmpty()){
      val (curVertex, curDistance) = pq.poll()
      if(curDistance > distance[curVertex]) continue // Already found better path

      graph[curVertex].forEach{(neighbor, weight) -> 
        val newDistance = distance[curVertex] + weight
        if(newDistance < distance[neighbor]){
          // Update
          distance[neighbor] = newDistance
          pq.add(Pair(neighbor, newDistance))
        }
      }
    }

    return distance
  }

}

fun main() {
  val br = BufferedReader(InputStreamReader(System.`in`))

  val firstLine = br.readLine().trim().split(" ")
  val vertex = firstLine[0].toInt()
  val num = firstLine[1].toInt()

  val road = Road(vertex + 1) // 1 base

  for(i in 0 until num){
    val line = br.readLine().trim().split(" ")
    road.add(line[0].toInt(), line[1].toInt(), line[2].toInt())
    road.add(line[1].toInt(), line[0].toInt(), line[2].toInt()) // Bi-directional
  }

  val distance = road.process(1)

  println(distance[vertex])

  br.close()
}
