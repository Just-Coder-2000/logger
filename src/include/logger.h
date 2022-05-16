#pragma once

/**
 * @file logger.h
 * @author csl (3079625093@qq.com)
 * @version 0.1
 * @date 2022-01-27
 *
 * @copyright Copyright (c) 2022
 */

#include "fmt/color.h"
#include "fmt/format.h"
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

/**
 * @brief the main message type macroes:
 * everything that overrides the operator '<<' can use the static functions.
 *
 * @param info
 * {Information; Message; real-time info Of information; Of messages;
 * Informative}
 * @param process
 * {The process of achieving a goal; The development of things, especially the
 * steps of natural change;}
 * @param warning
 * {about possible accidents, etc.; a warning, warning, etc about the punishment
 * to be suffered}
 * @param error
 * {Error; Errors; Fallacy;}
 * @param fatal
 * {Fatal; Catastrophic; Destructive; Cause failure}
 *
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

namespace ns_log {

  namespace ns_priv {
    /**
     * @brief base logger
     */
    class Logger {
    public:
      /**
       * @brief the members
       */
      std::ostream *_logerOS;

    public:
      /**
       * @brief construct a new Logger object
       */
      Logger(std::ostream *os) : _logerOS(os) {}

      virtual ~Logger() {}

      template <typename... ArgvsType>
      Logger &operator()(const std::string &desc, fmt::terminal_color color, const ArgvsType &...argvs) {
        std::stringstream stream;
        Logger::__print__(stream, argvs...);
        *(this->_logerOS) << this->getMessageHeader(desc, color) << ' '
                          << this->getMessage(stream.str(), color);
        return *this;
      }

      template <typename... ArgvsType>
      Logger &plaintext(const ArgvsType &...argvs) {
        std::stringstream stream;
        Logger::__print__(stream, argvs...);
        *(this->_logerOS) << this->getMessage(stream.str(), fmt::terminal_color::white);
        return *this;
      }

      template <typename... ArgvsType>
      Logger &info(const ArgvsType &...argvs) {
        (*this)("info", fmt::terminal_color::bright_green, argvs...);
        return *this;
      }

      template <typename... ArgvsType>
      Logger &warning(const ArgvsType &...argvs) {
        (*this)("warning", fmt::terminal_color::bright_yellow, argvs...);
        return *this;
      }

      template <typename... ArgvsType>
      Logger &process(const ArgvsType &...argvs) {
        (*this)("process", fmt::terminal_color::bright_blue, argvs...);
        return *this;
      }

      template <typename... ArgvsType>
      Logger &fatal(const ArgvsType &...argvs) {
        (*this)("fatal", fmt::terminal_color::bright_magenta, argvs...);
        return *this;
      }

      template <typename... ArgvsType>
      Logger &error(const ArgvsType &...argvs) {
        (*this)("error", fmt::terminal_color::bright_red, argvs...);
        return *this;
      }

      virtual std::string getMessageHeader(const std::string &desc, fmt::terminal_color color) = 0;

      virtual std::string getMessage(const std::string &msg, fmt::terminal_color color) = 0;

    protected:
      Logger &__print__(std::ostream &os) {
        os << '\n';
        return *this;
      }

      template <typename ArgvType>
      Logger &__print__(std::ostream &os, const ArgvType &argv) {
        os << argv << '\n';
        return *this;
      }

      template <typename ArgvType, typename... ArgvsType>
      Logger &__print__(std::ostream &os, const ArgvType &argv, const ArgvsType &...argvs) {
        os << argv;
        Logger::__print__(os, argvs...);
        return *this;
      }

      /**
       * @brief get the time when the message is outputed
       *
       * @return double
       */
      double curTime() {
        auto now = std::chrono::system_clock::now();
        return std::chrono::time_point_cast<std::chrono::duration<double>>(now)
            .time_since_epoch()
            .count();
      }

    protected:
      Logger() = delete;
      Logger(const Logger &) = delete;
      Logger(Logger &&) = delete;
      Logger &operator=(const Logger &) = delete;
      Logger &operator=(Logger &&) = delete;
    };

  } // namespace ns_priv

  class StdLogger : public ns_priv::Logger {

  public:
    StdLogger(std::ostream &os) : Logger(&os) {}

    virtual ~StdLogger() {}

    virtual std::string getMessageHeader(const std::string &desc, fmt::terminal_color color) override {
      auto flag = fmt::format(fmt::fg(color) | fmt::emphasis::bold, "{}", desc);
      auto tm = fmt::format(fmt::fg(color) | fmt::emphasis::italic, "{:.6f}(s)", Logger::curTime());
      return fmt::format("[ {0} ]-[ {1} ]", flag, tm);
    }

    virtual std::string getMessage(const std::string &msg, fmt::terminal_color color) override {
      return fmt::format(fmt::fg(color) | fmt::emphasis::italic, "{}", msg);
    }
  };

  class FileLogger : public ns_priv::Logger {
  public:
    FileLogger(const std::string &filename) : Logger(new std::ofstream(filename, std::ios::out)) {}

    virtual ~FileLogger() {
      delete this->_logerOS;
    }

    virtual std::string getMessageHeader(const std::string &desc, fmt::terminal_color color) override {
      return fmt::format("[ {0} ]-[ {1:.6f}(s) ]", desc, Logger::curTime());
    }

    virtual std::string getMessage(const std::string &msg, fmt::terminal_color color) override {
      return msg;
    }
  };

  namespace ns_priv {
    /**
     * @brief params to control
     * @param _splitor_ the splitor to split the elements
     * @param _firName_ the describe name for the first element of the std::pair
     * @param _sedName_ the describe name for the second element of the std::pair
     */
    static const std::string _splitor_(", ");

    static StdLogger stdCoutLogger(std::cout);
  } // namespace ns_priv

  /**
   * @brief the main message type macroes
   *
   * [0] plaintext {the plain text}
   * [1] info    {Information; Message; real-time info Of information; Of messages; Informative}
   * [2] process {The process of achieving a goal; The development of things, especially the steps of natural change;}
   * [3] warning {about possible accidents, etc.; a warning, warning, etc about the punishment to be suffered}
   * [4] error   {Error; Errors; Fallacy;}
   * [5] fatal   {Fatal; Catastrophic; Destructive; Cause failure}
   *
   */

  template <typename... ArgvsType>
  static ns_priv::Logger &plaintext(const ArgvsType &...argvs) {
    return ns_log::ns_priv::stdCoutLogger.plaintext(argvs...);
  }
