This repository contains all codes for Dynamic Programming problems being taught in Striver's Playlist 
With time, I will also add even more DP problems if found important from interview perspective.

Also, The only Pattern we need to remember for any DP problem.
First, Write the Recursive function, then make memoization from it and then make Tabulation. Lastly, if possible space optimise it. 

Also, for every DP problem, remember the pattern for writing/solving it..

1. Express function in terms of indexes.
2. Do all possible stuff on that index i.e explore all posibilites (base case + other calculations)
3. write the return statement (max or min or + or any another operation)

Points to remember for every DP problem:-
1. The direction of tabulation will always be opposite to that of memoization for base cases as well as logical calculations from base case to final state(and vice versa)
2. For tabulation always follow the below order:-
    a> Write down base case.
    b> Write the for loops
    c> Do traversal or other logical calculations inside the for loops, leading upto the final state
    d> return final state.
3. While writing the base cases, must maintain the order as in which base cases are reached earlier. It is really important.
