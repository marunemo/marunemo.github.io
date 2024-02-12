---
title: 트리
layout: blog
parent: 자료 구조
nav_order: 4
---

# **트리(Tree)**
{: .no_toc .fs-9 }

<br/>

1. TOC
{:toc}

---

## 트리란?
{: .fw-700 }

<div class="code-example" markdown="1">
**트리**는 임의의 두 노드 사이에 계층적인 관계성이 있는 그래프이다.
임의의 노드에 대해 상위 관계에 있는 노드를 **부모 노드(parent node)**,
하위 관계에 있는 노드를 **자식 노드(child node)**라고 부른다.
임의의 노드와 동일한 단계(level)에 있는 노드는 **형제 노드(sibling node)**라고 부르며,
여기서 말하는 노드의 단계는 임의의 상위 노드로부터 각각의 노드까지 내려온 정도를 의미하고 이를 **깊이(depth)**라고 부른다.
트리의 모든 노드 중 깊이가 가장 작은, 즉 깊이가 0인 노드를 **루트 노드(root node)**라고 부르며,
깊이가 0이기 때문에 상위 노드도 존재할 수 없으므로 루트 노드는 부모 노드가 없다.
반대로, 자식 노드를 가지고 있지 않은 노드를 **리프 노드(leaf node)**라고 부르며,
리프 노드의 깊이가 트리에 대해 가장 큰 깊이를 가질 필요는 없다.
하지만, 트리에 대해 깊이가 가장 큰 리프 노드부터 루트 노드까지의 깊이를 그 트리의 **높이(height)**라고 부른다.
</div>

## 트리의 특징
{: .fw-700 }

<div class="code-example" markdown="1">
앞서 말했듯이 일반적인 그래프와 달리 트리에는 부모나 자식과 같은 계층적인 관계성을 띤다.
그리고, 그 외 다른 특징으로는 트리의 **두 노드 사이에는 단 하나의 경로만이 존재한다**는 것이다.
다시 말해, 임의의 노드의 간선으로 직접 연결되어 있거나
그 간선과 이어진 다른 노드들의 간선으로 간접적으로 연결되는 방법을 통틀어 단 한 가지 연결만 존재한다는 것이다.
</div>

## 이진 트리(Binary Tree)
{: .fw-700 }

<div class="code-example" markdown="1">
트리의 각 노드는 하나 이상의 자식 노드를 가질 수 있다.
하지만, 그 중에서도 트리의 각 노드가 최대 2개까지의 자식 노드를 가지는 트리를 **이진 트리**라고 부른다.
이진 트리에도 다양한 유형이 있는데, 다음은 이진 트리의 종류에 관한 내용이다.

### 완전 이진 트리(Complete Binary Tree)
{: .fw-700 }

<div class="code-example" markdown="1">
**완전 이진 트리**는 다음 두 조건을 만족하는 이진 트리이다.
{: .mb-1 }

{: .highlight }
> 1. 깊이가 가장 큰 노드들을 제외한 모든 깊이의 노드들은 채울 수 있는 한 모두 채워져 있어야 한다.
> 2. 깊이가 가장 큰 노드들은 왼쪽부터 채워져 있어야 한다.
{: .py-1 .my-1 }

때문에, 완전 이진 트리의 깊이가 가장 큰 노드들을 제외한 각 깊이의 노드들은,
노드의 각 깊이를 d라고 할 때 각 깊이의 노드의 개수는 `2^d`만큼 존재해야 한다.
또한, 노드의 개수가 n개라고 한다면, 해당 완전 이진 트리의 높이는 `log₂(n+1)-1`이 된다(소숫점은 올림 처리한다).

#### 배열로 구현한 코드
{: .fs-5 .fw-700 .mb-2 }

완전 이진 트리를 배열을 통해 C++로 구현한 코드는 다음과 같다.
{: .mb-1 }

