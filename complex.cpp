//shifaakhatib28@gmail.com
#include "complex.hpp"

/**
 * @brief Constructs a Complex number with given real and imaginary parts.
 *
 * @param r The real part.
 * @param i The imaginary part.
 */
Complex::Complex(double r, double i) : re(r), im(i) {}


bool Complex::operator==(const Complex &other) const {
    return re == other.re && im == other.im;
}


bool Complex::operator!=(const Complex &other) const {
    return !(*this == other);
}


bool Complex::operator<(const Complex &other) const {
    if (re == other.re) {
        return im < other.im;
    }
    return re < other.re;
}


bool Complex::operator>(const Complex &other) const {
    if (re == other.re) {
        return im > other.im;
    }
    return re > other.re;
}

/**
 * @brief Outputs a complex number to an output stream.
 *
 * @param os The output stream.
 * @param c The complex number to output.
 * @return The output stream.
 */
std::ostream& operator<<(std::ostream &os, const Complex &c) {
    os << " " << c.re << " + " << c.im << "i ";
    return os;
}


double Complex::get_re() const {
    return re;
}


double Complex::get_im() const {
    return im;
}
