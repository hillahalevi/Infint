//
// Created by hilla on 11/6/18.
//

#include "LargeIntegers.h"
#include <vector>
#include <iostream>
#include <map>
#include <complex>
#include <algorithm>

using namespace std;

//Constructors
/**
 * Default Constructor
 */
InfInt::InfInt() {
    positive = true;
    base = deafultBase;
    infnum.push_back(0);
}

/**
 * Long Constructor
 */
InfInt::InfInt(long int num) {
    base = deafultBase;
    if (num < 0) {
        positive = false;
        num *= -1;
    } else {
        positive = true;
    }
/*
 * arrange the vector in a way that that the less positiveificant numbers
 * are first and the most positiveificant are at the back
 * so we can do actions more easily
 */if (num == 0) {
        infnum.push_back(0);
        return;
    }
    while (num) {
        infnum.push_back((int) (num % base));
        num /= base;
    }
}


/**
 * string contructor
 * @param bignum
 */
InfInt::InfInt(string bignum) {
    long size = bignum.length();

    base = deafultBase;
    positive = (bignum[0] != '-');
/*
 * arrange the vector in a way that that the less positiveificant numbers
 * are first and the most positiveificant are at the back
 * so we can do actions more easily
 */
    while (true) {
        if (size <= 0) break;
        if (!positive && size <= 1) break;

        int length = 0;
        int num = 0;
        int prefix = 1;
        for (int i(size - 1); i >= 0 && i >= size - 9; --i) {
            if (bignum[i] < '0' || bignum[i] > '9') {
                //validation check
                if (i == 0 && bignum[i] == '-') { continue; }
                cout << "not a valid number!" << endl;
                return;
            }
            //give it the place it needs
            num += (bignum[i] - '0') * prefix;
            prefix *= 10;
            ++length;
        }
        infnum.push_back(num);
        size -= length;
    }

}

/**
 * num contructor
 * @param num
 */
InfInt::InfInt(long long num) {
    base = deafultBase;
    if (num < 0) {
        positive = false;
        num *= -1;
    } else {
        positive = true;
    }
/*
 * arrange the vector in a way that that the less positiveificant numbers
 * are first and the most positiveificant are at the back
 * so we can do actions more easily
 */if (num == 0) {
        infnum.push_back(0);
        return;
    }
    while (num) {
        infnum.push_back((int) (num % base));
        num /= base;
    }

}

/**
 * num contructor
 * @param num
 */
InfInt::InfInt(int num) {
    base = deafultBase;
    if (num < 0) {
        positive = false;
        num *= -1;
    } else {
        positive = true;
    }
    infnum.push_back(num);


}

/**
 * char* contructor
 * @param num
 */
InfInt::InfInt(const char *str) {
    string bignum = (string) str;
    long size = bignum.length();

    base = deafultBase;
    positive = (bignum[0] != '-');
/*
 * arrange the vector in a way that that the less positiveificant numbers
 * are first and the most positiveificant are at the back
 * so we can do actions more easily
 */
    while (true) {
        if (size <= 0) break;
        if (!positive && size <= 1) break;

        int length = 0;
        int num = 0;
        int prefix = 1;
        for (int i(size - 1); i >= 0 && i >= size - 9; --i) {
            if (bignum[i] < '0' || bignum[i] > '9') {
                //validation check
                if (i == 0 && bignum[i] == '-') { continue; }
                cout << "not a valid number!" << endl;
                return;
            }
            //give it the place it needs
            num += (bignum[i] - '0') * prefix;
            prefix *= 10;
            ++length;
        }
        infnum.push_back(num);
        size -= length;
    }

}



//Add
/**
 * helper function for proper addition .
 * important:the numbers should have the same positive,the leading number should be
 * bigger then other--> *this| >= |other|
 * @param other
 */
