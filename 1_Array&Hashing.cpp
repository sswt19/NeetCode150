#include <vector>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <list>
#include <sstream>
#include <climits>
#include <unordered_set>

using namespace std;

/*
1. Contains Duplicate :https://leetcode.com/problems/contains-duplicate/description/
2. Valid Anagram: https://leetcode.com/problems/valid-anagram/description/
3. Two Sum: https://leetcode.com/problems/two-sum/description/
4. Group Anagrams: https://leetcode.com/problems/group-anagrams/description/
5. Top K Frequent Elements: https://leetcode.com/problems/top-k-frequent-elements/description/
6. String Encode and Decode: https://neetcode.io/problems/string-encode-and-decode
7. Product of Array Except Self: https://leetcode.com/problems/product-of-array-except-self/description/
8. Valid Sudoku: https://leetcode.com/problems/valid-sudoku/description/
9. Longest Consecutive Sequence: https://leetcode.com/problems/longest-consecutive-sequence/description/
*/

// 1.
class ContainsDuplicate
{
    /*
    1. For sorted array : no need for set, compare i and i-1 index values, if same there is duplicate
        T: O(n) S:O(1)

    2. For unsorted array: use hashmap/set
        T: O(n) S:O(n)
    */
public:
    bool containsDuplicate(vector<int> &nums)
    {
        unordered_set<int> s;
        for (auto v : nums)
        {
            if (s.find(v) != s.end())
                return true;
            s.insert(v);
        }
        return false;
    }
};

// 2.
class IsAnagram
{
    /*
        T:O(n) S:O(26)=>O(1)
    */
public:
    bool isAnagram(string s, string t)
    {
        // check number of characters are same in both strings first
        if (s.size() != t.size())
            return false;

        // use vector as map since already know the characters are lowercase alphabets
        vector<int> freq(26, 0);

        // increase frq for first string and decrease for the other if all freqs 0 at end then anagram
        for (int i = 0; i < s.size(); i++)
        {
            freq[s[i] - 'a']++;
            freq[t[i] - 'a']--;
        }

        for (auto v : freq)
            if (v != 0)
                return false;
        return true;
    }
};

// 3.
class TwoSum
{
    /*
        1. For Sorted array: use two pointers start and end
            T:O(n) S:O(1)

        2. For Unsorted array: use hashmap to store the index of each value
            we will check for nums[i] if target-nums[i] is already present
            T:O(n) S:O(n)
    */
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> value_to_index;
        for (int i = 0; i < nums.size(); i++)
        {
            if (value_to_index.find(target - nums[i]) != value_to_index.end())
                return {i, value_to_index[target - nums[i]]};
            value_to_index[nums[i]] = i;
        }
        return {};
    }
};

// 4.
class GroupAnagrams
{
    /*
        Number of strings: n, max size of each string: m
        1. Sort the strings and anagrams will be same after being sorted
            T:O(n*mlogm) S:O(nk)

        2. Do counting sort, saswat=> a2s2t1w1, anagrams will have same freq mapping
            T:O(nm) S:O(nm)
    */
private:
    string createFreqMap(const string &s)
    {
        vector<int> freq(26, 0);
        for (auto c : s)
            freq[c - 'a']++;

        string freqMap = "";
        for (int i = 0; i < 26; i++)
            if (freq[i] > 0)
                freqMap += char('a' + i) + to_string(freq[i]);
        return freqMap;
    }

public:
    // 1
    vector<vector<string>> groupAnagramsSortMethod(vector<string> &strs)
    {
        unordered_map<string, vector<string>> groups;

        for (int i = 0; i < strs.size(); i++)
        {
            string copy(strs[i]);
            sort(copy.begin(), copy.end());
            if (groups.find(copy) == groups.end())
                groups[copy] = {};
            groups[copy].push_back(strs[i]);
        }
        vector<vector<string>> ans;
        for (auto p : groups)
            ans.push_back(p.second);

        return ans;
    }
    // 2
    vector<vector<string>> groupAnagrams(vector<string> &strs)
    {
        vector<vector<string>> ans;
        unordered_map<string, vector<string>> groupedAnagrams;
        for (auto s : strs)
        {
            auto freqMap = createFreqMap(s);
            groupedAnagrams[freqMap].push_back(s);
        }
        for (auto p : groupedAnagrams)
            ans.push_back(p.second);
        return ans;
    }
};

// 5.
class topKFreq
{
    /*
        first find freq of all elements, push {freq, number} in min heap of size k at the end get the k elements from min heap
        T: O(n+nlogk) => O(nlogk)
        S: O(n+k) hash map + heap
    */
public:
    vector<int> topKFrequent(vector<int> &nums, int k)
    {
        unordered_map<int, int> freq;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pqMin;
        vector<int> topKFreq;

        // get freq
        for (auto v : nums)
        {
            if (freq.find(v) == freq.end())
                freq[v] = 0;
            freq[v]++;
        }

        // push in min heap with max size k allowed
        for (auto p : freq)
        {
            pqMin.push({p.second, p.first});
            if (pqMin.size() > k)
                pqMin.pop();
        }

        // retrieve top k elements
        while (!pqMin.empty())
        {
            topKFreq.push_back(pqMin.top().second);
            pqMin.pop();
        }
        return topKFreq;
    }
};