```cpp
#define MAX 1000
#define INF (~0U >> 2)

template <class T>
struct Tree {
    T array[MAX];
    int root = 0;
    int size = 0;
    
    int _parent(int i) {
        return (i - 1) / 2;
    }

    int _leftChild(int i) {
        return (2 * i) + 1;
    }

    int _rightChild(int i) {
        return (2 * i) + 2;
    }

    bool empty() {
        return size == 0;
    }

    void insert(T value) {
        if(size == MAX)
            return;
        array[size++] = value;
    }

    T remove() {
        if(empty())
            return -INF;
        return array[--size];
    }

    void PreOrder(int index) {
        if(index >= size)
            return;
        
        cout << array[index] << ' ';
        PreOrder(_leftChild(index));
        PreOrder(_rightChild(index));
    }

    void InOrder(int index) {
        if(index >= size)
            return;
        
        InOrder(_leftChild(index));
        cout << array[index] << ' ';
        InOrder(_rightChild(index));
    }

    void PostOrder(int index) {
        if(index >= size)
            return;
        
        PostOrder(_leftChild(index));
        PostOrder(_rightChild(index));
        cout << array[index] << ' ';
    }

    void LevelOrder(int index) {
        if(index >= size)
            return;
        
        queue<int> order;
        int top;
        
        order.push(index);
        while(!order.empty()) {
            top = order.front();
            order.pop();

            if(_leftChild(top) < size)
                order.push(_leftChild(top));
            if(_rightChild(top) < size)
                order.push(_rightChild(top));
            cout << array[top] << ' ';
        }
    }
};
```
{: .lh-0 .fw-700 .fs-4 }

#### 트리 노드로 구현한 코드
{: .fs-5 .fw-700 .mb-2 }

완전 이진 트리를 C++에서 임의의 트리 노드에 대한 재귀로 구현한 코드는 다음과 같다.
{: .mb-1 }

```cpp
#define INF (~0U >> 2)

template <class T>
struct Node {
    T value;
    struct Node<T>* parent = NULL;
    struct Node<T>* left = NULL;
    struct Node<T>* right = NULL;
};

template <class T>
struct Tree {
    Node<T>* root = NULL;
    queue<Node<T>*> parents;
    stack<Node<T>*> children;
    int size = 0;

    bool empty() {
        return size == 0;
    }

    void insert(T value) {
        Node<T>* node = new Node<T>;
        node->value = value;
        
        if(empty())
            root = node;
        else {
            Node<T>* parent = parents.front();
            parents.pop();

            if(!parent->left)
                parent->left = node;
            else if(!parent->right)
                parent->right = node;
            node->parent = parent;
        }

        parents.push(node);
        parents.push(node);
        children.push(node);
        size++;
    }

    T remove() {
        if(empty())
            return -INF;

        Node<T>* node = children.top();
        children.pop();

        int value = node->value;
        Node<T>* parent = node->parent;
        if(!parent)
            root = NULL;
        else if(parent->right)
            parent->right = NULL;
        else if(parent->left)
            parent->left = NULL;
        
        delete node;
        size--;

        return value;
    }

    void PreOrder(Node<T>* node) {
        if(!node)
            return;
        
        cout << node->value << ' ';
        PreOrder(node->left);
        PreOrder(node->right);
    }

    void InOrder(Node<T>* node) {
        if(!node)
            return;
        
        InOrder(node->left);
        cout << node->value << ' ';
        InOrder(node->right);
    }

    void PostOrder(Node<T>* node) {
        if(!node)
            return;
        
        PostOrder(node->left);
        PostOrder(node->right);
        cout << node->value << ' ';
    }

    void LevelOrder(Node<T>* node) {
        if(!node)
            return;
        
        queue<Node<T>*> order;
        Node<T>* top;

        order.push(node);
        while(!order.empty()) {
            top = order.front();
            order.pop();

            if(top->left)
                order.push(top->left);
            if(top->right)
                order.push(top->right);
            cout << top->value << ' ';
        }
    }
};
```
{: .lh-0 .fw-700 .fs-4 }
</div>

### 정 이진 트리(Full Binary Tree)
{: .fw-700 }

<div class="code-example" markdown="1">
**정 이진 트리**는 리프 노드를 제외한 모든 노드가 2개의 자식 노드를 가지는 이진 트리이다.
다시 말해, 트리의 모든 노드가 자식 노드를 0개 혹은 2개만을 가지고 있으며,
자식 노드를 1개만 가지고 있는 노드가 하나라도 있다면 이는 정 이진 트리라고 할 수 없다.
</div>

### 포화 이진 트리(Perfect Binary Tree)
{: .fw-700 }

