#include<Log4Data.h>
#include<sstream>
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<CoreSharedMemory.h>
#include<CoreLog.h>
#include<logClient.h>

log4cxx::LoggerPtr logger( log4cxx::Logger::getLogger( "CORE" ) );

using namespace bvmf::risk::core;
Log4Data* Log4Data::m_instance = 0;

Log4Data::Log4Data()
{
    m_UseLog=0;
    m_lasUseLog=0;
    m_ParamsLogMessage="";
}

Log4Data::~Log4Data()
{

}

std::string Log4Data::getMessageWithParams(const std::string &message)
{
    std::string messageAux;
    if (m_ParamsLogMessage != "")
    {
        messageAux = m_ParamsLogMessage;
    }
    messageAux += message;

    return messageAux;
}

short Log4Data::getLevel()
{
    return m_UseLog;
}

void Log4Data::enable(const bool &value)
{
    if( (value == false) && (m_UseLog != 0))
    {
        m_lasUseLog=m_UseLog;
        m_UseLog=0;
    }else if ( (value == true) && (m_lasUseLog != 0))
    {
        m_UseLog=m_lasUseLog;
        m_lasUseLog=0;
    }
}

void Log4Data::checkEnableLog()
{
    m_UseLog=L_INFO;

    if(const char* logLevel = std::getenv("LOG_LEVEL")) {
        m_UseLog = atoi(logLevel);
    }
    log4cxx::xml::DOMConfigurator::configure( "/etc/core/Log4.xml" );
}

void Log4Data::checkEnableLog(const CoreType &type)
{
    unsigned short processID;
    bool           useDefault=false;
    m_UseLog=L_INFO;

    try
    {
        CoreSharedMemory  *csm=CoreSharedMemory::getInstance();
        if(csm)
        {
            if(csm->connectSharedMemory() == CoreSharedMemory::SHM_OK)
            {
                switch(type)
                {
                    case CORE0: processID=CoreSharedMemory::CORE0_LOG_LEVEL;
                                break;
                    case CORE1: processID=CoreSharedMemory::CORE1_LOG_LEVEL;
                                break;
                    case CORE2: processID=CoreSharedMemory::CORE2_LOG_LEVEL;
                                break;
                    case CORE3: processID=CoreSharedMemory::CORE3_LOG_LEVEL;
                                break;
                    case CORE_MTM: processID=CoreSharedMemory::COREM_LOG_LEVEL;
                                break;
                    case VAL_SERVER: processID=CoreSharedMemory::VAL_SERVER_LOG_LEVEL;
                                break;
                    case LOADER_DB: processID=CoreSharedMemory::LOADER_DB_LOG_LEVEL;
                                break;
                    case IMDG: processID=CoreSharedMemory::IMDG_LOG_LEVEL;
                                break;
                    case CORE_TC: processID=CoreSharedMemory::CORETC_LOG_LEVEL;
                                break;
                    case CORE_AGENT: processID=CoreSharedMemory::COREAGENT_LOG_LEVEL;
                                break;
                    default:
                            useDefault=true;
                }
                if(useDefault == false)
                    m_UseLog=csm->getLogLevel(processID);
            }
        }
    }catch(...)
    {
        m_UseLog=L_INFO;
    }
}

void Log4Data::setCore(const CoreType &type)
{
#ifdef __USE_LOG

    m_type=type;
    switch(type)
    {
        case IMDG:
                    log4cxx::xml::DOMConfigurator::configure( "/etc/core/imdgLog4.xml" );
                    break;
        case LOADER:
                    log4cxx::xml::DOMConfigurator::configure( "/etc/core/LoaderLog4.xml" );
                    break;
        case CORE0:
                    log4cxx::xml::DOMConfigurator::configure( "/etc/core/Core0Log4.xml" );
                    break;
        case CORE1:
                    log4cxx::xml::DOMConfigurator::configure( "/etc/core/Core1Log4.xml" );
                    break;
        case CORE2:
                    log4cxx::xml::DOMConfigurator::configure( "/etc/core/Core2Log4.xml" );
                    break;
        case CORE3:
                    log4cxx::xml::DOMConfigurator::configure( "/etc/core/Core3Log4.xml" );
                    break;
        case CORE_MTM:
                    log4cxx::xml::DOMConfigurator::configure( "/etc/core/CoreMTMLog4.xml" );
                    break;
        case VAL_SERVER:
                    log4cxx::xml::DOMConfigurator::configure( "/etc/core/ValServerLog4.xml" );
                    break;
        case LOADER_DB:
                    log4cxx::xml::DOMConfigurator::configure( "/etc/core/ScenariosPublisherLog4.xml" );
                    break;
        case CORE_TC:
                    log4cxx::xml::DOMConfigurator::configure( "/etc/core/CoreTCLog4.xml" );
                    break;
        case CORE_AGENT:
                    log4cxx::xml::DOMConfigurator::configure( "/etc/core/CoreAgentLog4.xml" );
                    break;
        case EXECUTE_JOB:
                    log4cxx::xml::DOMConfigurator::configure( "/etc/core/ExecuteJob.xml" );
                    break;
    }
    checkEnableLog(type);
#endif
}

