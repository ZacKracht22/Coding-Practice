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
	Problem: You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.
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
};