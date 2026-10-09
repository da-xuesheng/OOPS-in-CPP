#include <bits/stdc++.h>
using namespace std;

class Student{
	int age;
	int roll;
	string name;
public:
	Student(int r, int a, string n):age(a), roll(r), name(n){
	}

	//getter of this class
	int getRoll(){
		return roll;
	}

	int getAge(){
		return age;
	}

	string getName(){
		return name;
	}

	void change_age(int new_age){
		age=new_age;
	}
};

int main(){
	Student s(54, 19, "AdStacy");
	cout<<s.getRoll()<<endl;
	cout<<s.getAge()<<endl;
	s.change_age(20);
	cout<<s.getAge()<<endl;
	cout<<s.getName()<<endl;
	return 0;
}