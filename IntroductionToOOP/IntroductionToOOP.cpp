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
    void operator=(const Point& other)
    {
        this->x = other.x;
        this->y = other.y;
        cout << "CopyAssignment:\t" << this << endl;
    }

    // Methods
    double distance(Point other)
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
#define CONSTRUCTORS_CHECK
//#define DISTANCE_CHECK

double distance(Point A, Point B)
{
    double x_distance = A.get_x() - B.get_x();
    double y_distance = A.get_y() - B.get_y();
    return sqrt(x_distance * x_distance + y_distance * y_distance);
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
    cout << "Расстояние от точки A до B: " << A.distance(B) << endl;
    cout << "Расстояние от точки A до B: " << B.distance(A) << endl;

    cout << "Расстояние между точками A и B: " << distance(A, B) << endl;
    cout << "Расстояние между точками B и A: " << distance(B, A) << endl;

#endif // DISTANCE_CHECK

    return 0;
}