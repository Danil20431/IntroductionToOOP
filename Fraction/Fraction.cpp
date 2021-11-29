#include <iostream>

using namespace std;

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
        set_denominator(denominator); // ����� �� ������ ���������� ������
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
    //      Methods:
    void to_improper() // ��������� ����� � ������������
    {
        numerator += integer * denominator;
        integer = 0;
    }
    void to_proper() // ��������� ����� � ����������
    {
        integer += numerator / denominator;
        numerator %= denominator;
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
    Fraction resoult
    (
        left.get_numerator() * right.get_numerator(),
        left.get_denominator() * right.get_denominator()
    );
    /*resoult.set_numerator(left.get_numerator() * right.get_numerator());
    resoult.set_denominator(left.get_denominator() * right.get_denominator());*/
    resoult.to_proper();
    return resoult;
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
    Fraction C = A * B;
    C.print();

    return 0;
}