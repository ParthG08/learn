# Multiset vs Priority Queue

Both can give you the largest element quickly, but they are designed for different purposes.

## Comparison Table

| Feature | `priority_queue` | `multiset` |
|---|---|---|
| Underlying data structure | Heap (usually binary heap) | Balanced BST (Red-Black Tree) |
| Get largest | `top()` → O(1) | `*rbegin()` → O(1) |
| Insert | O(log n) | O(log n) |
| Remove largest | `pop()` → O(log n) | `erase(prev(end()))` → O(log n) |
| Remove arbitrary element | Not efficient | `erase(find(x))` → O(log n) |
| Iterate in sorted order | No | Yes |
| Find an element | No | `find()` → O(log n) |
| Duplicates | Yes | Yes |

## Priority Queue

Think of it as a **pile where only the biggest item is easily accessible**.

```cpp
priority_queue<int> pq;

pq.push(5);
pq.push(3);
pq.push(6);

cout << pq.top();   // 6

pq.pop();           // removes 6

cout << pq.top();   // 5
```

Internally, it is **not sorted**. It might look like this in memory:

```
      6
     / \
    3   5
```

The only guarantee is:
- parent >= children
- `top()` is the largest

You **cannot** efficiently remove `3` directly.

## Multiset

Think of it as a **balanced search tree**.

```cpp
multiset<int> s;

s.insert(5);
s.insert(3);
s.insert(6);
```

The values are **always ordered**:

```
3 5 6
```

Largest:

```cpp
*s.rbegin();    // 6
```

Remove any value:

```cpp
s.erase(s.find(3));
```

Now:

```
5 6
```

Everything remains sorted automatically.

## Time Complexity (per operation)

### `priority_queue` (Binary Heap)

| Operation                        | Time     | Explanation                                                            |
| -------------------------------- | -------- | ---------------------------------------------------------------------- |
| `push(x)`                        | O(log n) | Insert at leaf, bubble up (max height = log n)                         |
| `pop()`                          | O(log n) | Swap root with last leaf, remove last, bubble down                     |
| `top()`                          | O(1)     | Root of the heap, always accessible                                    |
| `size()`                         | O(1)     | Stored as a member variable                                            |
| `empty()`                        | O(1)     | Stored as a member variable                                            |
| Find arbitrary element           | O(n)     | Must scan the entire underlying array — no ordering guarantee          |
| Remove arbitrary element         | O(n)     | Not supported; would require linear scan + rebuild                     |
| Iterate all elements             | O(n)     | Underlying array is a flat vector, but order is heap-order, not sorted |
| Construction (from `n` elements) | O(n)     | Bottom-up heapify (not `n × log n`)                                    |

> **Note:** There is no `find()`, no iterator, and no way to remove an arbitrary element efficiently. The only element you can touch is `top()`.

### `multiset` (Red-Black Tree)

| Operation | Time | Explanation |
|---|---|---|
| `insert(x)` | O(log n) | BST insertion + rebalancing (rotations, O(1) each) |
| `erase(it)` | O(log n) amortized | BST deletion + rebalancing; iterator version is O(1) amortized, but rebalancing adds log n |
| `erase(x)` (by value) | O(k + log n) | `k` = number of occurrences erased (all equal elements removed) |
| `find(x)` | O(log n) | Standard BST search |
| `count(x)` | O(log n) | BST search + count of equal keys in a subtree |
| `lower_bound(x)` / `upper_bound(x)` | O(log n) | BST search to find the first position |
| `begin()` / `rbegin()` | O(1) | Leftmost/rightmost node cached |
| `size()` | O(1) | Stored as a member variable |
| `empty()` | O(1) | Stored as a member variable |
| Iterate all elements | O(n) | In-order traversal, yields sorted order |

> **Key tradeoff:** `multiset` node allocation has higher constant-factor overhead (each node stores pointers, color, value) compared to the flat array backing a `priority_queue`.

## Space Complexity

| Data Structure | Space | Explanation |
|---|---|---|
| `priority_queue` | O(n) | A single contiguous array (`std::vector`) of size `n`. No per-node pointer overhead. Very cache-friendly. |
| `multiset` | O(n) | Each node stores: value + left pointer + right pointer + parent pointer + color (enum). Typically 3-4x the memory of an equivalent `priority_queue` for the same number of elements. |

### Per-element memory breakdown (64-bit system)

| | `priority_queue` | `multiset` |
|---|---|---|
| Per element | 4 bytes (`int`) | 4 bytes (`int`) + 24 bytes (3 pointers × 8) + 4 bytes (color, padded) ≈ **32 bytes** |
| For 10⁶ elements | ~4 MB | ~32 MB |

> The flat array of `priority_queue` also has excellent cache locality — iterating or pushing/poping touches memory sequentially. The pointer-chasing in `multiset`'s tree traversal causes frequent cache misses, making it slower per operation despite the same asymptotic O(log n).

## When to Use Which

- **Use `priority_queue`** when you only need the max/min element repeatedly (e.g., heap sort, Dijkstra, top-K problems). It's lighter and faster for this single use case.
- **Use `multiset`** when you need sorted-order traversal, arbitrary deletions, or element lookup alongside max/min access.
