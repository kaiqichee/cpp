/*******************************************************************************
 * Name    : student.cpp
 * Author  : Kaiqi Chee
 * Version : 1.0
 * Date    : September 9, 2020
 * Description : Creates a student class and various methods.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

class Student {
	public:
		//Constructor that uses initializer list.
    	Student(string first, string last, float gpa, int id) : first_{first}, last_{last}, gpa_{gpa}, id_{id} { }

	string full_name() const {
		return first_ + " " + last_;
		}

	int id() const {
		return id_;
		}

	float gpa() const {
		return gpa_;
		}

	void print_info() const {
		// print_info() should print in the format (GPA has 2 decimal places):
		// Bob Smith, GPA: 3.50, ID: 20146
		cout << full_name() << ", GPA: " << fixed << setprecision (2) << gpa()
			 << ", ID: " << id()<< endl;
		};

	private:
		// Member variables (fields). Use the trailing _ for these variables.
		string first_;
		string last_;
		float gpa_;
		int id_;
	};

	/**
	 * Takes a vector of Student objects, and returns a new vector
	 * with all Students whose GPA is < 1.0.
	 */
	vector<Student> find_failing_students(const vector<Student> &students) {
		vector<Student> failing_students;
		int j=students.size(); //does it need to be &students?
		for (int i=0; i<j; i++){
			float TempGpa=students.at(i).gpa();
			if (TempGpa<1.0){
				failing_students.insert(failing_students.end(), students.at(i));

			}
		}

		return failing_students;
	}


	/**
	* Takes a vector of Student objects and prints them to the screen.
	*/
	void print_students(const vector<Student> &students) {
	    // Iterates through the students vector, calling print_info() for each student.
		int j=students.size();
			for (int i=0; i<j; i++){
				students.at(i).print_info();
			}
	}

	/**
	* Allows the user to enter information for multiple students, then
	* find those students whose GPA is below 1.0 and prints them to the
	* screen.
	*/
	int main() {
	    string first_name, last_name;
	    float gpa;
	    int id;
	    char repeat;
	    vector<Student> students;
	    do {
	        cout << "Enter student's first name: ";
	        cin >> first_name;
	        cout << "Enter student's last name: ";
	        cin >> last_name;
	        gpa = -1;
	        while (gpa < 0 || gpa > 4) {
	            cout << "Enter student's GPA (0.0-4.0): ";
	            cin >> gpa;
	        }
	        cout << "Enter student's ID: ";
	        cin >> id;
	        students.push_back(Student(first_name, last_name, gpa, id));
	        cout << "Add another student to database (Y/N)? ";
	        cin >> repeat;
	    } while (repeat == 'Y' || repeat == 'y');
	    cout << endl << "All students:" << endl;
	    print_students(students);

	    // Print a space and the word 'None' on the same line if no students are
	    // failing.
	    // Otherwise, print each failing student on a separate line.
	    vector<Student> temp = find_failing_students(students);
	    if (temp.size()==0){
		    cout << endl << "Failing students:";
	    	cout<< " None"<< endl;
	    }
	    else{
		    cout<< endl<< "Failing students:"<< endl;
	    	print_students(temp);

	    			}

	    return 0;
	}