// 6.
class EncodeAndDecode
{
    /*
        We can't use a delimiter as it can be part of the string
        we will use format: string_size + ',' + orig_string to encode and decode

        n=num of strings m=max size of string
        Encode: T:O(n*m) S:O(n*m)
        Decode: T:O(n*m) S:O(n*m)
    */
public:
    string encode(vector<string> &strs)
    {
        string encoded = "";
        for (auto s : strs)
            encoded += to_string(s.size()) + "," + s;
        return encoded;
    }

    vector<string> decode(string s)
    {
        vector<string> decoded;
        int i = 0;
        string size = ""; // to store size of next string which will be decoded
        while (i < s.size())
        {
            // till ',' is reached we know it is a number
            while (s[i] != ',')
            {
                size += s[i];
                i++;
            }
            // decode: now we will get string of that size
            i++; // move i from 'i' to start of string
            int string_size = stoi(size);
            string orig = s.substr(i, string_size); // got the decoded string
            decoded.push_back(orig);

            // now look for next string
            size = "";
            i = i + string_size;
        }
        return decoded;
    }
};

// 7.
class ProductExceptSelf
{
    /*
        1. With division:
            Count of zeros: Two 0s all values will be 0, One 0 all except the index where nums[i] is 0 will be 0
                            Zero 0s ans[i]=mulAll/nums[i]
            T:O(n) S:O(n) to store answer

        2. Without division: for ans[i]=leftCumMul[i-1] * rightCumMul[i+1]
            we will store the answer in leftCumMul which we computed
            and rightCumMul we will store in a variable when we traverse from end
            T:O(n) S:O(n) to store answer
    */
public:
    vector<int> productExceptSelfWithoutDivision(vector<int> &nums)
    {

        int n = nums.size();
        vector<int> leftCumMul(nums); // we will store answer in this as well
        if (n <= 1)
            return leftCumMul;

        for (int i = 1; i < n; i++)
            leftCumMul[i] = leftCumMul[i - 1] * nums[i];

        int rightCumMul = 1;
        for (int i = n - 1; i >= 0; i--)
        {
            if (i == 0)
                leftCumMul[i] = rightCumMul;
            else
                leftCumMul[i] = leftCumMul[i - 1] * rightCumMul;

            rightCumMul = rightCumMul * nums[i];
        }
        return leftCumMul;
    }

    vector<int> productExceptSelfWithDivision(vector<int> &nums)
    {
        int zeroCount = 0;
        int allMulRes = 1;
        vector<int> ans(nums.size(), 0);

        for (auto n : nums)
        {
            if (n == 0)
                zeroCount++;
            else
                allMulRes *= n;
        }

        if (zeroCount > 1)
            return ans;

        for (int i = 0; i < ans.size(); i++)
        {
            if (zeroCount == 1)
            {
                if (nums[i] == 0)
                    ans[i] = allMulRes;
                else
                    ans[i] = 0;
            }
            else
                ans[i] = allMulRes / nums[i];
        }
        return ans;
    }
};

// 8.
class ValidSudoku
{
    bool isRowValid(const vector<vector<char>> &board, const int &row)
    {
        unordered_set<char> s;
        for (int i = 0; i < 9; i++)
        {
            if (board[row][i] == '.')
                continue;
            if (s.find(board[row][i]) != s.end())
                return false;
            s.insert(board[row][i]);
        }
        return true;
    }
    bool isColValid(const vector<vector<char>> &board, const int &col)
    {
        unordered_set<char> s;
        for (int i = 0; i < 9; i++)
        {
            if (board[i][col] == '.')
                continue;
            if (s.find(board[i][col]) != s.end())
                return false;
            s.insert(board[i][col]);
        }
        return true;
    }
    bool isSubBoxValid(const vector<vector<char>> &board, const int &row, const int &col)
    {
        unordered_set<char> s;
        for (int k = row; k < row + 3; k++)
        {
            for (int l = col; l < col + 3; l++)
            {
                if (board[k][l] != '.' && s.find(board[k][l]) != s.end())
                    return false;
                s.insert(board[k][l]);
            }
        }
        return true;
    }

public:
    bool isValidSudoku(vector<vector<char>> &board)
    {
        for (int i = 0; i < 9; i++)
            if (!(isRowValid(board, i) && isColValid(board, i)))
                return false;

        // check for sub-boxes
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (!isSubBoxValid(board, 3 * i, 3 * j))
                    return false;

        return true;
    }
};

// 9.
class LongestConsecutiveSeq
{
    /*
        For each number which is not seen yet, we will find the longest sequence containing that number
            we will do it by increasing the windows size by going both left and right of the number
        T:O(n) S:O(n)
    */
public:
    int longestConsecutive_slow(vector<int> &nums)
    {

        unordered_map<int, bool> marked; // to find which number is present in constant time
        int streak = 0;

        for (auto x : nums)
            marked[x] = false; // false means this numbr has not been used in any sequence

        for (auto start : nums)
        {
            if (marked[start] == false) // we will find sequence which includes the number
            {
                int end = start;
                marked[start] = true;
                while (marked.find(start - 1) != marked.end())
                {            // this loop finds start of sequence, if start-1 exists only then decrease start
                    start--; // start-1 is present, we reduce the window by 1 and mark it
                    marked[start] = true;
                }

                while (marked.find(end + 1) != marked.end())
                {          // this loop finds end of sequnece, if end+1 exist only then increase cur
                    end++; // we increase the window by 1 and mark it
                    marked[end] = true;
                }

                streak = max(streak, end - start + 1);
            }
        }
        return streak;
    }
};