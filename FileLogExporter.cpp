#include "FileLogExporter.h"
#include <iostream>
#include <sstream>

FileLogExporter::FileLogExporter(const std::string& filename) : outfile(filename, std::ios::app) {
    if (!outfile.is_open()) {
        std::cerr << "Failed to open log file: " << filename << std::endl;
    }
}

opentelemetry::sdk::common::ExportResult FileLogExporter::Export(
    const opentelemetry::nostd::span<std::unique_ptr<opentelemetry::logs::LogRecord>>& records) noexcept {
    if (!outfile.is_open()) {
        return opentelemetry::sdk::common::ExportResult::kFailure;
    }

    for (auto &record : records) {
        // Convert timestamp to human-readable format
        auto timestamp = std::chrono::system_clock::to_time_t(record->GetTimestamp());
        std::string timeStr = std::ctime(&timestamp);

        // Extract severity as string
        auto severity = record->GetSeverity();

        // Begin constructing the log message
        std::ostringstream logStream;
        logStream << timeStr.substr(0, timeStr.length() - 1) << " "; // Remove newline from ctime output
        logStream << "[" << severity << "] ";

        // Include key-value attributes if present
        for (const auto& kv : record->GetResource().GetAttributes()) {
            logStream << kv.first << "=" << kv.second << " ";
        }
        for (const auto& kv : record->GetAttributes()) {
            logStream << kv.first << "=" << kv.second << " ";
        }

        // Append the log message body
        logStream << record->GetBody();

        // Write the constructed log message to file and append newline
        outfile << logStream.str() << std::endl;
    }

    outfile.flush(); // Ensure all log entries are written to the file
    return opentelemetry::sdk::common::ExportResult::kSuccess;
}

bool FileLogExporter::Shutdown(std::chrono::microseconds /*timeout*/) noexcept {
    if (outfile.is_open()) {
        outfile.close();
    }
    return true;
}
