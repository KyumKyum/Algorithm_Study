# Divide and Conquer

- 주어진 문제를 둘 이상의 부분 문제 (Sub Problems)로 나눈 뒤, 각 문제에 대한 답을 재귀적인 호출을 통해 계산 후, 각 문제의 답으로부터 전체 문제의 답을 계산하는 해법.

  - 기존에 존재하는 (Polymorphic한 시간 안에 해결할 수 있는) Bruteforce 알고리즘을 더욱 적은 양의 다항식으로 효율적이게 문제를 분할 (Divide)후, 정복(Conquer)하는 알고리즘이다.

- D&C는 각각의 분할된 문제는 다음과 같은 특징을 가지고 있다.

1. 분할된 문제는 기존의 문제와 성격이 동일하며, 입력의 크기만이 작아진 것이다.
2. 각각의 분할된 문제들은 독접적이다.
   > 💫 하나의 거대한 문제를 같은 크기의 부분 문제로 나누는 것. 즉, 모든 문제의 성격은 동일하지만, 입력을 나누어 동일한 성격의 문제에 넣고, 나중에 각 부분 문제의 결과를 종합하여 최종 결과를 얻는 알고리즘이다.

- D&C는 다음과 같은 구성 요소로 구성이 되어있다.

1. Divide: 문제를 더욱 작은 문제로 분할하는 과정.
2. Base Case: 더 이상의 작은 문제로 분할이 되지 않고, 주어진 상태로 답을 만들 수 있는 기저 사례.
3. Merge: 각 분할된 문제에 대한 답을 원래 문제에 대한 최종 답으로 병합하는 과정.

- 각각의 sub problem이 중복되면 성능의 저하가 일어나게 되는데, 이러한 성능의 저하는 [Dynamic Programming](https://github.com/KyumKyum/Algorithm_Study/tree/main/DP)으로 해결하여 더욱 효율적인 알고리즘을 만들 수 있다.

---

### BOJ

- 색종이 만들기 (2630) [2630](https://github.com/KyumKyum/Algorithm_Study/blob/main/DivideAndConquer/2630.cpp) [S2]
- 별 찍기 - 10 (2447) [2447](https://github.com/KyumKyum/Algorithm_Study/blob/main/DivideAndConquer/2447.py) [G5]
- Moo 게임 (5904) [5904](https://github.com/KyumKyum/Algorithm_Study/blob/main/DivideAndConquer/5904.py) [G5]
- 별 찍기 - 11 (2448) [2448](https://github.com/KyumKyum/Algorithm_Study/blob/main/DivideAndConquer/2448.py) [G4]
- 행렬 제곱 (10830) [10830](https://github.com/KyumKyum/Algorithm_Study/blob/main/DivideAndConquer/10830.py) [G4]
- 사분면 (1891) [1891](https://github.com/KyumKyum/Algorithm_Study/blob/main/DivideAndConquer/1891.py) [G4]
- Secret Code (9994) [9994](https://github.com/KyumKyum/Algorithm_Study/blob/main/DivideAndConquer/9994.py) [G3]
- 박스 채우기 (1493) [1493](https://github.com/KyumKyum/Algorithm_Study/blob/main/DivideAndConquer/1493.cpp) [G3]
- 피보나치 수 6 (11444) [11444](https://github.com/KyumKyum/Algorithm_Study/blob/main/DivideAndConquer/11444.cpp) [G2]
- 히스토그램 (1725) [1725](https://github.com/KyumKyum/Algorithm_Study/blob/main/DivideAndConquer/1725.py) [P5]
- (1725와 동일한 문제) 히스토그램에서 가장 큰 직사각형 (6549) [6549](https://github.com/KyumKyum/Algorithm_Study/blob/main/DivideAndConquer/6549.py) [P5]
