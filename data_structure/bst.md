---
title: 이진 탐색 트리
layout: blog
parent: 자료 구조
nav_order: 6
---

# **이진 탐색 트리(Binary Search Tree)**
{: .no_toc .fs-9 }

<br/>

1. TOC
{:toc}

---

## 이진 탐색 트리란?
{: .fw-700 }

<div class="code-example" markdown="1">
**이진 탐색 트리**는 특정 값을 검색 혹은 탐색하는 데에 최적화된 이진 트리 자료 구조이다.
이분 탐색(binary search)의 탐색 과정이 이진 트리의 하위 노드로 내려감에 따라 수행되는 구조로 볼 수 있다.
때문에, 항상 정렬된 데이터 집합에서 특정 값을 찾는 쿼리가 여러 번 수행될 때 용이한 자료 구조다.

### 구현 코드
{: .fs-5 .fw-700 .mb-2 }

이진 탐색 트리를 C++로 구현한 코드는 다음과 같다.
{: .mb-1 }

```cpp
template <class T>
struct Node {
    T value;
    Node<T>* left = NULL;
    Node<T>* right = NULL;
};

template <class T>
struct BST {
    Node<T>* root = NULL;

    void insert(T value) {
        root = _insert(root, value);
    }

    void remove(T value) {
        root = _remove(root, value);
    }

    void inOrder(Node<T>* node) {
        if(!node)
            return;
        
        inOrder(node->left);
        cout << node->value << ' ';
        inOrder(node->right);
    }

    Node<T>* _insert(Node<T>* node, T value) {
        if(node == NULL) {
            Node<T>* newNode = new Node<T>;
            newNode->value = value;
            return newNode;
        }

        if(node->value > value)
            node->left = _insert(node->left, value);
        else
            node->right = _insert(node->right, value);
        return node;
    }

    Node<T>* _remove(Node<T>* node, T value) {
        if(node == NULL)
            return NULL;

        if(node->value > value)
            node->left = _remove(node->left, value);
        else if(node->value < value)
            node->right = _remove(node->right, value);
        else {
            if(!node->right){
                Node<T>* temp = node->left;
                delete node;
                return temp;
            }
            else if(!node->left) {
                Node<T>* temp = node->right;
                delete node;
                return temp;
            }

            Node<T>* leftNode = node->right;
            while(leftNode->left)
                leftNode = leftNode->left;
            node->value = leftNode->value;
            node->right = _remove(node->right, leftNode->value);
        }
        return node;
    }
};
```
{: .lh-0 .fw-700 .fs-4 }
</div>

## 이진 탐색 트리의 특징
{: .fw-700 }

<div class="code-example" markdown="1">
**이진 탐색 트리**에서의 임의의 노드가 가지는 자식 노드들은 항상 대소관계가 고정되어 있어야 한다.
예로 들어, 왼쪽의 자식 노드가 현재 노드의 값보다 작다면, 오른쪽 자식 노드에는 현재 노드보다 큰 값이 있어야 하며
이러한 성질은 두 자식 노드에도 재귀적으로 적용되어야 한다.
이는 곧, 이진 탐색 트리의 임의의 노드를 루트 노드로 가정했을 때, 그 트리도 동일한 성질의 이진 탐색 트리어야 한다는 것이다.
결과적으로, 이진 탐색 트리에 트리 순회 방식 중 중위 순회(in-order traversal)를 수행했을 때에는 데이터가 정렬되어 출력된다.
</div>

## 균형 이진 탐색 트리(Balanced Binary Search Tree)
{: .fw-700 }