void InfInt::help_add(const InfInt &other) {
    for (int i = 0, carry = 0;
         i < (int) max(infnum.size(), other.infnum.size()) || carry; ++i) {
        if (i == (int) infnum.size()) {
            //end of number ..add zero before so we can keep adding
            infnum.push_back(0);
        }

        infnum[i] +=
                carry + (i < (int) other.infnum.size() ? other.infnum[i] : 0);
        carry = infnum[i] >= base;
        if (carry) infnum[i] -= base;
    }
}

/**
 * add numbers and returns the result
 * @param other infint
 * @return infint
 */
InfInt InfInt::operator+(InfInt const &other) {
    InfInt c;
    if (*this >= other) {
        c = *this;
        c += other;
    } else {
        c = other;
        c += *this;
    }
    return c;
}

/**
 * iterate threw the Infint (repesented as vector) and implements
 * an adding function
 * @param other Infint number
 * @return our Infint number after the addition of other.
 */

InfInt &InfInt::operator+=(InfInt const &other) {
    if (other.positive != this->positive) {
        //the numbers  have different positive - send it to minus
        if (*this < other) {
            //a<b -a+b -->b-a
            InfInt temp = *this;
            *this = other;
            //this=other-|this|
            *this -= -temp;


        } else { *this -= -other; }

    } else if (compareAbs(other) < 0) {
        //always make sure to add the small to the big
        InfInt temp = *this;
        *this = other;
        help_add(temp);
    } else {
        help_add(other);
    }

    return *this;


}

/**
 * prefix increment--> ++x
 * @return our number after adding 1
 */
InfInt &InfInt::operator++() {
    *this += (1);
    return *this;
}

/**
 * postfix increment - return the number and add 1--> x++
 * @return our original number
 */
InfInt InfInt::operator++(int) {
    //temp to remember the initial value
    InfInt res = *this;
    //increment the number
    operator++();
    //return the number before
    return res;
}




//Subtraction
/**
 * subtract numbers and returns the result
 * @param other infint
 * @return infint
 */
InfInt InfInt::operator-(InfInt const &other) const {
    InfInt c = *this;
    c -= other;
    return c;
}

/**
 * helper function for proper subtraction .
 * important:the numbers should have the same positive,the leading number should be
 * bigger then other--> *this| >= |other|
 * @param other
 */
void InfInt::help_sub(const InfInt &other) {
    for (int i = 0, carry = 0; (i < (int) other.infnum.size()) || carry; ++i) {
        infnum[i] -=
                carry + (i < (int) other.infnum.size() ? other.infnum[i] : 0);
        carry = infnum[i] < 0;
        if (carry) infnum[i] += base;
    }
    //remove unwanted zeroes
    this->normalize();
}

/**
 * iterate threw the Infint (repesented as vector) and implements
 * a subtraction function
 * @param other Infint number
 * @return our Infint number after the subtraction of other.
 */
InfInt &InfInt::operator-=(InfInt const &other) {
    if (*this == other) {
        //a-a =0
        this->positive = true;
        this->infnum.clear();
        this->infnum.push_back(0);
        return *this;
    }
    if (positive && other.positive) {
        if (*this > other) {
            help_sub(other);
        } else {
            //a<b a-b = -(b-a)
            InfInt temp = *this;
            *this = other;
            help_sub(temp);
            *this = -*this;
        }
    } else {
        //change the positive -implement the minus and move it to plus
        *this += -(other);
    }
    return *this;


}

/**
 * prefix subtraction--> --x
 * @return our number after subtracting 1
 */
InfInt &InfInt::operator--() {
    *this -= (1);
    return *this;
}

/**
 * postfix subtraction - return the number and subtract 1--> x--
 * @return our original number
 */
InfInt InfInt::operator--(int) {
    //temp to remember the initial value
    InfInt res = *this;
    //increment the number
    operator--();
    //return the number before
    return res;
}

/**
 * takes a number and returns its value with different sign.
 * @return  Infinit number
 */
InfInt InfInt::operator-() const {
    InfInt res = *this;
    if (this->infnum.size() == 1 && this->infnum[0] == 0) { return res; }
    res.positive = !(this->positive);
    return res;

}



