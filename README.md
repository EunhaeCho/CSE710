
## Class bigint

I have defined a class called bigint to perform operations on large integers. The numbers are stored as strings in a private field called input, which can be accessed for computations. However, I have not yet fully implemented handling for negative numbers, so currently, operations are only supported for positive numbers.

### Constructors
The class contains the following 3 constructors:
* A default constructor, creating the integer 0.
* A constructor that takes a signed 64-bit integer and converts it to an arbitrary-precision integer.
* A constructor that takes a string of digits and converts it to an arbitrary-precision integer.

Therefore, when there is no input value, the private `std::string` field `input` stores "0". If the input is a 64-bit integer, the integer value is converted to a string and stored. If the input is provided as a string, the value is stored directly in `input`; however, if a non-numeric value is given, an error message is displayed.

## Overloaded operators
The class overloads the following operators:

* Addition (+ and +=)
    The concept for the operations was designed to closely mimic the way humans perform calculations. For addition, the process starts from the least significant digit, adding one digit at a time. If the sum of the digits exceeds 10, a carry is applied to the next higher digit. For negative integers, if both numbers to be added are negative, their signs are removed, and addition is performed as described above. The resulting sum then has the negative sign reattached. However, in cases where a negative and a positive integer are added, the intention was to use a subtraction operation (to be defined later). This part has not yet been fully implemented.
    The `+=` operator was defined first, and the `+` operator was subsequently defined as applying the `+=` operation to the left-hand operand.

* Subtraction (- and -=)
    For subtraction, the process is the reverse of addition. Starting from the least significant digit, each digit is subtracted. If the result is negative, a borrow is applied, adjusting the current digit to a positive value and subtracting 1 from the next higher digit in the subsequent operation. This approach ensures the correct computation of the result.
    The `-=` operator was defined first, and the `-` operator was implemented by applying the `-=` operation to the left-hand operand.

* Multiplication (* and *=)
    For multiplication, a similar approach was taken. First, the process determines whether the signs of the two operands are the same or different. Starting with the least significant digit of the left-hand operand, each digit is multiplied by the digits of the right-hand operand from the least significant digit to the most significant digit. The partial products are then summed to compute the overall product. The process is repeated for all digits of the left-hand operand. If the signs of the operands differ, a `-` sign is added to the beginning of the result. Due to time constraints, the code has not been fully optimized, resulting in repeated sections of code.
    The `*=` operator was defined first, and as before, the `*` operator was implemented by applying the `*=` operation to the left-hand operand and assigning the result.

* Negation (unary -)
    For negation, the implementation removes the `-` sign if it is already present. Otherwise, it adds a `-` sign to the value, effectively toggling the sign of the number.

* Comparison (==, !=, <, >, <=, and >=)
    For comparison, the implementation compares the `std::string` stored in the private space of the `bigint` class. If the two strings are identical, the `bigint` objects are considered equal; otherwise, they are not. 

    For greater or lesser comparisons, the implementation considers the signs of the numbers:
    - For `<` and `>`, if the numbers are equal, the result is `false`.  
    - If both numbers are positive, their lengths are compared to determine the result. If lengths are equal, the digits are compared one by one starting from the most significant digit.  
    - If both numbers are negative, the same process is applied, but the sign is reversed.  
    - If the signs differ, the result is `true` or `false` depending on whether one number is positive and the other is negative.  

    After defining `<`, the `>` operator was implemented such that it returns `false` if the numbers are equal or `<` is true, and `true` otherwise. Similarly, `<=` and `>=` were defined using `<` and `>`. Specifically, `<=` returns `true` if `>` is false, and `>=` returns `true` if `<` is false.

* Insertion (<<, to print the integer to a stream such as std::cout or a file)
    The `<<` operator and the built-in `print` function were designed to output the value stored in the private `std::string` variable, `input`. When either of these is used, the value of `input` is accessed and printed to the output. This ensures that the string representation of the `bigint` is displayed properly.


* Increment (++, both pre-increment and post-increment) and Decrement (--, both pre-decrement and post-decrement)
    For the `++` operator, it was defined as `+= 1`. Similarly, for the `--` operator, it was defined as `-= 1`. However, since it is not directly possible to subtract an integer from a `bigint`, a temporary `bigint` object with an `input` value of "1" was created. This temporary object was then used with `+=` and `-=` to perform the increment and decrement operations.