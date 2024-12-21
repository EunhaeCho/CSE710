#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <string>
#include <cstdint>

class bigint
{
private:
    // string variable
    std::string input = "0";

public:
    // Default constructor: coordinates are initialized to their default values as specified below
    bigint() {}

    // A constructor that takes a signed 64-bit integer and converts it to an arbitrary-precision integer.
    bigint(const std::int64_t &_y)
    {
        input = std::to_string(_y);
    }

    // A constructor that takes a string of digits and converts it to an arbitrary-precision integer.
    bigint(const std::string &_input) : input(_input)
    {

        // If an input other than "+", "-", or a number is received, throw an error message.
        for (std::int64_t i = 0; i < std::size(_input); i++)
            if (_input[0] != 43 and _input[0] != 45)
                if (_input[i] < 47 or _input[i] > 58)
                    throw not_number;
                else
                    continue;
            else if (i == 0)
                continue;
            else if (_input[i] < 48 or _input[i] > 57)
                throw not_number;

        // If the first character is a "+" or "0", store the remaining characters excluding them.
        for (std::int64_t i = 0; i < std::size(_input); i++)
            if (_input[i] == 43 or _input[i] == 48)
                input = input.erase(0, 1);
            else
                break;
    }

    // Overloaded binary operator +=.
    bigint &operator+=(const bigint &other)
    {
        bigint lhs;
        bigint rhs;
        // Temporal variable for size
        std::int64_t size_small = 0;
        std::int64_t size_large = 0;
        std::int64_t size_tmp_string = 0;
        // Temporal variable for integer
        std::int64_t tmp_integer = 0;
        std::int64_t tmp_sub = 0;
        // Temporal variable for string
        std::string tmp_short = "0";
        std::string tmp_string = "0";
        std::string other_tmp = "0";
        // Temporal variable for char
        char tmp_char1 = '0';
        char tmp_char2 = '0';

        lhs.input = input;
        rhs.input = other.input;

        // For same sign
        if ((other.input[0] == '-' and input[0] == '-') or (other.input[0] != '-' and input[0] != '-'))
        {
            if (lhs.input[0] == '-')
            {
                // If they have negative signs, erase them.
                input = input.erase(0, 1);
                other_tmp = other_tmp.erase(0, 1);
            }

            // Compare the string size and save it to size_small and size_large
            if (std::size(input) < other.get_size())
            {
                tmp_short = input;
                input = other.input;
            }

            else
            {
                tmp_short = other.input;
            }

            size_small = std::size(tmp_short);
            size_large = std::size(input);

            // Add each char of the last string.
            for (std::int64_t i = 0; i < size_small; ++i)
            {
                tmp_char1 = input[size_large - 1 - i];
                tmp_char2 = tmp_short[size_small - 1 - i];
                tmp_string = std::to_string(tmp_char1 - '0' + tmp_char2 - '0' + tmp_integer);
                size_tmp_string = std::size(tmp_string);
                input.replace(size_large - 1 - i, 1, std::string(1, tmp_string[size_tmp_string - 1]));
                if (size_tmp_string == 2)
                    tmp_integer = 1;
                else if (size_tmp_string == 1)
                    tmp_integer = 0;
                if (i == size_small - 1)
                {
                    if (tmp_integer == 1)
                    {
                        if (size_small == size_large)
                        {
                            input.replace(size_large - 1 - i, 1, tmp_string);
                        }
                        else
                        {
                            tmp_char1 = input[size_large - 2 - i];
                            tmp_string = std::to_string(tmp_char1 - '0' + tmp_integer);
                            size_tmp_string = std::size(tmp_string);
                            input.replace(size_large - 2 - i, 1, std::string(1, tmp_string[size_tmp_string - 1]));
                        }
                    }
                }
            }
            if (lhs.input[0] == '-')
            {
                input = '-' + input;
            }
        }
        else
        {
            if (rhs.input[0] == '-')
            {
                rhs.input = rhs.input.erase(0, 1);
                lhs -= rhs;
                input = lhs.input;
            }
            else
            {
                lhs.input = lhs.input.erase(0, 1);
                rhs -= lhs;
                input = rhs.input;
            }
        }

        return *this;
    }

