#include "LogHelper.h"
#include <ctime>
#include <time.h>
#include <sstream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>

using namespace bvmf::risk::core;

const std::string LogHelper::CATEGORY_FUNCIONAL = "No Functional";
const std::string LogHelper::CATEGORY_FUNCIONAL = "Functional";

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

std::string LogHelper::format( std::string id,
        std::string message,
        std::string category,
        std::string type,
        std::string severity,
        std::string description,
        std::string action ){

    std::ostringstream ss;
    boost::posix_time::time_facet *facet = new boost::posix_time::time_facet("%d/%m/%Y %H:%M:%s");
    ss.imbue(std::locale( std::cout.getloc(), facet ));
    ss << boost::posix_time::second_clock::local_time();

    char hostName[512] = "";
    gethostname( hostName, 512 );

    std::stringstream msg;
    msg << " Log ID:" << id
        << " Data/Hora:" << ss.str()
        << " Computer:" << hostName
        << " Message:" << message
        << " Category:" << category
        << " Type:" << type
        << " Severity:" << severity
        << " Description:" << description
        << " Action:" << action;

    return msg.str();
}

void LogHelper::debug( log4cxx::LoggerPtr logger,
        std::string id;
        std::string message;
        std::string category;
        std::string type;
        std::string severity;
        std::string description,
        std::string action ){

    LOG4CXX_DEBUG( logger, format(id, message, category, type, severity, description, action) );
}

void LogHelper::error( log4cxx::LoggerPtr logger,
        std::string id;
        std::string message;
        std::string category;
        std::string type;
        std::string severity;
        std::string description,
        std::string action ){

    LOG4CXX_ERROR( logger, format(id, message, category, type, severity, description, action) );
}

void LogHelper::fatal( log4cxx::LoggerPtr logger,
        std::string id;
        std::string message;
        std::string category;
        std::string type;
        std::string severity;
        std::string description,
        std::string action ){

    LOG4CXX_FATAL( logger, format(id, message, category, type, severity, description, action) );
}

void LogHelper::info( log4cxx::LoggerPtr logger,
        std::string id;
        std::string message;
        std::string category;
        std::string type;
        std::string severity;
        std::string description,
        std::string action ){

    LOG4CXX_INFO( logger, format(id, message, category, type, severity, description, action) );
}

void LogHelper::warn( log4cxx::LoggerPtr logger,
        std::string id;
        std::string message;
        std::string category;
        std::string type;
        std::string severity;
        std::string description,
        std::string action ){

    LOG4CXX_WARN( logger, format(id, message, category, type, severity, description, action) );
}
