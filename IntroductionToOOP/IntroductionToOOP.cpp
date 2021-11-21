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
};

//#define STRUCT_POINT

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

    Point A;
    A.set_x(2);
    A.set_y(3);
    cout << A.get_x() << "\t" << A.get_y() << endl;

    return 0;
}