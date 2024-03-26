#ifndef LOG_H_
#define LOG_H_

#include <string>
#include <log4cxx/logger.h>
//#include <log4cxx/xml/domconfigurator.h>
#include "log4cxx/basicconfigurator.h"

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

    static log4cxx::LoggerPtr logger;

public:
    LogHelper();
    virtual ~LogHelper();

public:
    static std::string format( std::string id,
            std::string message,
            std::string category,
            std::string type,
            std::string severity,
            std::string description,
            std::string action );

    static void debug( log4cxx::LoggerPtr logger,
            std::string message,
            std::string category,
            std::string type,
            std::string severity,
            std::string description,
            std::string action );

    static void error(log4cxx::LoggerPtr logger,
            std::string message,
            std::string category,
            std::string type,
            std::string severity,
            std::string description,
            std::string action );

    static void fatal( log4cxx::LoggerPtr loger,
            std::string message,
            std::string category,
            std::string type,
            std::string severity,
            std::string description,
            std::string action );

    static void info( log4cxx::LoggerPtr loger,
            std::string message,
            std::string category,
            std::string type,
            std::string severity,
            std::string description,
            std::string action );

    static void warn( log4cxx::LoggerPtr loger,
            std::string message,
            std::string category,
            std::string type,
            std::string severity,
            std::string description,
            std::string action );
};
}}}
#endif /* LOG_H_ */
