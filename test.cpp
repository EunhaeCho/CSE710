#include <iostream>
#include "bigint.hpp"
using namespace std;

int main()
{
     // Unit Tests
     // Define and Print bigint
     bigint p1;                                           // Uses default constructor
     p1.print();                                          // 0
     bigint p2(9223372036854775807);                      // Uses 64-bit integer constructor
     p2.print();                                          // 9223372036854775807
     bigint p3("+222");                                   // Uses string constructor
     p3.print();                                          // 922337
     bigint p4("11111111111111111111111111111111111111"); // Uses 64-bit integer constructor
     p4.print();                                          // 92233720368547758079223372036854775807

     // Addition
     bigint p5 = p4 + p3; //+ test
     p5.print();          // 11111111111111111111111111111111111333
     p5 += p3;
     p5.print(); // 11111111111111111111111111111111111555
     ++p5;
     p5.print(); // 11111111111111111111111111111111111556

     // Substrcation
     p5 = p4 - p3; //- test
     p5.print();   // 11111111111111111111111111111111110889
     p5 -= p3;
     p5.print(); // 11111111111111111111111111111111110667
     --p5;
     p5.print(); // 11111111111111111111111111111111110666

     // Multiplication
     p5 = p4 * p3;
     p5.print(); // 2466666666666666666666666666666666666642

     // Negative
     p5 = -p3;
     p5.print(); //-222

     // Comparison
     const bigint a = 123;
     const bigint b = 123;
     const bigint c = 1234;
     const bigint d = 567;
     std::cout << (a == a) << ' ' << (a != a) << '\n'; // 1 0
     std::cout << (a == b) << ' ' << (a != b) << '\n'; // 1 0
     std::cout << (a == c) << ' ' << (a != c) << '\n'; // 0 1
     std::cout << (a == d) << ' ' << (a != d) << '\n'; // 0 1
     std::cout << (a < b) << ' ' << (a > b) << '\n';   // 0 0
     std::cout << (a < c) << ' ' << (a > c) << '\n';   // 1 0
     std::cout << (a <= b) << ' ' << (a <= b) << '\n'; // 1 1
     std::cout << (a <= c) << ' ' << (a <= c) << '\n'; // 1 1

     // << Input test
     const bigint v = p3;
     std::cout << v << '\n'; // 222

     // Error Test
     bigint p6("+922dskjfe337"); // Uses string constructor
     p6.print();                 // error
}