<div class="code-example" markdown="1">
**균형 이진 탐색 트리**는 기존의 이진 탐색 트리의 문제점인
루트 노드에 대한 트리 구조에 따라 시간복잡도가 커지는 문제를 해결하기 위한 자료구조이다.
대표적인 예시가 한 방향으로만 노드가 연결되어 있는 사향 트리(skewed tree) 구조이다.
기존의 이진 탐색 트리는 이분 탐색과 마찬가지로 탐색에 있어 `O(log₂N)`만큼의 시간복잡도를 가진다.
하지만, 사향 트리처럼 트리의 모든 노드가 오른쪽이나 왼쪽에만 자식 노드를 가지고 있다면,
최악의 경우에는 `O(N)`만큼의 시간복잡도를 가지게 된다.
이러한 최악의 경우를 보완하기 위한 트리 구조가 아래에서 설명할 **균형 이진 탐색 트리**인 것이다.

### AVL 트리(AVL Tree)
{: .fw-700 }

<div class="code-example" markdown="1">
**AVL 트리**는 해당 구조를 발명한 Adelson-Velsky의 이름을 따서 명명된 트리 구조이다.
AVL 트리의 특징은 임의의 노드의 자식 노드를 각각 루트 노드로 할 때,
자식 노드로 구성된 트리의 높이가 2 이상 차이날 수 없도록 스스로 균형을 맞추는 데에 있다.
즉, 임의의 노드의 왼쪽 자식 노드가 오른쪽 자식 노드에 비해 과하게 커질 경우,
스스로 균형을 맞추는 트리 구조이다(왼쪽과 오른쪽이 반대인 경우도 마찬가지이다).

#### 구현 코드
{: .fs-5 .fw-700 .mb-2 }

AVL 트리를 C++로 구현한 코드는 다음과 같다.
{: .mb-1 }

```cpp
template <class T>
struct Node {
    T value;
    Node<T>* left = NULL;
    Node<T>* right = NULL;
    int height = 1;
};

template <class T>
struct BST {
    Node<T>* root = NULL;

    void insert(T value) {
        root = _insert(root, value);
    }
    
    void remove(T value) {
        root = _remove(root, value);
    }

    void inOrder(Node<T>* node) {
        if(!node)
            return;
        
        inOrder(node->left);
        cout << node->value << ' ';
        inOrder(node->right);
    }

    int getHeight(Node<T>* node) {
        if(!node)
            return 0;
        return node->height;
    }

    Node<T>* leftRotate(Node<T>* leftNode) {
        Node<T>* rootNode = leftNode->right;
        Node<T>* leftRightNode = rootNode->left;
        
        rootNode->left = leftNode;
        leftNode->right = leftRightNode;

        leftNode->height = max(getHeight(leftNode->left),
                               getHeight(leftNode->right)) + 1;
        rootNode->height = max(getHeight(rootNode->left),
                               getHeight(rootNode->right)) + 1;
        return rootNode;
    }

    Node<T>* rightRotate(Node<T>* rightNode) {
        Node<T>* rootNode = rightNode->left;
        Node<T>* rightLeftNode = rootNode->right;
        
        rootNode->right = rightNode;
        rightNode->left = rightLeftNode;

        rightNode->height = max(getHeight(rightNode->left),
                                getHeight(rightNode->right)) + 1;
        rootNode->height = max(getHeight(rootNode->left),
                                getHeight(rootNode->right)) + 1;
        return rootNode;
    }

    int getBalance(Node<T>* node) {
        if(!node)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    Node<T>* _insert(Node<T>* node, T value) {
        if(node == NULL) {
            Node<T>* newNode = new Node<T>;
            newNode->value = value;
            return newNode;
        }

        if(node->value > value)
            node->left = _insert(node->left, value);
        else
            node->right = _insert(node->right, value);
        
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

        int balance = getBalance(node);
        if(balance > 1) {
            if(value > node->left->value)
                node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if(balance < -1) {
            if(value < node->right->value)
                node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    Node<T>* _remove(Node<T>* node, T value) {
        if(node == NULL)
            return NULL;

        if(node->value > value)
            node->left = _remove(node->left, value);
        else if(node->value < value)
            node->right = _remove(node->right, value);
        else {
            if(!node->right) {
                Node<T>* temp = node->left;
                delete node;
                node = temp;
            }
            else if(!node->left) {
                Node<T>* temp = node->right;
                delete node;
                node = temp;
            }
            else {
                Node<T>* leftNode = node->right;
                while(leftNode->left)
                    leftNode = leftNode->left;
                node->value = leftNode->value;
                node->right = _remove(node->right, leftNode->value);
            }
        }

        if(!node)
            return node;
            
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        
        int balance = getBalance(node);
        if(balance > 1) {
            if(getBalance(node->left) < 0)
                node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if(balance < -1) {
            if(getBalance(node->right) > 0)
                node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }
};
```
{: .lh-0 .fw-700 .fs-4 }

