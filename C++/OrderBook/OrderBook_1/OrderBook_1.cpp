/** FIRST MILESTONE: Basic Order Book Implementation 
 * 1. add a resting order
 * 2. print the book
 * 3. query best bid/ask
 * **/

// side of the order
enum class Side
{
    Buy,
    Sell
};

// order structure
struct Order
{
    int id;
    Side side;
    int price;
    int qty;
};

#include <list>
// price level, contains all orders at the same price
struct Level
{
    std::list<Order> orders;
    int total_qty = 0;
};

// two sides of the book
// conceptual data model:
//    Bids
//    100 -> [order7, order9, order15]
//    99 -> [order20]
//
//    Asks
//    101 -> [order3, order8]
//    102 -> [order11]


#include <iostream>

#include <map>
#include <functional>
#include <optional>

class OrderBook {
public:
    void add_order(int id, Side side, int price, int qty)
    {
        Order order{id, side, price, qty};

        if (side == Side::Buy)
        {
            auto& level = bids_[price];
            level.orders.push_back(order);
            level.total_qty += qty;
        }
        else
        {
            auto& level = asks_[price];
            level.orders.push_back(order);
            level.total_qty += qty;
        }
    }

    std::optional<int> best_bid() const 
    {
        if (bids_.empty())
        {
            return std::nullopt;
        }
        return bids_.begin()->first;
    }

    std::optional<int> best_ask() const
    {
        if (asks_.empty())
        {
            return std::nullopt;
        }
        return asks_.begin()->first;
    }

    void print_book() const
    {
        std::cout << "Asks:\n";
        for (const auto& [price, level] : asks_)
        {
            std::cout << price << " x " << level.total_qty << "\n";
        }

        std::cout << "Bids:\n";
        for (const auto& [price, level] : bids_)
        {
            std:: cout << price << " x " << level.total_qty << "\n";
        }
    }

private:
    std::map<int, Level, std::greater<int> > bids_; // price -> level, sorted by price descending
    std::map<int, Level, std::less<int> > asks_; // price -> level, sorted by price ascending

    // this means:
    // - bids.begin() is the best bid (highest price); favors the buyer that pays the most
    // - asks.begin() is the best ask (lowest price); favors the seller that accepts the least

    // so far:
    // - best_bid() is O(1) from bids.begin()
    // - best_ask() is O(1) from asks.begin()
    // - add_order() is O(log n) to find the price level (n = number of distinct prices/active price levels), 
    //   then O(1) to add the order to the list
    // - remove_order() is O(log n) to find the price level (n = number of distinct prices/active price levels), 
    //   then O(k) to find the order in the list (k = number of orders at that price level)
};


int main()
{
    OrderBook ob;

    ob.add_order(1, Side::Buy, 100, 10);
    ob.add_order(2, Side::Buy, 100, 20);
    ob.add_order(3, Side::Buy, 99, 15);

    ob.add_order(4, Side::Sell, 101, 12);
    ob.add_order(5, Side::Sell, 102, 8);

    ob.print_book();

    auto bb = ob.best_bid();
    auto ba = ob.best_ask();

    if (bb)
    {
        std::cout << "Best Bid: " << *bb << "\n";
    }

    if (ba)
    {
        std::cout << "Best Ask: " << *ba << "\n";
    }
}