void Log4Data::setParamLog(std::string key, std::string value)
{
    std::stringstream message;
    std::map<std::string, std::string>::iterator it;
    int i;
    int total;

    m_paramsLog[key] = value;

    total = (int)m_paramsLog.size();
    for(it=m_paramsLog.begin(), i=0; it!=m_papramsLog.end(); ++it, ++i)
    {
        message << (*it).first << " [" << (*it).second << "] ";

        if (i < (total - 1))
        {
            //message << ";";
        }
    }
    //message << "] ";
    m_ParamsLogMessage = message.str();
}

void Log4Data::setParamLog(std::string key, int value)
{
    std::stringstream valueAux;
    valueAux << value;
    this->setParamLog(key, valueAux.str())
}

Log4Data* Log4Data::getInstance()
{
    if(m_instance == 0)
        m_instance = new Log4Data();

    return m_instance;
}

void Log4Data::logError(const std::string &message, const std::string &file, const std::string &function, const int &line)
{
    std::stringstream     errorMessage;
    std::string           messageAux;

    if(!file.empty())
        errorMessage << "FILE [" << file << "] ";
    if(!function.empty())
        errorMessage << "FUNCTION [" << function << "] ";
    if(line!=0)
        errorMessage << "Line ["<< line << "] ";

    errorMessage << message;
    messageAux = getMessageWithParams(errorMessage.str());
    CoreLog::error(logger,"",0,messageAux,CoreLog::CATEGORY_FUNCIONAL,CoreLog::TYPE_PROCESS,CoreLog::SEVERITY_ERROR, "ERROR CORE", "");
}

void Log4Data::logInformation(const std::string &message, const std::string &file, const std::string &function, const int &line)
{
    std::stringstream finalMessage;
    if(m_UseLog >= L_INFO)
    {
        pid_t pid=getpid();
        finalMessage << "PID [" << file << "] ";
        if(!file.empty())
            finalMessage << "FILE [" << function << "]";
        if(!function.empty())
            finalMessage << "FUNCTION [" << function << "]";
        if(line!=0)
            finalMessage << "LINE [" << line << "[";

        finalMessage << message;
        std::string messageAux = getMessageWithParams(finalMessage.str());
        PRINT_SHORT_INFO(logger, messageAux);
    }
}


void Log4Data::logTrace(const std::string &message, const std::string &file, const std::string &function, const int &line)
{
    if(m_UseLog >= L_TRACE)
    {
        std::stringstream   finalMessage;
        pid_t pid=getpid();

        finalMessage << "PID [" << pid << "]  ";
        if(!file.empty())
            finalMessage << "FILE [" << file << "] ";
        if(!function.empty())
            finalMessage << "FUNCTION [" << function << "]";
        if(line!=0)
            finalMessage << "LINE [" << line << "]";

        finalMessage << message;
        std::string messageAux = getMessageWithParams(finalMessage.str());
        PRINT_TRACE(logger, messageAux);
    }
}

bool Log4Data::isEnabled(const logLevel &level)
{
    return ((m_UseLog >= level) ? true : false);
}

void Log4Data::setLogName(const std::string &filename)
{
    this->setLogName(filename, m_type);
}

