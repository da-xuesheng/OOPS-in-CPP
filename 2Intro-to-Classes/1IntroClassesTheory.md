## Introduction to Class

**Class** is a user-defined data-type that acts as skeleton of an object. It binds data variables i.e. attributes and functions i.e. methods into a single unit to represent any object. 
Mathematically, class C is a structure that is an ordered pair of sets.
```math
C = (S, M)
```
**State Space($S$):** It is defined as the set of all possible attributes of an object. More precisely it is **Cartesian Product** of the attributes of an object.
```math
S = A_{1} \times A_{2} \times \dots \times A_{n}
```
**Methods($M$):** Set of operations that act upon the state space. $\forall m \in M \exists$ a mapping to the class's current state and arguments(optional) to the new state and/or the output,
```math
m:S \times Arg_{1}\times Arg_{2} \times \dots \times Arg_{n}\rightarrow S \times M
```

**Objects(o):** Objects is nothing but element of the state space.
```math
o \in S
```

### Why Class, why not struct
For this, one needs to know **Class Invariant**. Class Invariant is a condition that remains true for an object throughout its lifetime. If any object defies this rule, the object enters an invalid state, leading to crashes or undefined behaviour. In c-style struct there is no such invariant rule and this can lead to code failure in bigger projects. Implicitly, c-style struct makes the defined attributes public. 
```c
struct frac{
	int numerator;
	int denominator;
};
```
We know that denominator can never be 0, but no one can stop one to make the attribute denominator as 0.
```cpp
class frac{
	int numeartor;
	int denominator;
};
```
By default, the class makes the attributes private, thus one can't change the attributes directly. Hence classes becomes extremely important for bigger projects. 

To see mathematically, an invariant is a function from the state space to boolean vector space. Let iV be a invariant, then:
$$iV:S\rightarrow {True, False}$$
Let $s\in S$, then $iV(s)=True$ is called Valid state and $iV(s)=False$ is called invalid state.
The Constructor fucntion inside a class establishes that $iV(s_{initial})=True$ and for any method $m$ $iV(s_{old})=True \implies iV(s_{new})=True$.
We make invariant private inside any class. **The constructor evaluates the invariant to act as a security gatekeeper for object creation.** 
When the compiler given instruction to create an object, the OS first reserves block of memory for it, it's just meaningless bits(garbage value), at that point of time, which may fail the invariant test or may pass. The constructor overwrites the garbage values to meaningful initial values (defined inside the class) then inside the constructor the user defined invariant function checks if the given values to the object returns True or False. If it returns True, the object is born otherwise the constructor aborts and the object is killed before it's came alive hence leaving no corrupted memory. 

But one might think why can't the constructor be altered(because it's usually defined public).
##### Why Constructor can't be altered
Constructors are not like the attributes of an objects, the variables are stored in RAM while the constructors are stored in .text segment of executable memory which is only read-only. If altering is attempted, it'll cause the OS to crash the program, **Segmentation Fault**. In a more eaiser manner, an object's memory only contains its member variables, the constructor isn't stored here, thus constructor can't be accessed.
```cpp
class threeDobj{
	int width;
	int height;
	int length;
	bool ifValid(){
		return width>0 && length>=0 && height>=0;
	}
	threeDobj(int w, int h, int l){
		if(!ifValid()){
			cout<<"invalid object creation"<<endl;
		}
		width=w;
		height=h;
		length=l;
	}
};
```
In this manner we can define constructors inside a class.
```cpp
class threeDobj{
	int width=0.1;
	int height=0.1;
	int length=0.1;
	bool ifValid(){
		return width>0 && length>=0 && height>=0;
	}
	threeDobj(){
		if(!ifValid()){
			cout<<"invalid object creation"<<endl;
		}
	}
};
```
This is also correct, the constructor will automatically override the garbage value to initializations of 0.1.
```cpp
class threeDobj{
	int width;
	int height;
	int length;
	bool ifValid(){
		return width>0 && length>=0 && height>=0;
	}
	threeDobj(){
		if(!ifValid()){
			cout<<"invalid object creation"<<endl;
		}
	}
};
```
This gives undefined results, if the garbage values are positive, the object will get constrcuted, other wise object creation is aborted.

Let's move on to member function.

