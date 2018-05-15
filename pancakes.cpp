#include <iostream> // cin, cout
#include <vector> // to use vector
#include <algorithm> // to use "max( , )", "copy( , , )""
#include <iterator> // to use iter
#include <set> // to use set container
#include <utility> // to use pair
#include <unordered_set> // to use unordered_set
#include "pancakes.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::pair;
using std::set;
using std::unordered_set;

/**********************************************
*  node.first.first <- stack
*  node.first.second <- flip
*  node.second.first <- real flip cost
*  node.second.second <- estimated end cost
***********************************************/
typedef pair<pair<stack_type, flip_type>, pair<int,int> > node;


/************************************get_hash_value****************************************
*
* ARGUMENT : a vector v of int for which we want an unique key
*
* RETURN : an unique key corresponding to the given vector
*
*******************************************************************************************/
static size_t get_hash_value(const stack_type& vec);


/************************************compare**********************************************
*
* ARGUMENTS : 2 nodes a and b that we want to compare
*
* RETURN : a boolean value true if the cost of a is smaller than the cost of b
*
*******************************************************************************************/
static bool compare(const node& a, const node& b);


/************************************get_size_largest_pancake******************************
*
* ARGUMENT : a vector v of int in which we look for the biggest pancake not yet in place
*
* RETURN : the value of the largest pancake not yet in place
*
*******************************************************************************************/
static int get_size_largest_pancake(const stack_type& vec);



/************************************simple_pancake-sort************************************
*
* ARGUMENTS :
*	- pancakes : a vector of int to be sorted
*	- flips : a vector of int containing the indexes of where to flip to sort the vector
*
* RETURN : nothing
*
*******************************************************************************************/
void simple_pancake_sort(const stack_type& pancakes, flip_type& flips){

	stack_type copy;
	stack_type::iterator index_max;
	int index;

	// Copy the pancakes vector to be able to modify it
	std::copy(pancakes.begin(), pancakes.end(), back_inserter(copy));

	for(stack_type::iterator i = copy.end(); i != copy.begin(); --i){

		// Find the index of the largest pancake in the stack that is not yet in place
		index_max = std::max_element(copy.begin(), i);

		// If index_max is the last index of the stack, that element is in place
		if(index_max == i-1)
			continue;

		// Add the flip of the biggest element
		index = std::distance(copy.begin(), index_max);
		flips.push_back(index);

		//Flip it to the top of the stack
		std::reverse(copy.begin(), index_max+1);

		// Add the flip of the end of the stack
		index = std::distance(copy.begin(), i-1);
		flips.push_back(index);

		// Flip all the stack
		std::reverse(copy.begin(), i);	
	}
	return;
}



/************************************astar_pancake-sort************************************
*
* ARGUMENTS :
*	- pancakes : a vector of int to be sorted
*	- flips : a vector of int containing the indexes of where to flip to sort the vector
*
* RETURN : nothing
*
*******************************************************************************************/
void astar_pancake_sort(const stack_type& pancakes, flip_type& flips){

	//Create the set of nodes with the overloaded function "compare"
	set<node,bool(*)(const node&, const node&)> myset(&compare);

	// Create a unordered set of the vectors already met, where a vec is represented by an unique key
	unordered_set<int> set_of_parents;

	// Create the node parent, initialyze it and insert it to the set of already generated nodes (parents)
	node parent;
	std::copy(pancakes.begin(), pancakes.end(), back_inserter(parent.first.first));
	parent.second.first = 0;
	parent.second.second = 0;
	myset.insert(parent);

	// Create the final sorted vector
	stack_type sorted_vec;
	std::copy(pancakes.begin(), pancakes.end(), back_inserter(sorted_vec));
	std::sort(sorted_vec.begin(), sorted_vec.end());

	// Create variables for the real flip cost and the estimated end cost
	int real_flip_cost = 0;
	int estimated_end_cost = 0;

	// Variable used to calculate the key of a given vector for the unordered_map
	size_t key = 0;

	
	while(!std::equal(parent.first.first.begin(), parent.first.first.end(), sorted_vec.begin())){

		// Pop the new parent
		parent = *(myset.begin());
		myset.erase(myset.begin());

		// Insert the parent in the set of the nodes already met
		key = get_hash_value(parent.first.first);
		set_of_parents.insert(key);
		
		// Generate all children of the given vector
		for(stack_type::size_type i = 1; i < parent.first.first.size(); ++i){

			// Put back child to the initial parent stack
			node child = parent;

			// Reverse it
			std::reverse(child.first.first.begin(), child.first.first.begin() + i+1);

			// Check if the child hasn't been generated yet
			key = get_hash_value(child.first.first);
			if(set_of_parents.find(key) != set_of_parents.end())
				continue;
			
			// Calculate total cost of each child
			real_flip_cost = i+1;
			estimated_end_cost = get_size_largest_pancake(child.first.first);

			child.second.first += real_flip_cost;
			child.second.second = estimated_end_cost;

			// Generate the sequence of flips
			child.first.second.push_back(i);

			// Insert the new chil in the set
			myset.insert(child);
		}
	}

	flips = parent.first.second;

	return;
}




static size_t get_hash_value(const stack_type& vec){
	size_t key = 0;
	for(size_t i : vec)
		key = key*10 + i;

	return key;
}


static bool compare(const node& a, const node& b){
	int a_cost = a.second.first + a.second.second;
	int b_cost = b.second.first + b.second.second;
	if(a_cost == b_cost)
		return a < b;

	return  a_cost < b_cost;
}


static int get_size_largest_pancake(const stack_type& vec){
	int index;
	stack_type::const_iterator index_max;
	int largest_pancake = 0;

	for(stack_type::const_iterator i = vec.end(); i != vec.begin(); --i){

		index_max = std::max_element(vec.begin(), i);

		if(index_max+1 != i){
			index = std::distance(vec.begin(), index_max);
			largest_pancake = vec[index];
		}
	}
	return largest_pancake;
}