//Multiplication
/**
 * multiply numbers and update the result
 * @param other infint
 * @return infint
 */
InfInt &InfInt::operator*=(InfInt const &other) {
    *this = *this * other;
    return *this;
}

/**
 * multiply numbers in most efficant way and returns the result
 * @param other infint
 * @return infint
 */
InfInt InfInt::operator*(InfInt const &other) const {
    if (other.isZero() || this->isZero()) { return InfInt("0"); }
    if (infnum.size() * other.infnum.size() <= 1000111) {
        //simple mul - small numbers
        return help_mul_s(other);
    }
    if (infnum.size() > 500111 || other.infnum.size() > 500111) {
        //complex - big numbers
        return mul_fft(other);
    }
    //middle
    return mul_karatsuba(other);

}

/**
 * simple  school based multiplication
 * @param other
 * @return
 */
InfInt InfInt::help_mul_s(InfInt const &other) const {
    InfInt final;
    //total positive
    final.positive = !(positive ^ other.positive);
    //save us some reallocation
    final.infnum.resize(infnum.size() + other.infnum.size());
    for (int i = 0; i < (int) infnum.size(); ++i)
        if (infnum[i])
            for (int j = 0, carry = 0; j < (int) other.infnum.size() || carry; ++j) {
                long long add = (long long) infnum[i] * (j < (int) other.infnum.size() ? other.infnum[j] : 0);
                long long cur = final.infnum[i + j] + add + carry;
                carry = (int) (cur / base);
                final.infnum[i + j] = (int) (cur % base);
            }
    final.normalize();
    return final;
}

/**
 * fft muliplication web
 * @param other  to multiply
 * @return Infint
 */
InfInt InfInt::mul_fft(const InfInt &other) const {
    InfInt final;
    final.positive = !(positive ^ other.positive);
    help_mul_fft(convert_base(infnum, BASE_DIGITS, 3), convert_base(other.infnum, BASE_DIGITS, 3), final.infnum);
    final.infnum = convert_base(final.infnum, 3, BASE_DIGITS);
    final.normalize();
    return final;
}

/**
 * karatsuba Multiply web
 * @param other to multiply with
 * @return Infint
 */
InfInt InfInt::mul_karatsuba(const InfInt &other) const {
    vector<int> a6 = convert_base(this->infnum, BASE_DIGITS, 6);
    vector<int> b6 = convert_base(other.infnum, BASE_DIGITS, 6);
    vll a(a6.begin(), a6.end());
    vll b(b6.begin(), b6.end());
    while (a.size() < b.size())
        a.push_back(0);
    while (b.size() < a.size())
        b.push_back(0);
    while (a.size() & (a.size() - 1))
        a.push_back(0), b.push_back(0);
    vll c = karatsubaMultiply(a, b);
    InfInt final;
    final.positive = !(positive ^ other.positive);
    long long carry = 0;
    for (int i = 0; i < (int) c.size(); i++) {
        long long cur = c[i] + carry;
        final.infnum.push_back((int) (cur % 1000000));
        carry = cur / 1000000;
    }
    final.infnum = convert_base(final.infnum, 6, BASE_DIGITS);
    final.normalize();
    return final;
}


/**
 * help division - abs
 * @param denominator
 * @param numerator
 * @return pair of Infint
 */
pair<InfInt, InfInt> help_div(const InfInt &a1, const InfInt &b1) {
    long long norm = deafultBase / (b1.infnum.back() + 1);
    InfInt a = a1.abs() * norm;
    InfInt b = b1.abs() * norm;
    InfInt q = 0, r = 0;
    q.infnum.resize(a.infnum.size());

    for (int i = a.infnum.size() - 1; i >= 0; i--) {
        r *= deafultBase;
        r += a.infnum[i];
        long long s1 = r.infnum.size() <= b.infnum.size() ? 0 : r.infnum[b.infnum.size()];
        long long s2 = r.infnum.size() <= b.infnum.size() - 1 ? 0 : r.infnum[b.infnum.size() - 1];
        long long d = ((long long) deafultBase * s1 + s2) / b.infnum.back();
        r -= b * d;
        while (r < 0) {
            r += b, --d;
        }
        q.infnum[i] = d;
    }

    q.positive = !(a1.positive ^ b1.positive);
    r.positive = a1.positive;
    q.normalize();
    r.normalize();
    pair<InfInt, InfInt> res;
    res = make_pair(q, r / norm);
    if (res.second < 0) res.second += b1;
    return res;
}

