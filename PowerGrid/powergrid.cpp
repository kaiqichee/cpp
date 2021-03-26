/*******************************************************************************
 * Name        : powergrid.cpp
 * Author      : Kaiqi Chee
 * Version     : 1.0
 * Date        : 12/10/2020
 * Description : Finds the minimum path of the power grid using Kruskal's algorithm.
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

struct State {
	int from;
	int to;
	int weight;
	string name;
	State *parent;
	State(int _from, int _to, int _weight, string _name) :
		from{_from}, to{_to}, weight{_weight}, name{_name}, parent{nullptr} { }

		string to_string() {
			ostringstream oss;
			oss << name<< " [" <<weight<< "]";
			cout << name<< " [" <<weight<< "]";
			oss<< from<< ", "<<to<<", "<<weight<< ", "<< name;
			return oss.str();
		}
};

struct Ind {
	int value;
	Ind *parent;
	Ind(int _value) :
		value{_value}, parent{nullptr} { }

		string to_string() {
			ostringstream oss;
			oss << value;
			return oss.str();
		}
};

//deletes the States in vector x
void deleteS(vector<State*> x){
	int size=x.size();
	for (int i=0; i<size; i++){
		delete x.at(i);
	}
}

//returns true if y is found in x, false otherwise
bool found(vector<int> x, int y){
	int z=x.size();
	bool result=false;
	for (int i=0; i<z; i++){
		result=result || (x.at(i)==y);
	}
	return result;
}

//returns true if all nodes are represented in v, else false
bool all_edges(vector<int> v, int m){
	bool result=true;
	for(int i=1; i<m+1; i++){
		result=result && found(v, i);
	}
	return result;
}

//makeset function
vector<Ind*> ms(int x){
	vector<Ind*> individuals;
	for(int i=0; i<x; i++){
		Ind* n = new Ind(i);
		n->parent=n;
		individuals.push_back(n);
	}
	return individuals;
}

//returns the root of x
Ind* find(Ind* x){
	if(x->parent==x){
		return x;
	}
	else{
		return find(x->parent);
	}
}

//orders d by the weight
vector<State*> orderW(vector<State*> d){
	int size=d.size();
	for(int j=0; j<size; j++){
		int max=d.at(0)->weight;
		int index=0;
		for(int i=1; i<size-j; i++){
			if(d.at(i)->weight>max){
				max=d.at(i)->weight;
			}
			else{
				iter_swap(d.begin()+i, d.begin()+index);
			}
			index=i;
		}
	}
	return d;
}


//orders d by the name
vector<State*> orderN(vector<State*> d){
	int size=d.size();
	for(int j=0; j<size; j++){
		string max=d.at(0)->name;
		int index=0;
		for(int i=1; i<size-j; i++){
			if(d.at(i)->name>max){
				max=d.at(i)->name;
			}
			else{
				iter_swap(d.begin()+i, d.begin()+index);
			}
			index=i;
		}
	}
	return d;
}

//executes Kruskal's algorithm to find the minimum spanning roads
void minSet(vector<State*> x, int max){
	vector<State*> msr;
	vector<Ind*> nodes;
	nodes=ms(max);

	int size=x.size();
	for(int i=0; i<size; i++){
		if(find(nodes.at((x.at(i)->from)-1))!=find(nodes.at((x.at(i)->to)-1))){
			find(nodes.at((x.at(i)->to)-1))->parent=find(nodes.at((x.at(i)->from)-1));
			msr.push_back(x.at(i));
		}
	}
	int wire=0;
	size=msr.size();
	for(int i=0; i<size; i++){
		wire=wire+msr.at(i)->weight;
	}

	cout<< "Total wire length (meters): " << wire<< endl;

	msr=orderN(msr);

	//print out name and weight
	vector<string> t;
	for(int i=0; i<size; i++){
		istringstream yss;
		yss.str(msr.at(i)->name);
		string a;
		string b;
		yss>>a;
		yss>>b;
		string c;
		c=a+" "+b;
		t.insert(t.end(), c);
	}

	for(int i=0; i<size; i++){
		cout<< t.at(i)<< " ["<< msr.at(i)->weight<< "]"<< endl;
	}

	size=nodes.size();
	for (int i=0; i<size; i++){
		delete nodes.at(i);
	}

}

int main(int argc, char *argv[]){
	if (argc != 2){
		cout<< "Usage: ./powergrid <input file>" << endl;
		return 0;
	}
	else{
		ifstream input_file(argv[1]);
		if (!input_file) {
			cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
			return 1;
		}
		input_file.exceptions(ifstream::badbit);
		string line;
		vector<State*> distance;
		int max;

		try {
			unsigned int line_number = 1;
			vector<int> vertices;
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
					if(max>1000 || max<1){
						cout<< "Error: Invalid number of vertices '"<< max<<"' on line 1."<< endl;
						deleteS(distance);
						return 0;
					}
					if (max==1){
						cout<< "No solution."<<endl;
						deleteS(distance);
						return 0;
					}
				}

				else{
					vector<string> l;
					istringstream iss(line);
					string temp;
					while(getline(iss, temp, ',')){
						l.insert(l.end(), temp);
					}
					iss.clear();

					if(l.size()!=4){
						istringstream lss;
						lss.str(line);
						string a;
						string b;
						lss>>a;
						lss>>b;
						if(b.empty()==false){
							a=a+" "+b;
						}
						cout<<"Error: Invalid edge data '"<< a <<"' on line "<< line_number<< "."<<endl;
						deleteS(distance);
						return 0;
					}

					//uses string stream to set the values of the state
					int from;
					int to;
					int w;
					string name;
					istringstream q;
					q.str(l.at(0));
					q>>from;
					if(!from){
						cout<<"Error: Starting vertex '"<< l.at(0)<<"' on line "<< line_number<< " is not among valid values 1-"<< max<< "."<<endl;
						deleteS(distance);
						return 0;
					}
					q.clear();
					q.str(l.at(1));
					q>>to;
					if(!to){
						cout<<"Error: Ending vertex '"<< l.at(1)<<"' on line "<< line_number<< " is not among valid values 1-"<< max<< "."<<endl;
						deleteS(distance);
						return 0;
					}
					q.clear();
					q.str(l.at(2));
					q>>w;
					if(!w){
						cout<<"Error: Weight '"<< l.at(2)<<"' on line "<< line_number<< " is not among valid values 1-"<< max<< "."<<endl;
						deleteS(distance);
						return 0;
					}
					name=l.at(3);

					//build list of visited vertices
					if(found(vertices, from)==false){
						vertices.insert(vertices.end(), from);
					}
					if(found(vertices, to)==false){
						vertices.insert(vertices.end(), to);
					}

					//w is not a positive integer
					if(w<=0){
						cout<<"Error: Invalid edge weight '"<< w<<"' on line "<< line_number<< "."<<endl;
						deleteS(distance);
						return 0;
					}

					//from not in range
					else if(from<1 || from>max){
						cout<<"Error: Starting vertex '"<< from<<"' on line "<< line_number<< " is not among valid values 1-"<< max<< "."<<endl;
						deleteS(distance);
						return 0;
					}

					//to not in range
					else if(to<1 || to>max){
						cout<<"Error: Ending vertex '"<< to<<"' on line "<< line_number<< " is not among valid values 1-"<< max<< "."<<endl;
						deleteS(distance);
						return 0;
					}

					else{
						State* n = new State (from, to, w, name);
						distance.push_back(n);
					}
				}
				++line_number;
			}

			//checks that all nodes are reachable
			if(all_edges(vertices, max)==false){
				cout<< "No solution."<<endl;
				deleteS(distance);
				return 0;
			}

			else{
				distance=orderW(distance);
				minSet(distance, max);
			}

			deleteS(distance);
			input_file.close();
		}
		catch (const ifstream::failure &f) {
			cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
			return 1;
		}
		return 0;
	}
}
