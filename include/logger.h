#pragma once

/**
 * @file logger.h
 * @author csl (3079625093@qq.com)
 * @version 0.1
 * @date 2022-01-27
 * 
 * @copyright Copyright (c) 2022
 */

#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <chrono>

/**
 * @brief the main message type macroes: everything that overrides the operator '<<' can use the macroes.
 * [1] INFO    {Information; Message; real-time info Of information; Of messages; Informative}
 * [2] PROCESS {The process of achieving a goal; The development of things, especially the steps of natural change;}
 * [3] WARNING {about possible accidents, etc.; a warning, warning, etc about the punishment to be suffered}
 * [4] ERROR   {Error; Errors; Fallacy;}
 * [5] FATAL   {Fatal; Catastrophic; Destructive; Cause failure}
 * 
 * @brief the main methods.
 * [1] static void setCurOS(std::ostream &os)
 * [2] static void setSplitor(const std::string &sp)
 * [3] static void setFirSedName(const std::string &firstName, const std::string &secondName)
 * 
 * @brief output format for containers in the STL.
 * [1] std::pair
 * [2] std::map std::multimap std::unordered_map std::unordered_multimap
 * [3] std::set std::multiset std::unordered_set std::unordered_multiset
 * [4] std::vector std::list std::deque std::array
 * 
 * @brief the macroes to control the using of the STL containers output format
 * [1] FORMAT_MAP FORMAT_MULTIMAP FORMAT_UNORDERED_MAP FORMAT_UNORDERED_MULTIMAP
 * [2] FORMAT_SET FORMAT_UNORDERED_SET FORMAT_MULTISET FORMAT_UNORDERED_MULTISET
 * [3] FORMAT_VECTOR FORMAT_LIST FORMAT_DEQUE FORMAT_ARRAY
 * [4] FORMAT_STACK FORMAT_QUEUE
 */

namespace ns_log::ns_priv
{
    /**
     * @brief the ostream
     */
    static std::ostream *logerOS = &(std::cout);

    /**
     * @brief Get the current ostream
     * 
     * @return std::ostream& 
     */
    static std::ostream &getCurOS() { return *(ns_priv::logerOS); }

    struct Logger
    {
    private:
        /**
         * @brief the members
         */
        std::string _desc;
        bool _firCall;

    public:
        /**
         * @brief construct a new Logger object
         */
        Logger(const std::string &desc)
            : _desc(desc), _firCall(true) {}

        inline std::string &desc() { return this->_desc; }
        inline const std::string &desc() const { return this->_desc; }

        /**
         * @brief overload the operator '()'
         */
        void operator()()
        {
            std::string head(""), tail("");
            auto count = Logger::curTime();
#ifdef __linux__
            if (logerOS == &std::cout)
                head = "\e[1m", tail = "\e[0m";
#endif
            ns_priv::getCurOS() << head << this->_desc << " [" << count << "]" << tail << '\n';
            this->_firCall = true;
            return;
        }

        /**
         * @brief overload the operator '()'
         */
        template <typename ArgvType>
        void operator()(const ArgvType &argv)
        {
            if (this->_firCall)
            {
                std::string head(""), tail("");
                auto count = Logger::curTime();
#ifdef __linux__
                if (logerOS == &std::cout)
                    head = "\e[1m", tail = "\e[0m";
#endif
                ns_priv::getCurOS() << head << this->_desc << " [" << count << "] " << argv << tail << '\n';
            }
            else
            {
                std::string tail("");
#ifdef __linux__
                if (logerOS == &std::cout)
                    tail = "\e[0m";
#endif
                ns_priv::getCurOS() << argv << tail << '\n';
            }
            this->_firCall = true;
            return;
        }

        /**
         * @brief overload the operator '()'
         */
        template <typename ArgvType, typename... ArgvsType>
        void operator()(const ArgvType &argv, const ArgvsType &...argvs)
        {
            if (this->_firCall)
            {
                this->_firCall = false;
                std::string head("");
                auto count = Logger::curTime();
#ifdef __linux__
                if (logerOS == &std::cout)
                    head = "\e[1m";
#endif
                ns_priv::getCurOS() << head << this->_desc << " [" << count << "] " << argv;
            }
            else
                ns_priv::getCurOS() << argv;
            return (*this)(argvs...);
        }

