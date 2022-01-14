#pragma once

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

    const Logger &operator<<(const Logger &logger, const _Endl e)
    {
        curLogType = LogType::INIT, *(loggerOS) << '\n';
        return logger;
    }

} // namespace ns_log
