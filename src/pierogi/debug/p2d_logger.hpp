#ifndef P2D_LOGGER_HPP
#define P2D_LOGGER_HPP

#include <string>
#include <iostream>

namespace p2d { namespace debug {
    typedef std::string String;

    enum LogLevel {
        EXTREMELY_VERBOSE,
        INFO,
        DEBUG,
        ERROR,
        FATAL
    };

    std::string logLevelToString(const LogLevel& logLevel);

    class Logger {
    public:
        void log(const String& logString, const LogLevel logLevel = LogLevel::EXTREMELY_VERBOSE) const;
        void setLogLevel(const LogLevel& newLogLevel);

        static Logger* getInstancePtr();
        ~Logger();
    protected:
        Logger();

        static Logger* instancePtr;
    private:
        bool shouldLog(const LogLevel& logLevelGiven) const;
        LogLevel logLevel_ = LogLevel::EXTREMELY_VERBOSE;
    }; // Logger
} // namespace debug
} // namespace p2d

#endif