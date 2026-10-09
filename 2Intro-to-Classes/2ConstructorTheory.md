### Constructors

A Constructor is a non-static member function of a class in C++ that is automatically invoked whenever a new object of that class is created.
The contrsuctor actually doesn't create the object, it doesn't allocate storage for it. It initializes the object's subobjects when the object is initialized.
```cpp
class Stu{
	int roll;
public:
	Stu(){
		roll=01;
	}
};

int main(){
	Stu s;
}
```
First storage for s is allocated, then Stu::Stu() is automatically invoked and roll is initialized as 01.

Constructor has no return type, it's name is same as the class.
**Direct Initialization:** In this case the objects are initialized using an explicit set of arguments. 
```cpp
class Stu{
	int roll;
	string name;
	int mark_in_maths;
public:
	Stu(int r, string n, int mim){
		roll=r;
		name=n;
		mark_in_maths=mim;
	}
};
int main(){
	Stu s(54, "AdStacy", 87);
}
```
This is how we can do direct initialization.
To be precise, when Stu s(54, "AdStacy", 87) is executed in the main(), memory allocated for object s initialized using Direct Initialization, the compiler look for a contructor matching the signatures (int, string, int), if found it calls the constructor without creating temporary objects, neither it performs copy operations, rather uses = operator at the object level.
So, the arguments of the constructor r, n, mim are assigned as 54, "AdStacy", 87.
But inside the constructor body, before the code inside the curly braces runs C++ allocates memory for s and initializes its member variables, like the roll, name, mark_in_maths is initialized as garbage values, then roll is assigned the value of r, name is assigned as n, mark_in_maths is assigned as mim.
To make member variables use direct initialization:
```cpp
Stu(int r, string n, int mim):roll(r), name(n), mark_in_maths(mim){
}
```
Here the member variables are initialized as r, n, mim directly instead of getting assigned, this is called **Member Initializer List**.
In this case, Stu s is executed and as soon as the object is created in the memory, the object istances roll is initialized as r, same for other instances.

This has importance for those member variables which are const.
```cpp
class Stu{
	const int mark_in_maths;
public:
	Stu(int mim):mark_in_maths(mim){
	}
};
```
As soon as the object is created the mark_in_maths needs to initialized as mim, otherwise it will be initialized as a garbage value and as this is a const variable, it will not change no matter what is done.

Member variables are initialized in the order they are declared. 
```cpp
class Stu{
	int mark_in_maths;
	int roll;
public:
	Stu(int r, int mim):roll(r), mark_in_maths(mim){
	}
};
```
Here although roll(r) is written first but still it will be initialized in the second place, first mark_in_maths will be initialized, declaration order will be followed.
###### Default Constructor
It is type of constructor that accepts no arguments, it's usually defined with no parameters.
```cpp
class S{
	S(){
		cout<<"constructed"<<endl;
	}
};

int main(){
	S s;
}
```
Here we are calling the default constructor.
###### Value initialization and Default initialization
```cpp
int main(){
	int x;

	int y{};
}
```
Here the value x is by default initialized with some garbage value, if we print x the value may or may not be 0, it's value is undetermined, it is called default initialization.
But the value of y is initialized by 0, if we print y, it initialized by value.

###### Constructors with default arguments
```cpp
class S{
	S(){
		cout<<"constructed"<<endl;
	}
};

int main(){
	S s;
	S s1{};
}
```
In the case of class, both objects(regardless of being initialized by value or default) will call the default constructor.
But one should always prefer value initialization as, in this case the initialized values are known.
Constructors also can have default arguments.
```cpp
class S{
	int x;
	int y;
	S(int m=0, int n=0){
		x=m;
		y=n;
	}
};

class S1{
	int x1;
	int y1;
	S1(int m=0, int n=0):x(m), y(n){
	}
};

int main(){
	S s;
	S s_dash(1, 2);

	S1 s1;
	S1 s1_dash(1, 2);
}
```
In the first and second class S and S1, the constructors have default arguments, thus both objects(regardless of having arguments or not) will work.

#### Cosntructor Overloading
As we know constructor is also a kind of fucntion thus it can be also overloaded. In this case also the preferrence order of the fucntion overloading is applicable. Hence, we know that only 1 default contructor can be there in a class.
```cpp
class S{
	int x;
	int y;
public:
	S(){
	}
	S(int m, int n):x(m), y(n){
	}
};

class S1{
	int x;
	int y;
public:
	S1(){
	}
	S1(int m=0, int n=0):x(m), y(n){
	}
};

int main(){
	S s;
	S s_dash(1, 2);

	S1 s1;
	S1 s1_dash(1, 2);
}
```
In the first class there will be no issue as there is only 1 default constructor.
But in the second class there is 2 default constructor.
As **Constructor with default arguemnts are also default constructors** thus, there are two fucntions with the same name and arguments at the same hiararchy level, leading to compilation error, ambiguous constructor function call.
###### Implicit Default Constructor
If there is no user-declared constructor, then the compiler automatically generates a default contructor, which is called implicit default constructor.
```cpp
class S{
};
```
In this class there exists no constructor.
This is same as writing,
```cpp
class S{
	S(){
	}
};
```
An deafult constructor is auto written by the compiler.

