#include <iostream>
#include <list>
#include <map>
#include <unordered_map>

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

    void add(int id, Side side, int price, int qty)
    {
        if (qty <= 0 || order_index_.count(id)) return;
        
        Order incoming{id, side, price, qty};

        if (side == Side::Buy)
        {
            match_buy(incoming);
        }
        else
        {
            match_sell(incoming);
        }

        if (incoming.qty > 0)
        {
            add_resting(incoming);
        }
    }

    void cancel(int id)
    {
        auto it = order_index_.find(id);
        if (it == order_index_.end()) return;

        const OrderRef& ref = it->second;

        if (ref.side == Side::Buy)
        {
            auto level_it = bids_.find(ref.price);
            if (level_it != bids_.end())
            {
                level_it->second.orders.erase(ref.order_it);
                level_it->second.total_qty -= ref.order_it->qty;

                if (level_it->second.orders.empty())
                {
                    bids_.erase(level_it);
                }
            }
        }
        else
        {
            auto level_it = asks_.find(ref.price);
            if (level_it != asks_.end())
            {
                level_it->second.orders.erase(ref.order_it);
                level_it->second.total_qty -= ref.order_it->qty;

                if (level_it->second.orders.empty())
                {
                    asks_.erase(level_it);
                }
            }
        }

        order_index_.erase(it);
    }

    std::optional<int> best_bid() const
    {
        if (bids_.empty()) return std::nullopt;

        return bids_.begin()->first;
    }

    std::optional<int> best_ask() const
    {
        if (asks_.empty()) return std::nullopt;

        return asks_.begin()->first;
    }

    void print_book() const
    {
        std::cout << "Asks: " << "\n";

        for (const auto& [price, level] : asks_)
        {
            std::cout << price << " x " << level.total_qty << "\n";
        }

        std::cout << "Bids: " << "\n";

        for (const auto& [price, level] : bids_)
        {
            std::cout << price << " x " << level.total_qty << "\n";
        }
    }

private:
    std::map<int, Level, std::greater<int>> bids_;  // descending
    std::map<int, Level, std::less<int>> asks_; // ascending
    std::unordered_map<int, OrderRef> order_index_; // id -> OrderRef

private:

    void add_resting(const Order& order)
    {
        if (order.side == Side::Buy)
        {
            auto& level = bids_[order.price];
            level.orders.push_back(order);
            level.total_qty += order.qty;

            auto it = std::prev(level.orders.end());
            order_index_[order.id] = OrderRef{order.side, order.price, it};
        }
        else
        {
            auto& level = asks_[order.price];
            level.orders.push_back(order);
            level.total_qty += order.qty;

            auto it = std::prev(level.orders.end());
            order_index_[order.id] = OrderRef{order.side, order.price, it};
        }
    }

    // buy -> look for asks
    void match_buy(Order& incoming)
    {
        while (incoming.qty > 0 && !asks_.empty())
        {
            auto best_ask_it = asks_.begin();
            int ask_price = best_ask_it->first;

            // break when ask price goes beyond what we're willing to pay for
            if (ask_price > incoming.price) break;

            auto& level = best_ask_it->second;
            auto order_it = level.orders.begin();

            while (incoming.qty > 0 && order_it != level.orders.end())
            {
                int traded = std::min(incoming.qty, order_it->qty);

                incoming.qty -= traded;
                order_it->qty -= traded;
                level.total_qty -= traded;

                if (order_it->qty == 0)
                {
                    order_index_.erase(order_it->id);
                    order_it = level.orders.erase(order_it);
                }
                else
                {
                    ++order_it;
                }
            }

            if (level.orders.empty())
            {
                asks_.erase(best_ask_it);
            }
        }
    }

    // sell -> look for bids
    void match_sell(Order& incoming)
    {
        while (incoming.qty > 0 && !bids_.empty())
        {
            auto best_bid_it = bids_.begin();
            int bid_price = best_bid_it->first;

            // break when bid price has gone below what we're willing to sell for
            if (bid_price < incoming.price) break;

            auto& level = best_bid_it->second;
            auto order_it = level.orders.begin();

            while (incoming.qty > 0 && order_it != level.orders.end())
            {
                int traded = std::min(incoming.qty, order_it->qty);

                incoming.qty -= traded;
                order_it->qty -= traded;
                level.total_qty -= traded;

                if (order_it->qty == 0)
                {
                    order_index_.erase(order_it->id);
                    order_it = level.orders.erase(order_it);
                }
                else
                {
                    ++order_it;
                }
            }

            if (level.orders.empty())
            {
                bids_.erase(best_bid_it);
            }
        }
    }
};