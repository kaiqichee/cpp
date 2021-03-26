/*******************************************************************************
 * Name        : shortestpaths.cpp
 * Author      : Kaiqi Chee
 * Version     : 1.0
 * Date        : 11/25/2020
 * Description : Executes the shortest paths algorithm.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <string>
#include <map>
#include <limits>
#include <cmath>


using namespace std;
long infinity=1e15;

//returns the number of digits in num
long num_digits(long num) {
	if(num==0){
		return 1;
	}
	long count=0;
	while (num != 0) {
			num=floor(num/10);
			count++;
	}
	return count;
}

//delete an array a of size size
void deleteA(long** a, int size){
	// Delete each array
	for (int i = 0; i < size; ++i) {
		delete[] a[i];
	}
	// Delete the array itself.
	delete[] a;
}

//Displays the matrix on the screen formatted as a table
void displayP(long** const matrix, int s) {
	//find max value
	long max_val = 0;
	for (int i = 0; i < s; i++) {
		for (int j = 0; j < s; j++) {
			long cell = matrix[i][j];
			if (cell < infinity && cell > max_val) {
				max_val = matrix[i][j];
			}
		}
	}

	//get with of max value
	long max_cell_width = num_digits(max_val);

	//print first line of letter labels
	cout << ' ';
	for (int j = 0; j < s; j++) {
		cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
	}
	cout << endl;

	//print rest of table
	for (int i = 0; i < s; i++) {
		cout << static_cast<char>(i + 'A');
		for (int j = 0; j < s; j++) {
			cout << " " << setw(max_cell_width);
			if (matrix[i][j] == infinity) {
				cout << "-";
			}

			else {
				cout << matrix[i][j];
			}
		}
		cout << endl;
	}
	cout << endl;
}

//Displays the table of intermediaries
void displayI(long** const matrix, int s) {

	//print first line of letter labels
	cout << ' ';
	for (int j = 0; j < s; j++) {
		cout << setw(2) << static_cast<char>(j + 'A');
	}
	cout << endl;

	//print rest of table
	for (int i = 0; i < s; i++) {
		cout << static_cast<char>(i + 'A');
		for (int j = 0; j < s; j++) {
			cout << " ";
			if (matrix[i][j] == infinity) {
				cout << "-";
			}

			else {
				cout << static_cast<char>(matrix[i][j] + 'A');
			}
		}
		cout << endl;
	}
	cout << endl;
}

//recursive backtrack function, prints along the way
void backtrackH( long** y, long a, long b){
	if(y[a][b]==infinity ){
		cout<< char('A'+a)<< " -> ";
		return;
	}
	else{
		backtrackH(y, a, y[a][b]);
		backtrackH(y, y[a][b], b);
	}
}

//displays the list of paths
void displayL(long** x, long** y, int s){
	for(int i=0; i<s; i++){
		for(int j=0; j<s;j++){
			cout<< char('A'+i)<< " -> "<< char('A'+j) <<", distance: ";
			if (x[i][j]==infinity){
				cout<< "infinity"<< ", path: none"<< endl;;
			}
			else{
				cout << x[i][j] << ", path: ";
				if(y[i][j]==infinity){
					if(i==j){
						cout<< char('A'+i)<< endl;
					}
					else{
						cout<< char('A'+i)<< " -> "<< char('A'+j)<< endl;
					}
				}
				else{
					backtrackH(y, i, y[i][j]);
					backtrackH(y, y[i][j], j);
					cout<< char('A'+j);
					cout<< endl;
				}
			}
		}
	}
}

//executes the shortest path algorithm
long** shortestpath(long** x, int s){
	long** backtrack;
	backtrack=new long*[s];
	for(int i=0; i<s;i++){
		backtrack[i]=new long[s];
		for(int j=0; j<s; j++){
			backtrack[i][j]=infinity;
		}
	}

	for (int k=0; k<s; k++){
		for (int i=0; i<s; i++){
			for (int j=0; j<s; j++){
				if(i!=k && j!=k && i!=j && x[i][j]>x[i][k]+x[k][j]){
					x[i][j]=x[i][k]+x[k][j];
					backtrack[i][j]=k;
				}
			}
		}
	}

	//display results
	cout<<"Path lengths:"<<endl;
	displayP(x, s);
	cout<<"Intermediate vertices:"<<endl;
	displayI(backtrack, s);
	displayL(x, backtrack, s);

	deleteA(backtrack, s);
	return x;
}

int main(int argc, char *argv[]){
	if (argc != 2){
		cout<< "Usage: ./shortestpaths <filename>" << endl;
		return 0;
	}
	else{
		// Create an ifstream object.
		ifstream input_file(argv[1]);
		// If it does not exist, print an error message.
		if (!input_file) {
			cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
			return 1;
		}
		// Add read errors to the list of exceptions the ifstream will handle.
		input_file.exceptions(ifstream::badbit);
		string line;
		long **distance;
		int max;

		try {
			unsigned int line_number = 1;
			// Use getline to read in a line.
			while (getline(input_file, line)) {
				if(line_number==1){
					istringstream iss;
					iss.str(line);
					string m;
					iss>>m;
					int k=m.size();
					for (int i=0; i<k; i++){
						if(isdigit(m.at(i))==false){
							cout<< "Error: Invalid number of vertices '"<< m<<"' on line 1."<< endl;
							return 0;
						}
					}
					iss.clear();
					iss.str(m);
					iss>>max;
					if(max>26 || max<1){
						cout<< "Error: Invalid number of vertices '"<< max<<"' on line 1."<< endl;
						return 0;
					}
					distance=new long*[max];
					for(int i=0; i<max;i++){
						distance[i]=new long[max];
						for(int j=0; j<max; j++){
							if (i==j){
								distance[i][j]=0;
							}
							else{
								distance[i][j]=infinity;
							}
						}
					}
				}
				else{
					istringstream iss;
					iss.str(line);
					string from;
					string to;
					string w;
					iss>>from;
					iss>>to;
					iss>>w;

					//only 2 inputs
					if(w.empty()){
						cout<<"Error: Invalid edge data '"<< from << " "
							<< to <<"' on line "<< line_number<< "."<<endl;
						deleteA(distance, max);
						return 0;
					}
					//bad weight input
					int temp=w.size();
					for (int i=0; i<temp; i++){
						if(isdigit(w.at(i))==false){
							cout<<"Error: Invalid edge weight '"<< w<<"' on line "<< line_number<< "."<<endl;
							deleteA(distance, max);
							return 0;
						}
					}
					long weight;
					istringstream z;
					z.str(w);
					z>>weight;
					if(weight<=0){
						cout<<"Error: Invalid edge weight '"<< weight<<"' on line "<< line_number<< "."<<endl;
						deleteA(distance, max);
						return 0;
					}

					//not in range max
					else if(from[0]-'A'>max || from[0]-'A'<0){
						cout<<"Error: Starting vertex '"<< from<<"' on line "<< line_number<< " is not among valid values A-"<< char('A'+max-1)<< "."<<endl;
						deleteA(distance, max);
						return 0;
					}

					else if(to[0]-'A'>max || to[0]-'A'<0){
						cout<<"Error: Ending vertex '"<< to<<"' on line "<< line_number<< " is not among valid values A-"<< char('A'+max-1)<< "."<<endl;
						deleteA(distance, max);
						return 0;
					}

					else{
						distance[from[0]-'A'][to[0]-'A']=weight;
					}
				}
				++line_number;
			}

			cout<< "Distance matrix:" <<endl;
			displayP(distance, max);
			shortestpath(distance, max);


			deleteA(distance, max);

			// Don't forget to close the file.
			input_file.close();
		}
		catch (const ifstream::failure &f) {
			cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
			return 1;
		}
		return 0;
	}
}
















