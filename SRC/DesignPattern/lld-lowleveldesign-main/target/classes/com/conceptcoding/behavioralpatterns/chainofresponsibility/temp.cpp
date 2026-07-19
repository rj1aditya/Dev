#include<iostream>
#include<string>
#include<memory>
#include<string>

using namespace std;


class LogProcessor
{
    static constexpr int DEBUG = 1;
    static constexpr int INFO = 2;
    static constexpr int WARNING = 3;
    static constexpr int ERROR = 3;
    static constexpr int FATAL = 4;

    shared_ptr<LogProcessor> nextLoggerProcessor;
    int level;
    public:
    LogProcessor(int level) : level(level), nextLoggerProcessor(nullptr) {}

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


    virtual void write(const string &message) = 0;
};

class DebugLogProcessor : public LogProcessor
{
    public:
    DebugLogProcessor(int level) : LogProcessor(level) {}

    void write(const string &message) override
    {
        cout << "DEBUG: " << message << endl;
    }
};


class InfoLogProcessor : public LogProcessor
{
    public:
    InfoLogProcessor(int level) : LogProcessor(level) {}

    void write(const string &message) override
    {
        cout << "INFO: " << message << endl;
    }
};

class WarningLogProcessor : public LogProcessor
{
    public:
    WarningLogProcessor(int level) : LogProcessor(level) {}

    void write(const string &message) override
    {
        cout << "WARNING: " << message << endl;
    }
};

class ErrorLogProcessor : public LogProcessor
{
    public:
    ErrorLogProcessor(int level) : LogProcessor(level) {}

    void write(const string &message) override
    {
        cout << "ERROR: " << message << endl;
    }
};

class FatalLogProcessor : public LogProcessor
{
    public:
    FatalLogProcessor(int level) : LogProcessor(level) {}

    void write(const string &message) override
    {
        cout << "FATAL: " << message << endl;
    }
};  


int main()
{
    shared_ptr<LogProcessor> debugLogger = make_shared<DebugLogProcessor>(1);
    shared_ptr<LogProcessor> infoLogger = make_shared<InfoLogProcessor>(2);
    shared_ptr<LogProcessor> warningLogger = make_shared<WarningLogProcessor>(3);
    shared_ptr<LogProcessor> errorLogger = make_shared<ErrorLogProcessor>(3);
    shared_ptr<LogProcessor> fatalLogger = make_shared<FatalLogProcessor>(4);

    debugLogger->setNextLogger(infoLogger);
    infoLogger->setNextLogger(warningLogger);
    warningLogger->setNextLogger(errorLogger);
    errorLogger->setNextLogger(fatalLogger);


    debugLogger->logMessage(1, "This is a debug message.");
    debugLogger->logMessage(2, "This is an info message.");
    debugLogger->logMessage(3, "This is a warning message.");
    debugLogger->logMessage(3, "This is an error message.");
    debugLogger->logMessage(4, "This is a fatal message.");

    return 0;
}