위 코드에 대해 보기 전에 AVL 트리의 성질을 짚고 넘어가도록 한다.
AVL 트리의 가장 큰 특징은 회전(rotate)에 있는데, 이 회전을 통해 트리의 균형을 맞추게 된다.
여기서 트리의 균형이란 임의의 한 노드의 두 자식 노드에 대한 서브 트리의 높이 차가 1 이내인 상태를 의미한다(노드가 없다면 높이를 0으로 간주한다).
AVL 트리는 노드가 삽입 및 삭제될 때마다 수정되는 노드의 부모 노드들의 균형을 확인하고,
균형이 맞지 않을 경우 자동으로 회전하게 되므로, 일반적으로 균형이 맞지 않는 경우는 두 높이 차가 2인 경우이다.
{: .mb-0 }

회전에는 두 가지 종류가 있는데, Left Rotate와 Right Rotate이다.
이를 위해서는 이진 탐색 트리의 특징을 다시 한 번 생각해봐야 한다.
이진 탐색 트리에서 왼쪽 자식 노드에 현재 값보다 작은 값을, 오른쪽 자식 노드에 현재 값보다 큰 값을 삽입한다고 해보자.
왼쪽 자식 노드의 오른쪽 자식 노드에 위치한 모든 자식 노드들의 값들은 왼쪽 자식 노드의 값보다 크고 현재 노드의 값보다 작은 값이어야 한다.
이는 다시 생각해보면, 왼쪽 자식 노드를 루트 노드라고 한다면 해당 값들은 현재 노드의 왼쪽에 위치할 수도 있다는 것이다.
이러한 원리를 이용하여 회전할 때 자식 노드들의 위치를 변경할 수 있다.
{: .my-0 }

먼저, Right Rotate를 살펴보자.
현재 노드를 root, 왼쪽 자식 노드를 left, 왼쪽 자식 노드의 오른쪽 자식 노드를 left-right라고 해보자.
Right Rotate는 왼쪽 자식 노드와 현재 노드를 오른쪽으로 회전시키는 방법이므로,
왼쪽 자식 노드가 현재 노드의 부모 노드가 되고, 현재 노드는 왼쪽 자식 노드의 오른쪽 자식 노드가 되어야 한다.
따라서, left의 오른쪽 자식 노드를 root로 설정한다.
이때, left의 원래 오른쪽 자식이었던 left-right는 대소 관계에 따라 root의 왼쪽 자식 노드로 들어가게 된다.
결과적으로 root의 왼쪽 자식 노드는 left에서 left-right로,
left의 오른쪽 자식 노드는 left-right에서 root로만 바뀌면 된다.
높이가 변하는 노드는 root와 left 뿐이므로, 두 노드의 높이만 갱신해주면 된다(하위 노드부터 상위 노드로 갱신한다).
{: .my-0 }

Left Rotate의 경우에는 왼쪽 자식 노드와 왼쪽 자식 노드의 오른쪽 자식 노드만 좌우 대칭으로 해주면 된다.
즉, 왼쪽 자식 노드를 오른쪽 자식 노드로, 왼쪽 자식 노드의 오른쪽 자식 노드를 오른쪽 자식 노드의 왼쪽 자식 노드에 대해
위 과정을 수행해주면 Left Rotate가 된다.
{: .my-0 }

균형이 맞지 않을 때 회전을 사용하는 시기는 다음과 같이 정리할 수 있다.
{: .my-0 }

