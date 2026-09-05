# Introduction to OOP in C++

If we had to add two integers and two double values, we may think we have to use two differrent name functions
```cpp
int addInt(int a, int b){
	return a+b;
}
int addDouble(double a, double b){
	return a+b;
}
```
It has no issues, but for bigger projects where we may have to write same logic for multiple datatypes there we may get into trouble of not remembering the function names. C++ has a way to handle that.
```cpp
int add(int a, int b){
	return a+b;
}
double add(double a, double b){
	return a+b;
}
```
This is called **Function Overloading**.
Here we can name two function same, but if we keep the parameters(types of parameters, number of parameters) different then it'll giveus no issues, it'll compile.

When main() calls a function (that has been overloaded), compiler will try to match the function to the appropriate overload based on the arguments used. This is called **Overload Resolution**

While calling the overloaded function, the function must be distinct, otherwise it'll give compilation error.

## Function Overload Differentiation

### Function Overload Differentiation Using **Number of Parameters**
We can differentiate the number of parameters to differentiate overloads
```cpp
int add(int a, int b){
	return a+b;
}
int add(int a, int b, int c){
	return a+b+c;
}
```
### Function Overload Differentiation Using **Type of Parameters**
```cpp
int add(int a, int b){
	return a+b;
}
int add(double a, double b){
	return a+b;
}
```
Hence we can differntiate them
Typedefs and type aliases are not distinct types, hence overload based upon types of parameters won't work
```cpp
typedef int h;
using a=int;
void f(int val);//3
void f(a val);//1
void f(h val);//2
```
3 is not differentiated from 1 and 2 because they are all int data-type.

The **const** keyword sometimes acts as an overloading differentiator and sometimes it doesn't, it depends on the use case.
```cpp
void f(int x);
void f(const int x);
```
In this case, it will not act as an differentiator. It will give error, when called from main.
```cpp
void f(int &x);
void f(const int &x);
```
In this case it will act as a overload differentiator.

This happens because, whenever parameter is passed by **value**, the function recieves a completely independent copy of the argument passed. **const** only ensures that the local copy won't be changed after it's been initialized, but the caller see the exact same thing that "the function needs a copy of the argument". Thus it ignores the const qualifiers on the pass by value arguments.

But when the argument is passed by refferrence, copy isn't made, we're passing the actual data, thus compiler uses **cosnt** keyword as an overload resolution when passed by refferrence.

#### Use of Ellipsis
```cpp
void f(char c, int x);
void f(char ,...);
```
These two function are very much distinct. 
The precedence order of the ellipsis are the lowest as compared to the other overload resolutions.

##### Priority Order of the Overload Resolutions
Exact Match and Trivial Adjustments(matching int argument, adding an const, array to pointer decay) ----> Numeric Promotion(**integral promotion**; e.g. promotion of bool, char, short to int, **Floating promotion**; e.g. float to double) ----> Standard Conversions(int to double) ----> User defined conversions ----> Ellipsis

### Return type isn't an Overload Resolution
```cpp
double f();
int f();
```
This will give compilation error.

**Compiler issues Ambiguous Error when it finds more than one matching functions**

### What are Trivial Conversion
A conversion is considered "trivial" in C++ if it requires absolutely zero CPU instructions to execute at runtime. There are 3 types of Trivial Conversions.

**lvalue to rvalue conversion:**
An lvalue-to-rvalue conversion is the automated process where the compiler reads the data stored at a specific memory address (the lvalue) and extracts it as a raw, temporary value (the rvalue) so it can be used in a calculation or assignment.
```cpp
int x=5;
int y=x;
```
Here data is extracted from x's address(&x gives a real hexadecimal value) and the value extracted in 5. x is the lvalue, 5 is the rvalue. So, while assigning value to y, the compiler first sees the lvalue i.e. y(left side of the = sign), then checks the right side but sees no rvalue. It sees a lvalue again i.e. x. So it extracts the rvalue i.e. 5 then writes the value to the memory address of y.
```cpp
void f(int& x);
void f(const int& x);
void f(int&& x);

int main(){
	int a=10;
	f(a);
	f(5);
	f(a+20);
	const int b=4;
	f(b);
}
```
Here a is the lvalue and 10 is the rvalue, compiler sees lvalue referrence in f(int& x), so calling f(a) is actually calling f(int& x).
Next 5 is a rvalue a+20 is also a rvalue, f(int&& x) asks for an rvalue referrence, so calling f(5) or f(a+20) is calling f(int&& x).
Next b is an const int, compiler sees f(const int& x), so this is called.
```cpp
void f(int& x);
void f(const int& x);

int main(){
	int a=10;
	f(a);
	f(5);
	f(a+20);
	const int b=4;
	f(b);
}
```
Here in the f(5) line, 5 is an rvalue, which is constant, so compiler sees the overload f(const int& x), so it directly calls f(const int& x). It will not call the f(int& x) because C++ strictly forbids binding non-constant lvalue referrence to rvalue.

```cpp
void f(int&& x);

int main(){
	const int b=10;
	int a=9;
	f(b);
	f(a);
}
```
Both of f(a) and f(b) will lead to compilation error because a and b has persistent memory addresses. But the function f only expects its argument to be address of the rvalue, thus both of the calls will give compilation error.

**Qualification Conversion:**
A qualification conversion is the compiler's formal term for implicitly adding a const or volatile qualifier to a pointer or reference.
```cpp
void f(const int& x);

int main(){
	int x=10;
	f(10);
	const int y=11;
	f(y);
}
```
they won't give compilation error. Compiler automatically adds a **const** or **volatile** to a pointer or referrence.
```cpp
void f(int& x);

int main(){
	const int x=10;
	f(10);
}
```
This will lead to compilation error.
```cpp
void f(int* x);

int main(){
	int y=10;
	int* ptr=&y;
	f(ptr);
}
```
This is also completely fine. But we can't do this for int**.

**Function to pointer Decay**
**Qualification Conversion**

#### Valid Standard Coversion During Overloading
1. Numeric Conversions
   a. Integral to Integral
   b. Flaot to float
   c. Float to integral
2. Pointer & Reference Conversions
   a. Derived-to-Base Conversion (Upcasting)
   b. Any Pointer to void*
   c. Null Pointer Conversion: The generic nullptr_t type is converted into a typed null pointer, like int* or double*.
3. Bool concversion
   Any integer except can be converted to TRUE and zero is converted to FALSE