#include <bits/stdc++.h>
using namespace std;

void f(int x){
	cout<<"f integer"<<endl;
}

void g(int x){
	cout<<"g integer"<<endl;
}
void g(char c)=delete;
void g(bool b)=delete;

void h(int x){
	cout<<"h integer"<<endl;
}
template <typename T>
void h(T x)=delete;

int main(){
	int x=10;
	f(x);// it will give output
	f('a');// it will also give output
	f(true);// it will also give output

	int y=11;
	g(y);// it will give output
	g('a');// it will give compilation error
	g(true);// it will give compilation error

	int z=12;
	h(z);// it will give output
	h('a');// it will give compilation error
	h(true);// it will give compilation error
	return 0;
}