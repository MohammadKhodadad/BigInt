#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;


/**
 * @brief the class BigInt
 * The class has two parameters, value and sign.
The sign is the sign of the number. The value is the number itself stored in string format
 * 
 */
class BigInt
{

public:
    string value;
    char sign;
    BigInt();
    BigInt(int64_t num);
    BigInt(const string num);
    void reduce();
    bool operator==(const BigInt &other) const;
    bool operator!=(const BigInt &other) const;
    bool operator>(const BigInt &other) const;
    bool operator<(const BigInt &other) const;
    bool operator>=(const BigInt &other) const;
    bool operator<=(const BigInt &other) const;

    BigInt &operator=(const BigInt &other);
    BigInt &operator+=(const BigInt &other);
    BigInt &operator-=(const BigInt &other);
    BigInt &operator*=(const BigInt &other);

    BigInt operator+(const BigInt &other) const;
    BigInt operator-(const BigInt &other) const;
    BigInt operator*(const BigInt &other) const;

    friend ostream &operator<<(std::ostream &os, const BigInt &bigint);
};
/**
 * @brief removes zeros, checks the sign.
 * 
 * Does two things. First, removes zeros on the left side of the number. Second, if the number is zero, makes sure the sign is positive.
 *
 */
void BigInt::reduce()
{
    while ((value.size() > 1) && value[0] == '0')
        value = value.substr(1);
    if (value == "0")
        sign = '+';
}

/**
 * @brief The first constructor
 * The first constructor takes nothing and creates an object BigInt with sign positive and value 0
*/
BigInt::BigInt()
{
    value = "0";
    sign = '+';
}

/**
 * @brief The sceond constructor
 * 
 * The second constructor takes an int64_t and sets the absolute of the number as value and the sign of the number as sign. 
 * The constructors, using function reduce, make sure there are no zeros on the left side of the value, and also the number is positive if the value is 0.
 * 
 * @param num is an int64_t number the the value and sign is assigned to.
 */
BigInt::BigInt(int64_t num)
{
    if (num >= 0)
    {
        sign = '+';
        value = to_string(num);
    }
    else
    {
        sign = '-';
        value = to_string(-1 * num);
    }
    if (value == "0")
        sign = '+';
}
/**
 * @brief The third constructor
 * The third constructor takes a string. takes the first char if is + or - as the sign (if it is not - or +, assumes the number is positive as is obviously)
then the rest of the string is set as a value. For the string format, the code checks if the string is not empty, and does not have irrelevant chars. 
The number can start with '-' or '+'. The constructors, using function reduce, make sure there are no zeros on the left side of the value, and also the number is positive if the value is 0.
 * 
 * @param num is an string the represents the value and sign is assigned to
 */
BigInt::BigInt(string num)
{
    if (num.size() == 0)
        throw invalid_argument("string size should be greater than 1.");
    if ((num[0] != '+') && (num[0] != '-') && (num[0] < '0' || num[0] > '9'))
        throw invalid_argument("the first digit of the number must be + or - or a digit.");
    if (num[0] == '-')
    {
        sign = '-';
        num = num.substr(1);
    }
    else if (num[0] == '+')
    {
        sign = '+';
        num = num.substr(1);
    }
    else
    {
        sign = '+';
    }

    for (int i = 0; i < num.size(); i++)
    {
        if (num[i] < '0' || num[i] > '9')
            throw invalid_argument("the number must only consist of digits.");
    }
    value = num;
    if (value == "0")
        sign = '+';
    reduce();
}

/**
 * @brief Does assigning
 * The operator = assigns the value and the sign as the right hand side.
 * 
 * @param other the other object that value and sign is assigned to 
 * @return BigInt& the object assigned to
 */
BigInt &BigInt::operator=(const BigInt &other)
{
    value = other.value;
    sign = other.sign;
    return (*this);
}
/**
 * @brief checks ==
 * This operator checks if the size, the sign, and each digit in the two BigInts are the same.
 * 
 * @param other is the other object the is compared to
 * @return true if the objects are equal
 * @return false if the objects are not equal
 */
