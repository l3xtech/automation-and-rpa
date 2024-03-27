#ifndef __LOG_4_DATA_H
#define __LOG_4_DATA_H

#include <string>
#include <vector>
#include <map>
#include <Common.h>

using namespace bvmf::risk::core;

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define LOG4DATA_ERROR(message) Log4Data::getInstance()->logError(message,__FILENAME__,__FUNCTION__,__LINE__);
#define LOG4DATA_INFO(message) Log4Data::getInstance()->logInformation(message,__FILENAME__,__FUNCTION__,__LINE__);
#define LOG4DATA_TRACE(message) Log4Data::getInstance()->logTrace(message,__FILENAME__,__FUNCTION__,__LINE__);
#define LOG4DATA_WARN(message) Log4Data::getInstance()->logWarning(message,__FILENAME__,__FUNCTION__,__LINE__);


#define LMESSAGE_ID "30000"
#define LEVENT "30001"
#define LALGORITM "30002"
#define LSOURCE "30003"
#define LTARGET "30004"
#define LRISK_ENGINE "30005"
#define LSCENARIO_VERSION "30006"
#define LSCENARIO_QTY "30007"
#define LTOTAL_POSITIONS_QTY "3008"
#define LREGULAR_POSITIONS_QTY "30009"
#define LCOLLATERAL_QTY "30010"
#define LOPTION_FLEX_QTY "30011"
#define LSWAP_QTY "30012"
#define LSCENARIO_SELECTED "30013"
#define LDEFICIT_SURPLUS "30014"
#define LTOTAL_WITHOUT_COLLATERAL "30015"
#define LTRANSIENT_RISK "30016"
#define LPERMANENT_RISK "30017"
#define LTIME_TOTAL_TO_PROCESSING "30018"
#define LTOTAL_POSITION "30019"
#define LCALCULATION_TYPE "30020"
#define LSTATUS "30021" // 0 = ERROR; 1 = OK


enum CoreType
{
    LOADER = -1,
    CORE0 = 0,
    CORE1 = 1,
    CORE2 = 2,
    CORE3 = 3,
    IMDG = 4,
    CORE_MTM = 5,
    VAL_SERVER = 6,
    LOADER_DB = 7,
    CORE_TC = 8,
    CORE_AGENT = 11,
    EXECUTE_JOB = 12
};


enum LogLevel
{
    L_ERROR = 0,
    L_WARNING = 1,
    L_INFO = 2,
    L_INFO_2 = 3,
    L_TRACE = 99,
    L_DEBUG = 100
};

typedef struct logDataInputStruct
{
    std::string   _message_id;               //30000
    int           _event;                    //30001
    std::string   _algorithm;                //30002
    std::string   _source;                   //30003
    std::string   _target;                   //30004
    std::string   _risk_engine;              //30005
    std::string   _scenario_version;         //30006
    unsigned int  _scenario_qty;             //30007
    unsigned int  _total_positions_qty;      //30008
    unsigned int  _regular_positions_qty;    //30009
    unsigned int  _collateral_qty;           //30010
    unsigned int  _option_flex_qty;          //30011
    unsigned int  _swap_qty;                 //30012
    int           _calculationType;          //30020
}logDataInput;


typedef struct logDataOutputStruct
{
    std::string           _message_id;               //30000
    int                   _event;                    //30001
    std::string           _algorithm;                //30002
    std::string           _source;                   //30003
    std::string           _target;                   //30004
    std::string           _risk_engine;              //30005
    std::string           _scenario_version;         //30006
    std::vector<double>   _deficit_surplus;          //30014
    std::vector<double>   _total_without_collateral; //30015
    std::vector<double>   _transient_risk;           //30016
    std::vector<double>   _permanent_risk;           //30017
    std::string           _time_total_to_processing; //30018
    int                   _calculationType;          //30020
}logDataOutput;

typedef struct logDataStatusStruct
{
    std::string          _message_id;               //30000
    int                  _event;                    //30001
    std::string          _algorithm;                //30002
    std::string          _source;                   //30003
    std::string          _target;                   //30004
    std::string          _risk_engine;              //30005
    std::string          _scenario_version;         //30006
    int                  _calculationType;          //30020
    short                _status;                   //30021
}logDataStatus;

class Log4Data
{
private:
    Log4Data();

    static Log4Data *m_instance;

    short  m_UseLog;
    short  m_lasUseLog;
    std::map<std::string, std::string> m_paramsLog;
    std::string m_ParamsLogMessage;

    CoreType   m_type;

    std::string getMessageWithParams(const std::string &message);

public:
    ~Log4Data();

    static Log4Data* getInstance();

    void setCore(const CoreType &/*type*/);

    void setParamLog(std::string key, std::string value);
    void setParamLog(std::string key, int value);

    void logInformation(const std::string &message, const std::string &file="", const std::string &function="", const int &line=0);
    void logError(const std::string &message, const std::string &file="", const std::string &function="", const int &line=0);
    void logTrace(const std::string &message, const std::string &file="", const std::string &function="", const int &line=0);
    bool isEnabled(const LogLevel &level=L_TRACE);
    void checkEnableLog();
    void checkEnableLog(const CoreType &type);
    void setLogName(const std::string &filename, const CoreType &type);
    void setLogName(const std::string &filename);
    void logInformation(const logDataInput &value);
    void logInformation(const logDataOutput &value);
    void logInformation(const logDataStatus &value);
    void logWarning(const std::string &message, const std::string &file="", const std::string &function="", const int &line=0);
    void enable(const bool &value);
    short getLevel();
};

#endif // __LOG_4_DATA_H