###### Use of deafult keyword
When there exists a user-declared constructor, then implicit deafult constructor is not generated. But if the **default** is keyword in written then compiler generates an deafult constrcutor.
```cpp
class S{
	int x;
	int y;
public:
	S()=default;
	S(int m, int n):x(m), y(n){
	}
};
```
The above written code is the syntax of including the default keyword.

#### Calling of a constructor from the body of a function
Constructors can call functions but when constructors are called from a function body, an temporary object is created. So, if a  fucntion is calling a constructor then it may seem that the changes are happenning in the actual object, but actually changes happen in the temporary object.
```cpp
class Student{
	int age{};
	int roll{};
	string name{"NULL"};
	bool is_monitor{};
public:
	Student(int r, int a, string n):age(a), roll(r), name(n){
		cout<<name<<endl;
	}
	Student(int r, int a, string n, bool im):is_monitor(im){
		Student(r, a, n);
	}
	void getInfo(){
		cout<<name<<endl;
		cout<<age<<endl;
		cout<<roll<endl;
	}
}; 

int main(){
	Student s(54, 19, "AdStacy", 1);
}
```
As seen, Student(int, int, string) is getting called by Student(int, int, string, bool), so it may seem that object s is calling the constructor Student(int, int, string, bool) and as Student(int, int, string) is getting called by Student(int, int, string, bool), so info of s should've changed. 
But this will not work as expected, because of very simple reason.
Object s calls the Student(int, int, string, bool) but when it calls the Student(int, int, string)(i.e. the compiler enters the body of the Stduent(int, int, string)), it creates a temporary object and the changes are happening in the temporary object. 
The sub-objetcs of the object s gets initialized through the initializer list, so name of s is still "NULL", roll and age of s is still 0, the only thing that is getting updated is the is_monitor data of s.
The other changes of the members are happening for the temporary object whose life-time is the scope of the Student(int, int, string) constructor.
To not repeat the tasks of the Student(int, int, string) constructor we can **delegate** it.
```cpp
class Student{
	int age{};
	int roll{};
	string name{"NULL"};
	bool is_monitor{};
public:
	Student(int r, int a, string n):age(a), roll(r), name(n){
	}
	Student(int r, int a, string n, bool im):Student(r, a, n){
	}
	void getInfo(){
		cout<<name<<endl;
		cout<<age<<endl;
		cout<<roll<endl;
	}
}; 

int main(){
	Student s(54, 19, "AdStacy", 1);
}
```
Here the constructor is written in the initializer list.
Restriction of delegating constructor is that, the initializer list can only contain the **delegated-to-constructor**
```cpp
class Student{
	int age{};
	int roll{};
	string name{"NULL"};
	bool is_monitor{};
public:
	Student(int r, int a, string n):age(a), roll(r), name(n){
	}
	Student(int r, int a, string n, bool im):Student(r, a, n),is_monitor(im){
		// this is wrong
	}
	void getInfo(){
		cout<<name<<endl;
		cout<<age<<endl;
		cout<<roll<endl;
	}
}; 

int main(){
	Student s(54, 19, "AdStacy", 1);
}
```
The above written syntax is wrong.
Also delegation to itself is not allowed in C++.
```cpp
class Stduent{
	int age;
	int roll;
public:
	Student(int r, int a):Student(r, a){
	}
};
```
This is not allowed.
Delegation will not initialize those memebers that are not in the delegated-to-constructor, they will stay as default.

##### Redundant Constructor V/S Redundant Default Values
```cpp
class S{
	int x{0};
};
```
This is deafult value of the member or default member initializer. Here it is **default value for the memeber**.
```cpp
class S{
	int x;
public:
	S(int m=0):x(m){
	}
};
```
This is default constrcutor argument. Here it is **default value for the parameter**.
So, the actual trade-off is, **if fewer constructor required then duplicacy of the default values will occur and if fewer duplicacy required then more number of constructor will be needed**. 
Duplicacy can be avoided using the static constexpr keyword.
```cpp
class S{
	static constexpr default_val=0;
	int x{default_val};
public:
	S(int m=default_val):x(m){
	}
};
```
static keyword id required becuase without it every object will have its own copy of the deafult_val. By adding static it's getting ensured that the deafult_val is an property/instantioation of the class, not the object.
constexpr keyword ensures that the default_val is compile-time constant.

A good programmer should always avoid unneccessary variables. If a variable is getting used only once, then it should be replaced with the expression used to initialize that. 
