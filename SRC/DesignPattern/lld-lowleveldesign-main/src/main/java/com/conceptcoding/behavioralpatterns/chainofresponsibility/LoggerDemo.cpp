#include <iostream>
#include <memory>
#include "LogProcessor.h"
#include "DebugLogProcessor.h"
#include "InfoLogProcessor.h"
#include "ErrorLogProcessor.h"
#include "FatalLogProcessor.h"

using namespace std;

// Forward declaration
LogProcessor *getChainOfLoggers();

// Client code
int main()
{
    cout << "###### Chain of Responsibility Design Pattern ######" << endl;

    // Get the chain of loggers
    LogProcessor *logProcessor = getChainOfLoggers();

    cout << "Logging messages:" << endl;
    cout << "===== Logging DEBUG message =====" << endl;
    logProcessor->logMessage(LogProcessor::DEBUG, "This is a debug message");
    cout << "===== Logging INFO message =====" << endl;
    logProcessor->logMessage(LogProcessor::INFO, "This is an info message");
    cout << "===== Logging ERROR message =====" << endl;
    logProcessor->logMessage(LogProcessor::ERROR, "This is an error message");
    cout << "===== Logging FATAL message =====" << endl;
    logProcessor->logMessage(LogProcessor::FATAL, "This is a fatal message");

    // Clean up
    delete logProcessor->nextLoggerProcessor->nextLoggerProcessor->nextLoggerProcessor; // Delete FATAL
    delete logProcessor->nextLoggerProcessor->nextLoggerProcessor;                      // Delete ERROR
    delete logProcessor->nextLoggerProcessor;                                           // Delete INFO
    delete logProcessor;                                                                // Delete DEBUG

    return 0;
}

LogProcessor *getChainOfLoggers()
{
    LogProcessor *fatalLogger = new FatalLogProcessor(LogProcessor::FATAL); // 4
    LogProcessor *errorLogger = new ErrorLogProcessor(LogProcessor::ERROR); // 3
    LogProcessor *infoLogger = new InfoLogProcessor(LogProcessor::INFO);    // 2
    LogProcessor *debugLogger = new DebugLogProcessor(LogProcessor::DEBUG); // 1

    //  Dynamic Chaining: DEBUG -> INFO -> ERROR -> FATAL
    debugLogger->setNextLogger(infoLogger);
    infoLogger->setNextLogger(errorLogger);
    errorLogger->setNextLogger(fatalLogger);
    // fatalLogger->nextLoggerProcessor is nullptr; // Last logger in chain

    return debugLogger; // Return the first LogProcessor in chain
}