/**
 * divide numbers and returns the result
 * @param other infint
 * @return infint
 */
InfInt InfInt::operator/(const InfInt &other) const {
    if (other.isZero()) { throw "division in zero is a big no no"; }
    return help_div(*this, other).first;
}

/**
 * divide numbers and returns the result
 * @param other int
 * @return infint
 */
InfInt InfInt::operator/(int other) const {
    if (other == 0) { throw "division in zero is a big no no"; }

    if (llabs(other) >= deafultBase) {
        return *this / InfInt(other);
    }
    InfInt res = *this;
    res /= other;
    return res;
}

/**
 * divide numbers and update the result
 * @param other int
 * @return infint
 */
InfInt &InfInt::operator/=(int other) {
    if (other == 0) { throw "division in zero is a big no no"; }
    if (llabs(other) >= deafultBase) {
        *this /= InfInt(other);
        return *this;
    }
    if (other < 0)
        positive = !positive, other = -other;
    for (int i = (int) infnum.size() - 1, rem = 0; i >= 0; --i) {
        long long cur = infnum[i] + rem * (long long) deafultBase;
        infnum[i] = (int) (cur / other);
        rem = (int) (cur % other);
    }
    normalize();
    return *this;
}


/**
 * divide numbers and update the result
 * @param other infint
 * @return infint
 */
InfInt &InfInt::operator/=(const InfInt &other) {
    if (other.isZero()) { throw "division in zero is a big no no"; }
    *this = *this / other;
    return *this;
}


/**
 * divide numbers and returns the leftover
 * @param other infint
 * @return infint
 */
InfInt InfInt::operator%(const InfInt &other) const {
    if (other.isZero()) { throw "division in zero is a big no no"; }
    if (other > 0) {
        if (*this < 0) {
            return -(help_div(this->abs(), other).second);
        }
        return help_div(*this, other).second;
    }
    return *this;
}


/**
 * divide numbers and returns the leftover
 * @param other longlong
 * @return infint
 */
long long InfInt::operator%(long long other) const {
    if (other == 0) { throw "division in zero is a big no no"; }
    if (other > 0) { // not well-defined for other<= 0.

        long long m = 0;
        for (int i = (int) infnum.size() - 1; i >= 0; --i) {
            m = (infnum[i] + m * (long long) deafultBase) % other;
        }
        if (!positive) { return m * -1; }
        return m;
    }
}




//compare
/**
* this function compares 2 infints only by their absolute value(not positive)
* @param other infint to cpompare with
* @return -1 if less 0 if same 1 if more
*/
int InfInt::compareAbs(InfInt const &other) const {
    //other is longer --> bigger--> return less -->-1
    if (this->infnum.size() < other.infnum.size()) return -1;
    // I am longer -->   bigger --> return more -->1
    if (this->infnum.size() > other.infnum.size()) return 1;
    /**
     * same length iterate threw them and compare locally
     */
    for (size_t i(this->infnum.size()); i > 0; --i) {
        if (this->infnum[i - 1] < other.infnum[i - 1]) return -1;
        if (this->infnum[i - 1] > other.infnum[i - 1]) return 1;
    }
    //same same (only by value !)
    return 0;

}


/**
 * returns true if our infint is smaller than the other
 * @param other  infint
 * @return true||false
 */
bool InfInt::operator<(InfInt const &other) const {
    if (this->positive && other.positive) {
        //both positive determinate only by their value.
        return compareAbs(other) == -1;
    }
    if (!this->positive && !other.positive) {
        //both negative the bigger the value the smaller it gets.
        return compareAbs(other) == 1;
    }
    return !this->positive;

}

