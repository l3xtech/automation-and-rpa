#include "LogHelper.h"
#include <ctime>
#include <sstream>

using namespace bvmf::risk::core;

const std::string LogHelper::CATEGORY_FUNCIONAL = "Functional";
const std::string LogHelper::CATEGORY_NFUNCIONAL = "Non-Functional";

const std::string LogHelper::SEVERITY_EMERGENCY = "Emergency";
const std::string LogHelper::SEVERITY_CRITICAL = "Critical";
const std::string LogHelper::SEVERITY_ERROR = "Error";
const std::string LogHelper::SEVERITY_WARNING = "Warning";
const std::string LogHelper::SEVERITY_INFORMATION = "Information";

const std::string LogHelper::TYPE_ALARM = "Alarm";
const std::string LogHelper::TYPE_BATCH = "Batch";
const std::string LogHelper::TYPE_COMMUNICATION = "Communication";
const std::string LogHelper::TYPE_PROCESS = "Process";
const std::string LogHelper::TYPE_SECURITY = "Security";
const std::string LogHelper::TYPE_EVENT = "Event";

LogHelper::LogHelper() {
}

LogHelper::~LogHelper() {
}

std::string LogHelper::format(std::string id,
                              std::string message,
                              std::string category,
                              std::string type,
                              std::string severity,
                              std::string description,
                              std::string action) {
}

void LogHelper::debug(std::string message,
                      std::string category,
                      std::string type,
                      std::string severity,
                      std::string description,
                      std::string action) {
    
    CoreLog::debug(message, category, type, severity, description, action);
}

void LogHelper::error(std::string message,
                      std::string category,
                      std::string type,
                      std::string severity,
                      std::string description,
                      std::string action) {
    
    CoreLog::error(message, category, type, severity, description, action);
}


void LogHelper::fatal(std::string message,
                      std::string category,
                      std::string type,
                      std::string severity,
                      std::string description,
                      std::string action) {
    
    CoreLog::fatal(message, category, type, severity, description, action);
}

void LogHelper::info(std::string message,
                      std::string category,
                      std::string type,
                      std::string severity,
                      std::string description,
                      std::string action) {
    
    CoreLog::info(message, category, type, severity, description, action);
}

void LogHelper::warn(std::string message,
                      std::string category,
                      std::string type,
                      std::string severity,
                      std::string description,
                      std::string action) {
    
    CoreLog::warn(message, category, type, severity, description, action);
}
