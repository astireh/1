#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <locale.h>

//4 пункт что обозначает точность поиска
//когда начинаются большие числа, исчезает часть после запятой
double f(double x);//формирование функции
void calculate_value();
void table();
void find_extremum();
void find_x_by_y();
double Pr(double x);
void derivative_at_point();


int main() {
    int chislo;
    setlocale(LC_CTYPE, "Rus");

    do {
        printf("\n=== Главное меню ===\n");
        printf("1. Значение функции в точке\n");
        printf("2. Таблица значений\n");
        printf("3. Поиск минимума/максимума\n");
        printf("4. Поиск X по Y\n");
        printf("5. Производная в точке\n");
        printf("0. Выход\n");
        printf("Выберите пункт: ");
        scanf("%d", &chislo);

        switch (chislo) {
        case 1:
            calculate_value();
            break;
        case 2:
            table();
            break;
        case 3:
            find_extremum();
            break;
        case 4:
            find_x_by_y();
            break;
        case 5:
            derivative_at_point();
            break;
        case 0:
            printf("Выход из программы.\n");
            break;
        default:
            printf("Неверный ввод!\n");
        }
    } while (chislo != 0);

    return 0;
}

//F(x)
double f(double x) {
    if (x < -2) {
        return atan(x * x);
    }
    else if (x < 0) {
        return (exp(x) - 1) / x;
    }
    else {
        double sum = 0;
        for (int n = 0; n <= 12; n++) {
            double t = pow(-1, n) * pow(x, n + 1) / (n + 1);
            sum += t;
        }
        return sum;
    }
}
//ПУНКТ 1
void calculate_value() {
    double x;
    printf("Введите x: ");
    scanf("%lf", &x);
    printf("f(%.4f) = %.8f\n", x, f(x));
}
//ПУНКТ 2
void table() {
    double s, e, st;
    printf("Введите начало интервала: ");
    scanf("%lf", &s);
    printf("Введите конец интервала: ");
    scanf("%lf", &e);
    printf("Введите шаг: ");
    scanf("%lf", &st);
    printf("\n| %-10s | %-30s |\n", "x", "f(x)");
    printf("|------------|--------------------------------|\n");
    for (double x = s; x <= e; x += st) {
        printf("| %-10.2f | %-30.6f |\n", x, f(x));
    }
}
//ПУНКТ 3
void find_extremum() {
    double s, e, st;
    double minn = 2e10;
    double min_x = 0;
    double max_x = 0;
    double maxx = -2e10;
    printf("Введите начало интервала: ");
    scanf("%lf", &s);
    printf("Введите конец интервала: ");
    scanf("%lf", &e);
    for (double x = s; x <= e; x += 0.01) {
        if (f(x) < minn) {
            minn = f(x);
            min_x = x;
        }
        if (f(x) > maxx) {
            maxx = f(x);
            max_x = x;
        }
    }
    printf("\nМинимальное значение на отрезке: %.6f\nПри аргумерте: %.2f\n", minn, min_x);
    printf("Максимальное значение на отрезке: %.6f\nПри аргумерте: %.2f\n", maxx, max_x);
}

//ПУНКТ 4
void find_x_by_y() {
    double target_y, a, b, eps;
    int max_iterations = 1000;

    printf("Введите значение Y:");
    if (scanf("%lf", &target_y) != 1) {
        printf("Ошибка ввода!\n");
        return;
    }

    printf("Введите начало интервала поиска: ");
    if (scanf("%lf", &a) != 1) {
        printf("Ошибка ввода!\n");
        return;
    }

    printf("Введите конец интервала поиска: ");
    if (scanf("%lf", &b) != 1) {
        printf("Ошибка ввода!\n");
        return;
    }

    printf("Введите точность поиска (например, 0.0001): ");
    if (scanf("%lf", &eps) != 1 || eps <= 0) {
        printf("Ошибка! Точность должна быть положительным числом.\n");
        return;
    }


    double search_step = (b - a) / 1000.0;
    int solutions_found = 0;

    for (double x = a; x <= b - search_step; x += search_step) {
        double x1 = x;
        double x2 = x + search_step;
        double f1 = f(x1) - target_y;
        double f2 = f(x2) - target_y;

        
        if (f1 * f2 <= 0) {
            double left = x1;
            double right = x2;
            double mid;
            int iterations = 0;

            while ((right - left) > eps && iterations < max_iterations) {
                mid = (left + right) / 2.0;
                double f_mid = f(mid) - target_y;

                if (f1 * f_mid <= 0) {
                    right = mid;
                    f2 = f_mid;
                }
                else {
                    left = mid;
                    f1 = f_mid;
                }
                iterations++;
            }

            if (iterations < max_iterations) {
                printf("Найден x = %.10f, f(x) = %.10f (разница: %.10f)\n",
                    mid, f(mid), fabs(f(mid) - target_y));
                solutions_found++;
            }
        }
    }
}

//ПУНКТ 5
//поиск производной
double Pr(double x) {
    if (x < -2) {
        return 2 * x / (1 + pow(x, 4));
    }
    else if (x < 0) {
        return (exp(x) * (x - 1) + 1) / (x * x);
    }
    else {
        return (1 + pow(x, 13)) / (1 + x);
    }
}
void derivative_at_point() {
    double x;
    printf("Введите x для поиска производной: ");
    scanf("%lf", &x);
    printf("f'(%.4f) = %.4f\n", x, Pr(x));
}