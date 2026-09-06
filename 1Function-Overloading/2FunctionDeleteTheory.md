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
Same thing happens for f(b), it sees that the overload of function f with the argument as boolean value is already deleted, hence it gives compilation error.

Sometimes we may want to use overload of argument of one type only and may need to say that, "we don't want all other argument types".
Then we can use the **Template Function** for the case.
```cpp
void f(int x);

template <typename T>
void f(T x)=delete;

int main(){
	f(97);
	f('a');
	f(3.4);
	f(true);
}
```
Here only the call f(97) will work, the others will not work and give compilation error. Whenever f with argument of datatypes except int gets called, function template will take precedence for them and the compiler will see that overload of those argument types are already deleted, hence giving compilation error.
One may think that won't the double value, boolean value, char convert to int using standard conversion, but as we defined template function thus it means that double value, boolean value, char gets exact match with the arguments i.e. exact match, as we know exact match has higher priority than standard conversion, hence compiler will go to the template function only, the compiler will give error as, "Fucntion already deleted", not "Error: Ambiguous function". 