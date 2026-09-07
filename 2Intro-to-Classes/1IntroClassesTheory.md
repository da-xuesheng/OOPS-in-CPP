## Introduction to Class

**Class** is a user-defined data-type that acts as skeleton of an object. It binds data variables i.e. attributes and functions i.e. methods into a single unit to represent any object. 
Mathematically, class C is a structure that is an ordered pair of sets.
$$C = (S, M)$$
**State Space($S$):** It is defined as the set of all possible attributes of an object. More precisely it is **Cartesian Product** of the attributes of an object.
$$S = A_{1} \times A_{2} \times \dot \dot \dot \times A_{n}$$
**Methods($M$):** Set of operations that act upon the state space. $\forall m \in M \exists$ a mapping to the class's current state and arguments(optional) to the new state and/or the output,
$$m:S \times Arg_{1}\times Arg_{2} \times \dot \dot \dot \times Arg_{n}\rightarrow S*M$$

**Objects(o):** Objects is nothing but element of the state space.
$$o \in S$$

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
Constructors are not like the attributes of an objects, the variables are stored in RAM while the constructors are stored in .text segment of executable memory whicg is only read-only, hence they're only Read-Only. If altering is attempted, it'll cause the OS to crash the program, **Segmentation Fault**. In a more eaiser manner, an object's memory only contains its member variables, the constructor isn't stored here, thus constructor can't be accessed.
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