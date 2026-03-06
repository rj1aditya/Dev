#ifndef INFO_LOG_PROCESSOR_H
#define INFO_LOG_PROCESSOR_H

#include "LogProcessor.h"

// Concrete handler for INFO level
class InfoLogProcessor : public LogProcessor
{
public:
    explicit InfoLogProcessor(int logLevel)
    {
        this->level = logLevel;
    }

protected:
    void write(const std::string &message) override
    {
        std::cout << "INFO: " << message << std::endl;
    }
};

#endif // INFO_LOG_PROCESSOR_H
