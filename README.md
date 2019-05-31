# AlphaBeta-vs-Minimax
Comparing the system time of Alphabeta and Minimax.
The comparison has been made between the minimax and alphabeta tree pruning.
# Assumptions: 
1.) The tree supports the binary tree i.e. the algorithm is suitable to play a game tic tac toe.
2.) The input case with which it is compared is : (8 nodes:1,2,3,4,5,6,7,8 as values).
3.) Intialisation of node structure has been specified in the code.
# Algorithm : 
function alphabeta(node, depth, α, β, maximizingPlayer) is
    if node is a terminal node then
        return the heuristic value of node
    if maximizingPlayer then
        value := −∞
        for each child of node do
            value := max(value, alphabeta(child, depth − 1, α, β, FALSE))
            α := max(α, value)
            if α ≥ β then
                break (* β cut-off *)
        return value
    else
        value := +∞
        for each child of node do
            value := min(value, alphabeta(child, depth − 1, α, β, TRUE))
            β := min(β, value)
            if α ≥ β then
                break (* α cut-off *)
        return value
# Result : 
# shubhendra@shubhendra-Inspiron-660s:~/Desktop$ time ./minimax
8
1
2
3
4
5
6
7
8
Height is:3
The max value is :6
# real	0m6.545s
user	0m0.004s
sys	0m0.000s
# shubhendra@shubhendra-Inspiron-660s:~/Desktop$ time ./Alphabeta 
8
1
2
3
4
5
6
7
8
Height is:3
The max value is :6

# real	0m4.944s
user	0m0.004s
sys	0m0.000s

Such a small input case also had a significant difference of 2 ms in the execution time, thus proving the alphabeta pruning to be very effective in the practical situations.
