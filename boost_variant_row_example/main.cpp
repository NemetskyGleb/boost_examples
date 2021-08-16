#include <boost/variant.hpp>
#include <vector>
#include <string>
#include <iostream>

// использование variant для суммирования столбца бд

typedef boost::variant<int, float, std::string> cell_t;
typedef std::vector<cell_t> db_row_t;

db_row_t get_row(const char* /*query*/) // желательно использовать сcылку на строку std::string
{
    db_row_t row;
    row.push_back(10);
    row.push_back(10.1f);
    row.push_back("hello again");
    return row;
}

// Это код, необходимый для суммирвания значений
// Мы могли бы просто использовать boost::static_visitor<>
// если бы наш объект visitor ничего не возвращал

struct db_sum_visitor : public boost::static_visitor<double>
{
    double operator()(int value) const {
        return value;
    }
    double operator()(float value) const {
        return value;
    }
    double operator()(const std::string& /*value*/) const {
        return 0.0;
    }
};

int main()
{
    db_row_t row = get_row("Query");
    double res = 0.0;
    for (auto it = row.begin(), end = row.end(); it != end; ++it) {
        res += boost::apply_visitor(db_sum_visitor(), *it);
    }
    std::cout << "Sum of arithmetic types in database row is " << res << std::endl;
    return 0;
}
/*
 * Преимущества boost::variant
 * 1. мы знаем, какие типы может хранить переменная
 * 2. Если разработчик библиотеки интерфейса SQL добавляет или изменяет тип, хранящийся в variant,
 * вместо неопредленного поведения, мы поличим ошибку времени компиляции
 * */

/* std::variant из стандарта C++ 17 поддерживает эту идиому проектирования.
 * Просто напишите std::visit вместо boost::apply_visitor
 * */
