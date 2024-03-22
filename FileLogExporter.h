#ifndef FILELOGEXPORTER_H_
#define FILELOGEXPORTER_H_

#include "opentelemetry/sdk/logs/exporter.h"
#include <fstream>
#include <memory>

class FileLogExporter : public opentelemetry::sdk::logs::LogExporter {
public:
    explicit FileLogExporter(const std::string& filename);
    opentelemetry::sdk::common::ExportResult Export(
        const opentelemetry::nostd::span<std::unique_ptr<opentelemetry::logs::LogRecord>>& records) noexcept override;
    bool Shutdown(std::chrono::microseconds timeout = std::chrono::microseconds(0)) noexcept override;

private:
    std::ofstream outfile;
};

#endif // FILELOGEXPORTER_H_
