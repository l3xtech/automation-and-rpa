#include "Log4Data.h"
#include <sstream>
#include <iostream>
#include <cstdlib>
#include "CoreLog.h"

using namespace bvmf::risk::core;

Log4Data* Log4Data::m_instance = nullptr;

Log4Data::Log4Data() : m_UseLog(true) {}

Log4Data::~Log4Data() {}

Log4Data* Log4Data::getInstance() {
    if (m_instance == nullptr) {
        m_instance = new Log4Data();
    }
    return m_instance;
}

void Log4Data::setCore(const CoreType &type) {
    m_type = type;
}

void Log4Data::setParamLog(std::string key, std::string value) {
    m_paramsLog[key] = value;
}

void Log4Data::setParamLog(std::string key, int value) {
    m_paramsLog[key] = std::to_string(value);
}

std::string Log4Data::getMessageWithParams(const std::string &message) {
    std::stringstream messageBuilder;
    for (const auto& param : m_paramsLog) {
        messageBuilder << param.first << ": " << param.second << ", ";
    }
    messageBuilder << message;
    return messageBuilder.str();
}

void Log4Data::logInformation(const std::string &message, const std::string &file, const std::string &function, const int &line) {
    if (!isEnabled(L_INFO)) return;
    CoreLog::info(getMessageWithParams(message) + ", File: " + file + ", Function: " + function + ", Line: " + std::to_string(line));
}

void Log4Data::logError(const std::string &message, const std::string &file, const std::string &function, const int &line) {
    if (!isEnabled(L_ERROR)) return;
    CoreLog::error(getMessageWithParams(message) + ", File: " + file + ", Function: " + function + ", Line: " + std::to_string(line));
}

void Log4Data::logTrace(const std::string &message, const std::string &file, const std::string &function, const int &line) {
    if (!isEnabled(L_TRACE)) return;
    CoreLog::trace(getMessageWithParams(message) + ", File: " + file + ", Function: " + function + ", Line: " + std::to_string(line));
}

void Log4Data::logWarning(const std::string &message, const std::string &file, const std::string &function, const int &line) {
    if (!isEnabled(L_WARNING)) return;
    CoreLog::warn(getMessageWithParams(message) + ", File: " + file + ", Function: " + function + ", Line: " + std::to_string(line));
}

bool Log4Data::isEnabled(const LogLevel &level) {
    return m_UseLog;
}

void Log4Data::enable(const bool &value) {
    m_UseLog = value;
}

short Log4Data::getLevel() {
    return static_cast<short>(m_UseLog ? L_INFO : L_ERROR);
}

void Log4Data::logInformation(const logDataInput &value) {
    std::stringstream message;
    message << "MessageID: " << value._message_id << ", Event: " << value._event << ", Algorithm: " << value._algorithm;
    CoreLog::info(message.str());
}

void Log4Data::logInformation(const logDataOutput &value) {
    std::stringstream message;
    message << "MessageID: " << value._message_id << ", Event: " << value._event << ", Algorithm: " << value._algorithm;
    CoreLog::info(message.str());
}

void Log4Data::logInformation(const logDataStatus &value) {
    std::stringstream message;
    message << "MessageID: " << value._message_id << ", Status: " << value._status;
    CoreLog::info(message.str());
}