<div class="code-example" markdown="1">
**포화 이진 트리**는 모든 깊이의 노드들이 채울 수 있는 한 모두 채워져 있는 이진 트리이다.
즉, 루트 노드에 대해 깊이가 가장 큰 리프 노드들을 제외한 트리의 모든 노드들은 2개의 자식 노드를 가지고 있어야만 한다.
때문에, 포화 이진 트리는 완전 이진 트리와 정 이진 트리의 특성을 모두 만족한다.
{: .mb-1 }

앞서, 완전 이진 트리와 비슷하게 각 깊이의 노드들은 깊이를 d라고 할 때, 각 깊이마다 `2^d`개의 노드가 존재해야 한다.
다만, 포화 이진 트리는 깊이가 가장 큰 노드도 `2^d`개 존재해야 하며, 이는 등비수열의 형태로 나타낼 수 있다.
트리의 높이는 가장 깊이가 큰 노드의 깊이로 나타낼 수 있으므로,
높이가 h인 포화 이진 트리의 노드의 개수는 등비수열의 합에 따라 `2^(h+1)-1`이 된다.
첫째항이 1이고 공비가 2인 등비수열의 첫째항부터 제h항까지의 합이라고 생각하면 간단하게 증명할 수 있다.
{: .my-1 }

반대로, 노드의 개수도 총 개수를 n이라고 한다면, 포화 이진 트리의 높이는 `log₂(n+1)-1`이 된다.
이 경우에는 위에서 정리한 노드의 개수를 n에 대입하면 항상 2의 제곱꼴로 나오므로, 소숫점 처리를 하지 않아도 된다.
{: .mt-1 }
</div>
</div>

## 트리의 순회(Tree Traversal)
{: .fw-700 }

