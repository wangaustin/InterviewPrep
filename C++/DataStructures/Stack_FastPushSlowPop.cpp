// stack is LIFO

// problem statement: implement a stack using two queues
// here I'll implement extensive push

// time complexities
// - push: O(1)
// - pop: O(n)
// - top: O(n)

#include <queue>
#include <iostream>

class MyStack
{
private:
    std::queue<int> q1;
    std::queue<int> q2;

public:
    void push(int x )
    {
        q1.push(x);
    }

    // removes and returns most recently pushed element
    // approach: because queue removes from the front, we move all earlier items
    // out of the way until only the last inserted element remains
    int pop()
    {
        while (q1.size() > 1)
        {
            q2.push(q1.front());
            q1.pop();
        }

        int result = q1.front();
        q1.pop();

        // q1 is now empty, swap them so q1 becomes the main queue again
        std::swap(q1, q2);

        return result;
    }

    // returns most recently pushed element without removing it
    int top()
    {
        while (q1.size() > 1)
        {
            q2.push(q1.front());
            q1.pop();
        }

        // only element left in q1 is the stack top
        int result = q1.front();

        // unlike pop(), we must keep the element at the stack top
        q2.push(q1.front());
        q1.pop();

        std::swap(q1, q2);

        return result;
    }

    bool empty()
    {
        return q1.empty();
    }
};