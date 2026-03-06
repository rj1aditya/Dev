#ifndef LOG_PROCESSOR_H
#define LOG_PROCESSOR_H

#include <string>
#include <iostream>

// Abstract Logger class - defines the chain structure
class LogProcessor
{
public:
    static const int DEBUG = 1;
    static const int INFO = 2;
    static const int ERROR = 3;
    static const int FATAL = 4;

    LogProcessor() : level(0), nextLoggerProcessor(nullptr) {}
    virtual ~LogProcessor() = default;

    void setNextLogger(LogProcessor *nextLogger)
    {
        this->nextLoggerProcessor = nextLogger;
    }

    void logMessage(int logLevel, const std::string &message)
    {
        if (this->level == logLevel)
        {
            write(message);
            return;
        }

        // Pass to next handler in chain if exists
        if (this->nextLoggerProcessor != nullptr)
        {
            this->nextLoggerProcessor->logMessage(logLevel, message);
        }
    }

protected:
    int level;
    LogProcessor *nextLoggerProcessor;

    virtual void write(const std::string &message) = 0;
};

#endif // LOG_PROCESSOR_H
