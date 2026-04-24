// Find length of longest substring without repeating chars.
// "abcabcbb" -> 3 ("abc")

// Approach: Sliding Window
// - Use set or hashmap
// - Expand right pointer
// - If duplicate -> move left pointer until valid

#include <unordered_map>
#include <string>

int lengthOfLongestSubstring(std::string s)
{
    std::unordered_map<char, int>map; // character -> most recent index
    int left = 0, maxLength = 0;

    // expand window using the right pointer
    for (int right = 0; right < s.size(); ++ right)
    {
        // current character already exists in the map
        if (map.count(s[right]))
        {
            // move left pointer to the right of the last occurrence
            // NOTE: use max to avoid moving left backward
            left = std::max(left, map[s[right]] + 1);
        }

        // update the last seen index of the current character
        map[s[right]] = right;

        // update max length of valid substring
        // current window size = right - left + 1
        maxLength = std::max(maxLength, right-left-1);
    }

    return maxLength;
}