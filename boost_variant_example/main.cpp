#include <boost/variant.hpp>
#include <iostream>
#include <vector>
#include <string>

// Boost.Variant может хранить любые типы, указанные во время компиляции
// для достижения максимальной эффективности в шаблонном списке параметров указываем POD(простой тип)
void example1();
void example2();

int main()
{
    typedef boost::variant<int, const char*, std::string> my_var_t;
    std::vector<my_var_t> some_values;
    some_values.push_back(10);
    some_values.push_back("Hello there!");
    some_values.push_back(std::string("WOW!"));

    std::string& s = boost::get<std::string>(some_values.back());
    s += " That is great!";
    std::cout << s << std::endl;
    example1();
    return 0;
}

// empty всегда возвращает false
// Если нужно добавить пустое состояние, добавяляем вначале шаблонный параметр boost::blank

void example1()
{
    boost::variant<boost::blank, int, const char*, std::string> var;
    // Метод which возвращает индекс типа, который в настоящий момент содержиться
    assert(var.which() == 0); // boost::blank

    var = "Hello, dear reader!";
    assert(var.which() != 0);
}

// Получить значение из boost::variont можно двумя способами
void example2()
{
    boost::variant<int, std::string> var(0);
    // При следующем подходе при несоответствии фактического значения
    // выбрасывается исключение boost::bad_get
    int s1 = boost::get<int>(var);

    // Если фактичнское значение не является int, вернётся nullptr
    int* s2 = boost::get<int>(&var);
}

/*
 * Библа boost::variant является частью стандарта C++ 17
 * Отличия:
 * 1. Объявляется заголовочником <variant>
 * 2. вместо boost:get<type>(&var) используется std::get_if<type>(&var)
 * 3. Нет динамических выделений памяти
 * 4. Вместо which std::variant имеет функцию index
 * 5. Не может рекурсивно содержать самого себя
 * */