void Log4Data::setLogName(const std::string &filename, const CoreType &type)
{
    log4cxx::AppenderPtr         appenderTrace;
    log4cxx::AppenderPtr         appenderInfo;
    log4cxx::AppenderPtr         appenderError;
    log4cxx::AppenderPtr         appenderWarning;
    std::stringstream            traceFilename;
    std::stringstream            infoFilename;
    std::stringstream            errorFilename;
    std::stringstream            warningFilename;

    switch(type)
    {
        case CORE0:
                appenderTrace=logger->getAppender("CORE0LogTrace");
                appenderInfo=logger->getAppender("CORE0LogInformation");
                appenderError=logger->getAppender("CORE0LogError");
                appenderWarning=logger->getAppender("CORE0LogWarn");
                traceFilename <<"../log/"<<filename<<"_CORE0_trace.log";
                infoFilename <<"../log/"<<filename<<"_CORE0_info.log";
                errorFilename <<"../log/"<<filename<<"_CORE0_error.log";
                traceFilename <<"../log/"<<filename<<"_CORE0_warning.log";
                break;

        case CORE1:
                appenderTrace=logger->getAppender("CORE1LogTrace");
                appenderInfo=logger->getAppender("CORE1LogInformation");
                appenderError=logger->getAppender("CORE1LogError");
                appenderWarning=logger->getAppender("CORE1LogWarn");
                traceFilename <<"../log/"<<filename<<"_CORE1_trace.log";
                infoFilename <<"../log/"<<filename<<"_CORE1_info.log";
                errorFilename <<"../log/"<<filename<<"_CORE1_error.log";
                traceFilename <<"../log/"<<filename<<"_CORE1_warning.log";
                break;

        case CORE2:
                appenderTrace=logger->getAppender("CORE2LogTrace");
                appenderInfo=logger->getAppender("CORE2LogInformation");
                appenderError=logger->getAppender("CORE2LogError");
                appenderWarning=logger->getAppender("CORE2LogWarn");
                traceFilename <<"../log/"<<filename<<"_CORE2_trace.log";
                infoFilename <<"../log/"<<filename<<"_CORE2_info.log";
                errorFilename <<"../log/"<<filename<<"_CORE2_error.log";
                traceFilename <<"../log/"<<filename<<"_CORE2_warning.log";
                break;

        case CORE3:
                appenderTrace=logger->getAppender("CORE3LogTrace");
                appenderInfo=logger->getAppender("CORE3LogInformation");
                appenderError=logger->getAppender("CORE3LogError");
                appenderWarning=logger->getAppender("CORE3LogWarn");
                traceFilename <<"../log/"<<filename<<"_CORE3_trace.log";
                infoFilename <<"../log/"<<filename<<"_CORE3_info.log";
                errorFilename <<"../log/"<<filename<<"_CORE3_error.log";
                traceFilename <<"../log/"<<filename<<"_CORE3_warning.log";
                break;

        case CORE_MTM:
                appenderTrace=logger->getAppender("COREMTMLogTrace");
                appenderInfo=logger->getAppender("COREMTMLogInformation");
                appenderError=logger->getAppender("COREMTMLogError");
                appenderWarning=logger->getAppender("COREMTMLogWarn");
                traceFilename <<"../log/"<<filename<<"_COREMTM_trace.log";
                infoFilename <<"../log/"<<filename<<"_COREMTM_info.log";
                errorFilename <<"../log/"<<filename<<"_COREMTM_error.log";
                traceFilename <<"../log/"<<filename<<"_COREMTM_warning.log";
                break;

        case CORE_TC:
                appenderTrace=logger->getAppender("CORETCLogTrace");
                appenderInfo=logger->getAppender("CORETCLogInformation");
                appenderError=logger->getAppender("CORETCLogError");
                appenderWarning=logger->getAppender("CORETCLogWarn");
                traceFilename <<"../log/"<<filename<<"_CORETC_trace.log";
                infoFilename <<"../log/"<<filename<<"_CORETC_info.log";
                errorFilename <<"../log/"<<filename<<"_CORETC_error.log";
                traceFilename <<"../log/"<<filename<<"_CORETC_warning.log";
                break;

        default:
                appenderTrace=logger->getAppender("defaultLogTrace");
                appenderInfo=logger->getAppender("defaultLogInformation");
                appenderError=logger->getAppender("defaultLogError");
                appenderWarning=logger->getAppender("defaultLogWarn");
                traceFilename <<"../log/"<<filename<<"_trace.log";
                infoFilename <<"../log/"<<filename<<"_info.log";
                errorFilename <<"../log/"<<filename<<"_error.log";
                traceFilename <<"../log/"<<filename<<"_warning.log";
                break;
    }

    {
        if(appenderTrace != 0)
        {
            log4cxx::helpers::Pool pol;
            appenderTrace->activateOptions(pol);
            appenderTrace->setOption("file", traceFilename.str());
            appenderTrace->activateOptions(pol);
        }
    }
    {
        if(appenderInfo != 0)
        {
            log4cxx::helpers::Pool pol;
            appenderInfo->activateOptions(pol);
            appenderInfo->setOption("file", infoFilename.str());
            appenderInfo->activateOptions(pol);
        }
    }
    {
        if(appenderWarning != 0)
        {
            log4cxx::helpers::Pool pol;
            appenderWarning->activateOptions(pol);
            appenderWarning->setOption("file", warningFilename.str());
            appenderWarning->activateOptions(pol);
        }
    }
    {
        if(appenderError != 0)
        {
            log4cxx::helpers::Pool pol;
            appenderError->activateOptions(pol);
            appenderError->setOption("file", errorFilename.str());
            appenderError->activateOptions(pol);
        }
    }
}