1. 오른쪽보다 왼쪽 자식 노드가, 자식 노드의 오른쪽보다 왼쪽 자식 노드의 높이가 더 큰 경우(LL-case)
    - 부모 노드에 대해 Right Rotate를 실행한다.
2. 왼쪽보다 오른쪽 자식 노드가, 자식 노드의 왼쪽보다 오른쪽 자식 노드의 높이가 더 큰 경우(RR-case)
    - 부모 노드에 대해 Left Rotate를 실행한다.
3. 오른쪽보다 왼쪽 자식 노드가, 자식 노드의 왼쪽보다 오른쪽 자식 노드의 높이가 더 큰 경우(LR-case)
    - 자식 노드에서 Left Roate를 실행하여 LL-case로 바꿔준 뒤, 부모 노드에 대해 Right Rotate를 실행한다.
4. 왼쪽보다 오른쪽 자식 노드가, 자식 노드의 오른쪽보다 왼쪽 자식 노드의 높이가 더 큰 경우(RL-case)
    - 자식 노드에서 Right Roate를 실행하여 RR-case로 바꿔준 뒤, 부모 노드에 대해 Left Rotate를 실행한다.
{: .mt-1 }
</div>

### 레드-블랙 트리(Red-Black Tree)
{: .fw-700 }