#define LOG_PLAINTEXT(...) \
  ns_log::ns_priv::stdCoutLogger.plaintext(__VA_ARGS__);
#define LOG_PLAINTEXT_F(flogger, ...) \
  flogger.plaintext(__VA_ARGS__);

  template <typename... ArgvsType>
  static ns_priv::Logger &info(const ArgvsType &...argvs) {
    return ns_log::ns_priv::stdCoutLogger.info(argvs...);
  }
#define LOG_INFO(...) \
  ns_log::ns_priv::stdCoutLogger.info(__VA_ARGS__);
#define LOG_INFO_F(flogger, ...) \
  flogger.info(__VA_ARGS__);

  template <typename... ArgvsType>
  static ns_priv::Logger &process(const ArgvsType &...argvs) {
    return ns_log::ns_priv::stdCoutLogger.process(argvs...);
  }
#define LOG_PROCESS(...) \
  ns_log::ns_priv::stdCoutLogger.process(__VA_ARGS__);
#define LOG_PROCESS_F(flogger, ...) \
  flogger.process(__VA_ARGS__);

  template <typename... ArgvsType>
  static ns_priv::Logger &warning(const ArgvsType &...argvs) {
    return ns_log::ns_priv::stdCoutLogger.warning(argvs...);
  }
#define LOG_WARNING(...) \
  ns_log::ns_priv::stdCoutLogger.warning(__VA_ARGS__);
#define LOG_WARNING_F(flogger, ...) \
  flogger.warning(__VA_ARGS__);

  template <typename... ArgvsType>
  static ns_priv::Logger &error(const ArgvsType &...argvs) {
    return ns_log::ns_priv::stdCoutLogger.error(argvs...);
  }
#define LOG_ERROR(...) \
  ns_log::ns_priv::stdCoutLogger.error(__VA_ARGS__);
#define LOG_ERROR_F(flogger, ...) \
  flogger.error(__VA_ARGS__);

  template <typename... ArgvsType>
  static ns_priv::Logger &fatal(const ArgvsType &...argvs) {
    return ns_log::ns_priv::stdCoutLogger.fatal(argvs...);
  }
