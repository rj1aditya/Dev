#include <iostream>
#include <string>
#include <vector>
using namespace std;

class ILoggerWriter
{
public:
    ILoggerWriter() = default;

    virtual void write(string message) = 0;
};

class ConsoleLoggerWriter : public ILoggerWriter
{
public:
    ConsoleLoggerWriter() = default;

    void write(string message) override
    {
        cout << "Console Logger: " << message << endl;
    }
};

class FileLoggerWriter : public ILoggerWriter
{
public:
    FileLoggerWriter() = default;

    void write(string message) override
    {
        cout << "File Logger: " << message << endl;
    }
};

class DatabaseLoggerWriter : public ILoggerWriter
{
public:
    DatabaseLoggerWriter() = default;

    void write(string message) override
    {
        cout << "Database Logger: " << message << endl;
    }
};

enum class LogLevel
{
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    FATAL
};

class Logger
{
    LogLevel logLevel;
    vector<ILoggerWriter *> loggerWriter;

public:
    Logger(LogLevel logLvl) : logLevel(logLvl) {}

    void addLoggerWriter(ILoggerWriter *writer)
    {
        loggerWriter.push_back(writer);
    }

    void log(string message, LogLevel level)
    {
        if (level >= logLevel)
        {
            for (auto writer : loggerWriter)
                writer->write(message);
        }
    }
};

int main()
{
    ILoggerWriter *consoleLogger = new ConsoleLoggerWriter();
    ILoggerWriter *fileLogger = new FileLoggerWriter();
    ILoggerWriter *databaseLogger = new DatabaseLoggerWriter();

    Logger logger(LogLevel::ERROR);
    logger.addLoggerWriter(consoleLogger);
    logger.addLoggerWriter(fileLogger);
    logger.addLoggerWriter(databaseLogger);

    logger.log("This is an info message.", LogLevel::INFO);
    logger.log("This is a debug message.", LogLevel::DEBUG);
    logger.log("This is a warning message.", LogLevel::WARNING);
    logger.log("This is an error message.", LogLevel::ERROR);
    logger.log("This is a fatal message.", LogLevel::FATAL);

    return 0;
}
