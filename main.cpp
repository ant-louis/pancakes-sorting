#include <iostream> // cin, cout
#include <stdexcept> // to throw "domain_error" --> throw domain_error("...")
#include "pancakes.hpp"
#include <ctime>


using std::cout;
using std::endl;

int main(){

	int start_s;
	int stop_s;

	//int myints[] = {9,6,2,5};
	int myints[] = {1,9,6,2,5,3,8};
	//int myints[] = {1,9,6,2,5,3,8,4,7,0};
	//int myints[] = {5,7,3,9,2,1,8,0,6,4};
  	const stack_type vec (myints, myints + sizeof(myints) / sizeof(int) );

	flip_type flips;

	try{
		start_s=clock();
		astar_pancake_sort(vec, flips);
		stop_s=clock();
	}catch(std::domain_error e){
		std::cout << e.what();
	}
	
	cout << "time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC) << endl;

	return 0;
}