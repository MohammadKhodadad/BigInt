## BigInt
This is the project for our course CSE701.
The code is the implementation of BigInt with operations.
### Constructors
The code has three constructors.
The first constructor takes nothing and creates an object BigInt with sign positive and value 0
<code>  
BigInt num1;
</code>


The second constructor takes an int64_t and sets the absolute of the number as value and the sign of the number as sign
<code>  
BigInt num2(32);
</code>

The third constructor takes a string. takes the first char if is + or - as the sign (if it is not - or +, assumes the number is positive as is obviously)
then the rest of the string is set as a value.

<code>
BigInt num3("-0013");
</code>

The constructors, using function reduce, make sure there are no zeros on the left side of the value, and also the number is positive if the value is 0.

###Operators
The code includes multiple operators for different tasks.
####Assignment Operator
this operator assigns a variable as an object.
<code> 
BigInt new_num2=num2;
cout << "new_num2= " <<new_num2;
</code>

####Assignment Operator
The assignment operator lets us assign a new object to a variable.
<code> 
num2=BigInt(64);
cout << "num2= " <<num2;
</code>


####Comparison Operator
The operator > checks if the lhs is greater than rhs.This operator divides the problem into multiple settings. If the signs of the two numbers are different, the answer is the positive one. 
If the signs are the same, the code iterates over digits until one digit is bigger than another one.

<code> 
BigInt a1(42);
BigInt b1(52);
cout<< "42>52= "<< (a1>b1) <<"\n";
</code>

The operator < checks if the rhs is greater than lhs
BigInt a2(-23);
BigInt b2(+53);
cout<< "-23<+53= "<< (a2<b2) <<"\n";
</code>

The operator == checks if the rhs is equal to the lhs. this operator checks if the size, the sign, and each digit in the two BigInts are the same.
BigInt a3("+25");
BigInt b3("25");
cout<< "25==25 = "<< (a3==b3) <<"\n";
</code>
