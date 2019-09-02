/*The following functions are solutions to problems found on Leetcode in C++*/
class Solutions {
public:
	/*
		Problem: Given an array of integers, return indices of the two numbers such that they add up to a specific target.
		You may assume that each input would have exactly one solution, and you may not use the same element twice.
		Example:
		Given nums = [2, 7, 11, 15], target = 9,
		Because nums[0] + nums[1] = 2 + 7 = 9,
		return [0, 1].
	*/
    vector<int> twoSum(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        int val1, val2;
        vector<int> ret;
        
        vector<int> unsorted = nums;
        std::sort(nums.begin(),nums.end());
        while(left < right){
            if(nums[left] + nums[right] < target){
                left++;
            }else if(nums[left] + nums[right] > target){
                right--;
            }else{
                val1 = nums[left];
                val2 = nums[right];
                break;
            }
        }
        for(int i = 0; i < nums.size();i++){
            if(unsorted[i] == val1 || unsorted[i] == val2){
                ret.push_back(i);
            }
        }
        return ret;
    };
	
	/*
	Problem: You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order
	and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.
	You may assume the two numbers do not contain any leading zero, except the number 0 itself.
	Example:
	Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
	Output: 7 -> 0 -> 8
	Explanation: 342 + 465 = 807.
	*/
	/**
	 * Definition for singly-linked list.
	 * struct ListNode {
	 *     int val;
	 *     ListNode *next;
	 *     ListNode(int x) : val(x), next(NULL) {}
	 * };
	 */
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int carry = 0;
        ListNode* head = NULL;
        ListNode* nodeptr = NULL;
        ListNode* prev = NULL;
        while(l1 != NULL || l2 != NULL){
            int sum = 0;
            if(l1 == NULL){
                sum = l2->val + carry;
                l2 = l2->next;
            }else if(l2 == NULL){
                sum = l1->val + carry;
                l1 = l1->next;
            }else{
                sum = l1->val + l2->val + carry;
                l1 = l1->next;
                l2 = l2->next;
            }
            if(sum > 9){
                carry = 1;
                sum = sum%10;
            }
            else
                carry = 0;
            if(!nodeptr)
            {
                nodeptr = new ListNode(sum);
                if(!head)
                    head = nodeptr;
                if(prev)
                    prev->next = nodeptr;
            }
            prev = nodeptr;
            nodeptr = nodeptr->next;
        }
        if(carry == 1){
            nodeptr = new ListNode(1);
            prev->next = nodeptr;
        }
        return head;
    }
	
	/*
	Problem: Given a string, find the length of the longest substring without repeating characters.
	Example 1:
	Input: "abcabcbb"
	Output: 3 
	Explanation: The answer is "abc", with the length of 3.
	*/
	//Helper function to return whether or not a string has all unique characters
	bool isUnique(string s){
        map<char,int> char_map;
        for(int i = 0; i < s.size(); i++){
            if(char_map.find(s[i]) != char_map.end()){
                return false;
            }
            char_map[s[i]] = 1;
        }
        return true;
    }
    //Solution in O(n^2) time
    int lengthOfLongestSubstring(string s) {
        int i1 = s.size() - 2;
        int i2 = s.size() - 1;
        int sub_size = 2;
        int largest = 1;
        
        if(s.size() == 0) return 0;
        
        while(i1 >= 0){
            sub_size = i2-i1+1;
            string sub = s.substr(i1, sub_size);
            if(isUnique(sub)){
                if(sub_size > largest) largest = sub_size;
                i1--;
            }else{
                i2--;
                i1--;
            }
        }
        return largest;
    }
	
	/*
	Problem: There are two sorted arrays nums1 and nums2 of size m and n respectively.
	Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
	You may assume nums1 and nums2 cannot be both empty.
	Example 1:
	nums1 = [1, 3]
	nums2 = [2]
	The median is 2.0
	*/
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int size = nums1.size() + nums2.size();
        bool odd = (size%2) == 1;
        
        if(size == 1){
            return nums1.size() == 0 ? nums2[0] : nums1[0];
        }
        
        int middle = size / 2;
        vector<int> midNums(2,0);
        int index = 0;
        int val;
        for(int i = 0; i < middle+1; i++){
            if(nums1.size() == 0){
                val = nums2[0];
                nums2.erase(nums2.begin());
            }
            else if (nums2.size() == 0){
                val = nums1[0];
                nums1.erase(nums1.begin()); 
            }
            else if(nums1[0] <= nums2[0]){
                val = nums1[0];
                nums1.erase(nums1.begin());
            }
            else{
                val = nums2[0];
                nums2.erase(nums2.begin());
            }
            if(i >= middle-1){
                midNums[index] = val;
                index++;
            }
        }
        if(odd){
            return midNums[1];
        }
        return (midNums[0] + midNums[1]) / 2.0;
    }
	
	
	/*
	Problem: Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.
	Example 1:
	Input: "babad"
	Output: "bab"
	Note: "aba" is also a valid answer.
	*/
	//Helper function to return the longest palindrome from a starting left and right index
	pair<int,int> longestPalindrome(string s, int left, int right){
        while(left >= 0 && right < s.size()){
            if(s[left] != s[right])
                break;
                left--;
                right++;
        }
        pair<int,int> ret;
        ret.first = left+1;
        ret.second = right-1;
        return ret;
    }
    //Solution in O(n^2) time
    string longestPalindrome(string s) {  
        
        if(s.size() <= 1){
            return s;
        }
        if(s.size() == 2)
            return s[0] == s[1] ? s : string(1,s[0]);
        
        pair<int,int> oddPalindrome;
        pair<int,int> evenPalindrome;
        pair<int,int> longest(0,0);
        int lengthOdd, lengthEven, lengthLongest;
        for(int i = 1; i <s.size(); i++){
            oddPalindrome = longestPalindrome(s,i-1,i+1);
            evenPalindrome = longestPalindrome(s,i-1,i);
                        
            lengthOdd = oddPalindrome.second - oddPalindrome.first;
            lengthEven = evenPalindrome.second - evenPalindrome.first;
            lengthLongest = longest.second - longest.first;
            
            if(lengthOdd >= lengthEven && lengthOdd >= lengthLongest){
                longest = oddPalindrome;
            }
            else if(lengthEven >= lengthLongest)
                longest = evenPalindrome;
        }
        return s.substr(longest.first,longest.second-longest.first+1);
    }
	
	/*
	Problem:The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this:
	P   A   H   N
	A P L S I I G
	Y   I   R
	And then read line by line: "PAHNAPLSIIGYIR"
	Write the code that will take a string and make this conversion given a number of rows
	*/
	string convert(string s, int numRows) {
        if(numRows == 1){
            return s;
        }
        
        string ret;
        int index = 0;
        int row = 0;
        vector<vector<int>> zig(numRows,vector<int>());
        enum {UP, DOWN} direction = UP;
        
        while(index < s.size()){
            zig.at(row).push_back(s[index]);
            index++;
            if(row == 0){
                row++;
                direction = UP;
            }else if(row == numRows - 1){
                row--;
                direction = DOWN;
            }else if(direction == UP){
                row++;
            }else{
                row--;
            }
        }
        
        for(int i = 0; i < zig.size(); i++){
            for(int j = 0; j < zig.at(i).size();j++){
                ret.push_back(zig.at(i).at(j));
            }
        }
        
        return ret;
    }
	
	/*
	Problem: Given a 32-bit signed integer, reverse digits of an integer.
	*/
	int reverse(int x) {
        
        if(x > -10 && x < 10) return x;
        
        long ret = 0;
        
        while(x != 0){
            ret *= 10;
            ret += x%10;
            x = x/10;
            
        }
        
        if(x < 0){
            ret *= -1;
        }
        
        return ret > INT_MAX || ret < INT_MIN ? 0 : ret;
        
    }
	
	/*
	Problem: Implement atoi which converts a string to an integer.
	The function first discards as many whitespace characters as necessary until the first non-whitespace character is found. Then, starting from this character, takes an optional initial plus or minus sign followed by as many numerical digits as possible, and interprets them as a numerical value.
	The string can contain additional characters after those that form the integral number, which are ignored and have no effect on the behavior of this function.
	If the first sequence of non-whitespace characters in str is not a valid integral number, or if no such sequence exists because either str is empty or it contains only whitespace characters, no conversion is performed.
	If no valid conversion could be performed, a zero value is returned.
	Note:
	Only the space character ' ' is considered as whitespace character.
	Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: [−231,  231 − 1]. If the numerical value is out of the range of representable values, INT_MAX (231 − 1) or INT_MIN (−231) is returned.
	
	**This submission was faster than 100% of C++ submissions and used less memory than 100% of C++ submissions
	*/
	int myAtoi(string str) {
        enum {LEADING_WHITE_SPACE, VALUE} state = LEADING_WHITE_SPACE;
        long long int ret = 0;
        
        int i = 0;
        bool negative = false;
        while(i < str.size()){
            if(state == LEADING_WHITE_SPACE){
                if(str[i] == ' ')
                    i++;
                else if(str[i] == '+'){
                    i++;
                    state = VALUE;
                }
                else if(str[i] == '-'){
                    i++;
                    state = VALUE;
                    negative = true;
                }
                else if(str[i] >= '0' && str[i] <= '9')
                    state = VALUE;
                else
                    return 0;
            }else if (state == VALUE){
                if(str[i] >= '0' && str[i] <= '9'){
                    ret = ret * 10;
                    ret += str[i] - 48;
                    if(ret > INT_MAX)
                        return negative ? INT_MIN : INT_MAX;
                    i++;
                }else{
                    break;
                }
            }
        }
        if(negative)
            ret *= -1;
        
        return ret;
    }
	
	
	/*
	Problem: Determine whether an integer is a palindrome. An integer is a palindrome when it reads the same backward as forward.
	Example 1:
	Input: 121
	Output: true
	Example 2:
	Input: -121
	Output: false
	Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.
	*/
	bool isPalindrome(int x) {
        if(x<0)
            return false;
        else if(x < 10)
            return true;
        else if(x < 99)
            return x % 11 == 0;
        
        vector<int> v;
        while(x > 0){
            v.push_back(x%10);
            x = x/10;
        }
        
        int l = (v.size() / 2) - 1;
        int r = v.size()%2 == 1 ? l + 2 : l + 1;
        while(l >= 0 && r < v.size()){
            if(v[l] != v[r])
                return false;
            l--;
            r++;
        }
        return true;
    }
};