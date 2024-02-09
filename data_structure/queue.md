---
title: 큐
layout: blog
parent: 자료 구조
nav_order: 2
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
#define MAX 1000

template <class T>
struct Queue {
    T buffer[MAX];
    int head = 0;
    int tail = 0;

    bool empty() {
        return head == tail;
    }

    int size() {
        return tail - head;
    }

    T front() {
        if(empty())
            return -1;
        return buffer[head];
    }

    T rear() {
        if(empty())
            return -1;
        return buffer[tail-1];
    }

    void enqueue(T value) {
        if(tail == MAX)
            return;
        buffer[tail++] = value;
    }

    T dequeue() {
        if(empty())
            return -1;
        return buffer[head++];        
    }
};
```
{: .lh-0 .fw-700 .fs-4 }

#### 링크드 리스트로 구현한 코드
{: .fs-5 .fw-700 .mb-2 }

배열 외에도 링크드 리스트를 통해서도 큐를 구현할 수 있는데,
C++로 구현한 코드는 다음과 같다.
{: .mb-1 }

```cpp
#define MAX 1000

template <class T>
struct Node {
    T value;
    Node<T>* next;
};

template <class T>
struct Queue {
    Node<T>* head = NULL;
    Node<T>* tail = NULL;
    int index = 0;

    bool empty() {
        return head == NULL;
    }

    int size() {
        return index;
    }

    T front() {
        if(empty())
            return -1;
        return head->value;
    }

    T rear() {
        if(empty())
            return -1;
        return tail->value;
    }

    void enqueue(T value) {
        if(index == MAX)
            return;

        Node<T> *node = new Node<T>;
        node->value = value;
        node->next = NULL;
        
        if(empty())
            head = tail = node;
        else {
            tail->next = node;
            tail = node;
        }

        index++;
    }

    T dequeue() {
        if(empty())
            return -1;
        
        T value = head->value;
        Node<T>* next = head->next;
        delete head;

        index--;
        head = next;
        return value;
    }
};
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
**원형 큐**는 위의 큐를 구현하는 방식 중 배열을 기반으로 하는 큐의 문제점을 보완하기 위한 큐이다.
배열을 기반으로 하는 큐는 스택과 달리 데이터의 입출력이 이루어지는 위치가 프론트와 리어로 각각 다르기 때문에,
입출력을 반복하다보면 배열의 앞의 인덱스들이 사용되지 않은 채로 리어가 배열의 크기까지 도달하게 된다.
이렇듯 배열의 사용되지 못하는 공간을 활용하기 위한 방안으로 구현할 수 있는 큐가 바로 원형 큐인 것이다.

### 배열로 구현한 코드
{: .fs-5 .fw-700 .mb-2 }

원형 큐를 C++로 구현한 코드는 다음과 같다.
{: .mb-1 }

```cpp
#define MAX 1000

template <class T>
struct Queue {
    T buffer[MAX];
    int head = 0;
    int tail = 0;

    bool empty() {
        return head == tail;
    }

    int size() {
        if(tail < head)
            return tail + MAX - head;
        return tail - head;
    }

    T front() {
        if(empty())
            return -1;
        return buffer[head];
    }

    T rear() {
        if(empty())
            return -1;
        if(tail == 0)
            return buffer[MAX-1];
        return buffer[tail-1];
    }

    void enqueue(T value) {
        if((tail + 1) % MAX == head)
            return;
        buffer[tail] = value;
        tail = (tail + 1) % MAX;
    }

    T dequeue() {
        if(empty())
            return -1;
        T value = buffer[head];
        head = (head + 1) % MAX;
        return value;
    }
};
```
{: .lh-0 .fw-700 .fs-4 }
</div>

## 덱(Deque)
{: .fw-700 }

<div class="code-example" markdown="1">
**덱**은 큐와 스택의 특징을 섞어 프론트와 리어 모두에서 데이터를 입출력할 수 있도록 한 자료구조이다.

### 링크드 리스트로 구현한 코드
{: .fs-5 .fw-700 .mb-2 }

덱을 링크드 리스트를 통해 C++로 구현한 코드는 다음과 같다.
{: .mb-1 }

