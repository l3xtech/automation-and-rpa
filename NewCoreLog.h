#ifndef CORELOG_H_
#define CORELOG_H_

#include <opentelemetry/sdk/logs/logger_provider.h>
#include <opentelemetry/logs/log_record.h>
#include <opentelemetry/nostd/shared_ptr.h>
#include <opentelemetry/sdk/logs/logger.h>
#include <string>

namespace bvmf {
namespace risk {
namespace core {

namespace logs = opentelemetry::logs;
namespace sdk = opentelemetry::sdk::logs;
namespace nostd = opentelemetry::nostd;

class CoreLog {
public:
    static const std::string CATEGORY_NFUNCIONAL;
    static const std::string CATEGORY_FUNCIOANL;

    static const std::string SEVERITY_EMERGENCY;
    static const std::string SEVERITY_CRITICAL;
    static const std::string SEVERITY_ERROR;
    static const std::string SEVERITY_WARNING;
    static const std::string SEVERITY_INFORMATION;

    static const std::string TYPE_ALARM;
    static const std::string TYPE_BATCH;
    static const std::string TYPE_COMMUNICATION;
    static const std::string TYPE_PROCESS;
    static const std::string TYPE_SECURITY;
    static const std::string TYPE_EVENT;

    static nostd::shared_ptr<logs::Logger> logger;

public:
    CoreLog();
    virtual ~CoreLog();

    static void initLogger();

    static void debug(const std::string &message,
                      const std::string &category = "",
                      const std::string &type = "",
                      const std::string &severity = "",
                      const std::string &description = "",
                      const std::string &action = "");

    static void error(const std::string &message,
                      const std::string &category = "",
                      const std::string &type = "",
                      const std::string &severity = "",
                      const std::string &description = "",
                      const std::string &action = "");

    static void fatal(const std::string &message,
                      const std::string &category = "",
                      const std::string &type = "",
                      const std::string &severity = "",
                      const std::string &description = "",
                      const std::string &action = "");

    static void info(const std::string &message,
                      const std::string &category = "",
                      const std::string &type = "",
                      const std::string &severity = "",
                      const std::string &description = "",
                      const std::string &action = "");

    static void warn(const std::string &message,
                      const std::string &category = "",
                      const std::string &type = "",
                      const std::string &severity = "",
                      const std::string &description = "",
                      const std::string &action = "");

    static void trace(const std::string &message);
    static void info(const std::string &message);
    static void warn(const std::string &message);

private:
    static logs::Severity mapSeverityLevel(const std::string &severity);
};

}}}
#endif /* CORELOG_H_ */
