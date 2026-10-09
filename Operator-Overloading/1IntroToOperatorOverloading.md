## Operator Overloading

Using function overlaoding to overload operators is called **Operator Overloading**.
When numA + numB is written the compiler has a built-in version of + operator for integer operands that adds two integers and returns another integer, it is also has built-in version for double and floats.

example:
```cpp
class S{
	int x;
	int y;
	string name;
public:
	S()=default;
};

int main(){
	S s1(4, 5, "A");
	S s2(3, 4, "B");
	cout<<s1+s2<<endl;
}
```
This will result into error because + operation for this particular class has neither been defined nor it has any built-in version. Thus it's needed to make the compiler know that how the + operator work for the S class.

All operators can be overloader except **conditional(?:), sizeof(), scope resolution(::), member selector(.), pointer member selector(.* ), typeid, casting operators**
One can't create new operators, only those operators can be overloaded that exists.
Atleast one of the operands in an overloaded operator must be of user-defined type. One can overload operator+(double, S) but doing operator+(int, int) is not allowed. STL class is considered as user-defined thus overloading of operator+(vector, int) is possible.
Programmer can't change the number of operands an operator can take or the precedence, e.g. binary operators can't be made trinary.