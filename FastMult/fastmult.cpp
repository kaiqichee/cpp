/*******************************************************************************
 * Name        : fastmult.cpp
 * Author      : Kaiqi Chee
 * Version     : 1.0
 * Date        : 11/17/2020
 * Description : Executes the fast multiplication algorithm.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <string>
#include <cmath>

using namespace std;

string add(const string& a, const string& b) {
	istringstream x;
	istringstream y;
	x.str(a);
	y.str(b);
	long long i;
	long long j;
	x>>i;
	y>>j;
	long long z;
	z=i+j;
	string s=to_string(z);
	return s;
}
string subtract(const string& a, const string& b) {
	istringstream x;
	istringstream y;
	x.str(a);
	y.str(b);
	long long i;
	long long j;
	x>>i;
	y>>j;
	long long z;
	z=i-j;
	string s=to_string(z);
	return s;
}
string multiply(const string& a, const string& b) {
	istringstream x;
	istringstream y;
	x.str(a);
	y.str(b);
	long long i;
	long long j;
	x>>i;
	y>>j;
	long long z;
	z=i*j;
	string s=to_string(z);
	return s;
}

string padding(const string& a,  const string& b){
	istringstream x;
	x.str(a);
	string y;
	x>>y;
	long l=b.length()-a.length();
	for(int i=0; i<l; i++){
		y="0"+y;
	}
	return y;
}

string padding(const string& a,  int len){
	istringstream x;
	x.str(a);
	string y;
	x>>y;
	long l=len-a.length();
	for(int i=0; i<l; i++){
		y="0"+y;
	}
	return y;
}

//given a string returns a vector with the separated string i.e. 1234 -> <"12","34">
vector<string> seperate(const string& a){
	long len=a.length()/2;
	string temp;
	string temp2;
	vector<string> s;

	for(int i=0; i<len; i++){
		temp=temp+a[i];
		temp2=temp2+a[len+i];
	}
	s.insert(s.end(), temp);
	s.insert(s.end(), temp2);
	return s;
}

//Takes in the strings a, b, and c, multiples them by the appropriate base 10 value and adds them
string solve(const string& a, const string& b, const string& c, int len){
	vector<string> tens;
	vector<string> vars;
	string base;
	base="10";

	vars.insert(vars.begin(), a);
	vars.insert(vars.begin(), b);
	vars.insert(vars.begin(), c);

	for(int i=0; i<2;i++){
		string temps;
		temps="1";
		for(int i=0; i<len; i++){
			temps=multiply(temps,base);
		}
		tens.insert(tens.end(),temps);
		len=len/2;
	}
	base="1";
	tens.insert(tens.end(), base);

	string result;
	result="0";
	long size=vars.size();
	for(int i=0; i<size; i++){
		result=add(result,multiply(vars.at(i), tens.at(i)));
	}
	return result;
}

//Recursively computes the fast multiplication algorithm
string fastMult(const string& a, const string& b){
	if (a.length()==1 && b.length()==1){
		return multiply(a,b);
	}
	else{
		string a1=seperate(a).at(0);
		string a0=seperate(a).at(1);
		string b1=seperate(b).at(0);
		string b0=seperate(b).at(1);

		string c2;
		c2=fastMult(a1,b1);

		string c0;
		c0=fastMult(a0,b0);

		string c1;
		c1=subtract(multiply(add(a0,a1),add(b0,b1)),add(c0,c2));

		string c;
		c=solve(c0,c1,c2,a.length());
		return c;
	}
}

//Returns true if len is a power of 2, else returns false
bool power(size_t len){
	double n=log2(len);
	if(fmod(n,1)==0){
		return true;
	}
	else{
		return false;
	}
}

int main(int argc, char *argv[]) {
	if (argc!=3){
		cout<< "Usage: ./fastmult <int 1> <int 2>"<< endl;
		return 0;
	}

	else{
		istringstream x;
		x.str(argv[1]);
		string a;
		x>>a;
		istringstream y;
		y.str(argv[2]);
		string b;
		y>>b;

		if(a.length()==b.length() && power(a.length())==true){
			string f=fastMult(a, b);
			cout<< f<< endl;
			return 1;
		}
		else{
			//buffer them to equal lengths
			if(a.length()>b.length()){
				b=padding(b,a);
			}
			else if(a.length()<b.length()){
				a=padding(a,b);
			}

			//if once buffered they are not a power of 2, use the second padding function to buffer some more
			if(power(a.length())==true){
				string f=fastMult(a, b);
				cout<< f<< endl;
				return 1;
			}
			else{
				while(power(a.length())==false){
					long x=a.length();
					a=padding(a,x+1);
				}
				b=padding(b,a);
				string f=fastMult(a, b);
				cout<< f<< endl;
				return 1;
			}
		}
	}
	return 0;
}

