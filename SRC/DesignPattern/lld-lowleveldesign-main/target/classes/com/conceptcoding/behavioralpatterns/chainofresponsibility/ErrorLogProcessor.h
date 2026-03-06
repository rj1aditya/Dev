#ifndef ERROR_LOG_PROCESSOR_H
#define ERROR_LOG_PROCESSOR_H

#include "LogProcessor.h"

// Concrete handler for ERROR level
class ErrorLogProcessor : public LogProcessor
{
public:
    explicit ErrorLogProcessor(int logLevel)
    {
        this->level = logLevel;
    }

protected:
    void write(const std::string &message) override
    {
        std::cout << "ERROR: " << message << std::endl;
    }
};

#endif // ERROR_LOG_PROCESSOR_H
