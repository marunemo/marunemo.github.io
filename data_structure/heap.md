---
title: 힙
layout: blog
parent: 자료 구조
nav_order: 3
---

# **힙(Heap)**
{: .no_toc .fs-9 }

<br/>

1. TOC
{:toc}

---

## 힙이란?
{: .fw-700 }

<div class="code-example" markdown="1">
**힙**는 값들의 최댓값이나 최솟값을 빠르게 찾을 수 있는 자료 구조이다.
힙은 이진 트리로 이루어져 있기 때문에, 힙 트리(heap tree) 혹은 이진 힙(binary heap)이라고도 불린다.
힙의 각 상위 노드와 하위 노드의 대소 관계에 따라 [최대 힙(Max Heap)](#최대-힙max-heap)과 [최소 힙(Min Heap)](#최소-힙min-heap)으로 구분된다.
</div>

## 힙의 특징
{: .fw-700 }

<div class="code-example" markdown="1">
힙의 루트 노드에는 항상 모든 노드 중 최댓값이나 최솟값이 저장되기 때문에,
데이터 조회에 대한 시간 복잡도는 루트 노트만 확인하면 되므로 `O(1)`이 나오게 된다.
데이터의 삽입은 리프 노드부터 시작하여 데이터의 대소 관계에 따라 상위 노드로 올라가는 방식으로 이루어지며,
데이터의 삭제는 루트 노드를 제거하고 마지막 리프 노드를 루트 노드로 삽입하여 대소 관계에 따라 하위 노드로 내려가는 방식으로 이루어진다.
이때, 힙은 이진 트리로 이루어져 있기 때문에, 데이터의 대소 관계에 따라 노드가 이동하는 과정의 시간 복잡도는 `O(log₂N)`이다.
</div>

## 최대 힙(Max Heap)
{: .fw-700 }

<div class="code-example" markdown="1">
**최대 힙**은 루트 노드에 모든 노드의 최댓값이 저장되어 있고,
하위 노드로 갈수록 그 값이 작아지는 힙의 종류이다.
때문에, 부모 노드는 항상 자식 노드보다 큰 값이 저장되어 있다는 특징이 있다.

### 구현 코드
{: .fs-5 .fw-700 .mb-2 }

최대 힙을 C++로 구현한 코드는 다음과 같다.
{: .mb-1 }

```cpp
#define MAX 1000
#define INF (~0U >> 2)

template <class T>
struct MaxHeap {
    int tree[MAX];
    int tree_size = 0;

    int _parent(int i) {
        return (i - 1) / 2;
    }

    int _leftChild(int i) {
        return (i * 2) + 1;
    }

    int _rightChild(int i) {
        return (i * 2) + 2;
    }

    bool empty() {
        return tree_size == 0;
    }

    int size() {
        return tree_size;
    }

    T root() {
        if(empty())
            return -INF;
        return tree[0];
    }

    void insert(T value) {
        if(tree_size == MAX)
            return;
        
        int index = tree_size++;
        tree[index] = value;

        while(index > 0 && tree[_parent(index)] < tree[index]) {
            T tmp = tree[_parent(index)];
            tree[_parent(index)] = tree[index];
            tree[index] = tmp;

            index = _parent(index);
        }
    }

    T remove() {
        if(empty())
            return -INF;
        
        T value = tree[0];
        tree[0] = tree[--tree_size];

        int index = 0;
        while(true) {
            int next = index;
            int left = _leftChild(index);
            int right = _rightChild(index);
            if(left < tree_size && tree[left] > tree[next])
                next = left;
            if(right < tree_size && tree[right] > tree[next])
                next = right;

            if(index == next)
                break;
            
            T tmp = tree[next];
            tree[next] = tree[index];
            tree[index] = tmp;

            index = next;
        }

        return value;
    }
};
```
{: .lh-0 .fw-700 .fs-4 }
</div>

## 최소 힙(Min Heap)
{: .fw-700 }

<div class="code-example" markdown="1">
**최소 힙**은 최대 힙과 반대로 루트 노드에 모든 노드의 최솟값이 저장되어 있고,
하위 노드로 갈수록 그 값이 커지는 힙의 종류이다.
때문에, 부모 노드는 항상 자식 노드보다 작은 값이 저장되어 있다는 특징이 있다.

### 구현 코드
{: .fs-5 .fw-700 .mb-2 }

최소 힙을 C++로 구현한 코드는 다음과 같다.
사실상 최대 힙의 코드 삽입 및 삭제에서 대소 관계 비교 부분만 반대로 바꾸어 주면 된다.
{: .mb-1 }

```cpp
#define MAX 1000
#define INF (~0U >> 2)

template <class T>
struct MinHeap {
    int tree[MAX];
    int tree_size = 0;

    int _parent(int i) {
        return (i - 1) / 2;
    }

    int _leftChild(int i) {
        return (i * 2) + 1;
    }

    int _rightChild(int i) {
        return (i * 2) + 2;
    }

    bool empty() {
        return tree_size == 0;
    }

    int size() {
        return tree_size;
    }

    T root() {
        if(empty())
            return -INF;
        return tree[0];
    }

    void insert(T value) {
        if(tree_size == MAX)
            return;
        
        int index = tree_size++;
        tree[index] = value;

        while(index > 0 && tree[_parent(index)] > tree[index]) {
            T tmp = tree[_parent(index)];
            tree[_parent(index)] = tree[index];
            tree[index] = tmp;

            index = _parent(index);
        }
    }

    T remove() {
        if(empty())
            return -INF;
        
        T value = tree[0];
        tree[0] = tree[--tree_size];

        int index = 0;
        while(true) {
            int next = index;
            int left = _leftChild(index);
            int right = _rightChild(index);
            if(left < tree_size && tree[left] < tree[next])
                next = left;
            if(right < tree_size && tree[right] < tree[next])
                next = right;

            if(index == next)
                break;
            
            T tmp = tree[next];
            tree[next] = tree[index];
            tree[index] = tmp;

            index = next;
        }

        return value;
    }
};
```
{: .lh-0 .fw-700 .fs-4 }
</div>

## 참고 사이트
{: .fs-5 .fw-700 }

* [힙에 대한 설명 및 구현](https://www.geeksforgeeks.org/introduction-to-heap-data-structure-and-algorithm-tutorials/)