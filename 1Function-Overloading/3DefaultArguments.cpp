#include <bits/stdc++.h>
using namespace std;

void f(int x, int y=10){
	cout<<"y=10"<<endl;
}

// void g(int a=10, int b){
// 	cout<<"a=10"<<endl;
// }

void h(int a){
	cout<<"h(a)"<<endl;
}
void h(int a, int b=10){
	cout<<"h(a)"<<endl;
}

void fx(int a, int b, int c=10);
void fx(int a, int b=20, int c);
void fx(int a=30, int b, int c);
void fx(int a, int b, int c){
	cout<<"fx("<<a<<", "<<b<<", "<<c<<")"<<endl;
}

// void gx(int a, int b, int c=1){
// 	cout<<"gx(a, b, 1)"<<endl;
// }
// void gx(int a, int b, int c=4){
// 	cout<<"gx(a, b, 1)"<<endl;
// }

void hx(int a, int b, int c=3){
	cout<<"hx(a, b, "<<c<<")"<<endl;
	if(c==4){
		return;
	}
	void hx(int a, int b, int c=4);
	hx(a, b);
}

void kx(int a, int b, int c=10){
	cout<<"kx("<<a<<", "<<b<<", "<<c<<")"<<endl;
}
void kx(int a, int b=20, int c);
void kx(int a=30, int b, int c);

int main(){
	int x=1, y=2;
	f(x, y);// it executes and output is "y=10"
	//default argument of parameter y is 10
	f(x);// it also gets executed and gives output as "y=10"

	int a=11, b=10;
	//g(a, b);//this will raise error due to Right-to-Left rule explained
	
	int a1=10, b1=11;
	h(a1, b);//it'll execute and print h(a) due to exact match
	//h(a1);// it'll raise error due to Ambiguous function call

	int a2=10, b2=20, c2=30;
	fx(a2, b2, c2);//it'll execute and print fx(10, 20, 30)
	fx(a2, b2);//it'll execute and go to fx(int a, int b, int c=10) and it'll print "fx(a, b, 10)"
	fx(a2);//it'll execute and go to fx(int a, int b=20, int c) and it'll print "fx(a, 20, 10)"
	fx();//it'll execute and go to fx(int a=30, int b, int c) and it'll print "fx(30, 20, 10)"
	
	int a3=10, b3=20, c3=30;
	//gx(a3, b3, c3);//it'll raise error beacuse multiple overload having exact match
	//gx(a3, b3);//it'll raise error beacuse multiple overload having same priority level
	
	int a4=10, b4=20, c4=30;
	hx(a4, b4);

	kx(a2, b2, c2);//output kx(10, 20, 30)
	kx(a2, b2);//output kx(10, 20, 10)
	kx(a2);//output kx(10, 20, 10)
	kx();//output kx(30, 20, 10)
	return 0;
}