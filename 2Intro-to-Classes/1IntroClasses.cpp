#include <bits/stdc++.h>
using namespace std;

class Student{
	int roll;
	string name;
	int birth_year;
	bool ifValid(int birth_year, int roll){
		if(birth_year>2007&&(roll>=1&&roll<=96)){
			cout<<"student creation is invalid"<<endl;
			return 1;
		}
		return 0;
	}
public:
	Student(int r, string n, int by){
		if(!ifValid(by, r)){
			cout<<"student creation is invalid"<<endl;
			exit(EXIT_FAILURE);
		}else{
			roll=r;
			name=n;
			birth_year=by;
		}
	}
	void checkSection(){
		if(roll>=1 && roll<=30){
			cout<<"section: A1"<<endl;
		}else if(roll>=31 && roll <=61){
			cout<<"section: A2"<<endl;
		}else{
			cout<<"section: A3"<<endl;
	    }
	}
	void displayInfo(){
		cout<<"student name: "<<name<<endl;
		cout<<"student roll: "<<roll<<endl;
		cout<<"student birth year: "<<birth_year<<endl;
	}
};

int main(){
	Student s(54, "Odessey", 1997);
	s.displayInfo();
	//this will output the information of object s
	Student s1(91, "Ilius", 2009);
	//this will output invalid object creation 
	Student s2(1054, "Odessey junior", 2006);
	//this will also output invalid object creation
	return 0;
}