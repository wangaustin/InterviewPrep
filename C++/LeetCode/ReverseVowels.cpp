// Input:  "leetcode"
// Output: "leotcede"

#include <iostream>
#include <unordered_set>
#include <string>

std::string reverseVowels(std::string s)
{
    std::unordered_set<char> vowels = 
    {
        'a', 'e', 'i', 'o', 'u',
        'A', 'E', 'I', 'O', 'U'
    };

    int left = 0;
    int right = s.size() - 1;

    while (left < right)
    {
        while (left < right && vowels.count(s[left] == 0))
        {
            ++left;
        }

        while (left < right && vowels.count(s[right] == 0))
        {
            --right;
        }

        std::swap(s[left], s[right]);
        ++left;
        --right;
    }
}