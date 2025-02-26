import java.io.*;
import java.util.*;
import kotlin.io.readln

// To execute Kotlin code, please define a top level function named main

class Node(val value: Int) {
  var isPrefix: Boolean = false
  var child: MutableList<Node> = mutableListOf()
}

var tc = 0;


fun verify(phoneNum: String, node: Node): Boolean {

  if(phoneNum.length <= 0) {
    node.isPrefix = true // New prefix
    
    if(node.child.size > 0){
        return false; // This will be the prefix of another phone number
    }
    
    return true // This is verified.
  }

  if(node.isPrefix){
    // This is a prefix of another phone number
    return false;
  }

  val firstNum: Int = Character.getNumericValue(phoneNum.get(0))
  var tgtNode: Node = Node(-1); // This is an temporary initialization. lateinit gives me NZEC
  var found: Boolean = false;
  if(node.child.size > 0){
    node.child.forEach{ele -> 
      if(ele.value == firstNum){
        tgtNode = ele
        found = true
      }
    }

    if(!found){
      // Create new child
      tgtNode = Node(firstNum);
      node.child.add(tgtNode);
    }
  }else{
    // New child
    tgtNode = Node(firstNum);
    node.child.add(tgtNode);
  }

  return verify(phoneNum.substring(1), tgtNode);
}

fun main() {
    val reader = BufferedReader(InputStreamReader(System.`in`))
    val writer = BufferedWriter(OutputStreamWriter(System.out))
    
    val tc = reader.readLine().trim().toInt()
        
        for (i in 0 until tc) {
            val root = Node(-1)
            val n = reader.readLine().trim().toInt()
            var flag = true
            
            for (j in 0 until n) {
                val phoneNum = reader.readLine().trim()
                
                if (flag && !verify(phoneNum, root)) {
                    flag = false
                }
            }
            
            writer.write(if (flag) "YES\n" else "NO\n")
        }
        
        writer.flush()
        reader.close()
        writer.close()

}
