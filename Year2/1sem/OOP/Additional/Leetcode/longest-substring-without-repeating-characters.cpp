/*
Given a string s, find the length of the longest substring without repeating characters.

Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.

Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.

Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.


*/

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> ocurences(128, -1);

        int mx, sz;

        mx = 0;
        sz = s.length();
        int windowBeg = 0, windowEnd;

        for (int i = 0; i < sz; ++i)
        {
            if(ocurences[(int) s[i]] == -1)
            {
                windowEnd = i;
                ocurences[(int) s[i]] = i;
 
            }
            else
            {
                mx = max(mx, windowEnd-windowBeg+1);
                windowBeg = max(windowBeg, ocurences[(int) s[i]]+1);
                windowEnd = ocurences[(int) s[i]] = i;
      
                
                cout << windowBeg << ' ' << windowEnd << endl;
                
            }
        }
        

        return  max(mx, windowEnd-windowBeg+1); 
        
        
        
    }
};


int main()
{
    Solution s;
    cout << s.lengthOfLongestSubstring("abba") << endl;

}