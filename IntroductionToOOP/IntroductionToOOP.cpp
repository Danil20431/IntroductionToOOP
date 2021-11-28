#include <iostream>

using namespace std;

#define tab "\t"

class Point
{
    double x;
    double y;
public:
    //get-методы должны быть константными
    //константным называется метод который не изменяет объект для которого вызывается
    //для константного объекта могут быть только константные методы
    double get_x()const
    {
        return x;
    }
    double get_y()const
    {
        return y;
    }
    void set_x(double x)
    {
        this->x = x;
    }
    void set_y(double y)
    {
        this->y = y;
    }

    //         Constructors:
    /*Point()
    {
        x = y = 0;
        cout << "DefoultConstructor:\t" << this << endl;
    }*/
    //Point(double x)
    //{
    //    this->x = x;
    //    this->y = 0;  // double() - значение по умолчанию для типа double
    //    cout << "1argConstructor:\t" << this << endl;
    //}
    Point(double x=0, double y=0)
    {
        this->x = x;
        this->y = y;
        cout << "Constructor:\t" << this << endl;
    }
    Point(const Point& other)
    {
        this->x = other.x;
        this->y = other.y;
        cout << "CopyConstructor:" << this << endl;
    }
    ~Point()
    {
        cout<< "Destructor:\t" << this << endl;
    }

    // Operators
    Point& operator=(const Point& other)
    {
        this->x = other.x;
        this->y = other.y;
        cout << "CopyAssignment:\t" << this << endl;
        return *this;
    }

    Point& operator++()
    {
        this->x++;
        this->y++;
        return *this; // Возврат изменённого значения
    }

    Point operator++(int)
    {
        Point old = *this; //Сохраняем старое значение объекта
        x++;
        y++;
        return old;
    }

    // Methods
    double distance(const Point& other)const
    {
        //other - другой (другая точка)
        double x_distance = this->x - other.x;
        double y_distance = this->y - other.y;
        double distance = sqrt(x_distance * x_distance + y_distance * y_distance);
        //sqrt - Square Root (квадратный корень)
        return distance;
    }

    void print()const
    {
        cout << "X = " << x << "\tY = " << y << endl;
    }
};

//#define STRUCT_POINT
//#define CONSTRUCTORS_CHECK
//#define DISTANCE_CHECK
//#define ASSIGNMENT_CHECK

double distance(const Point& A, const Point& B)
{
    double x_distance = A.get_x() - B.get_x();
    double y_distance = A.get_y() - B.get_y();
    return sqrt(x_distance * x_distance + y_distance * y_distance);
}

Point operator+(const Point& left, const Point& right)
{
    Point result;
    result.set_x(left.get_x() + right.get_x());
    result.set_y(left.get_y() + right.get_y());
    return result;
}

//Point G - глобальный объект.
int g; //Глобальная переменная. Осуждается


int main()
{
    setlocale(LC_ALL, "");
#ifdef STRUCT_POINT

    //type name;
    int a; //Объявление переменной 'a' типа 'int'
    Point A;//Объявление переменной 'A' типа 'Point'/Объявление объекта 'A' структуры 'Point'/Создание экземпляра 'A' структуры 'Point'
    A.x = 2;
    A.y = 3;

    cout << A.x << tab << A.y << endl;

    Point* pA = &A; //Объявляем указатель на Point 'pA' и инициализируем его адресом объекта 'A'

    cout << pA->x << tab << pA->y << endl;
    cout << (*pA).x << tab << (*pA).y << endl;

#endif STRUCT_POINT

#ifdef CONSTRUCTORS_CHECK
    Point A;
    /*A.set_x(2);
    A.set_y(3);*/
    //cout << A.get_x() << "\t" << A.get_y() << endl;
    A.print();

    Point B(4, 5);
    B.print();

    Point C = 5; //single-argument constructor
    C.print();

    Point D(8);
    D.print();

    Point E = D; //CopyConstructor
    E.print();
    Point F(B); //CopyConstructor
    F.print();

    Point G;
    G = F; //CopyAssignmetn (operator=)
    G.print();
#endif // CONSTRUCTORS_CHECK

#ifdef DISTANCE_CHECK

    Point A(2, 3);
    Point B(3, 4);
    cout << "\n-------------------------------\n";
    cout << "Расстояние от точки A до B: " << A.distance(B) << endl;
    cout << "\n-------------------------------\n";
    cout << "Расстояние от точки A до B: " << B.distance(A) << endl;
    cout << "\n-------------------------------\n";

    cout << "Расстояние между точками A и B: " << distance(A, B) << endl;
    cout << "\n-------------------------------\n";
    cout << "Расстояние между точками B и A: " << distance(B, A) << endl;
    cout << "\n-------------------------------\n";

#endif // DISTANCE_CHECK

#ifdef ASSIGNMENT_CHECK
    Point A, B, C;
    cout << "\n----------------------------------------------\n";
    A = B = C = Point(2, 3); // Явно вызываем конструктор который временно создаёт безымянный объект
    cout << "\n----------------------------------------------\n";
    A.print();
    B.print();
    C.print();
#endif // ASSIGNMENT_CHECK

    Point A(2, 3);
    Point B(4, 5);
    Point C = A + B;
    C.print();
    C++;
    C.print();

    return 0;
}