    // Overloaded binary operator -=.
    bigint &operator-=(const bigint &other)
    {
        bigint lhs;
        bigint rhs;

        lhs.input = input;
        rhs.input = other.input;
        // Temporal variable for size
        std::int64_t size_small = 0;
        std::int64_t size_large = 0;
        std::int64_t size_tmp_string = 0;
        // Temporal variable for integer
        std::int64_t tmp_integer = 0;
        std::int64_t tmp_sub = 0;
        // Temporal variable for string
        std::string tmp_short = "0";
        std::string tmp_string = "0";
        std::string other_tmp = "0";
        // Temporal variable for char
        char tmp_char1 = '0';
        char tmp_char2 = '0';

        if ((other.input[0] == '-' and input[0] == '-') or (other.input[0] != '-' and input[0] != '-'))
        {
            if (lhs.input[0] == '-')
            {
                // If they have negative signs, erase them.
                input = input.erase(0, 1);
                other_tmp = other_tmp.erase(0, 1);
            }
            // Compare the string size and save it to size_small and size_large
            if (std::size(input) < other.get_size())
            {
                tmp_short = input;
                input = other.input;
            }
            else
            {
                tmp_short = other.input;
            }

            size_small = std::size(tmp_short);
            size_large = std::size(input);

            // Substract each char of the last string.
            for (std::int64_t i = 0; i < size_small; ++i)
            {
                tmp_char1 = input[size_large - 1 - i];
                tmp_char2 = tmp_short[size_small - 1 - i];
                tmp_sub = (tmp_char1 - '0') - (tmp_char2 - '0') - tmp_integer;
                if (tmp_sub < 0)
                {
                    tmp_integer = 1;
                }
                else
                {
                    tmp_integer = 0;
                }
                tmp_string = std::to_string(tmp_sub + tmp_integer * 10);
                size_tmp_string = std::size(tmp_string);
                input.replace(size_large - 1 - i, 1, std::string(1, tmp_string[size_tmp_string - 1]));
                if (i == size_small - 1 and tmp_integer == 1)
                {
                    input.replace(size_large - 2 - i, 1, std::string(1, input[size_large - 2 - i] - 1));
                }
            }
            if (lhs.input[0] == '-')
            {
                input = '-' + input;
            }
        }
        else
        {
            if (rhs.input[0] == '-')
            {
                rhs.input = rhs.input.erase(0, 1);
                lhs += rhs;
                input = lhs.input;
            }
            else
            {
                lhs.input = lhs.input.erase(0, 1);
                rhs += lhs;
                input = '-' + rhs.input;
            }
        }
        return *this;
    }

    // Overloaded binary operator *= to multiply bigint.
    bigint &operator*=(const bigint other)
    {
        bigint lhs;
        bigint rhs;

        lhs.input = input;
        rhs.input = other.input;
        // Temporal variable for size
        std::int64_t size_other = 0;
        std::int64_t size_input = 0;
        // Temporal variable for integer
        std::int64_t tmp_integer = 0;
        std::int64_t tmp_mul = 0;
        // Temporal variable for string
        std::string input_tmp = input;
        std::string other_tmp = other.input;
        std::string tmp_0 = "0";
        bigint tmp_short = 0;
        bigint tmp_ans = 0;
        // Temporal variable for char
        char tmp_char0 = '0';
        char tmp_char1 = '0';
        char tmp_char2 = '0';

        // When input and other have same signs.

        if (lhs.input[0] == '-')
        {
            // If they have negative signs, erase them.
            input_tmp = input.erase(0, 1);
            if (rhs.input[0] == '-')
                other_tmp = other_tmp.erase(0, 1);
        }
        size_other = std::size(other_tmp);
        size_input = std::size(input_tmp);
        for (std::int64_t i = 0; i < size_input; ++i)
        {
            tmp_integer = 0;
            tmp_short = other_tmp;
            for (std::int64_t j = 0; j < size_other; ++j)
            {
                tmp_char1 = other.input[size_other - 1 - j];
                tmp_char2 = input_tmp[size_input - 1 - i];
                tmp_mul = (tmp_char1 - '0') * (tmp_char2 - '0') + tmp_integer;
                if (tmp_mul > 10)
                {
                    tmp_integer = tmp_mul / 10;
                    tmp_char0 = std::to_string(tmp_mul)[1];
                }
                else
                {
                    tmp_integer = 0;
                    tmp_char0 = std::to_string(tmp_mul)[0];
                }
                tmp_short.input[size_other - 1 - j] = tmp_char0;

                if (j == std::size(other_tmp) - 1 and tmp_integer != 0)
                    tmp_short.input = std::to_string(tmp_integer) + tmp_short.input;
            }

            if (i == 0)
            {
                tmp_ans = tmp_short;
            }
            else
            {
                tmp_0 = "";
                for (std::int64_t n = 0; n < i; n++)
                {
                    tmp_0 = tmp_0 + "0";
                }

                tmp_short.input = tmp_short.input + tmp_0;
                tmp_ans += tmp_short;
            }
        }
        input_tmp = tmp_ans.input;
        if (lhs.input[0] == '-' and rhs.input[0] != '-')
            input_tmp = '-' + input_tmp;
        else if (lhs.input[0] != '-' and rhs.input[0] == '-')
            input_tmp = '-' + input_tmp;

        input = input_tmp;
        return *this;
    }