```cpp
#define MAX 1000

template <class T>
struct Node {
    T value;
    Node<T>* pre;
    Node<T>* next;
};

template <class T>
struct Deque {
    Node<T>* head = NULL;
    Node<T>* tail = NULL;
    int index = 0;

    bool empty() {
        return index == 0;
    }

    int size() {
        return index;
    }

    T front() {
        if(empty())
            return -1;
        return head->value;
    }

    T rear() {
        if(empty())
            return -1;
        return tail->value;
    }

    void push_front(T value) {
        if(index == MAX)
            return;

        Node<T> *node = new Node<T>;
        node->value = value;
        node->pre = NULL;
        node->next = NULL;
        
        if(empty())
            head = tail = node;
        else {
            node->next = head;
            head->pre = node;
            head = node;
        }

        index++;
    }

    void push_back(T value) {
        if(index == MAX)
            return;

        Node<T> *node = new Node<T>;
        node->value = value;
        node->pre = NULL;
        node->next = NULL;
        
        if(empty())
            head = tail = node;
        else {
            node->pre = tail;
            tail->next = node;
            tail = node;
        }

        index++;
    }

    T pop_front() {
        if(empty())
            return -1;
        
        T value = head->value;
        Node<T>* next = head->next;
        delete head;

        index--;
        head = next;
        if(head)
            head->pre = NULL;
        return value;
    }

    T pop_back() {
        if(empty())
            return -1;
        
        T value = tail->value;
        Node<T>* next = tail->pre;
        delete tail;

        index--;
        tail = next;
        if(tail)
            tail->next = NULL;
        return value;
    }
};
```
{: .lh-0 .fw-700 .fs-4 }

</div>

## 우선순위 큐(Priority Queue)
{: .fw-700 }

<div class="code-example" markdown="1">
**우선순위 큐**은 데이터를 입력(인큐)할 때는 동일하지만,
데이터를 출력(디큐)할 때에는 임의의 우선순위가 높은 원소부터 빼내는 자료 구조이다.
[배열](https://www.geeksforgeeks.org/priority-queue-using-array-in-c/)이나
[링크드 리스트](https://www.geeksforgeeks.org/priority-queue-using-linked-list/)를 통해 구현하는 것도 가능하지만,
이번에는 [힙 트리](https://www.geeksforgeeks.org/priority-queue-using-binary-heap/)를 통해 구현해 보았다.

### 이진 힙으로 구현한 코드
{: .fs-5 .fw-700 .mb-2 }

우선순위 큐를 이진 힙을 통해 C++로 구현한 코드는 다음과 같다.
{: .mb-1 }

```cpp
#define MAX 1000
#define INF (~0U >> 2)

template <class T>
struct PriorityQueue {
    T buffer[MAX];
    int buffer_size = 0;

    PriorityQueue() {
        for(int i = 0; i < MAX; i++)
            buffer[i] = -INF;
    }

    int _parent(int i) {
        return (i - 1) / 2;
    }

    int _leftChild(int i) {
        return (2 * i) + 1;
    }

    int _rightChild(int i) {
        return (2 * i) + 2;
    }

    void push(int value) {
        if(buffer_size == MAX)
            return;
        
        int index = buffer_size++;
        buffer[index] = value;
        
        // c++의 priority_queue에서 compare function의 대소 관계가 반대인 이유로 추측
        while(index > 0 && buffer[_parent(index)] > buffer[index]) {
            T tmp = buffer[_parent(index)];
            buffer[_parent(index)] = buffer[index];
            buffer[index] = tmp;
            
            index = _parent(index);
        }
    }

    T pop() {
        if(empty())
            return -INF;

        int value = buffer[0];
        int index = 0;
        int next;
        while(_leftChild(index) < MAX) {
            if(_rightChild(index) >= MAX)
                next = _leftChild(index);
            else if(buffer[_leftChild(index)] == -INF && buffer[_rightChild(index)] == -INF) {
                buffer[index] = -INF;
                break;
            }
            else if(buffer[_leftChild(index)] == -INF)
                next = _rightChild(index);
            else if(buffer[_rightChild(index)] == -INF)
                next = _leftChild(index);
            else if(buffer[_leftChild(index)] < buffer[_rightChild(index)])
                next = _leftChild(index);
            else
                next = _rightChild(index);
            buffer[index] = buffer[next];
            index = next;
            buffer[index] = -INF;
        }
        buffer_size--;
        return value;
    }

    T top() {
        return buffer[0];
    }

    int size() {
        return buffer_size;
    }

    bool empty() {
        return buffer_size == 0;
    }
};
```
{: .lh-0 .fw-700 .fs-4 }
</div>

## 참고 사이트
{: .fs-5 .fw-700 }

* [큐 자료 구조에 관한 구현 및 관련 문제](https://www.geeksforgeeks.org/queue-data-structure/)
* [우선순위 큐에 대한 설명 및 구현](https://www.geeksforgeeks.org/priority-queue-set-1-introduction/)