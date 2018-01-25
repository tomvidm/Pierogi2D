#include "p2d_logger.hpp"

namespace p2d { namespace debug {
    Logger* Logger::instancePtr = nullptr;

    std::string logLevelToString(const LogLevel& logLevel) {
        switch (logLevel) {
            case LogLevel::EXTREMELY_VERBOSE:
                return "VERBOSE: ";
            case LogLevel::INFO:
                return "INFO:    ";
            case LogLevel::DEBUG:
                return "DEBUG:   ";
            case LogLevel::ERROR:
                return "ERROR:   ";
            case LogLevel::FATAL:
                return "FATAL:   ";
            default:
                return "MAKE AMERICA GREAT AGAIN: ";
        } // switch
    } // logLevelToString

    void Logger::log(const String& logString, const LogLevel logLevel) const {
        if (shouldLog(logLevel)) {
            std::cout << logLevelToString(logLevel) << logString << std::endl;
        } // if
    } // log

    void Logger::setLogLevel(const LogLevel& newLogLevel) {
        logLevel_ = newLogLevel;
    } // setLogLevel

    Logger* Logger::getInstancePtr() {
        if (instancePtr == nullptr) {
            instancePtr = new Logger;
        } // if
        return instancePtr;
    } // getInstancePtr

    Logger::~Logger() {
        delete instancePtr;
    } // destructor

    Logger::Logger() {
        ;
    } // constructor

    bool Logger::shouldLog(const LogLevel& logLevelGiven) const {
        return static_cast<int>(logLevelGiven) >= static_cast<int>(logLevel_);
    } // shouldLog
} // namespace debug
} // namespace p2d