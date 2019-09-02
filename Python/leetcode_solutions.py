#file: leetcode_solutions.py
#author: Zac Kracht
#date: 9/2/2019
#description: The following classes/methods are python solutions to various problems found on leetcode.com


"""
Problem: Implement an LRU cache with the following functions:
get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
put(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.
Both operations should be done in O(1) time
"""
#Node class to use in LinkedList implementation
class Node:
    def __init__(self, key, val):
        self.key = key
        self.val = val
        self.next = None
        self.prev = None

#Implementation of a doubly linked list
class LinkedList:
    def __init__(self):
        #Create a dummy head and tail for easier list creation
        self.head = Node(None, 'head')
        self.tail = Node(None, 'tail')
        self.head.next = self.tail
        self.tail.prev = self.head

    def get_head(self):
        #return the next node from the dummy head
        return self.head.next

    def get_tail(self):
        #return the previous node from the dummy tail
        return self.tail.prev

    #Add a node to the end of the list by inserting it before the dummy tail
    def add(self, node):
        prev = self.tail.prev
        prev.next = node
        node.prev = prev
        node.next = self.tail
        self.tail.prev = node

    #Remove a node from the list
    def remove(self, node):
        prev = node.prev
        nxt = node.next
        prev.next = nxt
        nxt.prev = prev

#LRU Cache implementation with O(1) set and get functions
#A dict is used to map keys to node(key,val) objects within the list
class LRUCache(object):

    def __init__(self, capacity):
        """
        :type capacity: int
        """
        self.capacity = capacity
        self.dict = {}
        self.list = LinkedList()

    def get(self, key):
        """
        :type key: int
        :rtype: int
        """
        if key not in self.dict:
            return -1
        node = self.dict[key]
        self.list.remove(node)
        self.list.add(node)
        return node.val

    def put(self, key, value):
        """
        :type key: int
        :type value: int
        :rtype: None
        """
        #Check if the key has already been used and remove from dict and list to then be replaced
        if key in self.dict:
            temp = self.dict[key]
            self.list.remove(temp)
            del self.dict[key]
        node = Node(key, value)
        self.list.add(node)
        self.dict[key] = node
        #If capacity has been reached, remove the least frequently used key (head of the list)
        if len(self.dict) > self.capacity:
            head_node = self.list.get_head()
            self.list.remove(head_node)
            del self.dict[head_node.key]

"""
Problem: The Tribonacci sequence Tn is defined as follows: 

T0 = 0, T1 = 1, T2 = 1, and Tn+3 = Tn + Tn+1 + Tn+2 for n >= 0.

Given n, return the value of Tn.
"""
class Solution(object):
    #Solution using less memory than 100% of leetcode submissions in python, utilizing memoization
    def tribonacci(self, n):
        """
        :type n: int
        :rtype: int
        """
        nums = [0, 1, 1]
        if n < 3:
            return nums[n]
        for i in range(3, n):
            nums.append(nums[i-3] + nums[i-2] + nums[i-1])
        return nums[n-3] + nums[n-2] + nums[n-1]