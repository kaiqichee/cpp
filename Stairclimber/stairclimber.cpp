/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Kaiqi Chee
 * Date        : October 1, 2020
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;


//Return a vector of vectors of ints representing the different combinations of ways to climb num_stairs
//stairs, moving up either 1, 2, or 3 stairs at a time.
vector< vector<int> > get_ways(int num_stairs) {

	vector<vector<int>> ways;
	vector<vector<int>> result(1);
	if (num_stairs <= 0){
		return result;
	}

	else{
		for (int i=1; i<4; i++){
			if (num_stairs >= i){
				result = get_ways(num_stairs - i);
				int l=result.size();
				for (int j=0; j<l; j++){
					result[j].insert(result[j].begin(), 1, i);
				}
				ways.insert(ways.end(),result.begin(),result.end());
			}
		}
	}
	return ways;
}

//Display the ways to climb stairs by iterating over the vector of vectors and printing each combination.
void display_ways(const vector< vector<int> > &ways) {
	int size=ways.size();
	int length=to_string(size).size();
	for (int i=0; i<size; i++){
		int size2=ways.at(i).size();
		cout<< setw(length)<< i+1<< ". ["<< ways[i].at(0);
		for (int j=1; j<size2; j++){
			cout <<", " << ways[i].at(j);
		}
		cout<< "]" <<endl;
	}
}

int main(int argc, char * const argv[]) {
	if (argc<2){
		cout<< "Usage: ./stairclimber <number of stairs>"<< endl;
		return 0;
	}

	if (argc>2){
		cout<< "Usage: ./stairclimber <number of stairs>"<< endl;
		return 0;
	}

	if (argv[1]<=0){
		cout<< "Error: Number of stairs must be a positive integer."<< endl;
		return 0;
	}


	istringstream iss;
	iss.str(argv[1]);
	int t;

	if (!(iss >> t)){
		cout<< "Error: Number of stairs must be a positive integer."<< endl;
		return 0;
	}

	iss >> t;
	if (t<=0){
		cout<< "Error: Number of stairs must be a positive integer."<< endl;
		return 0;
	}

	else{
		int s=get_ways(t).size();

		if (t==1){
		cout<< s<< " way to climb "<< t<< " stair."<< endl;
		}

		else{
		cout<< s<< " ways to climb "<< t<< " stairs."<< endl;
		}

		display_ways(get_ways(t));
		return 1;
	}

}

