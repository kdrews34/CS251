


Name:
Kevin Andrews
-----------------------------------------------

Please confirm that you compiled your solution with test cases exercising ALL
functions using g++ -std=c++11.  Confirm this statement by typing YES below.
(If you did not do this, compilation errors may result in an overall grade of
zero!)


YES



Describe what augmentations to the bst data structures you made to complete the 
project -- i.e., what types / data members did you change and why?


The only changes I made to the bst data structures  was the addition of
a variable I called "numNodes" in the bst_node struct which kept track of 
the number of nodes in the subtree rooted at that bst_node




-----------------------------------------------
Which functions did you need to modify as a result of the augmentations from the previous
question?  

The functions I needed to modify were insert, remove, and the from_sorted_vector
helper function called "_from_vec"







-----------------------------------------------
For each function from the previous question, how did you ensure that the (asymptotic) runtime 
remained the same?

For insert, I made sure that incNumNodes, isSizeBalanced, and sizeBalance helper functions called in insert,
    maintained the same runtime as the original insert, so that the runtime would
    only increase by a scalar multiple of it's original runtime

For remove, I made sure that incNumNodes, isSizeBalanced, and sizeBalance helper functions called in insert,
    maintained the same runtime as the original insert, so that the runtime would
    only increase by a scalar multiple of it's original runtime

For from_sorted_vector, I only added a single line consisting of an assignment
    to numNodes of a sum of a couple passed-by-reference parameters


-----------------------------------------------
For each of the assigned functions, tell us how far you got using the choices 0-5 and
answer the given questions.  


0:  didn't get started
1:  started, but far from working
2:  have implementation but only works for simple cases
3:  finished and I think it works most of the time but not sure the runtime req is met. 
4:  finished and I think it works most of the time and I'm sure my design leads to 
       the correct runtime (even if I still have a few bugs).
5:  finished and confident on correctness and runtime requirements


to_vector level of completion:  _____5______  


-----------------------------------------------
get_ith level of completion:  _____5______  

    How did you ensure O(h) runtime?

    ANSWER:
-----------------------------------------------
position_of level of completion:  _____5______  

    How did you ensure O(h) runtime?

    ANSWER:
-----------------------------------------------
num_geq level of completion:  _____4______  

    How did you ensure O(h) runtime?

    ANSWER:

-----------------------------------------------
num_leq level of completion:  _____4_______

    How did you ensure O(h) runtime?

    ANSWER:

-----------------------------------------------
num_range level of completion:  _____3_______

    How did you ensure O(h) runtime?

    ANSWER:

-----------------------------------------------
extract_range level of completion:  _____3_______

    How did you ensure O(h+k) runtime?

    ANSWER:

Implementation of size-balanced criteria according to 
the given guidelines:

    Level of completion: _____5______