/**
 * returns true if our infint is smaller or same than the other
 * @param other  infint
 * @return true||false
 */
bool InfInt::operator<=(const InfInt &other) const {
    if (*this == other) {
        //same value  same positive --> =
        return true;

    }
    return *this < other;
}


/**
 * returns true if our infint is bigger than the other
 * @param other infint
 * @return true||false
 */
bool InfInt::operator>(const InfInt &other) const {
    if (*this == other) {
        //same same -->
        return false;
    }
    bool small = *this < other;
    return !(small);
}


/**
 * returns true if our infint is bigger or same than the other
 * @param other  infint
 * @return true||false
 */
bool InfInt::operator>=(const InfInt &other) const {
    if (*this == other) {
        //same value  same positive --> =
        return true;

    }
    return *this > other;
}


/**
 * checks of two numbers are the same
 * @param other infint
 * @return true or false
 */
bool InfInt::operator==(InfInt const &other) const {

    return (compareAbs(other) == 0) && (this->positive == other.positive);
}


/**
 * checks of two numbers are the different
 * @param other infint
 * @return true or false
 */
bool InfInt::operator!=(InfInt const &other) const {
    return !(*this == other);
}


//Input&Output
/**
 * <<
 * @param out
 * @param other
 * @return
 */
std::ostream &operator<<(std::ostream &out, InfInt const &other) {
    if (!other.infnum.size()) return out << 0;
    int i = other.infnum.size() - 1;
    for (; i >= 0 && other.infnum[i] == 0; --i);

    if (i == -1) return out << 0;
    if (!other.positive) out << '-';

    std::vector<int>::const_reverse_iterator it =
            other.infnum.rbegin() + (other.infnum.size() - i - 1);

    out << *it++;
    for (; it != other.infnum.rend(); ++it) {
        for (int i(0), len = other.segment_length(*it); i < 9 - len; ++i)
            out << '0';
        if (*it) out << *it;
    }

    return out;
}


/**
 *>>
 * @param in
 * @param a
 * @return
 */
std::istream &operator>>(std::istream &in, InfInt &a) {
    string str;
    in >> str;

    a = str;

    return in;
}



//bit crap

/**
 * xor
 * @param other
 * @return Infint
 */
InfInt InfInt::operator^(const InfInt &other) const {
    return gated(other, '^');
}

/**
 * AND
 * @param other
 * @return infint
 */
InfInt InfInt::operator&(const InfInt &other) const {
    return gated(other, '&');
}

/***
 * AND
 * @return this updated
 */
InfInt &InfInt::operator&=(const InfInt &other) {
    *this = *this & other;
    return *this;
}

/**
 * OR
 * @param other
 * @return  infint
 */
InfInt InfInt::operator|(const InfInt &other) const {
    return gated(other, '|');
}

/**
 * return Infint afte bit manipulation
 * @param other
 * @param c
 * @return Infint
 */
InfInt InfInt::gated(const InfInt &other, char c) const {
    string a = this->to_binary();
    string b = other.to_binary();
    match_length(a, b);
    string final;
    for (int i = 0; i < a.length(); i++) {
        if (c == '^') { final += (((a[i] - '0') ^ (b[i]) - '0') + '0'); }
        else if (c == '&') { final += (((a[i] - '0') & (b[i]) - '0') + '0'); }
        else if (c == '|') { final += (((a[i] - '0') | (b[i]) - '0') + '0'); }

    }
    string dec_final = to_decimal(final);
    InfInt finalInf = InfInt(dec_final);
    if (c == '^') { finalInf.positive = !(positive ^ other.positive); }
    else if (c == '&') { finalInf.positive = positive & other.positive; }
    else if (c == '|') { finalInf.positive = positive | other.positive; }
    if (finalInf.isZero()) { finalInf.positive = true; }
    return finalInf;

}