void Log4Data::logInformation(const logDataInput &value)
{
    LOGRAW(CoreSharedMemory::CORE0_LOG_LEVEL, LogTypes::LEVEL_ALWAYS,value._message_id, \
            << LMESSAGE_ID << "=" << value._message_id << "|" \
            << LEVENT << "=" << value._event << "|" \
            << LALGORITM << "=" << value._algorithm << "|" \
            << LSOURCE << "=" << value._source << "|" \
            << LTARGET << "=" << value._target << "|" \
            << LRISK_ENGINE << "=" << value._risk_engine << "|" \
            << LSCENARIO_VERSION << "=" << value._scenario_version << "|" \
            << LSCENARIO_QTY << "=" << value._scenario_qty << "|" \
            << LREGULAR_POSITIONS_QTY << "=" << value._regular_positions_qty << "|" \
            << LCOLLATERAL_QTY << "=" << value._collateral_qty << "|" \
            << LOPTION_FLEX_QTY << "=" << value._option_flex_qty << "|" \
            << LSWAP_QTY << "=" << value._swap_qty << "|" \
            << LTOTAL_POSITION << "=" << value._total_positions_qty << "|" \
            << LCALCULATION_TYPE << "=" << value._calculationType);
}

void Log4Data::logInformation(const logDataOutput &value)
{
    std::stringstream    listOfValues;
    unsigned int         i;

    try
    {
        for(i=0;i<value._deficit_surplus.size();i++)
        {
            listOfValues << LDEFICIT_SURPLUS << "=" << value._deficit_surplus.at(i) << "|" \
            << LTOTAL_WITHOUT_COLLATERAL << "=" << value._total_without_collateral.at(i) << "|" \
            << LTRANSIENT_RISK << "=" << value._transient_risk.at(i) << "|" \
            << LPERMANENT_RISK << "=" << value._permanent_risk.at(i) << "|";
        }

        LOGRAW(CoreSharedMemory::CORE0_LOG_LEVEL, LogTypes::LEVEL_ALWAYS, value._message_id, \
                << LMESSAGE_ID << "=" << value._message_id << "|" \
                << LEVENT << "=" << value._event << "|" \
                << LALGORITM << "=" << calue._algorithm << "|" \
                << LSOURCE << "=" << value._source << "|" \
                << LTARGET << "=" << value._target << "|" \
                << LRISK_ENGINE << "=" << value._risk_engine << "|" \
                << LSCENARIO_VERSION << "=" << value._scenario_version << "|" \
                <<listOfValues.str() \
                << LTIME_TOTAL_TO_PROCESSING << "=" << value. _time_total_to_processing << "|"
                << LCALCULATION_TYPE << "=" << value._calculationType);
    }catch(...)
    {
        this->logInformation("Error to create monitoring log...");
    }
}

void Log4Data::logInformation(const logDataStatus &value)
{
    LOGRAW(CoreSharedMemory::CORE0_LOG_LEVEL, LogTypes::LEVEL_ALWAYS, value._message_id, \
                << LMESSAGE_ID << "=" << value._message_id << "|" \
                << LEVENT << "=" << value._event << "|" \
                << LALGORITM << "=" << calue._algorithm << "|" \
                << LSOURCE << "=" << value._source << "|" \
                << LTARGET << "=" << value._target << "|" \
                << LRISK_ENGINE << "=" << value._risk_engine << "|" \
                << LSCENARIO_VERSION << "=" << value._scenario_version << "|" \
                << LCALCULATION_TYPE << "=" << value._calculationType << "|" \
                << LSTATUS << "=" << value._status);
}

void Log4Data::logWarning(const atd::string &message, const std::string &/*file*/, const std::string &/*function*/, const int &/*line*/)
{
    if(m_UseLog >= L_WARNING)
    {
        std::string messageAux = getMessageWithParams(message);

        PRINT_SHORT_WARN(logger, messageAux);
    }
}
