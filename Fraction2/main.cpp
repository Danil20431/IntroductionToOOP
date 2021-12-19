//Fraction

#pragma warning (disable:4326)	//��������� Warning �� ����.

#include<iostream>
using std::cin;
using std::cout;
using std::endl;

class Fraction;
Fraction operator*(Fraction left, Fraction right);	//��������� �������

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
		if (denominator == 0)denominator = 1;	//��������������� 0
		this->denominator = denominator;
	}
	//				Constructors:
	Fraction()
	{
		this->integer = 0;
		this->numerator = 0;
		this->denominator = 1;
		cout << "DefaultConstruct:\t" << this << endl;
	}
	explicit Fraction(int integer)
	{
		//explicit - �����.
		//explicit ��������� ������ ����� ��������������.
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		cout << "1argConstructor:\t" << this << endl;
	}
	Fraction(double decimal)
	{
		decimal += 1e-11;
		integer = decimal;
		denominator = 1e+9;	//1*10^9
		decimal -= integer;	//������� ����� ����� �� ���������� �����
		numerator = decimal * denominator;
		reduce();
	}
	Fraction(int numerator, int denominator)
	{
		this->integer = 0;
		this->numerator = numerator;
		set_denominator(denominator);	//����� �� ������ ���������� ������
		cout << "Constructor:\t" << this << endl;
	}
	Fraction(int integer, int numerator, int denominator)
	{
		this->integer = integer;
		this->numerator = numerator;
		set_denominator(denominator);
		cout << "Constructor:\t" << this << endl;
	}
	~Fraction()
	{
		cout << "Destructor:\t" << this << endl;
	}

	//					Operators:
	Fraction& operator=(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	Fraction& operator*=(const Fraction& other)
	{
		return *this = *this * other;
		//		 A	 =	 A  *  B
	}

	//				Type-cast operators:
	explicit operator int()const
	{
		return integer;
	}
	explicit operator double()const
	{
		return integer + (double)numerator / denominator;
	}

	//					Methods:
	Fraction& to_improper()//��������� ����� � �����������
	{
		numerator += integer * denominator;
		integer = 0;
		return *this;
	}
	Fraction& to_proper()//��������� ����� � ����������
	{
		integer += numerator / denominator;
		numerator %= denominator;
		//numerator = numerator % denominator;
		return *this;
	}
	Fraction& reduce()
	{
		//https://www.webmath.ru/poleznoe/formules_12_7.php
		if (numerator == 0)return *this;	//�������� ������ �������
		int more, less;
		int rest;	//������� �� �������
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
		/////////////////////////////////////////////////////
		do
		{
			rest = more % less;
			more = less;
			less = rest;
		} while (rest);
		int GCD = more;	//GCD - Greatest Common Divisor (���������� ����� ��������)
		numerator /= GCD;
		denominator /= GCD;
		return *this;
	}
	Fraction inverted()
	{
		to_improper();
		return Fraction(this->denominator, this->numerator);
	}
	std::ostream& print(std::ostream& os = cout)const
	{
		if (integer)os << integer;//���� ���� ����� �����, ������� �� �� �����
		if (numerator)
		{
			if (integer)os << "(";
			os << numerator << "/" << denominator;
			if (integer)os << ")";
		}
		else if (integer == 0)os << 0;
		return os;
	}
};

Fraction operator*(Fraction left, Fraction right)
{
	left.to_improper();	right.to_improper();
	/*Fraction result
	(
		left.get_numerator()*right.get_numerator(),
		left.get_denominator()*right.get_denominator()
	);*/
	/*result.set_numerator(left.get_numerator()*right.get_numerator());
	result.set_denominator(left.get_denominator()*right.get_denominator());*/
	//result.to_proper();
	//result.reduce();
	//return result;
	return Fraction	//���� �������� �����������, ������� ������� ��������� ���������� ������
	(
		left.get_numerator() * right.get_numerator(),
		left.get_denominator() * right.get_denominator()
	).to_proper().reduce();
}
Fraction operator/(Fraction left, Fraction right)
{
	return left * right.inverted();
}

