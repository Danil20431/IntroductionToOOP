#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#define delimiter "\n----------------------------------------------------\n"

//     ���������� ������

class String;
String operator+(const String& left, const String& right);

class String
{
	int size;	//������ ������ � ������
	char* str;	//����� ������ � ������������ ������
public:
	int get_size()const;
	const char* get_str()const;
	char* get_str();

	explicit String(int size = 80);
	String(const char str[]);
	String(const String& other);
	~String();

	//					Operators:
	String& operator=(const String& other);
	String& operator+=(const String& other);

	const char& operator[](int i)const;
	char& operator[](int i);

	//					Methods
	void print()const;
};  //  ����� ���������� ������
//  :: - �������� ����������� ��������� Scope Operator

//    ����������� ������
int String::get_size()const
{
	return size;
}
const char* String::get_str()const
{
	return str;
}
char* String::get_str()
{
	return str;
}

String::String(int size) :size(size), str(new char[size] {})
{
	//this->size = size;
	//this->str = new char[size] {};	//������, ���������� ��� ������ ����������� ����� ��������
	cout << "SizeConstructor:\t" << this << endl;
}
String::String(const char str[]) :String(strlen(str) + 1)
{
	/*this->size = strlen(str) + 1;
	this->str = new char[size] {};*/
	for (int i = 0; str[i]; i++)this->str[i] = str[i];
	cout << "Constructor:\t" << this << endl;
}
String::String(const String& other) :String(other.str)
{
	//Deep copy (��������� �����������):
	/*this->size = other.size;
	this->str = new char[size] {};
	for (int i = 0; i < size; i++)this->str[i] = other.str[i];*/
	cout << "CopyConstructor:\t" << this << endl;
}
String::~String()
{
	delete[] str;
	cout << "Destructor:\t" << this << endl;
}

//					Operators:
String& String::operator=(const String& other)
{
	if (this == &other)return *this;	//���������, �� �������� �� this � other ����� � ��� �� ��������
	delete[] this->str;
	//Deep copy (��������� �����������):
	this->size = other.size;
	this->str = new char[size] {};
	for (int i = 0; i < size; i++)this->str[i] = other.str[i];
	cout << "CopyAssignment:\t" << this << endl;
	return *this;
}
String& String::operator+=(const String& other)
{
	return *this = *this + other;
}

const char& String::operator[](int i)const
{
	return str[i];
}
char& String::operator[](int i)
{
	return str[i];
}

//					Methods
void String::print()const
{
	cout << "Size:\t" << size << endl;
	cout << "Str:\t" << str << endl;
}

String operator+(const String& left, const String& right)
{
	String result(left.get_size() + right.get_size() - 1);
	for (int i = 0; i < left.get_size(); i++)
		//l-value = r-value;
		result[i] = left[i];
	//result.get_str()[i] = left.get_str()[i];
	for (int i = 0; i < right.get_size(); i++)
		result[i + left.get_size() - 1] = right[i];
	//result.get_str()[i + left.get_size() - 1] = right.get_str()[i];
	return result;
}

std::ostream& operator<<(std::ostream& os, const String& obj)
{
	return os << obj.get_str();
}
std::istream& operator>>(std::istream& is, String& obj)
{
	//return is >> obj.get_str();
	const int SIZE = 1024 * 1000;
	char buffer[SIZE] = {};
	is >> buffer;
	obj = buffer;
	return is;
}

std::istream& getline(std::istream& is, String& obj)
{
	const int SIZE = 1024 * 1000;
	char buffer[SIZE] = {};
	is.getline(buffer, SIZE);
	obj = buffer;
	return is;
} //    ����� ����������� ������

//char str[] = { 'S', 't', 'r', 'o', 'k', 'a' };

//#define CONSTRUCTORS_CHECK
#define OPERATORS_CHECK
//#define INPUT_CHECK

void main()
{
	//char test[1024 * 1024]{};
	setlocale(LC_ALL, "");

#ifdef CONSTRUCTORS_CHECK
	String str1;		//Default constructor
	str1.print();
	cout << str1 << endl;

	String str2(25);	//Single-argument constructor
	str2.print();

	String str3 = "Hello";
	str3 = str3;
	cout << str3 << endl;

	String str4 = str3;	//CopyConstructor
	//Deep copy
	//Shallow copy
	//Debug Assertion Failed
	cout << str4 << endl;

	String str5;
	str5 = str3;	//CopyAssignment (operator=)
	cout << str5 << endl;
#endif // CONSTRUCTORS_CHECK

#ifdef OPERATORS_CHECK
	int a = 2;
	int b = 3;
	int c = a + b;

	String str1 = "Hello";
	String str2 = "World";
	cout << delimiter << endl;
	String str3 = str1 + str2;
	cout << delimiter << endl;
	cout << str3 << endl;
	cout << delimiter << endl;
	str1 += str2;
	cout << delimiter << endl;
	cout << str1 << endl;
	cout << delimiter << endl;
#endif OPERATORS_CHECK

#ifdef INPUT_CHECK
	String str;
	cout << "������� ������: ";
	//cin >> str;
	getline(cin, str);
	cout << str << endl;
	str.print();
#endif // INPUT_CHECK
}