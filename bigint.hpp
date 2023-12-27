#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

/*Here is the class definition. The class has two parameters, value and sign. 
The sign is the sign of the number. The value is the number itself stored in string format. */
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
// Reduce does two things. First, removes zeros on the left side of the number. Second, if the number is zero, makes sure the sign is positive.
void BigInt::reduce()
{
    while ((value.size() > 1) && value[0] == '0')
        value = value.substr(1);
    if (value == "0")
        sign = '+';
}
/*Here are the constructors
The first constructor takes nothing and creates an object BigInt with sign positive and value 0
The second constructor takes an int64_t and sets the absolute of the number as value and the sign of the number as sign
The third constructor takes a string. takes the first char if is + or - as the sign (if there is non assumes the number is positive as is obviously)
then the rest of the string is set as value. 
The constructors, using function reduce, make sure there is no zeros on the left side of the value, and also the number is positive if the value is 0.
 */
BigInt::BigInt()
{
    value = "0";
    sign = '+';
}

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
// For the string format, the code checks if the string is not empty, and does not have irrelevant chars. The number can start with '-' or '+'.
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

// the operator = assigns the value and the sign as the right hand side.


BigInt &BigInt::operator=(const BigInt &other)
{
    value = other.value;
    sign = other.sign;
    return (*this);
}
// this operator checks if the size, the sign, and each digits in the two BigInts are the same.
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

// This operator is the negation of ==.
bool BigInt::operator!=(const BigInt &other) const
{
    return ~(*this == other);
}
/*
This oeprator devides the problem into multiple settings. If the signs of the two numbers are different, the answer is the one that is postitve. 
If the signs are the same, the code iterates over digits until one digit is bigger than another one.
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
// this opertor is the oposite of >
bool BigInt::operator<(const BigInt &other) const
{
    return other > (*this);
}
// this opertor is > or ==
bool BigInt::operator>=(const BigInt &other) const
{
    return (((*this) > other) || ((*this) == other));
}

// this opertor is the oposite of >=
bool BigInt::operator<=(const BigInt &other) const
{
    return other >= (*this);
}
/*
This opertor divides the scenario in terms of numbers signs and whether the absolute of each one is greater than another one.
First, the case where both are positive.
It does the simple summation we used to do back in the primariy school. it iterates over the digits (from smallest to greatest). sums each two digit.
if the sum is over 9, 1 is carried to the next digit. 
Second, the case where both are negative.
In this case the code assumes both are postivie, finally negates the summed output.
Third, the case where one is positive and one is negative.
In this case, the code, first, finds the number with greater absolute and then calculates the difference between the absolute values,
using  the substraction method that we used to do in the primary school. It iterates over the digits of the number with lower absolute (from smallest to greatest). for each digit computes the greater number's digit - the smaller's number digit.
If the difference is bellow zero, reduces the next digit in the greater number by 1. After finishing the substraction, if the number with greater absolute is negative, negates the output. 
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
        else //(new_other>=new_this)
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

// This operator first negates the right hand side then does a summation
BigInt &BigInt::operator-=(const BigInt &other)
{
    BigInt new_other(other.value);
    if (other.sign == '+')
        new_other.sign = '-';
    return (*this) += new_other;
}
// This operator uses the summation and assignment that we wrote.
BigInt BigInt::operator+(const BigInt &other) const
{
    BigInt new_this = (*this);
    new_this += other;
    return new_this;
}
// This operator uses the substraction and assignment that we wrote.
BigInt BigInt::operator-(const BigInt &other) const
{
    BigInt new_this = (*this);
    new_this -= other;
    return new_this;
}
/*
This operation first finds the output sign. Then, does a multiplication just like the one we did in primary school.
 It iterates over the digits of the second number ( from smaller to greater digit), and does the multiplication. Finaly, summs them up.
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
// this operator uses the multiply and assign that we wrote.
BigInt BigInt::operator*(const BigInt &other) const
{
    BigInt new_this = (*this);
    new_this *= other;
    return new_this;
}
// this operator handles streams.
ostream &operator<<(std::ostream &os, const BigInt &bigint)
{
    return os << bigint.sign << bigint.value;
}