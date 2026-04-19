## What Changed from OrderBook_1?
- Added `std::unordered_map<int, OrderRef> order_index_`
- When inserting order, added
```
auto it = std::prev(level.orders.end());
order_index_[id] = OrderRef{side, price, it};
```

## Complexity
- Add Order: O(log P) to find/create level, O(1) to append
- Cancel Order: O(1) average to find by id, O(1) to erase, O(log P) to find level
- Best Bid/Ask: O(1)

## Next Steps
Matching incoming orders against the opposite side.
- Incoming buy matches lowest ask first
- Incoming sell matches highest bid first
- Partial fills
- FIFO within a level
- Remove fully filled resting orders
- Leave remaining incoming quantity resting on the book

## Knowledge Check
Why do we still need `price` if we have the list iterator?

<details>
  <summary>Click to reveal answer</summary>

  The list iterator only tells us the order's location inside the list, not which map entry owns that list. 
  Price is needed to find the level in the map and update `total_qty`.
</details>

<br>

For an incoming buy order, what exact condition tells us whether it should keep matching against the ask side?
<details>
  <summary>Click to reveal answer</summary>

  There are asks available. <br>
  Best ask price <= buy limit price.<br>
  Incoming quantity > 0.<br>

  In other words, buyer is willing to pay UP TO their limit, so any ask AT OR BELOW that price is acceptable.<br>
  <code>incoming.qty > 0 AND asks not empty AND best_ask <= buy_price </code><br>

  Example:<br>
  Buy order is "I will pay up to 100."<br>
  Ask at 99 -> match!<br>
  Ask at 100 -> match!<br>
  Ask at 101 -> NO match!<br>
</details>

<br>

When we partially fill a resting order, what exactly needs to be updated besides its quantity?
<details>
  <summary>Click to reveal answer</summary>
  1. The resting order's quantity: <code>order_it->qty -= traded;</code><br>
  2. The level's total quantity: <code>level.total_qty -= traded;</code><br>
  3. If the resting order is fully filled, remove it from the FIFO list and from `order_index_`<br>
  4. If the price level becomes emtpy, erase price level from the book itself<br>

</details>

<br>

When matching, should we process one order per price level, or potentially multiple orders within the same level before moving to the next price?

<details>
  <summary>Click to reveal answer</summary>

  Multiple.<br>

  Within each price level, we match orders in FIFO order, potentially consuming multiple resting orders before moving to the next price level.

  Example:<br>
  Ask 100:<br>
  [order1: qty 5]<br>
  [order2: qty 10]<br>
  [order3: qty 8]<br>
  <br>
  If incoming buy order has qty = 20:<br>
  1. Fill order1(5) -> remaining = 15<br>
  2. Fill order2(10) -> remaining = 5<br>
  3. Fill order3(5) -> remaining = 0<br>
  You process multiple orders at the same price level before moving on.

</details>

<br>

After matching, if the incoming order still has remaining quantity, what should happen to it?
<details>
  <summary>Click to reveal answer</summary>
  It becomes a resting order in the book at its limit price, placed at the end of the FIFO queue for that price level.
</details>