### Member Functions
Function that belong to a class type are called member function, otherwise they are called non-member function or free function. Member functions to be called member function, must be declared inside class, but it can be defined outside also. 
```cpp
class Student{
	int roll;
	string name;

	bool validStudent(){
		if(roll>=1 && roll<=96){
			return 1;
		}
		return 0;
	}
public:
	Student(int r, string n){
		if(!validStudent()){
			perror("Student not valid");
			exit(EXIT_FAILURE);
		}
		roll=r;
		name=n;
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
	void printStudentInfo(){
		cout<<roll<<" "<<name<<endl;
	}
};

int main(){
	Student s(54, "AdStacy");
	s.printStudentInfo();
	return 0;
}
```
This is an example to show writing member functions.
##### Implicit Object
An Implicit Object is an object that is created or used by the compiler without the coder to write it.
Take the previous example:
```cpp
Student s(54, "AdStacy");
s.printStudentInfo();
```
It may seem that printStduentInfo() has no arguments, but this is mathematically incorrect. This mathematically interprets that:
```math
printStudentInfo:\Phi_E \rightarrow output
```
But this can't happen, so this means that there is some argument that is passed **Implicitly** by the compiler. The function has to know which object's state space to print.
```cpp
printStudentInfo(s);
```
it is the actual fucntion argument that is happenning. 
Implicit object is the object on which a non-static member function is invoked.
##### Non-Static and Static Member Fucntions
Non-static member functions are those member function that does not have **static** keyword. These are those member functions that are associated with object's state space. 
```math
f:S \times Arguments \rightarrow Output
```
This is the mathematical defenition of Non-static function.

Static member functions are those member function that does have **static** keyword. These functions are not associated with object's state space.
```math
f:Arguments \rightarrow Output
```
Mathematically we can define the Static functions in this way.
##### Why Non-static gets associated with object's state space?
```cpp
Student s(54, "AdStacy");
s.printStudentInfo();
```
Here memory for the object s is allocated and it only contains the data members not copy of the printStudentInfo() function. The function's compiled machine code stays in the program's text segment. It is not in the stack, only the object's data members are in the stack. Hence for Multiple objects there is only one copy of the function.
Now when **Object.function()** is written, the Object is implicit object of the member function call. For this call **this** pointer points to Object, hence, inside printStudentInfo(), roll and name refers to roll belonging to s, representes by:
```cpp
this->roll;
this->name;
```
CPU loads 0x1000 into a dedicated register and jumps to the text segment where the function exists. Inside function() accessing member variables resolves:
```math
Address of member = Register(this) + Offset of member
```
Hence a non-static function associates with the object's state space only at the time of execution by binding this to the address of the object.
**What is Offset?**
It is the number of bytes from a starting base address to a specific location within a contiguous block of memory.
###### Member Variable and Functions declarations can be done in any order.
This is possible because compilation happens in 2 passes. In first pass the compiler records all member names, types, then it parses the code inside function bodies and as the first pass is completed hence all the variables are known.
```cpp
class Stu{
public:
	int x;
	int f(){
		y-=x;
	}
private:
	int y=10;
};
```
Although the variable y is defined below the function still it will compile and execute due to the 2 passes.
But we can't do this for Constructor Initialization List.
```cpp
class X {
    int a;
    int b;
public:
    X(int val) : b(val), a(b + 5) {} 
};
```
This will throw error not during compile-time but during run-time. It'll compile as the 2 pass method but during run-time compiler ignores your written sequence, generates machine code that executes in declaration order. As b is undeclared so a gets some garbage value.

**Differrence of Class Obj(arguments), Class(arguments)**
class obj(arg) is a named object, but class(args) is an explicit unnamed temporary object.
**Differrence of {} and () while object creation**
```cpp
class S{
	int x;
	int y;
public:
	S(int m, int n):x(m), y(n){
	}
};
```

It is known that temporary object of S can be created by S(1, 2) and S{1, 2} both ways. The differrence between them is that S{1, 2} does **List Initialization** and S(1, 2) does **direct initialization**.

To understand the following, one must know **Narrowing-conversion prevention**.
###### Narrowing-conversion prevention
A conversion is considered narrowing if the destination type cannot represent all possible values of the source type.
e.g. float-to-int, double-float, int-to-char, signed-to-unsigned
Usual initialization syntax like = or () permits narrowing but {} initialization prevents this and gives compile-time error.
```cpp
int a=3.14;
int b{3.14}; //this will give error

int x=1000;
char c1=x; //it will not give error
char c2{x}; //this will return error
```
{} initialization permits conversion from an integer type to a smaller integer type only if the source is a constant expression and the specific value fits in the target type without truncation. 
In the same manner, S(1, 2) and S{1, 2} will get initialized. 
Only writing S{} will create a temporary object using value-initializations. Writing S() will work the same, they have nothing much differrent. 
```cpp
int main(){
	S s1{};
	S s();
}
```
S s1{} will create a object named s1 of S type but S s() will not create any object, it is simply a function declaration whose return type is S and has no arguments. Thus best practice of creating object is using the curly-braces {}.
If S(1) or S{1} is written then an temporary object with argument 1 is created(given that S(int) constructor is defined).
But this only happens for literals, if it is done with some variable which is of same type as S then it gives error.
```cpp
int main(){
	S s2;
	S(s2);
}
```
The compiler sees S s2 and S(s2) as same which means it also sees it as redeclaration, thus gives error. 
But if we write S{s2} then it will create a temporary object and will not give error. 