bool BigInt::operator==(const BigInt &other) const
{
    if (sign != other.sign)
        return false;
    if (value.size() != other.value.size())
        return false;
    for (int i = 0; i < value.size(); i++)
    {
        if (value[i] != other.value[i])
            return false;
    }
    return true;
}

/**
 * @brief checks !=
 * This operator is the negation of ==.
 * 
 * @param other is the other object that is compared to
 * @return true if the objects are not equal
 * @return false if the objects are equal
 */
bool BigInt::operator!=(const BigInt &other) const
{
    return !(*this == other);
}
/**
 * @brief checks >
 * This operator divides the problem into multiple settings. If the signs of the two numbers are different, the answer is the positive one.
If the signs are the same, the code iterates over digits until one digit is bigger than another one.
 * 
 * @param other is the other object that is compared to
 * @return true if rhs>lhs
 * @return false if not rhs>lhs
 */
bool BigInt::operator>(const BigInt &other) const
{
    if ((sign == '+') && (other.sign == '-'))
        return true;

    else if ((sign == '+') && (other.sign == '+'))
    {
        if (value.size() > other.value.size())
            return true;
        else if (value.size() == other.value.size())
        {
            for (int64_t i = 0; i < value.size(); i++)
            {
                if (value[i] > other.value[i])
                    return true;
                else if (value[i] < other.value[i])
                    return false;
            }
            return false;
        }
        else
            return false;
    }
    else if ((sign == '-') && (other.sign == '+'))
        return false;

    else // if ((sign=='-') && (other.sign=='-'))
    {
        if (value.size() < other.value.size())
            return true;
        else if (value.size() == other.value.size())
        {
            for (int64_t i = 0; i < value.size(); i++)
            {
                if (value[i] < other.value[i])
                    return true;
                else if (value[i] > other.value[i])
                    return false;
            }
            return false;
        }
        else
            return false;
    }
    return false;
}
/**
 * @brief checks <
 * This opperator does > when rhs and lhs are switched.
 * 
 * @param other is the other option that is compared to 
 * @return true if rhs<lhs
 * @return false if not rhs<lhs
 */
bool BigInt::operator<(const BigInt &other) const
{
    return other > (*this);
}
/**
 * @brief checks >=
 * This opertor is > or ==
 * 
 * @param other is the other option that is compared to 
 * @return true if lhs>=rhs
 * @return false if not lhs>=rhs
 */
bool BigInt::operator>=(const BigInt &other) const
{
    return (((*this) > other) || ((*this) == other));
}

/**
 * @brief checks <=
 * This opertor does >= when rhs and lhs are switched.
 * 
 * @param other is the other option that is compared to 
 * @return true if rhs<=lhs
 * @return false if not rhs<=lhs
 */
bool BigInt::operator<=(const BigInt &other) const
{
    return other >= (*this);
}
/**
 *
 * @brief does +=
This operator divides the scenario in terms of numbers signs and whether the absolute of each one is greater than another one.
First, the case where both are positive.
It does the simple summation we used to do back in the primary school. it iterates over the digits (from smallest to greatest). sums every two digits.
if the sum is over 9, 1 is carried to the next digit.
Second, the case where both are negative.
In this case, the code assumes both are positive and finally negates the summed output.
Third, the case where one is positive and one is negative.
In this case, the code, first, finds the number with a greater absolute and then calculates the difference between the absolute values,
using  the subtraction method that we used to do in primary school. It iterates over the digits of the number with lower absolute (from smallest to greatest). for each digit computes the greater number's digit - the smaller's number digit.
If the difference is below zero, reduce the next digit in the greater number by 1. After finishing the subtraction, if the number with a greater absolute is negative, negates the output.
 * 
 * @param other is the other BigInt object that is summed by
 * @return BigInt& the out put of the summation
 */
