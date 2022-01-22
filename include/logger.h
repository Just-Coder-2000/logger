#pragma once
/**
 * @file logger.h
 * @author csl (3079625093@qq.com)
 * @version 0.1
 * @date 2022-01-22
 * 
 * @copyright Copyright (c) 2022
 */

#include <iostream>
#include <string>
#include <unordered_map>
#include <ctime>
#include <tuple>

namespace ns_log
{

    enum class LogType;

    enum class ColorType;

    class Logger
    {
    private:
        const LogType _logType;
        const ColorType _descColor;
        const ColorType _msgColor;

    public:
        Logger(const LogType &logType, const ColorType &descColor, const ColorType &msgColor)
            : _logType(logType), _descColor(descColor), _msgColor(msgColor) {}

        Logger() = delete;
        Logger(const Logger &) = delete;

    public:
        const LogType &logType() const { return this->_logType; }

        const ColorType &descColor() const { return this->_descColor; }

        const ColorType &msgColor() const { return this->_msgColor; }
    };

    struct _Endl
    {
    };
    static const _Endl endl;
#pragma region params

    enum class LogType
    {
        INIT,
        INFO,
        PROCESS,
        WARNING,
        ERROR,
        FATAL
    };

    /**
     * @brief 
     * @return std::unordered_map<LogType, std::string> 
     */
    static const std::unordered_map<LogType, std::string> descMap({std::make_pair(LogType::INFO, "[ info  ] "),
                                                                   std::make_pair(LogType::PROCESS, "[process] "),
                                                                   std::make_pair(LogType::WARNING, "[warning] "),
                                                                   std::make_pair(LogType::ERROR, "[ error ] "),
                                                                   std::make_pair(LogType::FATAL, "[ fatal ] ")});

    enum class ColorType
    {
        NONE,
        B_NONE,
        BLACK,
        B_BLACK,
        RED,
        B_RED,
        GREEN,
        B_GREEN,
        BROWN,
        B_BROWN,
        YELLOW,
        B_YELLOW,
        BLUE,
        B_BLUE,
        PURPLE,
        B_PURPLE,
        CYAN,
        B_CYAN,
        GRAY,
        WHITE,
    };

#ifdef __linux__
    static const std::unordered_map<ColorType, std::string> colorMap({std::make_pair(ColorType::NONE, "\e[0m"),
                                                                      std::make_pair(ColorType::B_NONE, "\e[1m"),
                                                                      std::make_pair(ColorType::BLACK, "\e[0;30m"),
                                                                      std::make_pair(ColorType::B_BLACK, "\e[1;30m"),
                                                                      std::make_pair(ColorType::RED, "\e[0;31m"),
                                                                      std::make_pair(ColorType::B_RED, "\e[1;31m"),
                                                                      std::make_pair(ColorType::GREEN, "\e[0;32m"),
                                                                      std::make_pair(ColorType::B_GREEN, "\e[1;32m"),
                                                                      std::make_pair(ColorType::BROWN, "\e[0;33m"),
                                                                      std::make_pair(ColorType::B_BROWN, "\e[1;33m"),
                                                                      std::make_pair(ColorType::YELLOW, "\e[0;33m"),
                                                                      std::make_pair(ColorType::B_YELLOW, "\e[1;33m"),
                                                                      std::make_pair(ColorType::BLUE, "\e[0;34m"),
                                                                      std::make_pair(ColorType::B_BLUE, "\e[1;34m"),
                                                                      std::make_pair(ColorType::PURPLE, "\e[0;35m"),
                                                                      std::make_pair(ColorType::B_PURPLE, "\e[1;35m"),
                                                                      std::make_pair(ColorType::CYAN, "\e[0;36m"),
                                                                      std::make_pair(ColorType::B_CYAN, "\e[1;36m"),
                                                                      std::make_pair(ColorType::GRAY, "\e[0;37m"),
                                                                      std::make_pair(ColorType::WHITE, "\e[1;37m")});
#endif

    static std::ostream *loggerOS = &std::cout;