//	type		name	(			parameters			)
std::ostream& operator<<(std::ostream& os, const Fraction& obj)
{
	//os - output stream
	/*if (obj.get_integer())os << obj.get_integer();//���� ���� ����� �����, ������� �� �� �����
	if (obj.get_numerator())
	{
		if (obj.get_integer())os << "(";
		os << obj.get_numerator() << "/" << obj.get_denominator();
		if (obj.get_integer())os << ")";
	}
	else if (obj.get_integer() == 0)os << 0;
	return os;*/
	return obj.print(os);
}
std::istream& operator>>(std::istream& is, Fraction& obj)
{
	/*int integer;
	int numerator;
	int denominator;
	is >> integer >> numerator >> denominator;
	obj.set_integer(integer);
	obj.set_numerator(numerator);
	obj.set_denominator(denominator);
	return is;*/

	obj = Fraction();

	const int SIZE = 256;
	char buffer[SIZE] = {};
	char delimiters[] = "() /";
	is.getline(buffer, SIZE);
	char* number[3] = {}; // ����� ������� ����� ������ ���������� ��� strtok
	int n = 0; // ������ �������� � ������� number

	for (char* pch = strtok(buffer, delimiters); pch; pch = strtok(NULL, delimiters))
	{
		number[n++] = pch;
	}

	/*for (int i = 0; i < n; i++)
	{
		cout << number[i] << "\t";
	}
	cout << endl;*/

	switch (n)
	{
	case 1: obj.set_integer(atoi(number[0])); break;
	case 2:
		obj.set_numerator(atoi(number[0]));
		obj.set_denominator(atoi(number[1]));
		break;
	case 3:
		obj.set_integer(atoi(number[0]));
		obj.set_numerator(atoi(number[1]));
		obj.set_denominator(atoi(number[2]));
	}

	return is;
}

//#define CONSTRUCTORS_CHECK
//#define OPERATORS_CHECK
//#define TYPE_CONVERSIONS_BASICS
//#define CONVERSIONS_FROM_OTHER_TO_CLASS
//#define CONVERSIONS_FROM_CLASS_TO_OTHER
//#define HOME_WORK
#define HOME_WORK_1
#define HOME_WORK_2

void main()
{
	setlocale(LC_ALL, "");
#ifdef CONSTRUCTORS_CHECK
	Fraction A;	//Default constructor
	A.print();
	double b = 5;
	Fraction B = 5;	//Single-argument constructor
	B.print();
	//Fraction C(7);	//Single-argument constructor
	//C.print();
	//Fraction D{ 8 };//Single-argument constructor
	//D.print();
	Fraction C(3, 4);
	C.print();
	Fraction D(2, 3, 4);
	D.print();
#endif // CONSTRUCTORS_CHECK

#ifdef OPERATORS_CHECK
	double a = 2.5;
	double b = 3.4;
	double c = a * b;
	cout << c << endl;

	Fraction A(2, 1, 2);
	Fraction B(3, 2, 5);
	/*Fraction C = A * B;
	C.print();*/

	/*Fraction D(840, 3600);
	D.reduce();
	D.print();*/

	/*C = A / B;
	C.print();*/

	A *= B;
	A.operator*=(B);
	A.print();
	A = A * B;
#endif // OPERATORS_CHECK

#ifdef TYPE_CONVERSIONS_BASICS
	//(type)value;	//C-like notation		(C-�������� ����� ������)
//type(value);	//Functional notation	(�������������� ����� ������)
//Warning: ... conversion from 'type' to 'type' possible loss of data.

	int a = 2;		//No converion (��� ��������������)
	double b = 3;	//From less to more (�� �������� � ��������)
	int c = b;		//From more to less without data loss (�� �������� � ������� ��� ������ ������)
	int d = 4.5;	//From more to less with data loss (�� �������� � �������� � ������� ������)
	cout << d << endl;
#endif // TYPE_CONVERSIONS_BASICS

#ifdef CONVERSIONS_FROM_OTHER_TO_CLASS
	double a = 2;	//From 'int' to 'double'
	Fraction A = (Fraction)5;	//From 'int' to 'Fraction'
		//Single-argument constructor
	A.print();
	Fraction B;
	cout << "\n----------------------------------\n";
	B = Fraction(8);		//CopyAssignment
	cout << "\n----------------------------------\n";
	B.print();

	//Fraction C = 12;	//explicit constructor ���������� ������� ���
	Fraction C(12);		//�� explicit constructor ������ ����� ������� ���  
#endif // CONVERSIONS_FROM_OTHER_TO_CLASS

#ifdef CONVERSIONS_FROM_CLASS_TO_OTHER
			//						Type-cast operators:
/*operator type()
{
	....
	....
}*/

	double b = 2;
	int c = b;		//From more to less
					//From 'double' to 'int'

	Fraction A(2);
	int a{ A };		//From more to less
					//From 'Fraction' to 'int'
	cout << a << endl;
	int i = (int)A;
	int j = int(A);
#endif // CONVERSIONS_FROM_CLASS_TO_OTHER

#ifdef HOME_WORK
	cout << ULLONG_MAX << endl;
	Fraction A(2, 3, 4);
	double a = A;	//����������� ��� ��� � ������ ��� (�������� ��������������)
	cout << a << endl;

	double b = 2.7711122;
	Fraction B = b;	//����������� ������ ��� � ���, ��� ����� ����� ����������� � ����� ���������� ���� double
	B.print();
#endif // HOME_WORK

	/*Fraction A(2, 3, 4);
	cout << A << endl;
	A.print();*/

	Fraction A;
	cout << "������� ������� �����: " << endl; cin >> A;
	cout << A << endl;
}