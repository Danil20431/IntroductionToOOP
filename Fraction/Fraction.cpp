#include <iostream>

using namespace std;

class Fraction;
Fraction operator*(Fraction left, Fraction right);

class Fraction
{
    int integer;
    int numerator;
    int denominator;
public:
    int get_integer()const
    {
        return integer;
    }
    int get_numerator()const
    {
        return numerator;
    }
    int get_denominator()const
    {
        return denominator;
    }
    void set_integer(int integer)
    {
        this->integer = integer;
    }
    void set_numerator(int numerator)
    {
        this->numerator = numerator;
    }
    void set_denominator(int denominator)
    {
        if (denominator== 0)denominator = 1;
        this->denominator = denominator;
    }

    //      Constructors:
    Fraction()
    {
        this->integer = 0;
        this->numerator = 0;
        this->denominator = 1;
        cout << "DefoultConstructor:\t" << this << endl;
    }
    Fraction(int integer)
    {
        this->integer = integer;
        this->numerator = 0;
        this->denominator = 1;
        cout << "1argConstructor:\t" << this << endl;
    }
    Fraction(int numerator, int denominator)
    {
        this->integer = 0;
        this->numerator = numerator;
        set_denominator(denominator); // Чтобы не обойти фильтрацию данных
        cout << "Constructor:\t" << this << endl;
    }
    Fraction(int integer, int numerator, int denominator)
    {
        this->integer = integer;
        this->numerator = numerator;
        this->denominator = denominator;
        cout << "Constructor:\t" << this << endl;
    }
    ~Fraction()
    {
        cout << "Destructor:\t" << this << endl;
    }
    //      Operators:
    Fraction& operator*=(const Fraction& other)
    {
        return *this = *this * other;
    }

    //      Methods:
    Fraction& to_improper() // Переводит дробь в неправильную
    {
        numerator += integer * denominator;
        integer = 0;
        return *this;
    }
    Fraction& to_proper() // Переводит дробь в правильную
    {
        integer += numerator / denominator;
        numerator %= denominator;
        return *this;
    }

    Fraction& reduce()
    {
        if (numerator == 0)
            return *this;
        int more, less;
        int rest;
        if (numerator > denominator)
        {
            more = numerator;
            less = denominator;
        }
        else
        {
            less = numerator;
            more = denominator;
        }
        do
        {
            rest = more % less;
            more = less;
            less = rest;
        } while (rest);
        int GCD = more; // Greatest Common Divisor (наибольший общий делитель)
        numerator /= GCD;
        denominator /= GCD;
        return *this;
    }

    Fraction inverted()
    {
        /*Fraction inverted = *this;
        inverted.to_improper();
        int buffer = inverted.numerator;*/
        to_improper();
        return Fraction(this->denominator, this->numerator);

    }

    void print()const
    {
        if (integer)cout << integer;
        if (numerator)
        {
            if (integer)cout << "(";
            cout << numerator << " / " << denominator;
            if (integer)cout << ")";
        }
        else if (integer == 0)cout << 0;
        cout << endl;
    }
};

Fraction operator*(Fraction left, Fraction right)
{
    left.to_improper();
    right.to_improper();
    /*Fraction resoult
    (
        left.get_numerator() * right.get_numerator(),
        left.get_denominator() * right.get_denominator()
    );*/
    /*resoult.set_numerator(left.get_numerator() * right.get_numerator());
    resoult.set_denominator(left.get_denominator() * right.get_denominator());*/
    /*resoult.to_proper();
    return resoult;*/
    return Fraction
    (
        left.get_numerator() * right.get_numerator(),
        left.get_denominator() * right.get_denominator()
    ).to_proper().reduce();
}

Fraction operator/(Fraction left, Fraction right)
{
    return left * right.inverted();
}

//#define CONSTRUCTORS_CHEC

int main()
{
    setlocale(LC_ALL, "");

#ifdef CONSTRUCTORS_CHEC
    Fraction A; // Default constructor
    A.print();
    double b = 5;
    Fraction B = 5; // Single-argument cpnstructor
    B.print();

    Fraction C(3, 4);
    C.print();
    Fraction D(2, 3, 4);
    D.print();
#endif // CONSTRUCTORS_CHEC

    double a = 2.5;
    double b = 3.4;
    double c = a * b;
    cout << c << endl;

    Fraction A(2, 1, 2);
    Fraction B(3, 2, 5);
    //Fraction C = A * B;
    //C.print();
    /*C.reduce();
    C.print();*/

    /*Fraction D(840, 3600);
    D.reduce().print();*/

    /*C = A / B;
    C.print();*/

    A *= B;
    A.print();

    return 0;
}