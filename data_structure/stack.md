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