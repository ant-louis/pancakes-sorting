#include <vector> // to use vector

typedef std::vector<int> stack_type;

typedef std::vector<stack_type::size_type> flip_type;


/************************************simple_pancake-sort************************************
*
* ARGUMENTS :
*	- pancakes : a vector of int to be sorted
*	- flips : a vector of int containing the indexes of where to flip to sort the vector
*
* RETURN : nothing
*
*******************************************************************************************/
void simple_pancake_sort(const stack_type& pancakes, flip_type& flips);



/************************************astar_pancake-sort************************************
*
* ARGUMENTS :
*	- pancakes : a vector of int to be sorted
*	- flips : a vector of int containing the indexes of where to flip to sort the vector
*
* RETURN : nothing
*
*******************************************************************************************/
void astar_pancake_sort(const stack_type& pancakes, flip_type& flips);