#ifndef LOGHELPER_H_
#define LOGHELPER_H_

#include <string>
#include "CoreLog.h"

namespace bvmf {
namespace risk {
namespace core {

class LogHelper {
public:
    static const std::string CATEGORY_NFUNCIONAL;
    static const std::string CATEGORY_FUNCIONAL;

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

public:
    LogHelper();
    virtual ~LogHelper();

    static std::string format(std::string id,
                              std::string message,
                              std::string category,
                              std::string type,
                              std::string severity,
                              std::string description,
                              std::string action);

    // Adapted logging methods
    static void debug(std::string message,
                      std::string category = "",
                      std::string type = "",
                      std::string severity = "",
                      std::string description = "",
                      std::string action = "");

    static void error(std::string message,
                      std::string category = "",
                      std::string type = "",
                      std::string severity = "",
                      std::string description = "",
                      std::string action = "");

    static void fatal(std::string message,
                      std::string category = "",
                      std::string type = "",
                      std::string severity = "",
                      std::string description = "",
                      std::string action = "");

    static void info(std::string message,
                      std::string category = "",
                      std::string type = "",
                      std::string severity = "",
                      std::string description = "",
                      std::string action = "");

    static void warn(std::string message,
                      std::string category = "",
                      std::string type = "",
                      std::string severity = "",
                      std::string description = "",
                      std::string action = "");

};
}}}

#endif /* LOGHELPER_H_ */
