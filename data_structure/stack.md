---
title: 스택
layout: blog
parent: 자료 구조
nav_order: 1
---

# **스택(Stack)**
{: .no_toc .fs-9 }

<br/>

1. TOC
{:toc}

---

## 스택이란?
{: .fw-700 }

<div class="code-example" markdown="1">
**스택**은 **LIFO(Last In First Out)** 형식을 따르는 자료구조이다.
스택에 데이터가 들어오는 연산을 **푸시(push)**라고 하고,
데이터가 빠져나가는 연산을 **팝(pop)**이라고 부른다.
스택에서 가장 마지막으로 들어온 데이터이자 가장 먼저 나가게 될 데이터를 **탑(top)** 혹은 **탑 포인터(top pointer)**이라고 하는데,
일반적으로 스택에서 데이터 조회는 탑 포인터에 있는 데이터만을 대상으로 하게 된다.

### 구현 코드
{: .fs-6 .fw-700 }

<div class="code-example" markdown="1">

#### 배열을 통해 구현한 코드
{: .fs-5 .fw-700 .my-2 }

스택을 C++에서 배열을 통해 구현한 코드는 다음과 같다.
{: .mb-1 }

```cpp
#define MAX 1000

template <class T>
struct Stack {
    T buffer[MAX];
    int index = 0;

    bool empty() {
        return index == 0;
    }

    int size() {
        return index;
    }

    T top() {
        if(empty())
            return -1;
        return buffer[index-1];
    }

    void push(T value) {
        if(index == MAX)
            return;
        buffer[index++] = value;
    }

    T pop() {
        if(empty())
            return -1;
        return buffer[--index];
    }
};
```
{: .lh-0 .fw-700 .fs-4 }

#### 링크드 리스트로 구현한 코드
{: .fs-5 .fw-700 .mb-2 }

배열 외에도 링크드 리스트를 통해서도 스택을 구현할 수 있는데,
C++로 구현한 코드는 다음과 같다.
{: .mb-1 }

```cpp
#define MAX 1000

template <class T>
struct Node {
    T value;
    Node<T>* front;
};

template <class T>
struct Stack {
    Node<T>* pointer = NULL;
    int index = 0;

    bool empty() {
        return pointer == NULL;
    }

    int size() {
        return index;
    }

    T top() {
        if(empty())
            return -1;
        return pointer->value;
    }

    void push(T value) {
        if(index == MAX)
            return;

        Node<T> *node = new Node<T>;
        node->value = value;
        node->front = pointer;
        pointer = node;

        index++;
    }

    T pop() {
        if(empty())
            return -1;
        
        T value = pointer->value;
        Node<T>* front = pointer->front;
        delete pointer;

        pointer = front;
        return value;
    }
};
```
{: .lh-0 .fw-700 .fs-4 }
</div>
</div>

## 스택의 특징
{: .fw-700 }

<div class="code-example" markdown="1">
앞서 나온 LIFO(Last In First Out)라는 용어에서 알 수 있듯이, 스택은 **가장 나중에 들어온 데이터를 먼저 꺼내는 입출력 방식**을 사용한다.
데이터를 이용할 때, 탑 포인터에서만 입출력 및 조회가 이루어지기 때문에 `O(1)`의 시간 복잡도를 가진다.
</div>

## 참고 사이트
{: .fs-5 .fw-700 }

* [스택 자료 구조에 관한 구현 및 관련 문제](https://www.geeksforgeeks.org/stack-data-structure/)