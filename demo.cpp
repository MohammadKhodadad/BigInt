#include <iostream>
#include <stdexcept>
#include "bigint.hpp"

int main()
{
    // Let's define multiple BigInts through different constructors
    BigInt num1;
    BigInt num2(32);
    BigInt num3("-0013");
    BigInt num4("+212");
    BigInt num5("120215121515458415120");
    BigInt num6("-53123421523315456231235523415120");
    BigInt num7("+99999912342123412342342345653453");
    try
    {
        BigInt num8("+2522%&^&%25353453");
    }
    catch (const std::exception &e)
    {
        cout << e.what() << "\n";
    }

    try
    {
        BigInt num9("+5522+25353453");
    }
    catch (const std::exception &e)
    {
        cout << e.what() << "\n";
    }

    // First, the outputstream operator<<
    cout << "num1= " << num1<< "\n";

    // Now the assignment operator
    num2 = BigInt(64);
    cout << "num2= " << num2<< "\n";
    // Now testing Comparison operations
    cout<< boolalpha;
    BigInt a1(42);
    BigInt b1(52);
    cout << "42>52= " << (a1 > b1) << "\n";

    BigInt a2(-23);
    BigInt b2(+53);
    cout << "-23<+53= " << (a2 < b2) << "\n";

    BigInt a3("+25");
    BigInt b3("25");
    cout << "25==25 = " << (a3 == b3) << "\n";

    BigInt a4("+14");
    BigInt b4("14");
    cout << "14!=14 = " << (a4 != b4) << "\n";

    // Now big numbers

    BigInt a5("+9552500215415124");
    BigInt b5("22154855451221888788995652326588451212002558852");
    cout << "+9552500215415124>= 2154855451221888788995652326588451212002558852 = " << (a5 >= b5) << "\n";

    BigInt a6("-95525002101242424242424210040458787878785754254215415124");
    BigInt b6("-45642334567867867534312312312312312353453123123123123123123123");
    cout << "-95525002101242424242424210040458787878785754254215415124 <= -45642334567867867534312312312312312353453123123123123123123123 = " << (a6 <= b6) << "\n";

    // Now arithmetic operations
    BigInt x1(41);
    BigInt y1(52);
    cout << "41+52= " << (x1 + y1) << "\n";
    x1 += y1;
    cout << "41+52= " << x1 << "\n";

    BigInt x2(61);
    BigInt y2(25);
    cout << "61-25= " << (x2 - y2) << "\n";
    x2 -= y2;
    cout << "61-25= " << x2 << "\n";

    BigInt x3("-21");
    BigInt y3("-42");
    cout << "-21+(-42)= " << (x3 + y3) << "\n";
    x3 += y3;
    cout << "-21+(-42)= " << (x3) << "\n";

    BigInt x4("-11");
    BigInt y4("+19");
    cout << "(-11)*(+19)= " << (x4 * y4) << "\n";
    x4 *= y4;
    cout << "(-11)*(+19)= " << x4 << "\n";

    BigInt x5("-6562226523265899811");
    BigInt y5("+1236699985956262655795269");
    cout << "(-6562226523265899811)*(+1236699985956262655795269)= " << (x5 * y5) << "\n";
    x5 *= y5;
    cout << "(-6562226523265899811)*(+1236699985956262655795269)= " << x5 << "\n";
}