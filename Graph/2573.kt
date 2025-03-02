import java.io.*;
import java.util.*;

// To execute Kotlin code, please define a top level function named main

class Iceberg(val r: Int, val c: Int){

  private var board: MutableList<IntArray> = mutableListOf()
  private var visited: MutableList<MutableList<Boolean>> = MutableList(r) { MutableList(c) {false}
  }
  private val iceberg: ArrayDeque<Pair<Int, Int>> = ArrayDeque<Pair<Int, Int>>()
  private val dx: IntArray = intArrayOf(-1, 0, 1, 0)
  private val dy: IntArray = intArrayOf(0, 1, 0 ,-1)


  constructor(r: Int, c: Int, inputs: MutableList<String>): this(r,c) {
    inputs.forEach { input -> 
      board.add(input.trim().split(" ").map{it.toInt()}.toIntArray())
    }

    //Init
    board.forEachIndexed{rIdx, row ->
      for(cIdx in 0 until row.size){
        if(row[cIdx] == 0) continue;
        iceberg.addLast(Pair(rIdx,cIdx)) // Enlist the ices
      }
    }
  }

  fun reset(){
    visited = MutableList(r) { MutableList(c) {false} }
  }

  fun isValid(ix: Int, iy: Int): Boolean {
    return ix >= 0 && ix < r && iy >= 0 && iy < c
  }

  fun melt(){
    val temp: MutableList<IntArray> = board.map { it.copyOf() }.toMutableList()

    for(i in 0 until iceberg.size){
      val (ix, iy) = iceberg.first()
      iceberg.removeFirst()

      for(j in 0 until 4){
        val nx = ix + dx[j]
        val ny = iy + dy[j]

        if(isValid(nx, ny) && board[nx][ny] == 0 && temp[ix][iy] > 0){
          // Adjacent to water
          temp[ix][iy] -= 1
        }
      }

      if(temp[ix][iy] > 0){
        // Put again
        iceberg.addLast(Pair(ix, iy))
      }
    }

    board = temp
  }

  fun bfs(rIdx: Int, cIdx: Int) {
    visited[rIdx][cIdx] = true;
    for(i in 0 until 4){
      val nx = rIdx + dx[i]
      val ny = cIdx + dy[i]

      if(isValid(nx, ny) && board[nx][ny] != 0 && !visited[nx][ny]){
        //Visit
        bfs(nx, ny)
      }
    }
  }

  fun check(): Boolean {
    val (rIdx, cIdx) = iceberg.first()
    bfs(rIdx, cIdx)

    for(i in 0 until r){
      for(j in 0 until c){
        if(!visited[i][j] && board[i][j] > 0){
          // Iceberg not visited exists! The iceberg had been separated.
          return true
        }
      }
    }

    return false
  }

  fun simulate(): Int{
    var year: Int = 0

    while(!iceberg.isEmpty()){
      if(check()) return year
      reset()
      melt()
      year++
    }

    // Iceberg is empty
    // All icebery is melted without being separated
    return 0
  }

}

fun main() {
  val br = BufferedReader(InputStreamReader(System.`in`))
  val (r, c) = br.readLine().trim().split(" ").map{it.toInt()}

  val list: MutableList<String> = mutableListOf()
  
  for(i in 0 until r){
    list.add(br.readLine())
  }

  val iceberg = Iceberg(r, c, list)

  println(iceberg.simulate())

  br.close()
}
