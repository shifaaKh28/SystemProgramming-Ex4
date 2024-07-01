//shifaakhatib28@gmail.com
#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>

/**
 * @class Complex
 * @brief A class to represent complex numbers.
 *
 * This class is used to represent complex numbers and provides basic arithmetic operations.
 */
class Complex {
private:
    double re; ///< The real part of the complex number.
    double im; ///< The imaginary part of the complex number.

public:
    /**
     * @brief Constructs a Complex number with given real and imaginary parts.
     *
     * @param r The real part.
     * @param i The imaginary part.
     */
    Complex(double r = 0, double i = 0);

    /**
     * @brief Checks equality of two complex numbers.
     *
     * @param other The complex number to compare.
     * @return True if the complex numbers are equal, otherwise false.
     */
    bool operator==(const Complex &other) const;

    /**
     * @brief Checks inequality of two complex numbers.
     *
     * @param other The complex number to compare.
     * @return True if the complex numbers are not equal, otherwise false.
     */
    bool operator!=(const Complex &other) const;

    /**
     * @brief Less than operator for complex numbers.
     *
     * @param other The complex number to compare.
     * @return True if this complex number is less than the other, otherwise false.
     */
    bool operator<(const Complex &other) const;

    /**
     * @brief Greater than operator for complex numbers.
     *
     * @param other The complex number to compare.
     * @return True if this complex number is greater than the other, otherwise false.
     */
    bool operator>(const Complex &other) const;

    /**
     * @brief Outputs a complex number to an output stream.
     *
     * @param os The output stream.
     * @param c The complex number to output.
     * @return The output stream.
     */
    friend std::ostream& operator<<(std::ostream &os, const Complex &c);

    /**
     * @brief Returns the real part of the complex number.
     *
     * @return The real part.
     */
    double get_re() const;

    /**
     * @brief Returns the imaginary part of the complex number.
     *
     * @return The imaginary part.
     */
    double get_im() const;
};

#endif // COMPLEX_HPP