/**s
 * shift
 * @param x
 * @return
 */
InfInt InfInt::operator<<(long x) const {
    if (isZero()) { return *this; }
    if (x < 0) { return *this >> x; }
    string f = this->to_binary();
    while (x > 0) {
        f += '0';
        x--;
    }
    InfInt shifted(to_decimal(f));
    shifted.positive = this->positive;
    return shifted;
}


/**
 * shift
 * @param x
 * @return
 */
InfInt InfInt::operator>>(long x) const {
    if (isZero()) { return *this; }
    if (x < 0) { return *this << x; }
    string f = this->to_binary();
    while (x > 0) {
        f.erase(f.length() - 1);
        f.insert(0, 1, '0');
        x--;
    }
    f = clearzero(f);
    if (f.empty() || f == "0") {
        return InfInt();
    }
    InfInt shifted(to_decimal(f));
    shifted.positive = this->positive;
    return shifted;
}


/**
 * shift
 * @param x
 * @return
 */
InfInt &InfInt::operator>>=(long x) {
    *this = *this >> x;
    return *this;
}


/**
 * int() conversion
 * @return int
 */
InfInt::operator int() const {
    string f = this->to_binary();
    if (f.size() > 32) {
        f = f.substr(f.length() - 31, f.length());
        f = clearzero(f);

    }
    string x = to_decimal(f);
    int final = atoi(x.c_str());
    if (!this->positive) { final = -final; }
    return final;
}



//helpers
/**
 * quick algoritem from the web to switch bases
 *  Convert base 10^old --> 10^new.
 * @param a
 * @param old_digits
 * @param new_digits
 * @return vector<int>
 */
vector<int> InfInt::convert_base(const vector<int> &a, int old_digits, int new_digits) {
    vector<long long> p(max(old_digits, new_digits) + 1);
    p[0] = 1;
    for (int i = 1; i < (int) p.size(); i++)
        p[i] = p[i - 1] * 10;
    vector<int> final;
    long long cur = 0;
    int cur_digits = 0;
    for (int i = 0; i < (int) a.size(); i++) {
        cur += a[i] * p[cur_digits];
        cur_digits += old_digits;
        while (cur_digits >= new_digits) {
            final.push_back((cur % p[new_digits]));
            cur /= p[new_digits];
            cur_digits -= new_digits;
        }
    }
    final.push_back((int) cur);
    while (!final.empty() && !final.back())
        final.pop_back();
    return final;

}


/**
 * applays fft -web
 * @param a  complex vectot
 * @param invert bool
 */
void InfInt::fft(vector<complex> &a, bool invert) const {
    int n = (int) a.size();

    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        for (; j >= bit; bit >>= 1)
            j -= bit;
        j += bit;
        if (i < j)
            swap(a[i], a[j]);

    }
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * 3.14159265358979323846 / len * (invert ? -1 : 1);
        complex wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            complex w(1);
            for (int j = 0; j < len / 2; ++j) {
                complex u = a[i + j];
                complex v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert)
        for (int i = 0; i < n; ++i)
            a[i] /= n;
}


/**
 * fft multiply -web
 * @param a
 * @param b
 * @param res
 */
void InfInt::help_mul_fft(const vector<int> &a, const vector<int> &b, vector<int> &res) const {
    vector<complex> fa(a.begin(), a.end());
    vector<complex> fb(b.begin(), b.end());
    int n = 1;
    while (n < (int) max(a.size(), b.size()))
        n <<= 1;
    n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; ++i)
        fa[i] *= fb[i];
    fft(fa, true);

    res.resize(n);
    long long carry = 0;
    for (int i = 0; i < n; ++i) {
        long long t = (long long) (fa[i].real() + 0.5) + carry;
        carry = t / 1000;
        res[i] = t % 1000;
    }
}


typedef vector<long long> vll;

/**
 * karatsuba Multiply
 * @param a
 * @param b
 * @return
 */
