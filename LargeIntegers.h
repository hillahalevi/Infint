//
// Created by hilla on 11/6/18.
//

#ifndef INFINT_INFINT_H
#define INFINT_INFINT_H

#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <complex>

using namespace std;
static const int deafultBase = 1000000000;

class InfInt {
    std::vector<int> infnum;
    bool positive;
    int base;
    int BASE_DIGITS = 9;

public:
    //Constructors
    InfInt();

    InfInt(int other);

    InfInt(string num);

    InfInt(const char* str);

    InfInt(long int num);

    InfInt(long long num);


    //Adding


    InfInt operator+(InfInt const &other);

    InfInt &operator+=(InfInt const &other);

    InfInt &operator++();

    InfInt operator++(int);


    //Subtraction
    InfInt operator-(InfInt const &) const;


    InfInt &operator-=(InfInt const &);

    InfInt &operator--();

    InfInt operator--(int);

    InfInt operator-() const;

    //Multiplication
    InfInt operator*(InfInt const &other) const;

    InfInt &operator*=(InfInt const &other);

    //Division
    InfInt operator/(InfInt const &other) const;

    InfInt &operator/=(InfInt const &other);

    InfInt &operator/=(int other);

    InfInt operator%(InfInt const &other) const;

    long long operator%(long long v) const;

    friend pair<InfInt, InfInt> help_div(const InfInt &denominator, const InfInt &numerator);

    InfInt operator/(int other) const;


    //Input&Output
    friend std::istream &operator>>(std::istream &, InfInt &);

    friend std::ostream &operator<<(std::ostream &, InfInt const &);


    //Compare
    bool operator<(const InfInt &) const;

    bool operator>(const InfInt &) const;

    bool operator<=(const InfInt &) const;

    bool operator>=(const InfInt &) const;

    bool operator==(const InfInt &) const;

    bool operator!=(const InfInt &) const;

    //bit crap
    InfInt operator^(const InfInt &) const;

    InfInt operator&(const InfInt &) const;

    InfInt &operator&=(const InfInt &);

    InfInt operator|(const InfInt &) const;

    InfInt gated(const InfInt &other,char c)const ;

    InfInt operator<<(long x)const ;

    InfInt operator>>(long x)const ;

    InfInt&operator>>=(long x);

    explicit operator int()const ;

    //Allocation
    InfInt &operator=(const long long &a);


    //help all
    int segment_length(int) const;

    void help_add(const InfInt &other);

    void help_sub(const InfInt &other);

    InfInt help_mul_s(InfInt const &) const;

    InfInt mul_fft(InfInt const &) const;

    typedef std::complex<long double> complex;

    void fft(vector<complex> &a, bool invert) const;

    static vector<int> convert_base(const vector<int> &a, int old_digits, int new_digits);

    void help_mul_fft(const vector<int> &a, const vector<int> &b, vector<int> &res) const;

    typedef vector<long long> vll;

    InfInt mul_karatsuba(const InfInt &other) const;

    static vll karatsubaMultiply(const vll &a, const vll &b);

    int compareAbs(InfInt const &other) const;

    string to_string();

    string to_binary() const;

    string to_decimal(string binary) const;

    bool isZero() const;


    InfInt abs() const;

    void normalize();

    string clearzero(string str) const;

    void match_length(string &a, string &b) const;




};

#endif //UNTITLED4_INFINT_H
