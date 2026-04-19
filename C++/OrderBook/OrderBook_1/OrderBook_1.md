## TLDR:
Use a sorted map for each side of the book so we can get the best price directly from begin(). 
Each price level stores a FIFO list of orders. 
This separates price priority from time priority cleanly.

## What's Missing
- Does not prevent duplicate `order_id`
- Does not support cancel
- Does not support matching
- Does not store where an order lives for O(1) cancel

## Next Steps
- Map from `order_id` to actual order location
    - Otherwise cancel is too slow, as you need to scan:
        - All bid price levels
        - All ask price levels
        - All orders in each level
    - `std::unordered_map<int, OrderRef> order_index`
        - `OrderRef` stores:
            - side
            - price
            - iterator to the order in the list

## Recap
- The order book is split into bid and ask sides
- Each side is organized by price
    - Bid descending
    - Ask ascending
- Each price level contains FIFO orders (time priority)
- `std::map + std::list` and `std::unordered_map` is a clean, classic baseline design
- `unordered_map` is needed for fast cancel by `order_id`

## Knowledge Check
Why is `std::list` better than `std::vector` for orders inside a price level in this order book design?

<details>
  <summary>Click to reveal answer</summary>
  TLDR: O(1) erase using iterator; stable iterators for order lookup; natural FIFO behavior.
  <br><br>
  <code>std::list</code> provides stable iterators (iterators stay valid unless that element is erased) and allows O(1) deletion given an iterator, critical for fast order cancellation. <code>std::vector</code>, on the other hand, requires shifting elements on erase, making cancellation O(n), and would also invalidate iterators.
  <br><br>
  Additionally, <code>std::list</code> naturally supports <code>push_back()</code> for adding new orders and <code>pop_front()</code> for matching oldest order.
</details>

<br>

`std::list` is slow due to cache locality. Why still use it?

<details>
    <summary>Click to reveal answer</summary>
    <code>std::list</code> has poor cache locality due to pointer chasing. In production HFT systems, we might use a contiguous structure or intrusive list with memory pooling. But for an interview, <code>std::list</code> gives the cleanest correctness with O(1) cancel and stable iterators.
    <br><br>
    In a real system, we might replace <code>std::list</code> with an intrusive linked list or a custom allocator-backed structure to reduce heap allocations and improve cache locality.
</details>