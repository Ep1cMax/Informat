#include <iostream>
#include <math.h>

int main()
{
    setlocale(LC_CTYPE, "rus");

    float x, y, R, S, C;
    x = y = R = S = C = 0.0;

    std::cout << "Введите x: ";
    std::cin >> x;
    std::cout << std::endl << "Введите y: ";
    std::cin >> y;

    R = sqrt(x * y) / abs(x);
    S = cos(y) * log2(x);

    std::cout << std::endl << "Значение R = " << R << std::endl;
    std::cout << "Значение S = " << S << std::endl;

    C = std::max(R, S);
    std::cout << "Наибольший из элементов R и C: " << C << std::endl;

    std::cout << std::endl << "Нажмите Enter для завершения программы..." << std::endl;
    std::cin.get();

    return 0;

}
