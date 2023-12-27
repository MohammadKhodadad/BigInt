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

The constructors, using function reduce, make sure there is no zeros on the left side of the value, and also the number is positive if the value is 0.