    static LogType curLogType = LogType::INIT;

    static bool printTime = true;

    static const Logger info(LogType::INFO, ColorType::B_NONE, ColorType::NONE);
    static const Logger process(LogType::PROCESS, ColorType::B_GREEN, ColorType::GREEN);
    static const Logger warning(LogType::WARNING, ColorType::B_YELLOW, ColorType::YELLOW);
    static const Logger error(LogType::ERROR, ColorType::B_RED, ColorType::RED);
    static const Logger fatal(LogType::FATAL, ColorType::B_PURPLE, ColorType::PURPLE);

    static void setOstream(std::ostream &os) { loggerOS = &os; }

    static void setPrintTime(bool printTime) { ns_log::printTime = printTime; }

    static std::tuple<uint, uint, uint> curTime()
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        return {ltm->tm_hour, ltm->tm_min, ltm->tm_sec};
    }

#pragma endregion

#ifdef __linux__
    template <typename _Ty>
    const Logger &operator<<(const Logger &logger, const _Ty &msg)
    {
        if (loggerOS == &std::cout)
            *(loggerOS) << colorMap.at(logger.descColor());

        if (logger.logType() != curLogType)
        {
            *(loggerOS) << descMap.at(logger.logType());
            curLogType = logger.logType();
            if (printTime)
            {
                auto [h, m, s] = curTime();
                *(loggerOS) << '[' << h << ':' << m << ':' << s << "] ";
            }
        }

        if (loggerOS == &std::cout)
            *(loggerOS) << colorMap.at(logger.msgColor());

        *(loggerOS) << msg;

        if (loggerOS == &std::cout)
            *(loggerOS) << colorMap.at(ColorType::NONE);

        return logger;
    }

#else
    template <typename _Ty>
    const Logger &operator<<(const Logger &logger, const _Ty &msg)
    {
        if (logger.logType() != curLogType)
        {
            *(loggerOS) << descMap.at(logger.logType());
            curLogType = logger.logType();
            if (printTime)
            {
                auto [h, m, s] = curTime();
                *(loggerOS) << '[' << h << ':' << m << ':' << s << "] ";
            }
        }

        *(loggerOS) << msg;

        return logger;
    }
#endif

    static const Logger &operator<<(const Logger &logger, const _Endl e)
    {
        curLogType = LogType::INIT, *(loggerOS) << '\n';
        return logger;
    }

#pragma region macro

#pragma region process
    void __print__process()
    {
        return;
    }

    template <typename ArgvType>
    void __print__process(const ArgvType &argv)
    {
        ns_log::process << argv;
        return;
    }

    template <typename ArgvType, typename... ElseType>
    void __print__process(const ArgvType &argv, const ElseType &...argvs)
    {
        ns_log::process << argv;
        return __print__process(argvs...);
    }

#define PROCESS(...)                       \
    ns_log::__print__process(__VA_ARGS__); \
    ns_log::process << (ns_log::endl);
#define PROCESS_BEG(...)                   \
    ns_log::__print__process(__VA_ARGS__); \
    ns_log::process << ('\n');
#define PROCESS_OUT(...)                   \
    ns_log::__print__process(__VA_ARGS__); \
    ns_log::process << ('\n');
#define PROCESS_END(...)                   \
    ns_log::__print__process(__VA_ARGS__); \
    ns_log::process << ns_log::endl;
#pragma endregion

#pragma region info
    void __print__info()
    {
        return;
    }

    template <typename ArgvType>
    void __print__info(const ArgvType &argv)
    {
        ns_log::info << argv;
        return;
    }

    template <typename ArgvType, typename... ElseType>
    void __print__info(const ArgvType &argv, const ElseType &...argvs)
    {
        ns_log::info << argv;
        return __print__info(argvs...);
    }

#define INFO(...)                       \
    ns_log::__print__info(__VA_ARGS__); \
    ns_log::info << (ns_log::endl);
#define INFO_BEG(...)                   \
    ns_log::__print__info(__VA_ARGS__); \
    ns_log::info << ('\n');
