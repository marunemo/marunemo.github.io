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
</div>

### 구현 코드
{: .fw-700 }

```cpp
struct Node {
    int value;
    Node* front;
    Node* back;
    
    Node(int value) {
        this.value = value;
    }
}

struct Stack {
    Node *top;

    bool empty() {
        return top == NULL;
    }

    void push(int value) {
        Node item = Node(value);
        item.front = top;
        top = item;
    }

    int pop() {
        if(empty())
            return;
        
        int value = item.value;
        top = item.front;
        return value;
    }
};
```
{: .lh-0 .fw-700 .fs-4 }