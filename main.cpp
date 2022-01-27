#include "logger.h"
#include <fstream>
#include <cmath>

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

#pragma region output for container

/**
 * @brief params to control
 * @param splitor the splitor to split the elements
 * @param firName the describe name for the first element of the std::pair
 * @param sedName the describe name for the second element of the std::pair
 */
static std::string splitor(", ");
static std::string firName("fir");
static std::string sedName("sed");

/**
 * @brief Set the splitor
 */
static void setSplitor(const std::string &sp)
{
    splitor = sp;
}

/**
 * @brief Set the firName and sedName
 */
static void setFirSedName(const std::string &firstName, const std::string &secondName)
{
    firName = firstName, sedName = secondName;
}

/**
 * @brief overload the operator '<<' for std::pair
 */
template <typename Key, typename Val>
std::ostream &operator<<(std::ostream &os, const std::pair<Key, Val> &p)
{
    os << "{'" + firName + "': " << p.first << ", '" + sedName + "': " << p.second << '}';
    return os;
}

/**
 * @brief output format for container
 */
template <typename ConType>
std::ostream &outputCon(std::ostream &os, const ConType &s)
{
    os << '[';
    auto iter = s.cbegin();
    for (; iter != (--s.cend()); ++iter)
        os << *iter << splitor;
    os << *iter << ']';
    return os;
}

/**
 * @brief overload the operator '<<' for std::vector
 */
template <typename Val>
std::ostream &operator<<(std::ostream &os, const std::vector<Val> &s)
{
    return outputCon(os, s);
}

#pragma endregion

void log()
{
    INFO("this", ' ', "is", ' ', "a", ' ', "vector<int>: ", std::vector<int>{1, 2, 3, 4, 5});
    PROCESS("we all konw that PI equals to ", M_PI);
    WARNING("here is a 'Info' type struct object: ", Info(12, 13.4f));
    ERROR("the ofstream is open? (", true, ")");
    FATAL("hello, world. ", "My E-Mail is ", "3079625093@qq.com.");
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