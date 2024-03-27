
#ifndef LOG4DATA_H_
#define LOG4DATA_H_

#include <string>
#include <vector>
#include <map>
#include "CoreLog.h"

using namespace bvmf::risk::core;

// Macro definitions remain the same but will use CoreLog methods
#define LOG4DATA_ERROR(message) Log4Data::getInstance()->logError(message, __FILENAME__, __FUNCTION__, __LINE__);
#define LOG4DATA_INFO(message) Log4Data::getInstance()->logInformation(message, __FILENAME__, __FUNCTION__, __LINE__);
#define LOG4DATA_TRACE(message) Log4Data::getInstance()->logTrace(message, __FILENAME__, __FUNCTION__, __LINE__);
#define LOG4DATA_WARN(message) Log4Data::getInstance()->logWarning(message, __FILENAME__, __FUNCTION__, __LINE__);


enum CoreType {
    
};

enum LogLevel {
    
};

class Log4Data {
private:
    Log4Data();
    static Log4Data *m_instance;

    // Updated to reflect removal of specific Log4cxx configurations
    bool m_UseLog;
    std::map<std::string, std::string> m_paramsLog;

    CoreType m_type;

public:
    ~Log4Data();
    static Log4Data* getInstance();

    void setCore(const CoreType &type);

    // Simplified parameter set methods
    void setParamLog(const std::string &key, const std::string &value);
    void setParamLog(const std::string &key, int value);

    // Updated logging methods
    void logInformation(const std::string &message, const std::string &file = "", const std::string &function = "", int line = 0);
    void logError(const std::string &message, const std::string &file = "", const std::string &function = "", int line = 0);
    void logTrace(const std::string &message, const std::string &file = "", const std::string &function = "", int line = 0);
    void logWarning(const std::string &message, const std::string &file = "", const std::string &function = "", int line = 0);

    // Methods for structured data logging might need adaptation to utilize CoreLog or OpenTelemetry's structured logging capabilities
    void logInformation(const logDataInput &value);
    void logInformation(const logDataOutput &value);
    void logInformation(const logDataStatus &value);

    // Configuration and utility methods adapted for use without Log4cxx
    bool isEnabled(LogLevel level = L_TRACE);
    void enable(bool value);
    short getLevel();
};

#endif // LOG4DATA_H_
