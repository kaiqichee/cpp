/*******************************************************************************
 * Name    : waterjugpuzzle.cpp
 * Author  : Kaiqi Chee
 * Version : 1.0
 * Date    : October 19, 2020
 * Description : Returns the appropriate pours to reach goal state from initial state.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>

using namespace std;

//Struct to represent state of water in the jugs.
struct State {
	int a, b, c;
	string directions;
	State *parent;
	State(int _a, int _b, int _c, string _directions) :
		a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} { }


		// String representation of state in tuple form.
		string to_string() {
			ostringstream oss;
			oss << "(" << a << ", " << b << ", " << c << ")";
			return oss.str();
		}
};

//Displays waterjug results
void display(vector<State> s, State* initial){
	if (s.size()==0){
		cout<< "No solution."<< endl;
	}

	else{
		cout<< initial->directions<< " " << initial->to_string()<<endl;
		while (s.size()!=0){
			cout<< s.back().directions<< " " << s.back().to_string()<<endl;
			s.pop_back();
		}
	}
}

//Executes waterjug algorithm
vector<State> waterjug(int x, int y, int z, int a, int b, int c){
	vector<State> result;
	State* n = new State (0, 0, z, "Initial state.");
	State* goal = new State (a, b, c, "Goal state");

	if(n->a==goal->a && n->b==goal->b && n->c==goal->c){
		cout<< n->directions<< " " << n->to_string()<<endl;
		return result;
	}

	//make 2d array
	int size=x+1;
	int size2=y+1;
	State ***s = new State **[size];

	//For each row, make an array of 'size2' filled with nullptr.
	for (int i = 0; i < size; ++i) {
		s[i] = new State *[size2];
		fill(s[i], s[i] + size2, nullptr);
	}
	queue<State*> q;
	q.push(n);
	s[n->a][n->b]=n;

	while (q.size() != 0){
		State* current=q.front();
		string instructions;

		if (current->a==goal->a && current->b==goal->b && current->c==goal->c){
			vector<State> path;
			State* current2=current;

			while (current2->parent != nullptr){
				path.insert(path.end(), *current2);
				current2=current2->parent;
			}
			display(path,n);

			// Delete each array, that is, all the columns, first.
			for (int i = 0; i < size; ++i) {
				for (int j=0; j<size2; ++j){
					if (s[i][j]!=nullptr){
						delete s[i][j];
					}}
				delete[] s[i];
			}
			// Delete the array itself.
			delete[] s;
			return path;
		}

		else {
			if(current->a<x){
				if (current->c>=(x-current->a) && s[current->a+(x-current->a)][current->b]==nullptr){
					if(x-current->a==1){
						instructions="Pour " + to_string(x-current->a) + " gallon from C to A.";}
					else{
						instructions="Pour " + to_string(x-current->a) + " gallons from C to A.";}
					State* temp = new State (current->a+(x-current->a), current->b, current->c-(x-current->a), instructions);
					temp->parent=current;
					s[temp->a][temp->b]=temp;
					q.push(temp);
				}
				else if (current->c<(x-current->a) && s[current->a+current->c][current->b]==nullptr){
					if (current->c==1){
						instructions="Pour " + to_string(current->c) + " gallon from C to A.";}
					else{
						instructions="Pour " + to_string(current->c) + " gallons from C to A.";}
					State* temp = new State (current->a+current->c, current->b, current->c-current->c, instructions);
					temp->parent=current;
					s[temp->a][temp->b]=temp;
					q.push(temp);
				}
			}

			if(current->a<x){
				if (current->b>=(x-current->a) && s[current->a+(x-current->a)][current->b-(x-current->a)]==nullptr){
					if(x-current->a==1){
						instructions="Pour " + to_string(x-current->a) + " gallon from B to A.";}
					else{
						instructions="Pour " + to_string(x-current->a) + " gallons from B to A.";}
					State* temp = new State (current->a+(x-current->a), current->b-(x-current->a), current->c, instructions);
					temp->parent=current;
					s[temp->a][temp->b]=temp;
					q.push(temp);
				}
				else if (current->b<(x-current->a) && s[current->a+current->b][current->b-current->b]==nullptr){
					if(current->b==1){
						instructions="Pour " + to_string(current->b) + " gallon from B to A.";}
					else{
						instructions="Pour " + to_string(current->b) + " gallons from B to A.";}
					State* temp = new State (current->a+current->b, current->b-current->b, current->c, instructions);
					temp->parent=current;
					s[temp->a][temp->b]=temp;
					q.push(temp);
				}
			}

			if(current->b<y){
				if (current->c>=(y-current->b) && s[current->a][current->b+(y-current->b)]==nullptr){
					if(y-current->b==1){
						instructions="Pour " + to_string(y-current->b) + " gallon from C to B.";}
					else{
						instructions="Pour " + to_string(y-current->b) + " gallons from C to B.";}
					State* temp = new State (current->a, current->b+(y-current->b), current->c-(y-current->b), instructions);
					temp->parent=current;
					s[temp->a][temp->b]=temp;
					q.push(temp);
				}
				else if (current->c<(y-current->b) && s[current->a][current->b+current->c]==nullptr){
					if (current->c==1){
						instructions="Pour " + to_string(current->c) + " gallon from C to B.";}
					else{
						instructions="Pour " + to_string(current->c) + " gallons from C to B.";}
					State* temp = new State (current->a, current->b+current->c, current->c-current->b, instructions);
					temp->parent=current;
					s[temp->a][temp->b]=temp;
					q.push(temp);
				}
			}

			if(current->b<y){
				if(current->a>=(y-current->b) && s[current->a-(y-current->b)][current->b+(y-current->b)]==nullptr){
					if(current->a==1){
						instructions="Pour " + to_string(y-current->b) + " gallon from A to B.";}
					else{
						instructions="Pour " + to_string(y-current->b) + " gallons from A to B.";}
					State* temp = new State (current->a-(y-current->b), current->b+(y-current->b), current->c, instructions);
					temp->parent=current;
					s[temp->a][temp->b]=temp;
					q.push(temp);
				}
				else if(current->a<(y-current->b) && s[current->a-current->a][current->b+current->a]==nullptr){
					if(current->a==1){
						instructions="Pour " + to_string(current->a) + " gallon from A to B.";}
					else{
						instructions="Pour " + to_string(current->a) + " gallons from A to B.";}
					State* temp = new State (current->a-current->a, current->b+current->a, current->c, instructions);
					temp->parent=current;
					s[temp->a][temp->b]=temp;
					q.push(temp);
				}
			}

			if(current->c<z){
				if (current->b>=(z-current->c) && s[current->a][current->b-(z-current->c)]==nullptr){
					if(z-current->c==1){
						instructions="Pour " + to_string(z-current->c) + " gallon from B to C.";}
					else{
						instructions="Pour " + to_string(z-current->c) + " gallons from B to C.";}
					State* temp = new State (current->a, current->b-(z-current->c), current->c+(z-current->c), instructions);
					temp->parent=current;
					s[temp->a][temp->b]=temp;
					q.push(temp);
				}
				else if (current->b<(z-current->c) && s[current->a][current->b-current->b]==nullptr){
					if(current->b==1){
						instructions="Pour " + to_string(current->b) + " gallon from B to C.";}
					else{
						instructions="Pour " + to_string(current->b) + " gallons from B to C.";}
					State* temp = new State (current->a, current->b-current->b, current->c+current->b, instructions);
					temp->parent=current;
					s[temp->a][temp->b]=temp;
					q.push(temp);
				}
			}

			if(current->c<z){
				if(current->a>=(z-current->c) && s[current->a-(z-current->c)][current->b]==nullptr){
					if(z-current->c==1){
						instructions="Pour " + to_string(z-current->c) + " gallon from A to C.";}
					else{
						instructions="Pour " + to_string(z-current->c) + " gallons from A to C.";}
					State* temp = new State (current->a-(z-current->c), current->b, current->c+(z-current->c), instructions);
					temp->parent=current;
					s[temp->a][temp->b]=temp;
					q.push(temp);
				}
				else if(current->a<(z-current->c) && s[current->a-current->a][current->b]==nullptr){
					if(current->a==1){
						instructions="Pour " + to_string(current->a) + " gallon from A to C.";}
					else{
						instructions="Pour " + to_string(current->a) + " gallons from A to C.";}
					State* temp = new State (current->a-current->a, current->b, current->c+current->a, instructions);
					temp->parent=current;
					s[temp->a][temp->b]=temp;
					q.push(temp);
				}
			}
		}
		q.pop();
	}
	display(result, n);

	// Delete each array, that is, all the columns, first.
	for (int i = 0; i < size; ++i) {
		for (int j=0; j<size2; ++j){
			if (s[i][j]!=nullptr){
				delete s[i][j];
			}
		}
		delete[] s[i];
	}

	// Delete the array itself.
	delete[] s;

	return result;
}

//Checks if the arguments are all numbers
bool check(string arg[]){

	istringstream iss;

	for (int i=0; i<6; i++){
		int t;
		iss.str(arg[i]);
		int jug=i;

		if (!(iss >> t) || t<0 || (jug==2 && t==0)){
			if(jug<=2){
				cout<< "Error: Invalid capacity '"<< arg[jug]<< "' for jug ";
				if(jug==0){
					cout<< "A."<< endl;
				}
				if(jug==1){
					cout<< "B."<< endl;
				}
				if(jug==2){
					cout<< "C."<< endl;
				}
				return 0;
			}
			else if(jug>=3){
				cout<< "Error: Invalid goal '"<< arg[jug]<< "' for jug ";
				if(jug==3){
					cout<< "A."<< endl;
				}
				if(jug==4){
					cout<< "B."<< endl;
				}
				if(jug==5){
					cout<< "C."<< endl;
				}
				return 0;
			}
		}
		iss.clear();
	}
	return 1;
}

//Checks if the arguments are all valid
bool check2(int arg[]){
	if(arg[3]>arg[0]){
		cout<< "Error: Goal cannot exceed capacity of jug A."<< endl;
		return 0;
	}
	if(arg[4]>arg[1]){
		cout<< "Error: Goal cannot exceed capacity of jug B."<< endl;
		return 0;
	}

	if(arg[5]>arg[2]){
		cout<< "Error: Goal cannot exceed capacity of jug C."<< endl;
		return 0;

	}
	if(arg[3]+arg[4]+arg[5]!=arg[2]){
		cout<< "Error: Total gallons in goal state must be equal to the capacity of jug C."<< endl;
		return 0;
	}

	return 1;
}


int main(int argc, char * const argv[]) {
	if(argc!=7){
		cout<< "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>"<<endl;
		return 1;
	}

	string arg[6];
	for (int i=0; i<6; i++){
		arg[i]=argv[i+1];
	}

	if (check(arg)==true){
		int arg2[6];
		istringstream iss2;
		int t2;
		for (int i=0; i<6; i++){
			iss2.str(argv[i+1]);
			iss2>>t2;
			arg2[i]=t2;
			iss2.clear();
		}
		if(check2(arg2)==true){
			waterjug(arg2[0], arg2[1], arg2[2], arg2[3], arg2[4], arg2[5]);
			return 0;
		}
	}
	else{
		return 1;
	}
}



