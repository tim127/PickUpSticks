Hello Heartflow!

Thanks for taking the time to introduce me to your company! I'm excited to see
what is next. Here I will describe on a high level, my algorithm for the connected components
problem, and discuss what other advanced optimizations I might make, and any shortcomings
that are inherent in the code.

1) Algorithm Brief Overview

Note: x1,x2,y1,y2 are not the same as that written in the text file. Here, the endpoints are defined
such that x1 < x2 or if x1 = x2, y1 < y2.

1. Get all sticks and sort them by x1. O(nlogn) operation
2. For each stick, 
	- Add to the component if it intersects with one of the components lines'.
	- Merge components that connected to the same stick.
	- Optimization Trick::Cleaning up components
3. Return number of components left.

I introduce an optimization that cleans up a component by removing lines that are irrelevant to the
algorithm because they will never intersect a line again. In particular, we provided an ordering to x1
in step 1. Any line with x2 < x1 of the current line processed can be removed.
This allows me to decrease the time complexity from O(n^2), but worst case analysis is still O(n^2).

2) Advanced Optimizations

This algorithm works particularly well when the range of x values is large and the lengths of the sticks short, allowing us to 
remove many lines from the components along the way. However, it does not work as well when the range of x is small, and rather y is large,
but you can do the same exact algorithm but across a different dimension, ie sorting by y values.

You can discretize the entire coordinate x-y space first into grid blocks, and have each stick activate each grid block that it falls under.
Intersections are then found between the sticks that fall under the same block, creating a huge connected graph, where nodes are sticks and edges
are formed when two sticks intersect. Then you can find connected components in this graph.

3) Pitfalls
- Since the algorithm depends on the ordering in which we process the sticks, sorting this list,
this algorithm would not generalize to a case where sticks are coming in non-consecutively by data streams.

- As it stands, it assumes that the list of sticks will fit in memory. But I can imagine an improvement
where the blocks of sticks are read from disk and sorted in memory and blocks of sticks are written out 
when doing the sorting operation. 

-There are parts in the code where classes don't necessarily follow good object-oriented design, 
i.e. making encapsulated variables public. we can provide getter functions for these variables.

I spent 6 hours on this project.
