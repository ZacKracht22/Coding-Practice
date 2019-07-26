"""
File: fib.py
Author: Zac Kracht
Date: 7/26/2019
Description: Implementing functions to solve for the n'th number in Fibonacci's sequence
using various methods
"""

"""
Function: dynamic_fib
Description: Compute the n'th number in Fibonacci's sequence using dynamic programming
             Computes in O(n) time
"""
def dynamic_fib(n):
    if n == 1 or n == 2:
        return 1
    sequence = [None] * (n+1)
    sequence[1] = 1
    sequence[2] = 1
    for i in range(3, n+1):
        sequence[i] = sequence[i-1] + sequence[i-2]
    return sequence[n]

"""
Function: memoize_fib
Description: Compute the n'th number in Fibonacci's sequence using memoization
             Initially called with a memo = [None] * (n + 1)
             Computes in O(n) time
"""
def memoize_fib(n, memo):
    if memo[n] != None:
        return memo[n]
    if n == 1 or n == 2:
        result = 1
    else:
        result = memoize_fib(n-1, memo) + memoize_fib(n-2, memo)
    memo[n] = result
    return result

"""
Function: recursive_fib
Description: Compute the n'th number in Fibonacci's sequence using recursion
             Computes in O(2^n) time
"""
def recursive_fib(n):
    if n == 1 or n == 2:
        return 1
    return recursive_fib(n-1) + recursive_fib(n-2)



# Main Function
if __name__ == '__main__':
    print((dynamic_fib(5), dynamic_fib(25),dynamic_fib(100)))
    print((memoize_fib(5,[None]*6), memoize_fib(25, [None]*26),memoize_fib(100, [None]*101)))
    #Since the recursive function is O(2^n) rather than O(n), the 100th value takes significantly longer to compute
    print((recursive_fib(5), recursive_fib(25), recursive_fib(100)))