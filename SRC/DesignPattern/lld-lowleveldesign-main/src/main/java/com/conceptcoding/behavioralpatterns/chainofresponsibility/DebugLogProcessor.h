#ifndef DEBUG_LOG_PROCESSOR_H
#define DEBUG_LOG_PROCESSOR_H

#include "LogProcessor.h"

// Concrete handler for DEBUG level
class DebugLogProcessor : public LogProcessor
{
public:
    explicit DebugLogProcessor(int logLevel)
    {
        this->level = logLevel;
    }

protected:
    void write(const std::string &message) override
    {
        std::cout << "DEBUG: " << message << std::endl;
    }
};

#endif // DEBUG_LOG_PROCESSOR_H
