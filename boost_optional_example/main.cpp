#include <boost/optional.hpp>
#include <iostream>

class locked_device
{
private:
    explicit locked_device(const char* /*param*/) {
        // У нас есть уникальный доступ к устройству
        std::cout << "Device is locked\n";
    }
    static bool try_lock_device_impl()
    {
        return true;
    }
public:
    void use() {
        std::cout << "Success!\n";
    }
    /**
     * @brief Эта функция пытается захватить уникальный доступ у устройству
     * @return в зависимости от возвращаемого значения, фукнция может успешно завершиться или провалиться
     */
    static boost::optional<locked_device> try_lock_device() {
        if (!try_lock_device_impl()) {
            // Не удалось получить уникальный доступ
            return boost::none;
        }
        // Успешно!
        return locked_device("device name");
    }
    ~locked_device() {} // Снимает блокировку с устройства
};

int main()
{
    for (int i = 0; i < 10; ++i) {
        boost::optional<locked_device> t = locked_device::try_lock_device();
        // Можно преоброзовать к bool
        if (t) {
            t->use();
            return 0;
        } else {
            std::cout << "...trying again\n";
        }
    }
    std::cout << "Failure!\n";
    return -1;
}