<div class="code-example" markdown="1">
**레드-블랙 트리**는 각 노드에 레드와 블랙이라는 특성을 부여하여,
조건을 만족하도록 색을 변화시키거나 [AVL 트리](#avl-트리avl-tree)처럼 회전하는 방식으로 균형을 유지하는 균형 이진 탐색 트리이다.
레드-블랙 트리의 균형을 유지하기 위한 조건은 다음과 같다.
{: .mb-1 }

1. 모든 노드에는 레드 혹은 블랙이어야 한다.
2. 루트 노드는 블랙이다.
3. 모든 리프 노드는 블랙이다.
4. 레드 노드의 자식 노드는 블랙이다.
    1. 레드 노드의 부모가 레드이면, 위 조건에 위배되므로 레드 노드의 부모는 블랙이다.
    2. 결과적으로, 레드 노드는 연속으로 나타날 수 없다.
5. 루트 노드에서 임의의 리프 노드까지의 가장 간단한 경로 내에 있는 블랙 노드의 수는 깊이에 관계없이 모든 리프 노드에 대해 항상 같아야 한다.
{: .my-0 }

이러한 복잡한 조건이 주어진 대신,
데이터의 삽입 및 삭제, 탐색에서 최악의 경우에도 `O(log₂N)`의 시간복잡도를 보장한다(worst-case guarantees).
때문에, 파이썬에서 딕셔너리(dict)라고도 불리는 연관 집합이나 집합(set) 외에도 다양한 자료 구조들의 기반이 되는 자료 구조이다.
{: .mt-1 }

#### 구현 코드
{: .fs-5 .fw-700 .mb-2 }

레드-블랙 트리를 C++로 구현한 코드는 다음과 같다.
구현의 용이성을 위해 모든 리프 노드가 값이 없는(NIL) 블랙 노드를 자식 노드를 가지고 있는 것으로 가정한다(3번 조건 완화).
{: .mb-1 }

```cpp
enum Color {
    COLOR_RED,
    COLOR_BLACK
};

template <class T>
struct Node {
    T value;
    Node<T>* left = NULL;
    Node<T>* right = NULL;
    Node<T>* parent = NULL;
    Color color = COLOR_RED;
};

template <class T>
struct BST {
    Node<T>* root = NULL;

    void insert(T value) {
        root = _insert(root, value);
        root->color = COLOR_BLACK;
    }
    
    void remove(T value) {
        _remove(root, value);
        root->color = COLOR_BLACK;
    }

    void inOrder(Node<T>* node) {
        if(!node)
            return;
        
        inOrder(node->left);
        cout << node->value << ' ';

        inOrder(node->right);
    }

    Node<T>* leftRotate(Node<T>* leftNode) {
        Node<T>* rootNode = leftNode->right;
        Node<T>* leftRightNode = rootNode->left;
        
        rootNode->left = leftNode;
        leftNode->right = leftRightNode;
        leftNode->parent = rootNode;
        if(leftRightNode)
            leftRightNode->parent = leftNode;

        return rootNode;
    }

    Node<T>* rightRotate(Node<T>* rightNode) {
        Node<T>* rootNode = rightNode->left;
        Node<T>* rightLeftNode = rootNode->right;
        
        rootNode->right = rightNode;
        rightNode->left = rightLeftNode;
        rightNode->parent = rootNode;
        if(rightLeftNode)
            rightLeftNode->parent = rightNode;

        return rootNode;
    }

    Node<T>* getSibling(Node<T>* node) {
        if(!node->parent)
            return NULL;
        
        if(node->parent->left == node)
            return node->parent->right;
        return node->parent->left;
    }

    Node<T>* _insert(Node<T>* node, T value) {
        Node<T>* childNode;
        bool doubleRed = false;
        
        Node<T>* siblingNode;
        bool LeftLeft = false;
        bool LeftRight = false;
        bool RightLeft = false;
        bool RightRight = false;

        if(node == NULL) {
            Node<T>* newNode = new Node<T>;
            newNode->value = value;
            return newNode;
        }

        if(node->value > value) {
            childNode = _insert(node->left, value);
            childNode->parent = node;
            node->left = childNode;
            
            if(childNode->color == COLOR_RED) {
                if(childNode->left && childNode->left->color == COLOR_RED)
                    doubleRed = true;
                else if(childNode->right && childNode->right->color == COLOR_RED)
                    doubleRed = true;
            }
        }
        else if(node->value < value) {
            childNode = _insert(node->right, value);
            childNode->parent = node;
            node->right = childNode;

            if(childNode->color == COLOR_RED) {
                if(childNode->left && childNode->left->color == COLOR_RED)
                    doubleRed = true;
                else if(childNode->right && childNode->right->color == COLOR_RED)
                    doubleRed = true;
            }
        }
        else
            return node;

        if(!doubleRed)
            return node;
        
        siblingNode = getSibling(childNode);
        if(!siblingNode || siblingNode->color == COLOR_BLACK) {
            if(childNode->left && childNode->left->color == COLOR_RED) {
                if(childNode == node->left)
                    LeftLeft = true;
                else
                    RightLeft = true;
            }
            else if(childNode->right && childNode->right->color == COLOR_RED) {
                if(childNode == node->left)
                    LeftRight = true;
                else
                    RightRight = true;
            }
        }
        else {
            childNode->color = COLOR_BLACK;
            siblingNode->color = COLOR_BLACK;
            node->color = COLOR_RED;
        }
        
        if(LeftLeft) {
            node = rightRotate(node);
            node->color = COLOR_BLACK;
            node->right->color = COLOR_RED;
        }
        else if(RightLeft) {
            node->right = rightRotate(node->right);
            node->right->parent = node;

            node = leftRotate(node);
            node->color = COLOR_BLACK;
            node->left->color = COLOR_RED;
        }
        else if(RightRight) {
            node = leftRotate(node);
            node->color = COLOR_BLACK;
            node->left->color = COLOR_RED;
        }
        else if(LeftRight) {
            node->left = leftRotate(node->left);
            node->left->parent = node;
            
            node = rightRotate(node);
            node->color = COLOR_BLACK;
            node->right->color = COLOR_RED;
        }
        return node;
    }

    Color getColor(Node<T>* node) {
        if(!node)
            return COLOR_BLACK;
        return node->color;
    }

    void swapColor(Color *c1, Color *c2) {
        Color tmp = *c1;
        *c1 = *c2;
        *c2 = tmp;
    }

    void fixDoubleBlack(Node<T>* node) {
        Node<T>* parent = node->parent;
        Node<T>* sibling = getSibling(node);

        // case 1
        if(!parent) {
            node->color = COLOR_BLACK;
            return;
        }
        // case 2
        else if(getColor(sibling) == COLOR_RED) {
            if(!parent->parent) {
                if(parent->right == node)
                    root = rightRotate(parent);
                else
                    root = leftRotate(parent);
            }
            else {
                if(parent->parent->right == parent) {
                    if(parent->right == node)
                        parent->parent->right = rightRotate(parent);
                    else
                        parent->parent->right = leftRotate(parent);
                }
                else {
                    if(parent->right == node)
                        parent->parent->left = rightRotate(parent);
                    else
                        parent->parent->left = leftRotate(parent);
                }
            }
            swapColor(&parent->color, &sibling->color);
            return fixDoubleBlack(node);
        }
        // case 3
        else if(getColor(parent) == COLOR_BLACK
                && getColor(sibling) == COLOR_BLACK
                && getColor(sibling->left) == COLOR_BLACK
                && getColor(sibling->right) == COLOR_BLACK) {
            sibling->color = COLOR_RED;
            return fixDoubleBlack(parent);
        }
        // case 4
        else if(getColor(parent) == COLOR_RED
                && getColor(sibling) == COLOR_BLACK
                && getColor(sibling->left) == COLOR_BLACK
                && getColor(sibling->right) == COLOR_BLACK) {
            swapColor(&parent->color, &sibling->color);
            return;
        }
        else {
            if(parent->right == node) {
                // case 6
                if(getColor(sibling->left) == COLOR_RED) {
                    if(!parent->parent)
                        root = rightRotate(parent);
                    else if(parent->parent->right == parent)
                        parent->parent->right = rightRotate(parent);
                    else if(parent->parent->left == parent)
                        parent->parent->left = rightRotate(parent);

                    swapColor(&parent->color, &sibling->color);
                    sibling->left->color = COLOR_BLACK;
                    return;
                }
                // case 5
                else if(getColor(sibling->right) == COLOR_RED) {
                    parent->left = leftRotate(sibling);

                    swapColor(&sibling->color, &sibling->parent->color);
                    return fixDoubleBlack(node);
                }
            }
            else {
                // case 6
                if(getColor(sibling->right) == COLOR_RED) {
                    if(!parent->parent)
                        root = leftRotate(parent);
                    else if(parent->parent->right == parent)
                        parent->parent->right = leftRotate(parent);
                    else if(parent->parent->left == parent)
                        parent->parent->left = leftRotate(parent);

                    swapColor(&parent->color, &sibling->color);
                    sibling->right->color = COLOR_BLACK;
                    return;
                }
                // case 5
                if(getColor(sibling->left) == COLOR_RED) {
                    parent->right = rightRotate(sibling);

                    swapColor(&sibling->color, &sibling->parent->color);
                    return fixDoubleBlack(node);
                }
            }
        }
    }

    void _remove(Node<T>* node, T value) {
        if(node == NULL)
            return;
        
        if(node->value > value)
            _remove(node->left, value);
        else if(node->value < value)
            _remove(node->right, value);
        else {
            if(!node->left) {
                if(node->color == COLOR_BLACK) {
                    if(!node->right || node->right->color == COLOR_BLACK)
                        fixDoubleBlack(node);
                    else
                        node->right->color = COLOR_BLACK;
                }

                if(!node->parent) {
                    root = node->right;

                    if(node->right)
                        node->right->parent = NULL;
                }
                else {
                    if(node->parent->right == node)
                        node->parent->right = node->right;
                    else
                        node->parent->left = node->right;

                    if(node->right)
                        node->right->parent = node->parent;
                }
                delete node;
            }
            else if(!node->right) {
                if(node->color == COLOR_BLACK) {
                    if(!node->left || node->left->color == COLOR_BLACK)
                        fixDoubleBlack(node);
                    else
                        node->left->color = COLOR_BLACK;
                }

                if(!node->parent) {
                    root = node->left;

                    if(node->left)
                        node->left->parent = NULL;
                }
                else {
                    if(node->parent->right == node)
                        node->parent->right = node->left;
                    else
                        node->parent->left = node->left;
                        
                    if(node->left)
                        node->left->parent = node->parent;
                }
                delete node;
            }
            else {
                Node<T>* inorderSuccessor = node->right;
                while(inorderSuccessor->left)
                    inorderSuccessor = inorderSuccessor->left;
                
                node->value = inorderSuccessor->value;
                _remove(node->right, inorderSuccessor->value);
            }
        }
    }
};
```
{: .lh-0 .fw-700 .fs-4 }

위 코드에 대해 설명하기 전, 다시 한 번 레드-블랙 트리의 조건에 대해 복습해보자.
조건들 중에서 삽입에서는 4번 조건인 연속된 레드 노드가 존재하면 안된다는 부분에 중점을 두며,
4번 조건에 위배되는 상황을 Double Red라고 부른다.
삭제에서는 5번 조건인 루트 노드와 리프 노드 사이의 블랙 노드의 수가 모든 리프 노드에 대해 같아야 한다는 부분에 중점을 두며,
여기서의 루트 노드와 리프 노드 사이의 블랙 노드의 개수를 Black Depth라고 부른다.
때문에, 삭제에서는 5번 조건에 부합하지 않는 리프 노드가 발생할 경우 Black Depth에 위배된다고 볼 수 있다.
{: .mb-1 }

본 코드를 설명하기 앞서 모든 리프 노드에 빈 노드(NIL)가 있다고 가정하며,
이는 유의미한 데이터가 아닌 노드이지만 노드의 색은 블랙인 것으로 간주한다.
{: .my-1 }

노드 삽입 시에는 다음과 같은 규칙을 따르면 된다.
{: .my-1 }

1. 루트 노드는 삽입될 때 색을 블랙으로 한다.
2. 루트 노드를 제외한 모든 노드는 삽입될 때 색을 레드로 한다.
    1. 레드 노드가 삽입되었을 때, 부모가 블랙이라면 그대로 유지한다.
    2. 만약 부모가 레드라면 레드-블랙 트리의 조건에 위배되므로(Double Red), 다음과 같은 조치를 한다.
        1. 연속된 레드 노드 중 상위 노드의 형제 노드의 색이 레드인 경우
            - 블랙인 부모 노드의 색을 레드로 바꾸고 현재 노드와 형제 노드의 색을 블랙으로 바꾼다.
        2. 연속된 레드 노드 중 상위 노드의 형제의 색이 블랙인 경우,
            - 부모 노드에서 회전한 뒤에 부모 노드의 위치로 올라간 노드의 색을 블랙으로, 부모 노드였던 노드의 색을 레드로 변경한다.
        이때, 회전 방향과 횟수는 AVL 트리에서 LR-case, RL-case, LL-case, RR-case와 동일하며, 부모 노드에서 회전한 경우에만 색을 변경한다.
        3. 위의 두 과정 중 하나를 시행한 뒤에는 상위 노드까지 연속된 레드 노드(Double Red)가 있는 지 확인하며, 
        연속된 레드 노드에 대해 위 두 과정 중 해당하는 작업을 시행한다.
        이러한 절차를 루트 노드까지 반복하여 시행하고, 루트 노드의 색이 레드로 바뀌었을 때에는 다시 블랙으로 변경한다.
{: .mt-1 .mb-2 }

노드 삭제 시에는 다음과 같은 규칙을 따르면 된다.
{: .mt-2 .mb-1 }

1. 트리 순회를 통해 삭제하고자 하는 노드 탐색하고, 만약 일치하는 노드가 있다면 그 노드를 다음과 같이 삭제한다.
    1. 삭제하고자 하는 노드가 리프 노드라면, 현재 노드를 빈 노드(NIL)로 바꾼다.
    2. 삭제하고자 하는 노드에게 자식 노드가 1개만 있다면, 자식 노드를 그대로 가져온다.
    3. 삭제하고자 하는 노드에게 자식 노드가 2개가 있다면,
    오른쪽 자식 노드의 가장 왼쪽에 있는 노드의 값으로 교체하고 해당 노드를 삭제한다.
    (삭제되는 노드는 in-order successor라고도 하며, in-order traversal에서 현재 노드 다음으로 방문할 노드를 가리킴)
2. 위 과정에서 지워지는 노드가 레드라면 그대로 유지한다.
3. 만약 지워지는 노드가 블랙이라면 다음 중 조건에 맞는 작업을 수행한다.
    1. 지워지는 노드에게 자식 노드가 1개만 있으며 그 노드가 레드라면, 그 노드의 색만 블랙으로 변경하고 그대로 가져온다.
    2. 그 외의 경우에는 레드-블랙 트리 조건에 위배되므로(Black Depth), 다음 중 조건에 맞는 작업을 수행한다.
        1. 지워지는 노드가 루트 노드인 경우
            - 지워지는 노드의 색을 블랙으로 색을 변경한다.
        2. 지워지는 노드의 형제 노드가 레드인 경우
        (이때, 연속된 레드 노드는 존재할 수 없으므로, 조건에서의 부모 노드와 형제 노드의 자식 노드의 색은 항상 블랙이다)
            - 회전 후 부모 노드였던 노드와 형제 노드였던 노드의 색을 서로 바꾸고 현재 노드에서 Black Depth에 대한 작업을 다시 수행한다.
        회전 방향은 부모 노드에서 현재 노드가 있는 방향으로, 현재 노드가 부모 노드의 (왼쪽/오른쪽)에 있다면 (Left/Right) Rotate를 실행한다.
        3. 지워지는 노드의 부모 노드, 형제 노드, 형제 노드의 두 자식 노드의 색이 모두 블랙인 경우
            - 형제 노드의 색만 레드로 바꾸고 부모 노드에서 Black Depth에 대한 작업을 다시 수행한다.
        4. 지워지는 노드의 부모가 레드이고 형제 노드와 그 자식 노드의 색이 모두 블랙인 경우
            - 부모 노드와 형제 노드의 색을 서로 바꾼다.
        5. 지워지는 노드가 (왼쪽/오른쪽)일 때
        형제 노드의 자식 노드의 (왼쪽/오른쪽) 노드만 레드인 경우(부모 노드와 형제 노드의 다른 자식 노드의 색은 모두 블랙인 경우)
            - 형제 노드에 대해 (Right/Left) Rotate를 하고 형제 노드와 레드였던 형제 노드의 (왼쪽/오른쪽) 노드의 색을 뒤바꾼다.
            그 다음, 현재 노드에서 Black Depth에 대한 작업을 다시 수행한다.
        6. 지워지는 노드가 (왼쪽/오른쪽)일 때 형제 노드의 (오른쪽/왼쪽) 자식 노드의 색이 레드인 경우(부모의 색과 다른 자식 노드 색은 무관)
            - 지워지는 노드의 부모 노드에 대해 (Left/Right) Rotate를 한 뒤, 부모 노드였던 노드와 형제 노드였던 노드의 색을 서로 뒤바꾸고
            형제 노드의 (오른쪽/왼쪽) 자식 노드였던 노드의 색을 블랙으로 바꿈
{: .my-1 }

</div>
</div>

## 참고 사이트
{: .fs-5 .fw-700 }

* [이진 탐색 트리에 대한 설명](https://www.geeksforgeeks.org/binary-search-tree-data-structure/)
* [AVL 트리에 대한 설명](https://www.geeksforgeeks.org/introduction-to-avl-tree/)
* [레드-블랙 트리에 대한 설명](https://www.geeksforgeeks.org/introduction-to-red-black-tree/)
* [레드-블랙 트리 삽입](https://www.youtube.com/watch?v=UaLIHuR1t8Q)
* [레드-블랙 트리 삭제](https://www.youtube.com/watch?v=CTvfzU_uNKE)