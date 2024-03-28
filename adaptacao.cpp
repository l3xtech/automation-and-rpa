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
