// stack is LIFO

// problem statement: implement a stack using two queues
// here I'll implement extensive pop

// time complexities
// - push: O(n)
// - pop: O(1)
// - top: O(1)

#include <queue>
#include <iostream>

class MyStack
{
private:
    std::queue<int> q1;
    std::queue<int> q2;

public:
    int push(int x)
    {
        // step 1: put new element into q2 first so it becomes
        // the front later
        q2.push(x);

        // step 2: move all existing elements behind new element
        while (!q1.empty())
        {
            q2.push(q1.front());
            q1.pop();
        }

        // q2 has the correct stack order, so swap to make 
        // q1 the main queue
        std::swap(q1, q2);
    }

    // removes and returns top of stack
    int pop()
    {
        int result = q1.front();
        q1.pop();
        return result;
    }

    // returns top of stack without removing it
    int top()
    {
        return q1.front();
    }

    bool empty()
    {
        return q1.empty();
    }
};