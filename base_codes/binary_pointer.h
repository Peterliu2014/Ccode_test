#ifndef BINARY_POINTER_
#define BINARY_POINTER_

#include <string>
#include <vector>
#include <unordered_map>

namespace binary_pointer
{

// https://leetcode-cn.com/problems/longest-substring-without-repeating-characters//
int lengthOfLongestSubstring(std::string s);

// https://leetcode-cn.com/problems/minimum-window-substring/
std::string minWindow(std::string s, std::string t);

// https://leetcode-cn.com/problems/substring-with-concatenation-of-all-words/
std::vector<int> findSubstring(std::string s, std::vector<std::string>& words);
bool is_ok(std::string s, int start, std::unordered_map<std::string, int> map, int word_len, int words_num);

std::vector<int> findSubstring_v2(std::string s, std::vector<std::string>& words);



} // namespace binary_pointer



#endif