<div class="code-example" markdown="1">
**트리의 순회**는 트리 내에 있는 각 노드를 한 번씩 방문하여, 내부 데이터를 조회하거나 탐색하는 과정을 의미한다.
일반적으로 상위 노드부터 하위 노드 순으로 데이터를 재귀적으로 확인하는 방법을 사용하는데,
그 순서나 방법에 따라 [전위 순회](#전위-순회pre-order-traversal),
[중위 순회](#중위-순회in-order-traversal),
[후위 순회](#후위-순회post-order-traversal),
[단계 순회](#단계-순회level-order-traversal) 등이 있다.

### 전위 순회(Pre-order Traversal)
{: .fw-700 }

<div class="code-example" markdown="1">
**전위 순회**는 **DFS 그래프 탐색** 방법에 따라 다음 순서대로 트리를 순회하는 방법이다.
{: .mb-1 }

{: .highlight }
> 1. 현재 노드를 확인한다.
> 2. 현재 노드의 왼쪽 자식 노드를 확인한다.
> 3. 현재 노드의 오른쪽 자식 노드를 확인한다.
{: .py-1 .my-1 }

위의 과정을 이진 트리에서 배열로 구현한 코드에 적용하면 다음과 같이 나타낼 수 있다.
{: .my-1 }

```cpp
void PreOrder(int index) {
    if(index >= size)
        return;
    
    cout << array[index] << ' ';
    PreOrder(_leftChild(index));
    PreOrder(_rightChild(index));
}
```
{: .lh-0 .fw-700 .fs-4 }

위의 과정을 이진 트리에서 트리 노드로 구현한 코드에 적용하면 다음과 같이 나타낼 수 있다.
{: .mb-1 }

```cpp
void PreOrder(Node<T>* node) {
    if(!node)
        return;
    
    cout << node->value << ' ';
    PreOrder(node->left);
    PreOrder(node->right);
}
```
{: .lh-0 .fw-700 .fs-4 }
</div>

### 중위 순회(In-order Traversal)
{: .fw-700 }

<div class="code-example" markdown="1">
**중위 순회**는 **DFS 그래프 탐색** 방법에 따라 다음 순서대로 트리를 순회하는 방법이다.
{: .mb-1 }

{: .highlight }
> 1. 현재 노드의 왼쪽 자식 노드를 확인한다.
> 2. 현재 노드를 확인한다.
> 3. 현재 노드의 오른쪽 자식 노드를 확인한다.
{: .py-1 .my-1 }

위의 과정을 이진 트리에서 배열로 구현한 코드에 적용하면 다음과 같이 나타낼 수 있다.
{: .my-1 }

```cpp
void InOrder(int index) {
    if(index >= size)
        return;
    
    InOrder(_leftChild(index));
    cout << array[index] << ' ';
    InOrder(_rightChild(index));
}
```
{: .lh-0 .fw-700 .fs-4 }

위의 과정을 이진 트리에서 트리 노드로 구현한 코드에 적용하면 다음과 같이 나타낼 수 있다.
{: .mb-1 }

```cpp
void InOrder(Node<T>* node) {
    if(!node)
        return;
    
    InOrder(node->left);
    cout << node->value << ' ';
    InOrder(node->right);
}
```
{: .lh-0 .fw-700 .fs-4 }
</div>

### 후위 순회(Post-order Traversal)
{: .fw-700 }

<div class="code-example" markdown="1">
**후위 순회**는 **DFS 그래프 탐색** 방법에 따라 다음 순서대로 트리를 순회하는 방법이다.
{: .mb-1 }

{: .highlight }
> 1. 현재 노드의 왼쪽 자식 노드를 확인한다.
> 2. 현재 노드의 오른쪽 자식 노드를 확인한다.
> 3. 현재 노드를 확인한다.
{: .py-1 .my-1 }

위의 과정을 이진 트리에서 배열로 구현한 코드에 적용하면 다음과 같이 나타낼 수 있다.
{: .my-1 }

```cpp
void PostOrder(int index) {
    if(index >= size)
        return;
    
    PostOrder(_leftChild(index));
    PostOrder(_rightChild(index));
    cout << array[index] << ' ';
}
```
{: .lh-0 .fw-700 .fs-4 }

위의 과정을 이진 트리에서 트리 노드로 구현한 코드에 적용하면 다음과 같이 나타낼 수 있다.
{: .mb-1 }

```cpp
void PostOrder(Node<T>* node) {
    if(!node)
        return;
    
    PostOrder(node->left);
    PostOrder(node->right);
    cout << node->value << ' ';
}
```
{: .lh-0 .fw-700 .fs-4 }
</div>

### 단계 순회(Level-order Traversal)
{: .fw-700 }

<div class="code-example" markdown="1">
**단계 순회**는 위의 세 방법과 달리 **BFS 그래프 탐색** 방법에 따라 트리를 순회하는 방법이다.
각 깊이별 노드들을 모두 확인한 뒤에 다음 깊이로 내려가 해당 깊이의 노드들을 확인하는 과정을 반복하여 수행하는 방식이다.
{: .mb-1 }

단계 순회를 이진 트리에서 배열로 구현한 코드에 적용하면 다음과 같이 나타낼 수 있다.
BFS 방식을 위해 **큐** 자료 구조를 사용해야 한다.
{: .my-1 }

```cpp
void LevelOrder(int index) {
    if(index >= size)
        return;
    
    queue<int> order;
    int top;
    
    order.push(index);
    while(!order.empty()) {
        top = order.front();
        order.pop();

        if(_leftChild(top) < size)
            order.push(_leftChild(top));
        if(_rightChild(top) < size)
            order.push(_rightChild(top));
        cout << array[top] << ' ';
    }
}
```
{: .lh-0 .fw-700 .fs-4 }

위의 과정을 이진 트리에서 트리 노드로 구현한 코드에 적용하면 다음과 같이 나타낼 수 있다.
마찬가지로 큐를 사용하여 구현하였다.
{: .mb-1 }

```cpp
void LevelOrder(Node<T>* node) {
    if(!node)
        return;
    
    queue<Node<T>*> order;
    Node<T>* top;

    order.push(node);
    while(!order.empty()) {
        top = order.front();
        order.pop();

        if(top->left)
            order.push(top->left);
        if(top->right)
            order.push(top->right);
        cout << top->value << ' ';
    }
}
```
{: .lh-0 .fw-700 .fs-4 }
</div>
</div>

## 참고 사이트
{: .fs-5 .fw-700 }

* [트리에 대한 설명 및 구현](https://www.geeksforgeeks.org/introduction-to-tree-data-structure-and-algorithm-tutorials/)
* [이진 트리의 종류](https://www.geeksforgeeks.org/types-of-binary-tree/)