// given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

// Input: n = 3
// Output: ["((()))","(()())","(())()","()(())","()()()"]

#include<vector>

class Solution {
public:
    std::vector<std::string> generateParenthesis(int n) {
        std::vector<std::string> result;
        backtrack(result, "", 0, 0, n);
        return result;
    }

private:
    void backtrack(std::vector<std::string>& result, std::string current, int open, int close, int n) {
        // base case: valid full string -> add to result
        if (current.length() == 2 * n) {
            result.push_back(current);
            return;
        }

        // option 1: add '(' if we still have some 'n' left
        if (open < n) {
            backtrack(result, current + "(", open + 1, close, n);
        }

        // option 2: add ')' only if it stays valid
        if (close < open) {
            backtrack(result, current + ")", open, close + 1, n);
        }
    }
};