BigInt &BigInt::operator+=(const BigInt &other)
{

    if ((sign == '+') && (other.sign == '+'))
    {

        int64_t max_len = max(value.size(), other.value.size());
        string new_value = "";
        int64_t carry = 0;
        int64_t temp_sum = 0;
        for (int64_t i = 0; i < max_len; i++)
        {
            if (i < value.size())
                temp_sum += (value[value.size() - i - 1] - '0');
            if (i < other.value.size())
                temp_sum += (other.value[other.value.size() - i - 1] - '0');
            temp_sum += carry;
            carry = 0;
            if (temp_sum > 9)
            {
                carry = (temp_sum / 10);
                temp_sum = temp_sum % 10;
            }
            new_value = to_string(temp_sum) + new_value;
            temp_sum = 0;
        }
        if (carry != 0)
            new_value = to_string(carry) + new_value;
        *this = BigInt(new_value);
        return *this;
    }

    else if ((sign == '-') && (other.sign == '-'))
    {
        int64_t max_len = max(value.size(), other.value.size());
        string new_value = "";
        int64_t carry = 0;
        int64_t temp_sum = 0;
        for (int64_t i = 0; i < max_len; i++)
        {
            if (i < value.size())
                temp_sum += (value[value.size() - i - 1] - '0');
            if (i < other.value.size())
                temp_sum += (other.value[other.value.size() - i - 1] - '0');
            temp_sum += carry;
            carry = 0;
            if (temp_sum > 9)
            {
                carry = (temp_sum / 10);
                temp_sum = temp_sum % 10;
            }
            new_value = to_string(temp_sum) + new_value;
            temp_sum = 0;
        }
        if (carry != 0)
            new_value = to_string(carry) + new_value;
        *this = BigInt("-" + new_value);
        return *this;
    }

    else if ((sign == '+') && (other.sign == '-'))
    {
        BigInt new_other(other.value);
        BigInt new_this(value);
        if (new_this >= new_other)
        {
            int64_t temp_neg = 0;
            for (int64_t i = 0; i < new_other.value.size(); i++)
            {
                temp_neg = new_this.value[new_this.value.size() - 1 - i] - new_other.value[new_other.value.size() - 1 - i];
                if (temp_neg < 0)
                {
                    new_this.value[new_this.value.size() - 1 - i] = (temp_neg + 10) + '0';
                    new_this.value[new_this.value.size() - 2 - i] = new_this.value[new_this.value.size() - 2 - i] - 1;
                }
                else
                    new_this.value[new_this.value.size() - 1 - i] = temp_neg + '0';
            }
            new_this.reduce();
            *this = new_this;
            return *this;
        }
        else
        {
            int64_t temp_neg = 0;
            for (int64_t i = 0; i < new_this.value.size(); i++)
            {
                temp_neg = new_other.value[new_other.value.size() - 1 - i] - new_this.value[new_this.value.size() - 1 - i];
                if (temp_neg < 0)
                {
                    new_other.value[new_other.value.size() - 1 - i] = (temp_neg + 10) + '0';
                    new_other.value[new_other.value.size() - 2 - i] = new_other.value[new_other.value.size() - 2 - i] - 1;
                }
                else
                    new_other.value[new_other.value.size() - 1 - i] = temp_neg + '0';
            }
            new_other.sign = '-';
            new_other.reduce();
            *this = new_other;
            return *this;
        }
    }

    else // if ((sign=='-')&&(other.sign=='+'))
    {
        BigInt new_other(other.value);
        BigInt new_this(value);
        if (new_this >= new_other)
        {
            int64_t temp_neg = 0;
            for (int64_t i = 0; i < new_other.value.size(); i++)
            {
                temp_neg = new_this.value[new_this.value.size() - 1 - i] - new_other.value[new_other.value.size() - 1 - i];
                if (temp_neg < 0)
                {
                    new_this.value[new_this.value.size() - 1 - i] = (temp_neg + 10) + '0';
                    new_this.value[new_this.value.size() - 2 - i] = new_this.value[new_this.value.size() - 2 - i] - 1;
                }
                else
                    new_this.value[new_this.value.size() - 1 - i] = temp_neg + '0';
            }
            new_this.sign = '-';
            new_this.reduce();
            *this = new_this;
            return *this;
        }
        else
        {
            int64_t temp_neg = 0;
            for (int64_t i = 0; i < new_this.value.size(); i++)
            {
                temp_neg = new_other.value[new_other.value.size() - 1 - i] - new_this.value[new_this.value.size() - 1 - i];
                if (temp_neg < 0)
                {
                    new_other.value[new_other.value.size() - 1 - i] = (temp_neg + 10) + '0';
                    new_other.value[new_other.value.size() - 2 - i] = new_other.value[new_other.value.size() - 2 - i] - 1;
                }
                else
                    new_other.value[new_other.value.size() - 1 - i] = temp_neg + '0';
            }
            new_other.reduce();
            *this = new_other;
            return *this;
        }
    }
}

