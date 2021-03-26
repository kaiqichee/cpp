/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Kaiqi Chee
 * Version     : 1.0
 * Date        : 10/30/2020
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
	long counter=0;
	for(int i=0; i<length; i++){
		for (int j=i+1; j<length; j++){
			if(array[i]>array[j]){
				counter++;
			}
		}
	}
	return counter;
}


/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
	vector<int> s;
	s.reserve(length);
	return mergesort(array, &s[0], 0, length-1);
}

//Recursive mergesort function
static long mergesort(int array[], int scratch[], int low, int high) {
	long counter=0;
	if (low < high){
		int mid=low+(high-low)/2;
		counter=counter+mergesort(array, scratch, low, mid);
		counter=counter+mergesort(array, scratch, mid+1, high);
		int L=low;
		int H=mid+1;
		for (int k=low; k<=high; k++){
			if((L<=mid) && (H>high || array[L]<= array[H])){
				scratch[k]=array[L];
				L++;
			}
			else{
				counter=counter+mid-L+1;
				scratch[k]=array[H];
				H++;
			}
		}
		for (int j=low; j<=high; j++){
			array[j]=scratch[j];
		}
	}

	return counter;
}

int main(int argc, char *argv[]) {
	bool slow=false;
	if(argc>2){
		cout<< "Usage: ./inversioncounter [slow]"<<endl;
		return 1;
	}

	if (argc==2){
		istringstream x;
		string temp;
		x.str(argv[1]);
		x >> temp;
		if(temp!="slow"){
			cout<< "Error: Unrecognized option '"<< temp << "'."<<endl;
			return 1;
		}
		else{
			slow=true;
		}
		x.clear();
	}

	cout << "Enter sequence of integers, each followed by a space: " << flush;
	istringstream iss;
	int value, index = 0;
	vector<int> values;
	string str;
	str.reserve(11);
	char c;
	while (true) {
		c = getchar();
		const bool eoln = c == '\r' || c == '\n';
		if (isspace(c) || eoln) {
			if (str.length() > 0) {
				iss.str(str);
				if (iss >> value) {
					values.push_back(value);
				} else {
					cerr << "Error: Non-integer value '" << str
					     << "' received at index " << index << "." << endl;
					return 1;
				}
				iss.clear();
				++index;
			}
			if (eoln) {
				break;
			}
			str.clear();
		} else {
			str += c;
		}
	}
	int num_values = values.size();
	if (num_values == 0) {
		cerr << "Error: Sequence of integers not received." << endl;
		return 1;
	}

	if(slow){
		long t=count_inversions_slow(&values[0], num_values);
		cout<<"Number of inversions: "<< t<<endl;
		return 0;
	}
	else{
		long t=count_inversions_fast(&values[0], num_values);
		cout<<"Number of inversions: "<< t<<endl;
		return 0;
	}
	return 0;
}








