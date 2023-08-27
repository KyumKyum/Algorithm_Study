# Algorithm Study
## 알고리즘 스터디 관련 공부 자료 정리

=============================

  서비스 개발만 했던 내게 제일 부족한 점은 바로 코딩테스트 준비, 알고리즘 활용 지식이 아닐까 싶다.
  물론 실제 서비스 개발시 필요한 기본 CS 지식은 알고 있지만, 코딩 테스트를 준비하기 위한 지식은 충분하지 않다.
  이번 방학에 좋은 친구들을 모아서 이런 부족한 점에 대해서 공부하고 알아나갈 생각이다. 
  
  이 곳에는 내가 배운 것들과 문제 풀에 대해서 간단히 정리를 하는 공간이 될 것이다. 😎😎
  
-----------------------------
- [Bruteforce](https://github.com/KyumKyum/Algorithm_Study/tree/main/Bruteforce)
- [Divide And Conquer](https://github.com/KyumKyum/Algorithm_Study/tree/main/DivideAndConquer)
- [Dynamic Programming](https://github.com/KyumKyum/Algorithm_Study/tree/main/DP)
- [Greedy](https://github.com/KyumKyum/Algorithm_Study/tree/main/Greedy)
- [Stack](https://github.com/KyumKyum/Algorithm_Study/tree/main/Stack)
- [Queue](https://github.com/KyumKyum/Algorithm_Study/tree/main/Queue)
- [Deque](https://github.com/KyumKyum/Algorithm_Study/tree/main/Deque)
- [Tree](https://github.com/KyumKyum/Algorithm_Study/tree/main/Tree)
- [Graph](https://github.com/KyumKyum/Algorithm_Study/tree/main/Graph)
- [String](https://github.com/KyumKyum/Algorithm_Study/tree/main/String)
- [Bitmask](https://github.com/KyumKyum/Algorithm_Study/tree/main/Bitmask)
- [Implementation](https://github.com/KyumKyum/Algorithm_Study/tree/main/Implementation)
- [Miscellaneous](https://github.com/KyumKyum/Algorithm_Study/tree/main/Miscellaneous)

-----------------------------
### 명예의 전당 (Hall of Fame)
여기에는 내가 풀면서 난이도가 있었으면서도 되게 재밌었고, 공부가 되었던 문제들을 적을 것이다. 
> 고려 요소.
>  - 난이도. (얼마나 많은 절망을 나에게 안겨주었는지.)
>  - 배움. (얼마나 많은 성장을 하였는지.)
>  - 창의성. (얼마나 많은 "진짜 무친 문제다..."를 연발하게 했는지.)


> 각 문제에 대한 Comment는 문제에 대한 스포일러가 될 수도 있으니 Toggle로 달았다.


1. 전깃줄 [2565](https://www.acmicpc.net/problem/2565) (G5)
<details>
<summary>➡️ 전깃줄 (2565) comment</summary>
이걸 진짜 LIS로 풀 수 있을 거라고는 전혀 생각을 못했다... 3시간 고민하고 결국 풀이를 찾아봤는데, LIS로 푸는거 봤을 때 머리가 얼얼하더라ㅋㅋ
</details>

2. N-Queen [9663](https://www.acmicpc.net/problem/9663) (G4)
<details>
<summary>➡️ N-Queen (9663) comment</summary>
대각선 이동을 1차원 배열에 기록하여 푼다라는 접근은 너무 새로웠다. 여기서 내가 정말 마음에 와 닿았던 코멘트: "산으로 가고 있다면 아이디어를 다시 생각해보아요"ㅋㅋㅋ
</details>

3. 벽 부수고 이동하기 [2206](https://www.acmicpc.net/problem/27532) (G3)
<details>
<summary>➡️ 벽 부수고 이동하기 (2206) comment</summary>
재밌었기도 했고, BFS의 특징을 완전히 이해시켜준 문제. 특히 차원(?)을 나누어 접근해야 한다는 것과, 이미 queue에 있는 것을 재방문 하지 않도록 처리하는 로직을 생각해내는 과정은 정말 도움이 많이 되었다.
</details>


4. 할로윈의 양아치 [20303](https://www.acmicpc.net/problem/20303) (G3)
<details>
<summary>➡️ 할로윈의 양아치 (20303) comment</summary>
내가 계속 헷갈리던 Knapsack 관련 문제를 완전히 이해시켜준 고마운 문제. 그리고 문제를 푼 후에 solved.ac에서 정말 웃겼던 댓글: "친구들을 분리 집합으로 감싼 다음 어른들 몰래 배낭에 넣어버리는 양아치 스브러스의 이야기"
ㅋㅋㅋㅋㅋㅋㅋㅋㅋ 근데 정말 이렇게 풀었다!
</details>

5. 백조의 호수 [3197](https://www.acmicpc.net/problem/3197) (P5)
<details>
<summary>➡️ 백조의 호수(3197) comment</summary>
BFS 와 Disjoint Set을 정말 적절히 사용한데다가, 일반적인 BFS문제처럼 풀면 무조건 TLE가 나기에 다음 대상을 queue에 넣어 관리해야한다는 아이디어를 생각해야하는 문제이다. BFS는 초기에 단 한번만 이루어지고, 백조가 만날 수 있는가는 분리 집합으로 관리하는 문제.
할로윈의 양아치처럼 어렵지만 즐거운 문제였다.
</details>

6. 롤러코스터 [2873](https://www.acmicpc.net/problem/2873) (P3)
<details>
<summary>➡️ 롤러코스터(2873) comment</summary>
"구현은 자신 있지"라고 자신만만하던 나에게 철퇴를 때린 문제.
</details>