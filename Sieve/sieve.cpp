/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Kaiqi Chee
 * Date        : 9/17/2020
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
	PrimesSieve(int limit);

	~PrimesSieve() {
		delete[] is_prime_;
	}

	int num_primes() const {
		return num_primes_;
	}

    void display_primes() const;

private:
	// Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
	is_prime_{new bool[limit + 1]}, limit_{limit} {
		sieve();
		num_primes_=count_num_primes();
		max_prime_=0;
		for (int i=0; i<=limit_; i++){
			if (is_prime_[i]==true && i>max_prime_){
				max_prime_=i;
			}
		}

}

// Displays the primes in the specified format
void PrimesSieve::display_primes() const {

	const int max_prime_width = num_digits(max_prime_),
	primes_per_row = 80 / (max_prime_width + 1);

	int total_num_digits=0;

	for (int i=2; i<=limit_; i++){
			if (is_prime_[i]==true){
				total_num_digits=total_num_digits+1;
			}
		}


	if (total_num_digits<=primes_per_row){
		cout << endl;
		cout << "Number of primes found: " << count_num_primes() << endl;
		cout << "Primes up to " << limit_ << ":" << endl;
		int temp=0;
		for (int i=2; i<=limit_; i++){
			while (i!=temp){
				if (is_prime_[i]==true){
					cout << i;
					temp=i;
				}
			}
			break;
		}
		for (int i=temp+1; i<=limit_; i++){
			if (is_prime_[i]==true){
				cout << " "<< i;
			}
		}
		cout << endl;
	}

	else{
		int count=primes_per_row;
		cout << endl;
		cout << "Number of primes found: " << count_num_primes() << endl;
		cout << "Primes up to " << limit_ << ":" << endl;
		for (int i=2; i<=limit_;i++){
			if (is_prime_[i]==true){
				cout << setw(max_prime_width) << i;
				count--;
				if (count==0){
					cout << endl;
					count=primes_per_row;
				}
				else{
					if (i!=max_prime_){
						cout << " ";
					}
				}
			}
		}
	}
	cout << endl;
}


//Counts the number of primes found
int PrimesSieve::count_num_primes() const {
	int count=0;
	for (int i=2; i<=limit_; i++){
		if (is_prime_[i]==true) {
			count++;
		}
	}
	return count;
}

//Executes the sieve algorithm
void PrimesSieve::sieve() {
	for (int i=0; i<=limit_; i++){
		is_prime_[i]=true;
	}

	for (int i=2; i<=sqrt((double) limit_);i++){
		if (is_prime_[i]==true){
			for (int j=i*i; j<= limit_; j=j+i){
				is_prime_[j]=false;
			}
		}
	}
}

// Determines how many digits are in an integer by dividing by 10.
int PrimesSieve::num_digits(int num) {
	int count=0;
	while (num != 0) {
			num=floor(num/10);
			count++;
	}
	return count;
}

int main() {
	cout << "**************************** " << "Sieve of Eratosthenes" <<
			" ****************************" << endl;
	cout << "Search for primes up to: ";
	string limit_str;
	cin >> limit_str;
	int limit;

	// Use stringstream for conversion. Don't forget to #include <sstream>
	istringstream iss(limit_str);

	 // Check for error.
	if ( !(iss >> limit) ) {
		cerr << "Error: Input is not an integer." << endl;
		return 1;
	}

	  if (limit < 2) {
		  cerr << "Error: Input must be an integer >= 2." << endl;
		  return 1;
	  }

	  PrimesSieve mySieve(limit);
	  mySieve.display_primes();

	  return 0;
}
