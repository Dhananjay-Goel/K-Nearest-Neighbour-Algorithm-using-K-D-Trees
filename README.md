# K-Nearest-Neighbour-Algorithm-using-K-D-Trees
Implementation of K-Nearest-Neighbour Algorithm using K-D Tree and custom build Priority Queue. From a given dataset, it gives us the nearest neighbour and any number of neighbours to any given point.

To run the program, compile and execute the main.c file

# Input
The input is in a text format 
1st line: Dimensions - K
2nd line: Number of neighbours to find
3rd line: Number of input points of K dimension
4th line: the data point for which the neighbours are to be found 
Then the data points are input line by line

For the given input file, the dataset repesent the following-
The columns are equal to the number of dimensions of the data points

#Output
The program will give the number of nearest neighbours for the given point.

For the given inpiut file:-
Given the number of dimensions - 4
Number of nearest neighbours to find- 10
Number of data points given - 10000
The data point around which neighbours to find - {689,7890,55,909}

Results of Application OF KNN Algorithm :
{1005,4940,2989,2625}
{3967,7037,2663,43}
{5133,8413,2210,994}
{4543,9680,110,1618}
{2870,7522,474,3499}
{2138,10700,530,2461}
{3322,13287,334,703}
{4343,9578,1187,113}
{1446,5886,2679,699}
{4872,8106,3656,3343}


Finding Minimum Neighbour and then Deleting them and then finding Minimum Neighbour till we get given number of neighbours :
{1446,5886,2679,699}
{2870,7522,474,3499}
{2138,10700,530,2461}
{4343,9578,1187,113}
{4543,9680,110,1618}
{3967,7037,2663,43}
{1005,4940,2989,2625}
{5133,8413,2210,994}
{3322,13287,334,703}
{4872,8106,3656,3343}