#define LOG_FATAL(...) \
  ns_log::ns_priv::stdCoutLogger.fatal(__VA_ARGS__);
#define LOG_FATAL_F(flogger, ...) \
  flogger.fatal(__VA_ARGS__);

// the prefix used when print variables
#define LOG_PREFIX "-- "

// the suffix used when print variables
#define LOG_SUFFIX ""

// a macro launcher
#define MACRO_VAR_ARGS_IMPL_COUNT(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, N, ...) N
#define COUNT_MACRO_VAR_ARGS(...) MACRO_VAR_ARGS_IMPL_COUNT(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define MACRO_COMBINE_2(MACRO, ARGS_COUNT) MACRO##ARGS_COUNT
#define MACRO_COMBINE_1(MACRO, ARGS_COUNT) MACRO_COMBINE_2(MACRO, ARGS_COUNT)
#define MACRO_COMBINE(MACRO, ARGS_COUNT) MACRO_COMBINE_1(MACRO, ARGS_COUNT)

#define MACRO_LAUNCHER(MACRO, ...)                        \
  MACRO_COMBINE(MACRO, COUNT_MACRO_VAR_ARGS(__VA_ARGS__)) \
  (__VA_ARGS__)

// a helper
#define _LOG_VAR_PACK_(var) \
#var << ": " << var << ", "

#define _LOG_VAR_1(var) #var << ": " << var
#define _LOG_VAR_2(var, ...) _LOG_VAR_PACK_(var) << _LOG_VAR_1(__VA_ARGS__)
#define _LOG_VAR_3(var, ...) _LOG_VAR_PACK_(var) << _LOG_VAR_2(__VA_ARGS__)
#define _LOG_VAR_4(var, ...) _LOG_VAR_PACK_(var) << _LOG_VAR_3(__VA_ARGS__)
#define _LOG_VAR_5(var, ...) _LOG_VAR_PACK_(var) << _LOG_VAR_4(__VA_ARGS__)
#define _LOG_VAR_6(var, ...) _LOG_VAR_PACK_(var) << _LOG_VAR_5(__VA_ARGS__)
#define _LOG_VAR_7(var, ...) _LOG_VAR_PACK_(var) << _LOG_VAR_6(__VA_ARGS__)
#define _LOG_VAR_8(var, ...) _LOG_VAR_PACK_(var) << _LOG_VAR_7(__VA_ARGS__)
#define _LOG_VAR_9(var, ...) _LOG_VAR_PACK_(var) << _LOG_VAR_8(__VA_ARGS__)
#define _LOG_VAR_10(var, ...) _LOG_VAR_PACK_(var) << _LOG_VAR_9(__VA_ARGS__)

// print variables for debug or something else
#define LOG_VAR(...)                                                \
  std::cout << LOG_PREFIX << MACRO_LAUNCHER(_LOG_VAR_, __VA_ARGS__) \
            << LOG_SUFFIX << std::endl;

// print var value to a file
#define LOG_VAR_F(flogger, ...)                                               \
  *(flogger._logerOS) << LOG_PREFIX << MACRO_LAUNCHER(_LOG_VAR_, __VA_ARGS__) \
                      << LOG_SUFFIX << std::endl;

} // namespace ns_log

#pragma region output for container

/**
 * @brief overload the operator '<<' for std::pair
 */
template <typename Key, typename Val>
std::ostream &operator<<(std::ostream &os, const std::pair<Key, Val> &p) {
  os << "{'" << p.first << "': " << p.second << '}';
  return os;
}

/**
 * @brief output format for container
 */
template <typename ConType>
std::ostream &orderedConer(std::ostream &os, const ConType &s) {
  os << '[';
  if (s.empty()) {
    os << "]";
    return os;
  }
  auto iter = s.cbegin();
  for (; iter != (--s.cend()); ++iter)
    os << *iter << ns_log::ns_priv::_splitor_;
  os << *iter << ']';
  return os;
}

/**
 * @brief output format for unordered container
 */