    // Member function to obtain (but not modify) the size of bigint.
    int64_t get_size() const
    {
        return std::size(input);
    }

    // Prints the coordinates of the point as a tuple
    void print()
    {
        std::cout << input << "\n";
    }

    // Overloaded binary operator << to easily print out a bigint to a stream.
    friend std::ostream &operator<<(std::ostream &out, const bigint &rhs)
    {
        out << rhs.input;
        return out;
    }

    // Overloaded unary operator - to take the negative of a bigint.
    friend bigint operator-(bigint other)
    {
        if (other.input[0] == '-')
        {
            other.input = other.input.erase(0, 1);
        }
        else
        {
            other.input = '-' + other.input;
        }
        return other;
    }

    // Overloaded binary operator == to compare two bigints.
    friend bool operator==(const bigint &lhs, const bigint &rhs)
    {
        if (lhs.input != rhs.input)
        {
            return false;
        }
        return true;
    }

    // Overloaded binary operator != to compare two bigints.
    friend bool operator!=(const bigint &lhs, const bigint &rhs)
    {
        return !(lhs == rhs);
    }

    // Overloaded binary operator > to compare two bigints.
    friend bool operator>(const bigint &lhs, const bigint &rhs)
    {
        if (lhs == rhs or (lhs.input[0] == '-' and rhs.input[0] != '-'))
        {
            return false;
        }
        else if (lhs.input[0] != '-' and rhs.input[0] != '-')
        {
            if (lhs.get_size() > rhs.get_size())
            {
                return true;
            }
            else if (lhs.get_size() < rhs.get_size())
            {
                return false;
            }
            else
            {
                for (std::int64_t i = 0; i < lhs.get_size(); ++i)
                {
                    if (lhs.input[i] > rhs.input[i])
                    {
                        return true;
                    }
                    else if (lhs.input[i] < rhs.input[i])
                    {
                        return false;
                    }
                    else
                        continue;
                }
            }
        }
        else if (lhs.input[0] == '-' and rhs.input[0] == '-')
        {
            if (lhs.get_size() > rhs.get_size())
            {
                return false;
            }
            else if (lhs.get_size() < rhs.get_size())
            {
                return true;
            }
            else
            {
                for (std::int64_t i = 0; i < lhs.get_size(); ++i)
                {
                    if (lhs.input[i] > rhs.input[i])
                    {
                        return false;
                    }
                    else if (lhs.input[i] < rhs.input[i])
                    {
                        return true;
                    }
                    else
                        continue;
                }
            }
        }
        else if (lhs.input[0] == '-' and rhs.input[0] != '-')
        {
            return false;
        }
        return true;
    }

    // Overloaded binary operator < to compare two bigints.
    friend bool operator<(const bigint &lhs, const bigint &rhs)
    {
        if (lhs == rhs or lhs > rhs)
        {
            return false;
        }
        return true;
    }

    // Overloaded binary operator >= to compare two bigints.
    friend bool operator>=(const bigint &lhs, const bigint &rhs)
    {
        if (lhs < rhs)
        {
            return false;
        }
        return true;
    }

    // Overloaded binary operator <= to compare two bigints.
    friend bool operator<=(const bigint &lhs, const bigint &rhs)
    {
        if (lhs > rhs)
        {
            return false;
        }
        return true;
    }

    // Overloaded binary operator ++ to add two bigint.
    bigint
    operator++()
    {
        bigint output = input;
        bigint tmp_bigint = 1;
        output += tmp_bigint;
        input = output.input;
        return *this;
    }

    // Overloaded binary operator -- to add two bigint.
    bigint operator--()
    {
        bigint output = input;
        bigint tmp_bigint = 1;
        output -= tmp_bigint;
        input = output.input;
        return *this;
    }

    // Exception to be thrown if the number of rows or columns given to the constructor is zero.
    inline static std::invalid_argument not_number = std::invalid_argument("Integer cannot contain characters other than digits!");
};

// Overloaded binary operator + to add two bigint.
bigint operator+(bigint lhs, const bigint &rhs)
{
    lhs += rhs;
    return lhs;
}

// Overloaded binary operator - to add two bigint.
bigint operator-(bigint lhs, const bigint &rhs)
{
    lhs -= rhs;
    return lhs;
}

// Overloaded binary operator * to add two bigint.
bigint operator*(bigint lhs, const bigint &rhs)
{
    lhs *= rhs;
    return lhs;
}