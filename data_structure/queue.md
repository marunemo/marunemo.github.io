---
title: 큐
layout: blog
parent: 자료 구조
nav_order: 1
---

# **큐(Queue)**
{: .no_toc .fs-9 }

<br/>

1. TOC
{:toc}

---

## 큐란?
{: .fw-700 }

<div class="code-example" markdown="1">
**큐**는 **FIFO(First In First Out)** 형식을 따르는 자료구조이다.
큐에 데이터가 들어오는 연산을 **인큐(enqueue)**라고 하고,
데이터가 빠져나가는 연산을 **디큐(dequeue)**이라고 부른다.
또한, 큐에서 가장 먼저 나가게 될 데이터의 위치를 **프론트(front)** 혹은 **헤드(head)**이라고 부르며,
반대로 가장 최근에 들어온 데이터의 위치를 **리어(rear)** 혹은 **테일(tail)**이라 부른다.
조회는 일반적으로 프론트에 있는 데이터를 대상으로 하지만, 리어도 조회할 수 있는 경우도 있다.

### 구현 코드
{: .fs-6 .fw-700 }

<div class="code-example" markdown="1">

#### 배열을 통해 구현한 코드
{: .fs-5 .fw-700 .my-2 }

큐를 C++에서 배열을 통해 구현한 코드는 다음과 같다.
{: .mb-1 }

```cpp

```
{: .lh-0 .fw-700 .fs-4 }

#### 링크드 리스트로 구현한 코드
{: .fs-5 .fw-700 .mb-2 }

배열 외에도 링크드 리스트를 통해서도 큐를 구현할 수 있는데,
C++로 구현한 코드는 다음과 같다.
{: .mb-1 }

```cpp

```
{: .lh-0 .fw-700 .fs-4 }
</div>
</div>

## 큐의 특징
{: .fw-700 }

<div class="code-example" markdown="1">
앞서 나온 FIFO(First In First Out)라는 용어에서 알 수 있듯이, 큐는 **가장 먼저 들어온 데이터부터 꺼내는 입출력 방식**을 사용한다.
데이터를 이용할 때, 처음과 끝 인덱스인 프론트와 리어에서만 입출력 및 조회가 이루어지기 때문에 `O(1)`의 시간 복잡도를 가진다.
</div>

## 원형 큐(Circular Queue)
{: .fw-700 }

<div class="code-example" markdown="1">

</div>

## 덱(Deque)
{: .fw-700 }

<div class="code-example" markdown="1">

</div>

## 우선순위 큐(Priority Queue)
{: .fw-700 }

<div class="code-example" markdown="1">

</div>

## 참고 사이트
{: .fs-5 .fw-700 }

* [스택 자료 구조에 관한 구현 및 관련 문제](https://www.geeksforgeeks.org/stack-data-structure/)