template <typename ConType>
std::ostream &unorderedConer(std::ostream &os, const ConType &c) {
  os << '[';
  if (c.empty()) {
    os << "]";
    return os;
  }
  std::stringstream stream;
  for (const auto &elem : c)
    stream << elem << ns_log::ns_priv::_splitor_;
  std::string str = stream.str();
  os << std::string_view(str.c_str(),
                         str.size() - ns_log::ns_priv::_splitor_.size())
     << ']';
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
std::ostream &operator<<(std::ostream &os, const std::map<Key, Val> &m) {
  return orderedConer(os, m);
}
#endif

#ifdef FORMAT_MULTIMAP
#include <map>
/**
 * @brief overload the operator '<<' for std::multimap
 */
template <typename Key, typename Val>
std::ostream &operator<<(std::ostream &os, const std::multimap<Key, Val> &m) {
  return orderedConer(os, m);
}
#endif

#ifdef FORMAT_UNORDERED_MAP
#include <unordered_map>
/**
 * @brief overload the operator '<<' for std::unordered_map
 */
template <typename Key, typename Val>
std::ostream &operator<<(std::ostream &os,
                         const std::unordered_map<Key, Val> &m) {
  return unorderedConer(os, m);
}

#endif

#ifdef FORMAT_UNORDERED_MULTIMAP
#include <unordered_map>
/**
 * @brief overload the operator '<<' for std::unordered_multimap
 */
template <typename Key, typename Val>
std::ostream &operator<<(std::ostream &os,
                         const std::unordered_multimap<Key, Val> &m) {
  return unorderedConer(os, m);
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
std::ostream &operator<<(std::ostream &os, const std::set<Val> &s) {
  return orderedConer(os, s);
}
#endif

#ifdef FORMAT_UNORDERED_SET
#include <unordered_set>
/**
 * @brief overload the operator '<<' for std::unordered_set
 */
template <typename Val>
std::ostream &operator<<(std::ostream &os, const std::unordered_set<Val> &s) {
  return unorderedConer(os, s);
}
#endif

#ifdef FORMAT_MULTISET
#include <set>
/**
 * @brief overload the operator '<<' for std::multiset
 */
template <typename Val>
std::ostream &operator<<(std::ostream &os, const std::multiset<Val> &s) {
  return orderedConer(os, s);
}
#endif

#ifdef FORMAT_UNORDERED_MULTISET
#include <unordered_set>
/**
 * @brief overload the operator '<<' for std::unordered_multiset
 */
template <typename Val>
std::ostream &operator<<(std::ostream &os,
                         const std::unordered_multiset<Val> &s) {
  return unorderedConer(os, s);
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
std::ostream &operator<<(std::ostream &os, const std::vector<Val> &s) {
  return orderedConer(os, s);
}
#endif

#ifdef FORMAT_LIST
#include <list>
/**
 * @brief overload the operator '<<' for std::list
 */
template <typename Val>
std::ostream &operator<<(std::ostream &os, const std::list<Val> &s) {
  return orderedConer(os, s);
}
#endif

#ifdef FORMAT_DEQUE
#include <deque>
/**
 * @brief overload the operator '<<' for std::deque
 */
template <typename Val>
std::ostream &operator<<(std::ostream &os, const std::deque<Val> &s) {
  return orderedConer(os, s);
}
#endif

#ifdef FORMAT_ARRAY
#include <array>
/**
 * @brief overload the operator '<<' for std::array
 */
template <typename Val, std::size_t Size>
std::ostream &operator<<(std::ostream &os, const std::array<Val, Size> &s) {
  os << '[';
  for (int i = 0; i != s.size() - 1; ++i)
    os << s[i] << ns_log::ns_priv::_splitor_;
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
std::ostream &operator<<(std::ostream &os, const std::stack<Val> &s) {
  if (s.empty()) {
    os << "[]";
    return os;
  }
  os << "['top' ";
  auto cs = s;
  while (cs.size() != 1) {
    os << cs.top() << ns_log::ns_priv::_splitor_;
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
std::ostream &operator<<(std::ostream &os, const std::queue<Val> &q) {
  if (q.empty()) {
    os << "[]";
    return os;
  }
  os << "['front' ";
  auto cq = q;
  while (cq.size() != 1) {
    os << cq.front() << ns_log::ns_priv::_splitor_;
    cq.pop();
  }
  os << cq.front() << "]";
  return os;
}
#endif

#pragma endregion