    protected:
        /**
             * @brief get the time when the message is outputed
             * 
             * @return int64_t
             */
        static int64_t curTime()
        {
            auto now = std::chrono::system_clock::now();
            return std::chrono::time_point_cast<std::chrono::seconds>(now).time_since_epoch().count();
        }
    };

    void __print__()
    {
        getCurOS() << '\n';
        return;
    }

    template <typename ArgvType>
    void __print__(const ArgvType &argv)
    {
        getCurOS() << argv << '\n';
    }

    template <typename ArgvType, typename... ArgvsType>
    void __print__(const ArgvType &argv, const ArgvsType &...argvs)
    {
        getCurOS() << argv;
        __print__(argvs...);
    }

    static Logger info("[ info  ]"), process("[process]"), warning("[warning]"), error("[ error ]"), fatal("[ fatal ]");

    /**
     * @brief params to control
     * @param splitor the splitor to split the elements
     * @param firName the describe name for the first element of the std::pair
     * @param sedName the describe name for the second element of the std::pair
     */
    static std::string splitor(", ");
    static std::string firName("fir");
    static std::string sedName("sed");
} // namespace ns_log::ns_priv

#pragma region output for container

/**
 * @brief overload the operator '<<' for std::pair
 */
template <typename Key, typename Val>
std::ostream &operator<<(std::ostream &os, const std::pair<Key, Val> &p)
{
    os << "{'" + ns_log::ns_priv::firName + "': " << p.first << ", '" + ns_log::ns_priv::sedName + "': " << p.second << '}';
    return os;
}

/**
 * @brief output format for container
 */
template <typename ConType>
std::ostream &outputCon(std::ostream &os, const ConType &s)
{
    os << '[';
    if (s.empty())
    {
        os << "(empty)]";
        return os;
    }
    auto iter = s.cbegin();
    for (; iter != (--s.cend()); ++iter)
        os << *iter << ns_log::ns_priv::splitor;
    os << *iter << ']';
    return os;
}

#pragma endregion

#pragma region map

#ifdef FORMAT_MAP
#include <map>
/**
 * @brief overload the operator '<<' for std::map
 */
template <typename Key, typename Val>
std::ostream &operator<<(std::ostream &os, const std::map<Key, Val> &m)
{
    return outputCon(os, m);
}
#endif

#ifdef FORMAT_MULTIMAP
#include <map>
/**
 * @brief overload the operator '<<' for std::multimap
 */
template <typename Key, typename Val>
std::ostream &operator<<(std::ostream &os, const std::multimap<Key, Val> &m)
{
    return outputCon(os, m);
}
#endif

#ifdef FORMAT_UNORDERED_MAP
#include <unordered_map>
/**
 * @brief overload the operator '<<' for std::unordered_map
 */
template <typename Key, typename Val>
std::ostream &operator<<(std::ostream &os, const std::unordered_map<Key, Val> &m)
{
    return outputCon(os, m);
}

#endif

#ifdef FORMAT_UNORDERED_MULTIMAP
#include <unordered_map>
/**
 * @brief overload the operator '<<' for std::unordered_multimap
 */
template <typename Key, typename Val>
std::ostream &operator<<(std::ostream &os, const std::unordered_multimap<Key, Val> &m)
{
    return outputCon(os, m);
}
#endif

#pragma endregion

#pragma region set

#ifdef FORMAT_SET
#include <set>
/**
 * @brief overload the operator '<<' for std::set
 */
template <typename Val>
std::ostream &operator<<(std::ostream &os, const std::set<Val> &s)
{
    return outputCon(os, s);
}
#endif

#ifdef FORMAT_UNORDERED_SET
#include <unordered_set>
/**
 * @brief overload the operator '<<' for std::unordered_set
 */
template <typename Val>
std::ostream &operator<<(std::ostream &os, const std::unordered_set<Val> &s)
{
    return outputCon(os, s);
}
#endif

#ifdef FORMAT_MULTISET
#include <set>
/**
 * @brief overload the operator '<<' for std::multiset
 */
template <typename Val>
std::ostream &operator<<(std::ostream &os, const std::multiset<Val> &s)
{
    return outputCon(os, s);
}
#endif

#ifdef FORMAT_UNORDERED_MULTISET
#include <unordered_set>
/**
 * @brief overload the operator '<<' for std::unordered_multiset
 */
