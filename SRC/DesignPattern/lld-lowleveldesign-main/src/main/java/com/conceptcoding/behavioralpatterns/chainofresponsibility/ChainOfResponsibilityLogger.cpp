#include <iostream>
#include <string>
#include <memory>

using namespace std;

// Abstract base class - defines the chain structure
class LogProcessor
{
protected:
    int level;
    shared_ptr<LogProcessor> nextLoggerProcessor;

public:
    // Log level constants
    static constexpr int DEBUG = 1;
    static constexpr int INFO = 2;
    static constexpr int ERROR = 3;
    static constexpr int FATAL = 4;

    LogProcessor(int level) : level(level), nextLoggerProcessor(nullptr) {}

    virtual ~LogProcessor() = default;

    void setNextLogger(shared_ptr<LogProcessor> nextLogger)
    {
        this->nextLoggerProcessor = nextLogger;
    }

    void logMessage(int level, const string &message)
    {
        if (this->level == level)
        {
            write(message);
            return;
        }

        // Pass to next handler in chain if exists
        if (this->nextLoggerProcessor != nullptr)
        {
            this->nextLoggerProcessor->logMessage(level, message);
        }
    }

protected:
    virtual void write(const string &message) = 0;
};

// Concrete handler for DEBUG level
class DebugLogProcessor : public LogProcessor
{
public:
    DebugLogProcessor(int level) : LogProcessor(level) {}

    void write(const string &message) override
    {
        cout << "DEBUG: " << message << endl;
    }
};

// Concrete handler for INFO level
class InfoLogProcessor : public LogProcessor
{
public:
    InfoLogProcessor(int level) : LogProcessor(level) {}

    void write(const string &message) override
    {
        cout << "INFO: " << message << endl;
    }
};

// Concrete handler for ERROR level
class ErrorLogProcessor : public LogProcessor
{
public:
    ErrorLogProcessor(int level) : LogProcessor(level) {}

    void write(const string &message) override
    {
        cout << "ERROR: " << message << endl;
    }
};

// Concrete handler for FATAL level
class FatalLogProcessor : public LogProcessor
{
public:
    FatalLogProcessor(int level) : LogProcessor(level) {}

    void write(const string &message) override
    {
        cout << "FATAL: " << message << endl;
    }
};

// Client code
class LoggerDemo
{
public:
    static shared_ptr<LogProcessor> getChainOfLoggers()
    {
        auto fatalLogger = make_shared<FatalLogProcessor>(LogProcessor::FATAL); // 4
        auto errorLogger = make_shared<ErrorLogProcessor>(LogProcessor::ERROR); // 3
        auto infoLogger = make_shared<InfoLogProcessor>(LogProcessor::INFO);    // 2
        auto debugLogger = make_shared<DebugLogProcessor>(LogProcessor::DEBUG); // 1

        // Dynamic Chaining: DEBUG -> INFO -> ERROR -> FATAL
        debugLogger->setNextLogger(infoLogger);
        infoLogger->setNextLogger(errorLogger);
        errorLogger->setNextLogger(fatalLogger);
        // fatalLogger->nextLoggerProcessor is nullptr; // Last logger in chain

        return debugLogger; // Return the first LogProcessor in chain
    }

    static void main()
    {
        cout << "###### Chain of Responsibility Design Pattern ######" << endl;

        // Get the chain of loggers
        auto logProcessor = getChainOfLoggers();

        cout << "Logging messages:" << endl;
        cout << "===== Logging DEBUG message =====" << endl;
        logProcessor->logMessage(LogProcessor::DEBUG, "This is a debug message");
        cout << "===== Logging INFO message =====" << endl;
        logProcessor->logMessage(LogProcessor::INFO, "This is an info message");
        cout << "===== Logging ERROR message =====" << endl;
        logProcessor->logMessage(LogProcessor::ERROR, "This is an error message");
        cout << "===== Logging FATAL message =====" << endl;
        logProcessor->logMessage(LogProcessor::FATAL, "This is a fatal message");
    }
};

// Entry point
int main()
{
    LoggerDemo::main();
    return 0;
}