#include "CoreLog.h"
#include <opentelemetry/sdk/logs/logger_provider.h>
#include <opentelemetry/logs/logger.h>
#include <opentelemetry/nostd/shared_ptr.h>
#include <sstream>
#include <ctime>

using namespace bvmf::risk::core;
using namespace opentelemetry;

std::unique_ptr<sdk::logs::LoggerProvider> logger_provider = nullptr;

nostd::shared_ptr<logs::Logger> CoreLog::logger = nullptr;

const std::string CoreLog::CATEGORY_NFUNCIONAL = "No Functional";
const std::string CoreLog::CATEGORY_FUNCIOANL = "Functional";

const std::string CoreLog::SEVERITY_EMERGENCY = "Emergency";
const std::string CoreLog::SEVERITY_CRITICAL = "Critical";
const std::string CoreLog::SEVERITY_ERROR = "Error";
const std::string CoreLog::SEVERITY_WARNING = "Warning";
const std::string CoreLog::SEVERITY_INFORMATION = "Information";

const std::string CoreLog::TYPE_ALARM = "Alarm";
const std::string CoreLog::TYPE_BATCH = "Batch";
const std::string CoreLog::TYPE_COMMUNICATION = "Communication";
const std::string CoreLog::TYPE_PROCESS = "Process";
const std::string CoreLog::TYPE_SECURITY = "Security";
const std::string CoreLog::TYPE_EVENT = "Event";

CoreLog::CoreLog() {
}

CoreLog::~CoreLog() {
}

void CoreLog::initLogger() {
    if (!logger_provider) {
        logger_provider = std::make_unique<sdk::logs::LoggerProvider>();
    }

    if (!logger) {
        logger = logger_provider->GetLogger("CoreLogger");
    }
}

void CoreLog::debug(const std::string &message,
                    const std::string &category,
                    const std::string &type,
                    const std::string &severity,
                    const std::string &description,
                    const std::string &action) {
    if (!logger) initLogger();

    auto record = logger->log_record();
    record->SetSeverity(logs::Severity::kDebug);
    setLogAttributes(record, category, type, severity, description, action);
    record->SetBody(message);

    logger->Log(std::move(record));
}

void CoreLog::error(const std::string &message,
                    const std::string &category,
                    const std::string &type,
                    const std::string &severity,
                    const std::string &description,
                    const std::string &action) {
    if (!logger) initLogger();

    auto record = logger->log_record();
    record->SetSeverity(logs::Severity::kError);
    setLogAttributes(record, category, type, severity, description, action);
    record->SetBody(message);

    logger->Log(std::move(record));
}

void CoreLog::fatal(const std::string &message,
                    const std::string &category,
                    const std::string &type,
                    const std::string &severity,
                    const std::string &description,
                    const std::string &action) {
    if (!logger) initLogger();

    auto record = logger->log_record();
    record->SetSeverity(logs::Severity::kFatal);
    setLogAttributes(record, category, type, severity, description, action);
    record->SetBody(message);

    logger->Log(std::move(record));
}

void CoreLog::info(const std::string &message,
                    const std::string &category,
                    const std::string &type,
                    const std::string &severity,
                    const std::string &description,
                    const std::string &action) {
    if (!logger) initLogger();

    auto record = logger->log_record();
    record->SetSeverity(logs::Severity::kInfo);
    setLogAttributes(record, category, type, severity, description, action);
    record->SetBody(message);

    logger->Log(std::move(record));
}

void CoreLog::warn(const std::string &message,
                    const std::string &category,
                    const std::string &type,
                    const std::string &severity,
                    const std::string &description,
                    const std::string &action) {
    if (!logger) initLogger();

    auto record = logger->log_record();
    record->SetSeverity(logs::Severity::kWarn);
    setLogAttributes(record, category, type, severity, description, action);
    record->SetBody(message);

    logger->Log(std::move(record));
}


void CoreLog::trace(const std::string &message) {
    if (!logger) initLogger();

    auto record = logger->log_record();
    record->SetSeverity(logs::Severity::kTrace);
    record->SetBody(message);

    logger->Log(std::move(record));
}

void setLogAttributes(std::shared_ptr<logs::LogRecord> &record,
                      const std::string &category,
                      const std::string &type,
                      const std::string &severity,
                      const std::string &description,
                      const std::string &action) {
    record->SetAttribute("category", category);
    record->SetAttribute("type", type);
    record->SetAttribute("severity", mapSeverityLevel(severity));
    record->SetAttribute("description", description);
    record->SetAttribute("action", action);
}

logs::Severity CoreLog::mapSeverityLevel(const std::string &severity) {
    if (severity == SEVERITY_EMERGENCY || severity == SEVERITY_CRITICAL) {
        return logs::Severity::kFatal;
    } else if (severity == SEVERITY_ERROR) {
        return logs::Severity::kError;
    } else if (severity == SEVERITY_WARNING) {
        return logs::Severity::kWarn;
    } else if (severity == SEVERITY_INFORMATION) {
        return logs::Severity::kInfo;
    }

    return logs::Severity::kDebug;
}
