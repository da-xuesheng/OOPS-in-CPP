#include <bits/stdc++.h>
using namespace std;

//functions with same logic and different names
int addInt(int a, int b){
	return a+b;
}

double addDouble(double a, double b){
	return a+b;
}

//function with same logic and same name but differenbt parameter
int add(int a, int b){
	return a+b;
}

double add(double a, double b){
	return a+b;
}

int main(){
	int a, b;
	double a1, b1;
	cin>>a>>b>>a1>>b1;

	cout<<addInt(a, b)<<endl;
	cout<<addDouble(a1, b1)<<endl;

	cout<<add(a, b)<<endl;
	cout<<add(a1, b1)<<endl;

	//output:
	//a=1, b=1, a1=1.11, b1=2.22
	// addInt(a, b)=2;
	// addDouble(a1, b1)=3.33

	// add(a, b)=2;
	// add(a1, b1)=3.33
	return 0;
}