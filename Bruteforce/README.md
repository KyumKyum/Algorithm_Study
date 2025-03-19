# Bruteforce

- 모든 가능한 경우의 수를 탐색하여 방법을 찾는 방법. (Exhaustive Searching)
  - 모든 조합 찾기 / 나열하기
  - 모든 순열 만들기
  - 2^n가지 경우의 수 만들기. (n개에 대한 경우의 수에 대한 답이 2가지인 경우 (ex: Yex/No))
  - 최적화 문제.


- Base Case (기저 사례)
  - 더 이상의 반복이 필요 없는, 최소한의 작업 상태. (return 발생)
    - 가능한 case
    1. 오류 케이스 (더 이상 탐색할 필요가 없음)
    2. 정답을 찾은 경우. (해당 경우에 대한 정답 여부를 찾아 더 이상 찾을 필요가 없을 경우
  - 항상 오류 케이스에 대한 return을 먼저하는 것을 습관화 하기. (Corner Case 방지)


- 중복 (Duplication)
  - 순서가 중요하지 않거나, 모든 조합을 구하는 문제와 같은 곳에서는 중복이 오류의 원인이 됨
    - (a,b), (b,a) 모두 같은 것이지만, 이를 다르게 체크를 하는 경우.
  - 순서를 강제하여 해당 중복을 제거. 
    - a,b,c,d,e에 대해서 찾을 때, b에 대한 조합을 검사할 때 이 전인 a에 대해서는 신경을 쓰지 않는 것.
      - 즉, 항상 본인보다 앞에 있는 element로만 조합을 찾아주는 것.
  - 문제를 풀 때 해당 케이스가 중복인지, 문제를 풀 때 검사를 해야 하는 케이스 인지는 꼭꼭 확인하기.


- 백트래킹 (Back-tracking)
  - 기존의 Bruteforce는 모든 케이스를 나열해서 푸는 것.
  - 백 트래킹은, 답이 아니거나 다른 답을 찾아야 할 시, 한 단계 되돌아가서 다시 찾아가는 기법.
    - A,B,C,D,E의 경우, {ABCDE}를 찾았으면, 전 단계로 돌아가 ({ABC}) 새로운 답을 찾아가는 것 {ABCED}
  - 이때 다음 상태로 나아갈 방향을 찾을 때, 해당 방향에 오류가 있어서 가망이 없을 경우, 해당 방향은 전체를 무시. (가지 치기: Pruning)
  - Tree, Graph에 더욱 자세히 설명할 예정. 일단 지금은 '조금 더 효율적인 Bruteforce' 정도로 이해하기.


--------------------------------

# Problem List
### Algospot
- PICNIC [Picnic](https://github.com/KyumKyum/Algorithm_Study/blob/main/Bruteforce/picnic.py).
- CLOCKSYNC [Clocksync](https://github.com/KyumKyum/Algorithm_Study/blob/main/Bruteforce/clocksync.py)

### BOJ
- 블랙잭 (2798) [2978](https://github.com/KyumKyum/Algorithm_Study/blob/main/Bruteforce/2978.py) <span style="color:#A6442E;">[B2]</span>
- 체스판 다시 칠하기 (1018) [1018](https://github.com/KyumKyum/Algorithm_Study/blob/main/Bruteforce/1018.py) <span style="color:#ADADAD;">[S4]</span>
- N과 M (2) (15650) [15650](https://github.com/KyumKyum/Algorithm_Study/blob/main/Bruteforce/15650.cpp) [S3]
- N과 M (3) (15651) [15651](https://github.com/KyumKyum/Algorithm_Study/blob/main/Bruteforce/15651.cpp) [S3]
- N과 M (4) (15652) [15652](https://github.com/KyumKyum/Algorithm_Study/blob/main/Bruteforce/15652.cpp) [S3]
- N과 M (5) (15654) [15654](https://github.com/KyumKyum/Algorithm_Study/blob/main/Bruteforce/15654.cpp) [S3]
- N과 M (9) (15663) [15663](https://github.com/KyumKyum/Algorithm_Study/blob/main/Bruteforce/15663.cpp) [S3]
- 시계 맞추기 (27532) [27532](https://github.com/KyumKyum/Algorithm_Study/blob/main/Bruteforce/27532.py) [G5]
- 감시 피하기 (18428) [18428](https://github.com/KyumKyum/Algorithm_Study/blob/main/Bruteforce/18428.py) [G5]
- 암호 만들기 (1759) [18428](https://github.com/KyumKyum/Algorithm_Study/blob/main/Bruteforce/1759.cpp) [G5]
- N-Queen (9663) [9663](https://github.com/KyumKyum/Algorithm_Study/blob/main/Bruteforce/9663.py) [G4]
- 월드컵 (6987) [6987](https://github.com/KyumKyum/Algorithm_Study/blob/main/Bruteforce/6987.py) [G4]
- 연구소 (14502) [14502](https://github.com/KyumKyum/Algorithm_Study/blob/main/Bruteforce/14502.cpp) [G4]
- 연구소 3 (17142) [17142](https://github.com/KyumKyum/Algorithm_Study/blob/main/Bruteforce/17142.cpp) [G3]
- Maaaaaaaaaze (16985) [16985](https://github.com/KyumKyum/Algorithm_Study/blob/main/Bruteforce/16985.cpp) [G2]
