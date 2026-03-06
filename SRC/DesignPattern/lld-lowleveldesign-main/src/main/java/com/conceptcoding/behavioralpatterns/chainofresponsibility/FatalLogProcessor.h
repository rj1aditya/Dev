#ifndef FATAL_LOG_PROCESSOR_H
#define FATAL_LOG_PROCESSOR_H

#include "LogProcessor.h"

// Concrete handler for FATAL level
class FatalLogProcessor : public LogProcessor
{
public:
    explicit FatalLogProcessor(int logLevel)
    {
        this->level = logLevel;
    }

protected:
    void write(const std::string &message) override
    {
        std::cout << "FATAL: " << message << std::endl;
    }
};

#endif // FATAL_LOG_PROCESSOR_H
