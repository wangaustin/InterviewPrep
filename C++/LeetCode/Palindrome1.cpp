// Check if a string is a palindrome, ignoring non-alphanumeric and case.
// "A man, a plan, a canal: Panama" -> true

// Approach: Two-Pointers
// - Left at start, right at end
// - Skip non-alphanumeric
// - Compare lowercase
#include <string>

bool isPalindrome(std::string s)
{
    int left = 0, right = s.size() - 1;

    while (left < right)
    {
        // skip non-alphanumeric
        while (left < right && !isalnum(s[left])) ++left;
        while (left < right && !isalnum(s[right])) --right;

        // compare lower case
        if (std::tolower(s[left]) != std::tolower(s[right]))
        {
            return false;
        }

        ++left;
        --right;
    }

    return true;
}