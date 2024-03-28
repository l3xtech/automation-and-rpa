std::string Log4Data::constructStructuredMessage(const std::string& type, const std::string& message, const std::string& file, const std::string& function, const int& line) {
    std::stringstream ss;
    ss << "TYPE=" << type << "|"
       << "MESSAGE=" << message << "|"
       << "FILE=" << file << "|"
       << "FUNCTION=" << function << "|"
       << "LINE=" << line;
    for (const auto& kv : m_paramsLog) {
        ss << "|" << kv.first << "=" << kv.second;
    }
    return ss.str();
}


void Log4Data::logInformation(const logDataInput& value) {
    std::stringstream ss;
    ss << "LMESSAGE_ID=" << value._message_id << "|"
       << "LEVENT=" << value._event << "|"
       << "LALGORITHM=" << value._algorithm << "|"
       << "LSOURCE=" << value._source << "|"
       << "LTARGET=" << value._target << "|"
       << "LRISK_ENGINE=" << value._risk_engine << "|"
       << "LSCENARIO_VERSION=" << value._scenario_version << "|"
       << "LSCENARIO_QTY=" << value._scenario_qty << "|"
       << "LREGULAR_POSITIONS_QTY=" << value._regular_positions_qty << "|"
       << "LCOLLATERAL_QTY=" << value._collateral_qty << "|"
       << "LOPTION_FLEX_QTY=" << value._option_flex_qty << "|"
       << "LSWAP_QTY=" << value._swap_qty << "|"
       << "LTOTAL_POSITION=" << value._total_positions_qty << "|"
       << "LCALCULATION_TYPE=" << value._calculationType;
    CoreLog::info(ss.str());
}