vll InfInt::karatsubaMultiply(const vll &a, const vll &b) {
    long n = a.size();
    vll res(static_cast<unsigned long>(n + n));
    if (n <= 32) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                res[i + j] += a[i] * b[j];
        return res;
    }

    long k = n >> 1;
    vll a1(a.begin(), a.begin() + k);
    vll a2(a.begin() + k, a.end());
    vll b1(b.begin(), b.begin() + k);
    vll b2(b.begin() + k, b.end());

    vll a1b1 = karatsubaMultiply(a1, b1);
    vll a2b2 = karatsubaMultiply(a2, b2);

    for (int i = 0; i < k; i++)
        a2[i] += a1[i];
    for (int i = 0; i < k; i++)
        b2[i] += b1[i];

    vll r = karatsubaMultiply(a2, b2);
    for (int i = 0; i < (int) a1b1.size(); i++)
        r[i] -= a1b1[i];
    for (int i = 0; i < (int) a2b2.size(); i++)
        r[i] -= a2b2[i];

    for (int i = 0; i < (int) r.size(); i++)
        res[i + k] += r[i];
    for (int i = 0; i < (int) a1b1.size(); i++)
        res[i] += a1b1[i];
    for (int i = 0; i < (int) a2b2.size(); i++)
        res[i + n] += a2b2[i];
    return res;
}


/**
 * chaecks if infint is basiclly zaro
 * @return true||false
 */
bool InfInt::isZero() const {
    return infnum.empty() || (infnum.size() == 1 && !infnum[0]);
}


/**
 * returns the absolute form of infint
 * @return Infint
 */
InfInt InfInt::abs() const {
    InfInt a = *this;
    a.positive = true;
    return a;
}


/**
 * remove unneeded zeroes
 */
void InfInt::normalize() {
    while (!infnum.empty() && !infnum.back())
        infnum.pop_back();
    if (infnum.empty()) {
        infnum.push_back(0);
        positive = true;
        return;
    }
}


/**
 * help function to get segment't segment
 * @param segment
 * @return  int
 */
int InfInt::segment_length(int segment) const {
    int length = 0;
    while (segment) {
        segment /= 10;
        ++length;
    }

    return length;
}


/**
 * returns a string form
 * @param value  Infint
 * @return  string
 */
string InfInt::to_string() {
    std::ostringstream stream;
    stream << *this;

    return stream.str();
}


/**
 * binary string to decimal
 * @param binary string
 * @return string
 */
string InfInt::to_decimal(string binary) const {
    string num = binary;
    InfInt final = 0;

    // Initializing base value to 1
    InfInt base = 1;

    long len = num.length();
    for (long i = len - 1; i >= 0; i--) {
        if (num[i] == '1')
            final += base;
        base = base * 2;
    }

    return final.to_string();
}


/**
 * decimal string to binary
 * @param value
 * @return string
 */
string InfInt::to_binary() const {
    if (isZero()) { return "0"; }
    std::string final;
    InfInt value = *this;
    value.positive = true;
    while (!value.isZero()) {
        final = (value % 2 == 0 ? "0" : "1") + final;
        value /= 2;
    }

    return clearzero(final);

}


/**
 * remove unwanted zeroes
 * @param str
 * @return clear binary string
 */
string InfInt::clearzero(string str) const {
    string binary = str;
    while (binary.length() > 1 && binary[0] == '0') {
        binary.erase(0, 1);
    }
    return binary;

}


/**
 * takes to string of bits and add zeroes until they have
 * the same length
 * @param a string
 * @param b string
 */
void InfInt::match_length(string &a, string &b) const {
    while (a.length() > b.length()) {
        b.insert(0, 1, '0');
    }
    while (b.length() > a.length()) {
        a.insert(0, 1, '0');
    }

}


/**
 * allocation
 * @param a
 * @return  this
 */
InfInt &InfInt::operator=(const long long &a) {
    infnum.clear();
    long long t = a;
    do {
        infnum.push_back((int) (t % base));
        t /= base;
    } while (t != 0);

    return *this;
}




















