## Deletion of Functions

We may want to delete a function that is not behaving according to us.
E.g. Overloaded fucntions' arguments' primary conversion
```cpp
void f(int x);

int main(){
	int x=5;
	char c='a';
	bool b=true;
	f(x);
	f(c);
	f(b);
}
```
All of the above function will work, but we may not want our char and bool data types to convert to int and pass as an argument in the function f.
So, we may need to **delete** them.
```cpp
void f(int x);
void f(char c)=delete;
void f(bool b)=delete;

int main(){
	int x=5;
	char c='a';
	bool b=true;
	f(x);
	f(c);
	f(b);
}
```
So, when this program runs, as soon as the compiler goes to f(c), it sees that the overload of function f with argument as character is already deleted, hence it gives compilation error.
Same thing happens for 