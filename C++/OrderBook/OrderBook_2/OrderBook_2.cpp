/** SECOND MILESTONE: Basic Order Book Cancel 
 * 1. lookup order_id in order_index_
 * 2. get side, price, and order_it
 * 3. find the level in bids_ or asks_
 * 4. subtract that order's qty from total_qty
 * 5. erase the order from the list
 * 6. if the level is now empty, erase the price level
 * 7. erase the id from order_index_
 * **/

#include <iostream>
#include <map>
#include <list>
#include <unordered_map>
#include <functional>
#include <optional>

enum class Side
{
    Buy,
    Sell
};

struct Order
{
    int id;
    Side side;
    int price;
    int qty;
};

struct Level
{
    std::list<Order> orders;
    int total_qty;
};

struct OrderRef
{
    Side side;
    int price;
    std::list<Order>::iterator order_it;
};

class OrderBook
{
public:
    bool add_order(int id, Side side, int price, int qty)
    {
        // if quanty is invalid OR an order with this id already exists, reject
        // note: order_index_.count(id) ~= order_index_.contains(id), but .contains() requires C++20
        if (qty <= 0 || order_index_.count(id)) 
        {
            return false;
        }

        Order order{id, side, price, qty};

        if (side == Side::Buy)
        {
            auto& level = bids_[price];
            level.orders.push_back(order);
            auto it = std::prev(level.orders.end()); // .end() points one past the last element, so we want the prev
            level.total_qty += qty;
            order_index_[id] = OrderRef{side, price, it};
        }
        else // sell
        {
            auto& level = asks_[price];
            level.orders.push_back(order);
            auto it = std::prev(level.orders.end());
            level.total_qty += qty;
            order_index_[id] = OrderRef{side, price, it};
        }

        return true;
    }

    bool cancel_order(int id)
    {
        auto idx_it = order_index_.find(id);
        if (idx_it == order_index_.end())
        {
            return false;
        }

        const OrderRef& ref = idx_it->second;

        if (ref.side == Side::Buy)
        {
            auto level_it = bids_.find(ref.price);
            if (level_it == bids_.end()) // not found
            {
                return false;
            }

            level_it->second.total_qty -= ref.order_it->qty;
            level_it->second.orders.erase(ref.order_it);

            if (level_it->second.orders.empty())
            {
                bids_.erase(level_it);
            }
        }
        else // sell
        {
            auto level_it = asks_.find(ref.price);
            if (level_it == bids_.end())
            {
                return false;
            }

            level_it->second.total_qty -= ref.order_it->qty;
            level_it->second.orders.erase(ref.order_it);

            if (level_it->second.orders.empty())
            {
                asks_.erase(level_it);
            }
        }

        order_index_.erase(idx_it);
        return true;
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

        std::cout << "\n";

        std::cout << "Bids:\n";
        for (const auto& [price, level] : bids_)
        {
            std::cout << price << " x " << level.total_qty << "\n";
        }
    }

private:

    std::map<int, Level, std::greater<int>> bids_; // descending order
    std::map<int, Level, std::less<int>> asks_; // ascending order
    std::unordered_map<int, OrderRef> order_index_;
};


int main()
{
    OrderBook ob;

    ob.add_order(1, Side::Buy, 100, 10);
    ob.add_order(2, Side::Buy, 100, 20);
    ob.add_order(3, Side::Sell, 101, 15);

    ob.print_book();

    std::cout << "---- cancel 2 ----\n";
    ob.cancel_order(2);
    ob.print_book();

}