#define INFO_OUT(...)                   \
    ns_log::__print__info(__VA_ARGS__); \
    ns_log::info << ('\n');
#define INFO_END(...)                   \
    ns_log::__print__info(__VA_ARGS__); \
    ns_log::info << ns_log::endl;
#pragma endregion

#pragma region error
    void __print__error()
    {
        return;
    }

    template <typename ArgvType>
    void __print__error(const ArgvType &argv)
    {
        ns_log::error << argv;
        return;
    }

    template <typename ArgvType, typename... ElseType>
    void __print__error(const ArgvType &argv, const ElseType &...argvs)
    {
        ns_log::error << argv;
        return __print__error(argvs...);
    }

#define ERROR(...)                       \
    ns_log::__print__error(__VA_ARGS__); \
    ns_log::error << (ns_log::endl);
#define ERROR_BEG(...)                   \
    ns_log::__print__error(__VA_ARGS__); \
    ns_log::error << ('\n');
#define ERROR_OUT(...)                   \
    ns_log::__print__error(__VA_ARGS__); \
    ns_log::error << ('\n');
#define ERROR_END(...)                   \
    ns_log::__print__error(__VA_ARGS__); \
    ns_log::error << ns_log::endl;
#pragma endregion

#pragma region fatal
    void __print__fatal()
    {
        return;
    }

    template <typename ArgvType>
    void __print__fatal(const ArgvType &argv)
    {
        ns_log::fatal << argv;
        return;
    }

    template <typename ArgvType, typename... ElseType>
    void __print__fatal(const ArgvType &argv, const ElseType &...argvs)
    {
        ns_log::fatal << argv;
        return __print__fatal(argvs...);
    }

#define FATAL(...)                       \
    ns_log::__print__fatal(__VA_ARGS__); \
    ns_log::fatal << (ns_log::endl);
#define FATAL_BEG(...)                   \
    ns_log::__print__fatal(__VA_ARGS__); \
    ns_log::fatal << ('\n');
#define FATAL_OUT(...)                   \
    ns_log::__print__fatal(__VA_ARGS__); \
    ns_log::fatal << ('\n');
#define FATAL_END(...)                   \
    ns_log::__print__fatal(__VA_ARGS__); \
    ns_log::fatal << ns_log::endl;
#pragma endregion

#pragma region warning
    void __print__warning()
    {
        return;
    }

    template <typename ArgvType>
    void __print__warning(const ArgvType &argv)
    {
        ns_log::warning << argv;
        return;
    }

    template <typename ArgvType, typename... ElseType>
    void __print__warning(const ArgvType &argv, const ElseType &...argvs)
    {
        ns_log::warning << argv;
        return __print__warning(argvs...);
    }

#define WARNING(...)                       \
    ns_log::__print__warning(__VA_ARGS__); \
    ns_log::warning << (ns_log::endl);
#define WARNING_BEG(...)                   \
    ns_log::__print__warning(__VA_ARGS__); \
    ns_log::warning << ('\n');
#define WARNING_OUT(...)                   \
    ns_log::__print__warning(__VA_ARGS__); \
    ns_log::warning << ('\n');
#define WARNING_END(...)                   \
    ns_log::__print__warning(__VA_ARGS__); \
    ns_log::warning << ns_log::endl;
#pragma endregion

#pragma region plaintext

    void __print__()
    {
        return;
    }

    template <typename ArgvType>
    void __print__(const ArgvType &argv)
    {
        *(ns_log::loggerOS) << argv;
        return;
    }

    template <typename ArgvType, typename... ElseType>
    void __print__(const ArgvType &argv, const ElseType &...argvs)
    {
        *(ns_log::loggerOS) << argv;
        return __print__(argvs...);
    }

#define PLAINTEXT(...)              \
    ns_log::__print__(__VA_ARGS__); \
    *(ns_log::loggerOS) << '\n';

#pragma endregion

#pragma endregion

} // namespace ns_log
