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
then the rest of the string is set as a value. The code also checks if the string is not empty, and does not have irrelevant chars.

<code>
 BigInt num3("-0013");
</code>

The constructors, using function reduce, make sure there are no zeros on the left side of the value, and also the number is positive if the value is 0.

###Operators
The code includes multiple operators for different tasks.

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
<code>
 BigInt a2(-23);
 BigInt b2(+53);
 cout<< "-23<+53= "<< (a2<b2) <<"\n";
</code>

The operator == checks if the rhs is equal to the lhs. this operator checks if the size, the sign, and each digit in the two BigInts are the same.
 <code>
 BigInt a3("+25");
 BigInt b3("25");
 cout<< "25==25 = "<< (a3==b3) <<"\n";
</code>

The operator != is the negation of ==

<code>
 BigInt a4("+14");
 BigInt b4("14");
 cout << "14!=14 = " << (a4 != b4) << "\n";
</code>

The operators >= and <= are the combination of > and = or < and =.
<code>
BigInt a5("+9552500215415124");
BigInt b5("22154855451221888788995652326588451212002558852");
cout<< "+9552500215415124>= 2154855451221888788995652326588451212002558852 = "<< (a5>=b5) <<"\n";
</code>


The operators += and + are designed in this way. += divides the scenario in terms of numbers signs and whether the absolute of each one is greater than another one.
First, the case where both are positive.
It does the simple summation we used to do back in the primary school. it iterates over the digits (from smallest to greatest). sums every two digits.
if the sum is over 9, 1 is carried to the next digit. 
Second, the case where both are negative.
In this case, the code assumes both are positive and finally negates the summed output.
Third, the case where one is positive and one is negative.
In this case, the code, first, finds the number with a greater absolute and then calculates the difference between the absolute values,
using  the subtraction method that we used to do in primary school. It iterates over the digits of the number with lower absolute (from smallest to greatest). for each digit computes the greater number's digit - the smaller's number digit.
If the difference is below zero, reduce the next digit in the greater number by 1. After finishing the subtraction, if the number with a greater absolute is negative, negates the output. 

<code>
 BigInt x1(41);
 BigInt y1(52);
 cout<< "41+52= "<< (x1+y1) <<"\n";
 x1+=y1;
 cout<< "41+52= "<< x1 <<"\n";
</code>


-= and = first negate the rhs and then does a summation
<code>
 BigInt x2(61);
 BigInt y2(25);
 cout<< "61-25= "<< (x2-y2) <<"\n";
 x2-=y2;
 cout<< "61-25= "<< x2 <<"\n";
</code>

Operator *= and * Tfirst find the output sign. Then, do a multiplication just like the one we did in primary school.
 It iterates over the digits of the second number ( from smaller to greater digit) and does the multiplication. Finally, sums them up.


<code>
 BigInt x4("-11");
 BigInt y4("+19");
 cout << "(-11)*(+19)= " << (x4 * y4) << "\n";
 x4 *= y4;
 cout << "(-11)*(+19)= " << x4 << "\n";
</code>


<< operator inserts to an output stream

<code>
 BigInt num1;
 cout << "num1= " << num1<< "\n";
</code>