/**
 * @brief does -=
 * This operator first negates the right hand side then does a summation
 * 
 * @param other is the other BigInt object that is substracted by
 * @return BigInt&  the output of the substraction
 */
BigInt &BigInt::operator-=(const BigInt &other)
{
    BigInt new_other(other.value);
    if (other.sign == '+')
        new_other.sign = '-';
    return (*this) += new_other;
}
/**
 * @brief does +
 * This operator uses the summation and assignment that we wrote.
 * 
 * @param other is the other BigInt object that is substracted by
 * @return BigInt the output of the summation
 */
BigInt BigInt::operator+(const BigInt &other) const
{
    BigInt new_this = (*this);
    new_this += other;
    return new_this;
}
/**
 * @brief does -
 * This operator uses the substraction and assignment that we wrote.
 * 
 * @param other is the other BigInt object that is sumed by
 * @return BigInt the output of the substraction
 */
BigInt BigInt::operator-(const BigInt &other) const
{
    BigInt new_this = (*this);
    new_this -= other;
    return new_this;
}
/**
 * @brief does *=
 * This operation first finds the output sign. Then, does a multiplication just like the one we did in primary school.
 It iterates over the digits of the second number ( from smaller to greater digit) and does the multiplication. 
 To do the multiplication, the digit is multiplied by each digit in the first number (from the smallest to the greatest),
the modulo by 10 is stored as the output number for the corresponding digit, and the remaining divided by 10 is carried to the next digit.
Finally, sums them up.
 * 
 * @param other is the other BigInt object that is multiplied by
 * @return BigInt& the output of the multiplication
 */
BigInt &BigInt::operator*=(const BigInt &other)
{
    char new_sign;
    if (sign == other.sign)
        new_sign = '+';
    else
        new_sign = '-';
    int64_t carry = 0;
    int64_t temp_mul = 0;
    BigInt summed(0);
    summed.sign = new_sign;
    BigInt temp(0);

    for (int64_t i = 0; i < other.value.size(); i++)
    {
        temp.value = "";
        carry = 0;
        for (int64_t k = 0; k < i; k++)
            temp.value = temp.value + "0";
        for (int64_t j = 0; j < value.size(); j++)
        {
            temp_mul = (other.value[other.value.size() - 1 - i] - '0') * (value[value.size() - 1 - j] - '0');
            temp_mul += carry;
            carry = temp_mul / 10;
            temp_mul = temp_mul % 10;
            temp.value = to_string(temp_mul) + temp.value;
        }
        if (carry > 0)
            temp.value = to_string(carry) + temp.value;
        summed += temp;
    }
    *this = summed;
    return *this;
}
/**
 * @brief does *
 * This operator uses the multiply and assign that we wrote.
 * 
 * @param other is the other BigInt object that is multiplied by
 * @return BigInt the output of the multiplication
 */
BigInt BigInt::operator*(const BigInt &other) const
{
    BigInt new_this = (*this);
    new_this *= other;
    return new_this;
}
/**
 * @brief stream operation
 * This operator inserts to an output stream
 * 
 * @param os the output stream
 * @param bigint the value that should be streamed
 * @return ostream& the output stream with object streamed inside.
 */
ostream &operator<<(std::ostream &os, const BigInt &bigint)
{
    return os << bigint.sign << bigint.value;
}