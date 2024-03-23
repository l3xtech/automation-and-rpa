opentelemetry::sdk::common::ExportResult FileLogExporter::Export(
    const opentelemetry::nostd::span<std::unique_ptr<opentelemetry::logs::LogRecord>>& records) noexcept {
    openLogFile();

    if (!outfile) {
        return opentelemetry::sdk::common::ExportResult::kFailure;
    }

    for (auto &record : records) {
        
        auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
            record->GetTimestamp().time_since_epoch()).count();

        
        auto severity = record->GetSeverity();

        outfile << "[" << timestamp << "] "
                << "[" << record->GetName() << "] "
                << "[" << opentelemetry::sdk::logs::SeverityNumToText(severity) << "] "
                << record->GetBody();

        for (const auto& kv : record->GetAttributes()) {
            outfile << " " << kv.first << "=" << kv.second;
        }

        outfile << std::endl;
    }

    return opentelemetry::sdk::common::ExportResult::kSuccess;
}
