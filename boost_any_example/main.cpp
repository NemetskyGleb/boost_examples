#include <iostream>
#include <vector>
#include <string>
#include <boost/any.hpp>

using namespace std;

int main()
{
    std::vector<boost::any> some_values;
    some_values.push_back(10);
    some_values.push_back("Hello there!");
    some_values.push_back(std::string("Wow!"));

    std::string& s = boost::any_cast<std::string&>(some_values.back());
    s += "That is great!";
    std::cout << s << std::endl;
    return 0;
}


// Как мы можем получить значение из boost::any?

void example() {
    boost::any variable(std::string("Hello!"));
    // Может выбрасываться исключение boost::bad_any_cast
    //если фактическое значение не явяляется std::string
    std::string s1 = boost::any_cast<std::string>(variable);

    // Исключение не будет выброшено. Если фактическое значение
    // в переменной не явялется std::string будет возвразен указатель nullptr
    std::string* s2 = boost::any_cast<std::string>(&variable);
}
