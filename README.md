# prodcos

The sample input file "in" contains the lines:

-128
2
3
6
9
12
20

The first negative number means that we want the algorithm to run over all precisions from 8 bits to 128 bits. If we'd put there 128 rather -128, the algorithm would run simply once with 128 bits of precision. The following lines are numbers to partition. The output is an integer containing the number of possible equal-sum partitions. Note that a zero partition and its negation are counted twice.
