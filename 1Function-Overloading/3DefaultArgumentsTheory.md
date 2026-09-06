## Default Arguments

Default arguments are fallback values given to function parameters. If the function caller chooses not to provide a value for that parameter, then the function automatically uses the default value at compile time.
```cpp
void f(int x, int y=10);

int main(){
	int x=10, y=15;
	f(x, y);
	f(x);
}
```
In the called function f(x, y) as the assigned value to the varibale y is 15, thus the function takes x=10 and y=15 as arguments. But in the second case as only f(x) is called thus the fucntion falls back and takes y=10 as a default argument of the second parameter. 

#### The Right to Left Rule
As the compiler evaluates fucntion arguments strictly form left to right, so once we define a parameter with a default argument, every parameter to the **right** of it **must have a default argument**

##### Effect of Default arguments in fucntion overloading
```cpp
void f(int a);
void f(int a, int b=10);

int main(){
	f(10, 20);
	f(10);
}
```
Here, the first function call, will work fine, it is exact match(highest priority), but the seconf function call will lead to compilation error("Ambiguous"), because f(10) has exact match with f(int a) and also f(int a, int b=10) takes b=10 as default value when nothing is passed as argument to parameter b, thus it is also exact match, hence the two overload are at same priority level, leading to compilation error.

##### Redeclaration of Default Arguments
```cpp
void f(int a, int b, int c=10);
void f(int a, int b=20, int c);
void f(int a=1, int b, int c);

int main(){
	int a=1, b=2, c=3;
	f(a, b);
	f(a);
	f();
}
```
**This is completely valid.** When the compiler sees this it reads line f(int a, int b, int c=10) and sets that parameter c has default argument as 10. Next it reads f(int a, int b=20, int c), as it has already set that parameter c has default argument 10, thus it also sets parameter b's default argument as 20, it shows no error flag(One may think that b has deafult argument, but if c has no deafult argument, then it must give error, but the compiler already has set the parameter c's default argument as 10, hence gives no error). Next, it sees f(int a=1, int b, int c), as parameter b and c already has deafult arguments thus parameter a is also set to default argument 1, giving no error.
```cpp
void f(int a=1, int b, int c);
void f(int a, int b=10, int c);
void f(int a, int b, int c=2);
```
**This is completely invalid**, because the compiler reads the first parameter has default argument, but the next two parameters do not have any default value. Thus it raises an error flag.
```cpp
void f(int a, int b, int c=1);
void f(int a; int b=1, int c=4);
```
**This also raises error**, because when f(a, b, c) is called(where a, b, c are not the default values) the compiler gets confused, which function to call(the both overloads are exact match, they both are at same priority level), even if a, b, c are deafult arguments(e.g. f(a, b) or f(a) is called), then too the compiler gets confused which default argument to take., raising an error flag. **C++ forbids repettition of default arguments' parameter in same scope**
Thus for **Recursive function calls will have no issues with repettition**.
```cpp
void f(int a, int b, int c=3){
	void f(int a, int b, int c=4);
	f(a, b);
}

int main(){
	f(1, 2);
}
```
The call from main() executes f(1, 2, 3) (because it parameter c got default argument for the global scope as 3). When we're inside the function, we ignore the global scope, precisely **Scope Hiding/Shadowing** happens, global scope f(int a, int b, int c=3) ceases to exist in the compiler. Next when the compiler goes to the next line f(a, b), compiler searches for the nearest visible declaration, as it finds f(int a, int b, int c=4) as its nearest declaration, f(a, b) line is executed as f(a, b, 4).

### ODR Rule of C++
**One-Definition-Rule**
Inside a single source file, declaration of a function, variable, class, or template is possible as many times as one want, but definition is only allowed once. Disobeying this law leads to compilation error.

#### Rules of Redeclaring a function
1. A function can be redeclared as many as one wants, but the return type and the number of the parameters and the type of parameters must remain same, then only it'll be called redeclaring otherwise it'll be called overloading.
2. A default value that was already declared can't be repeated.
3. New defaults must continuously satisfy the rule that all parameters to their right already have defaults.