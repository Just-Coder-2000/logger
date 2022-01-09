#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

namespace ns_log
{

    enum class LogType
    {
        INIT,
        INFO,
        WARNING,
        ERROR,
        FATAL
    };

    static std::unordered_map<LogType, std::string> logMap({std::make_pair(LogType::INFO, "[ info  ] "),
                                                            std::make_pair(LogType::WARNING, "[warning] "),
                                                            std::make_pair(LogType::ERROR, "[ error ] "),
                                                            std::make_pair(LogType::FATAL, "[ fatal ] ")});

    class Logger
    {
    private:
        const LogType _logType;
        const std::string _prefix;

    public:
        Logger(const LogType &logType, const std::string &prefix)
            : _logType(logType), _prefix(prefix) {}

        Logger() = delete;
        Logger(const Logger &) = delete;

    public:
        const LogType &logType() const { return this->_logType; }

        const std::string &prefix() const { return this->_prefix; }
    };

    static std::ostream *loggerOS = &std::cout;

    static const Logger info(LogType::INFO, "\033[32m");
    static const Logger warning(LogType::WARNING, "\033[33m");
    static const Logger error(LogType::ERROR, "\033[31m");
    static const Logger fatal(LogType::FATAL, "\033[35m");

    static LogType curLogType = LogType::INIT;

    static const char endl = '\n';

    void setLoggerOS(std::ostream &os) { loggerOS = &os; }

    template <typename _Ty>
    const Logger &operator<<(const Logger &logger, const _Ty &msg)
    {
        *(loggerOS) << logger.prefix();

        if (logger.logType() != curLogType)
            *(loggerOS) << logMap.at(logger.logType()), curLogType = logger.logType();

        *(loggerOS) << msg;
        
        *(loggerOS) << "\033[37m";

        return logger;
    }

} // namespace ns_log
