#include <bits/stdc++.h>
using namespace std;

class Student{
    int roll;
public:
    Student(){
        roll=01;
    }
};

class S{
    int roll;
    string name;
    int mark_in_math;
public:
    S(int r, string n, int mim){
        roll=r;
        name=n;
        mark_in_math=mim;
    }
};

class S1{
    int roll;
    string name;
    int mark_in_maths;
public:
    S1(int r, string n, int mim):roll(r), name(n), mark_in_maths(mim){
    }
};

class S2{
    const int imp_val_for_s2;
public:
    S2(int val):imp_val_for_s2(val){
    }
};

class S3{
    int value;
    int imp_val;
public:
    S3(){
        cout<<"constructor"<<endl;
    }
    // this is default constructor due to having no arguments
};

class S4{
    int x;
    int y;
public:
    S4(int m=0, int n=0):x(m), y(n){
    }
};

class S5{
};

class S6{
    int value;
    int data;
public:
    S6()=default;
    S6(int m=0, int n=0):value(m), data(n){
    }
};

int main(){
    Student s; //constructor is invokek, it doesn't initializes the object rather the subobjects of the objects

    S s1(54, "Adstacy", 89);//here the subobject values are assigned as the 54, Adstacy, 89
    S1 s1_dash(54, "Adstacy", 89);//here the subobject values are initialized as 54, Adstacy, 89
    S2 s2(65); //if not used the member iniiializer list, then the subobject will be initialized with a garbage value and due to being const it'll not change ever, mauy give error eventually
    S3 s3; //its subobjects are initialized with garbage value
    S3 s3_dash{}; //its subobjects are initialized with 0
    //but both s3 and s3_dash will call the default constructor
    
    S4 s4;
    //as constructor with default arguments are also default constructor, thus two functions being in the same preferrence level will cause compilation error

    S5 s5; //here although there no user defines constructor, there is implicit default constructor

    //S6 s6;
    //this will call the default constructor, but will give error
    S6 s6_dash(10, 20); // this will call the constructor with the arguments
    S6 s6(); //this will compile but give warning, because it's not any object, it's a function declaration
    return 0;
}