template <typename Val>
std::ostream &operator<<(std::ostream &os, const std::unordered_multiset<Val> &s)
{
    return outputCon(os, s);
}
#endif
#pragma endregion

#pragma region seq cons

#ifdef FORMAT_VECTOR
#include <vector>
/**
 * @brief overload the operator '<<' for std::vector
 */
template <typename Val>
std::ostream &operator<<(std::ostream &os, const std::vector<Val> &s)
{
    return outputCon(os, s);
}
#endif

#ifdef FORMAT_LIST
#include <list>
/**
 * @brief overload the operator '<<' for std::list
 */
template <typename Val>
std::ostream &operator<<(std::ostream &os, const std::list<Val> &s)
{
    return outputCon(os, s);
}
#endif

#ifdef FORMAT_DEQUE
#include <deque>
/**
 * @brief overload the operator '<<' for std::deque
 */
template <typename Val>
std::ostream &operator<<(std::ostream &os, const std::deque<Val> &s)
{
    return outputCon(os, s);
}
#endif

#ifdef FORMAT_ARRAY
#include <array>
/**
 * @brief overload the operator '<<' for std::array
 */
template <typename Val, std::size_t Size>
std::ostream &operator<<(std::ostream &os, const std::array<Val, Size> &s)
{
    os << '[';
    for (int i = 0; i != s.size() - 1; ++i)
        os << s[i] << ns_log::ns_priv::splitor;
    os << s.back() << ']';
    return os;
}
#endif

#ifdef FORMAT_STACK
#include <stack>
/**
 * @brief overload the operator '<<' for std::stack
 */
template <typename Val>
std::ostream &operator<<(std::ostream &os, const std::stack<Val> &s)
{
    if (s.empty())
    {
        os << "[(empty)]";
        return os;
    }
    os << "[(top) ";
    auto cs = s;
    while (cs.size() != 1)
    {
        os << cs.top() << ns_log::ns_priv::splitor;
        cs.pop();
    }
    os << cs.top() << "]";
    return os;
}
#endif

#ifdef FORMAT_QUEUE
#include <queue>
/**
 * @brief overload the operator '<<' for std::queue
 */
template <typename Val>
std::ostream &operator<<(std::ostream &os, const std::queue<Val> &q)
{
    if (q.empty())
    {
        os << "[(empty)]";
        return os;
    }
    os << "[(front) ";
    auto cq = q;
    while (cq.size() != 1)
    {
        os << cq.front() << ns_log::ns_priv::splitor;
        cq.pop();
    }
    os << cq.front() << "]";
    return os;
}
#endif

#pragma endregion

namespace ns_log
{
    /**
     * @brief Set the current ostream
     * 
     * @param os the ostream
     */
    static void setCurOS(std::ostream &os) { ns_priv::logerOS = &os; }

    /**
     * @brief Set the splitor for container output format
     */
    static void setSplitor(const std::string &sp)
    {
        ns_log::ns_priv::splitor = sp;
    }

    /**
     * @brief Set the firName and sedName for std::pair
     */
    static void setFirSedName(const std::string &firstName, const std::string &secondName)
    {
        ns_log::ns_priv::firName = firstName, ns_log::ns_priv::sedName = secondName;
    }

/**
 * @brief the main message type macroes
 * 
 * [1] info    {Information; Message; real-time info Of information; Of messages; Informative}
 * [2] process {The process of achieving a goal; The development of things, especially the steps of natural change;}
 * [3] warning {about possible accidents, etc.; a warning, warning, etc about the punishment to be suffered}
 * [4] error   {Error; Errors; Fallacy;}
 * [5] fatal   {Fatal; Catastrophic; Destructive; Cause failure}
 * 
 */
#define INFO(...) ns_log::ns_priv::info(__VA_ARGS__)
#define PROCESS(...) ns_log::ns_priv::process(__VA_ARGS__)
#define WARNING(...) ns_log::ns_priv::warning(__VA_ARGS__)
#define ERROR(...) ns_log::ns_priv::error(__VA_ARGS__)
#define FATAL(...) ns_log::ns_priv::fatal(__VA_ARGS__)

#define TEXT(...) ns_log::ns_priv::__print__(__VA_ARGS__)

} // namespace ns_log
