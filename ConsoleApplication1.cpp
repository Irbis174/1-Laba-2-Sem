#include <iostream>;
#include <conio.h>;
#include <math.h>;
#include <functional>;
#include <cmath>;
#include <tuple>;
const int n = 2; // Число точек n в квадратуре 
const int N = 2; // Степень полинома Лежандра 

using namespace std;

double integr(double, double, function <double(double)> );
double fun(double);
double fun2(double);
tuple <double, double> integr(function<double(double)>, function<double(double)>);
double integr(function<double(double)>);

int main()
{
    setlocale(LC_ALL, "Ru");
    double a = 1; // Нижний предел интегрирования 
    double b = 5; // Верхний предел интегрирования
    double s = 0.0, s2 = 0.0, x, y, x1, y1;
    cout << "Первая фунция: y=(x^2)/4" << endl << "Вторая функция: y=8/(x^2)+4" << endl;

    for (int i = 0; i < N; i++)
    {
        s += integr(a + i * (b - a) / N, a + (i + 1) * (b - a) / N, fun);
    }

    for (int i = 0; i < N; i++)
    {
        s2 += integr(a + i * (b - a) / N, a + (i + 1) * (b - a) / N, fun2);
    }

    cout << "I = " << max(s2, s) - min(s2, s) << endl; // Нахождение площади под графиком
    x1 = integr(fun);
    y1 = integr(fun2);
    tie(x, y) = integr(fun, fun2);
}

double fun(double x)
{
    return pow(x, 2) / 4;
}

double fun2(double x)
{
    return 8 / (pow(x, 2) + 4);
}

double integr(double a, double b,function <double(double)> fun) // Вычисление интеграла методом Гаусса-Лежандра
{
    const double Xi[n] = { -0.5773503, 0.5773503 }; // Значения аргумента
    const double Ci[n] = { 1,1 }; // Весовые коэффициенты 

    double ra = (b - a) / 2;
    double su = (a + b) / 2;
    double q, sum = 0.0;

    for (int i = 0; i < n; i++)
    {
        q = su + ra * Xi[i];
        sum += Ci[i] * fun(q);
    }
    return ra * sum;
}

tuple <double, double> integr(function<double(double)> fun, function<double(double)>fun2)
{   
    return make_tuple(fun(0) - fun2(0), fun(0) + fun2(0));
}

double integr(function<double(double)> fun) // Метод Ньютона
{
    double epsilon = 0.000001;
    double h = 0.00001;
    double x = 0.0000; 
    int k = 0;
    while ((fabs(fun(x)) > epsilon) && (!(isinf(x))) && (k!=1))
    {
        x -= (fun(x)) / ((fun(x + h) - fun(x - h)) / (2 * h)); // формула центральной производной
        k++;
    }
    return x;
}

