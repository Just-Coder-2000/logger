#define FORMAT_ARRAY
#define FORMAT_LIST
#define FORMAT_VECTOR

#include <fstream>
#include <cmath>
#include "logger.h"

#pragma region output for structure

struct Info
{
private:
    /**
     * @brief the members
     */
    int _id;
    float _dur;

public:
    /**
     * @brief construct a new Info object
     */
    Info(const int &id, const float &dur)
        : _id(id), _dur(dur) {}

    inline int &id() { return this->_id; }
    inline const int &id() const { return this->_id; }

    inline float &dur() { return this->_dur; }
    inline const float &dur() const { return this->_dur; }
};
/**
 * @brief override operator '<<' for type 'Info'
 */
std::ostream &operator<<(std::ostream &os, const Info &obj)
{
    os << '{';
    os << "'id': " << obj.id() << ", 'dur': " << obj.dur();
    os << '}';
    return os;
}

#pragma endregion

void log()
{
    INFO("this is a list<int>: ", std::list<int>{1, 2, 3, 4, 5});
    INFO();
    TEXT();
    INFO("test");
    TEXT("herry");
    INFO("test", "test");
    TEXT("herry", "potter");
    INFO("test", "test", "test");
    TEXT("this is a text message: ", "hello, ", "world.");
    INFO("this is a array<int, 3>: ", std::array<int, 3>{1, 4, 5});
    INFO("this is a empty vector<double>: ", std::vector<double>{});
    PROCESS("we all konw that PI equals to ", M_PI);
    WARNING("here is a 'Info' type struct object: ", Info(12, 13.4f));
    INFO();
    ERROR("the ofstream is open? (", true, ")");
    FATAL("hello, world. ", "My E-Mail is ", "[3079625093@qq.com].");
}

int main(int argc, char const *argv[])
{
    /**
     * @brief std::cout
     */
    ::log();

    /**
     * @brief std::ofstream
     */
    std::ofstream ofs("../log.log");
    ns_log::setCurOS(ofs);
    ::log();
    ofs.close();
    return 0;
}