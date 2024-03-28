#include "Log4Data.h"
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "CoreSharedMemory.h"
#include "CoreLog.h"

// Removed the log4cxx::LoggerPtr logger instantiation since we will use CoreLog directly

using namespace bvmf::risk::core;

Log4Data* Log4Data::m_instance = nullptr;

Log4Data::Log4Data() : m_UseLog(0), m_lasUseLog(0), m_ParamsLogMessage("") {
    // Initialization logic if necessary. For example, setting up default log parameters.
}

Log4Data::~Log4Data() {
    // Clean-up logic if necessary. For instance, closing log files or flushing logs.
}


std::string Log4Data::getMessageWithParams(const std::string &message) {
    std::string messageAux = m_ParamsLogMessage.empty() ? "" : m_ParamsLogMessage + " ";
    messageAux += message;
    return messageAux;
}

short Log4Data::getLevel() {
    return m_UseLog;
}

void Log4Data::enable(const bool &value) {
    if (!value && m_UseLog != 0) {
        m_lasUseLog = m_UseLog;
        m_UseLog = 0;
    } else if (value && m_lasUseLog != 0) {
        m_UseLog = m_lasUseLog;
        m_lasUseLog = 0;
    }
}

void Log4Data::checkEnableLog() {
    m_UseLog = L_INFO; // Default to INFO level

    if (const char* logLevel = std::getenv("LOG_LEVEL")) {
        m_UseLog = std::atoi(logLevel);
    }

    // Assuming CoreLog or the underlying logging system can be configured here if needed.
    // CoreLog::configure("/etc/core/Log4.xml"); // Hypothetical example if CoreLog supports XML configuration
}

void Log4Data::checkEnableLog(const CoreType &type) {
    unsigned short processID;
    bool useDefault = false;
    m_UseLog = L_INFO;

    try {
        CoreSharedMemory *csm = CoreSharedMemory::getInstance();
        if (csm) {
            if (csm->connectSharedMemory() == CoreSharedMemory::SHM_OK) {
                switch (type) {
                    case CORE0: processID = CoreSharedMemory::CORE0_LOG_LEVEL; break;
                    case CORE1: processID = CoreSharedMemory::CORE1_LOG_LEVEL; break;
                    case CORE2: processID = CoreSharedMemory::CORE2_LOG_LEVEL; break;
                    case CORE3: processID = CoreSharedMemory::CORE3_LOG_LEVEL; break;
                    case CORE_MTM: processID = CoreSharedMemory::COREM_LOG_LEVEL; break;
                    case VAL_SERVER: processID = CoreSharedMemory::VAL_SERVER_LOG_LEVEL; break;
                    case LOADER_DB: processID = CoreSharedMemory::LOADER_DB_LOG_LEVEL; break;
                    case IMDG: processID = CoreSharedMemory::IMDG_LOG_LEVEL; break;
                    case CORE_TC: processID = CoreSharedMemory::CORETC_LOG_LEVEL; break;
                    case CORE_AGENT: processID = CoreSharedMemory::COREAGENT_LOG_LEVEL; break;
                    default: useDefault = true;
                }
                if (!useDefault)
                    m_UseLog = csm->getLogLevel(processID);
            }
        }
    } catch (...) {
        m_UseLog = L_INFO;
    }

    // Note: No direct CoreLog equivalent shown here since the function primarily
    // depends on shared memory for configuration, which is outside CoreLog's concern.
    // Ensure CoreLog is properly initialized elsewhere if needed.
}


