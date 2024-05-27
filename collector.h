#ifndef OPEN_TELEMETRY_LOGGER_H
#define OPEN_TELEMETRY_LOGGER_H

#include "opentelemetry/sdk/trace/simple_processor.h"
#include "opentelemetry/sdk/trace/simple_span_processor.h"
#include "opentelemetry/sdk/trace/tracer_provider.h"
#include "opentelemetry/exporters/otlp/otlp_exporter.h"
#include "opentelemetry/sdk/trace/samplers/always_on.h"

#include <memory>
#include <string>

namespace ot = opentelemetry;

class OpenTelemetryLogger {
public:
    OpenTelemetryLogger(const std::string& endpoint) {
        // Configurar o exportador OTLP para enviar traces para o OpenTelemetry Collector
        auto exporter = std::unique_ptr<ot::sdk::trace::SpanExporter>(
            new ot::exporter::otlp::OtlpExporter(endpoint));

        // Configurar o provedor de traçamento
        auto processor = std::make_shared<ot::sdk::trace::SimpleSpanProcessor>(std::move(exporter));
        provider_ = std::make_shared<ot::sdk::trace::TracerProvider>(
            new ot::sdk::trace::TracerProvider(processor, std::make_shared<ot::sdk::trace::AlwaysOnSampler>()));

        // Setar o provedor de traçamento como provedor padrão
        ot::trace::Provider::SetTracerProvider(provider_);
    }

    void Log(const std::string& message) {
        // Criar um tracer
        auto tracer = ot::trace::Provider::GetTracer("logger");

        // Criar um span
        auto span = tracer->StartSpan("log_span");

        // Adicionar o log como um atributo
        span->SetAttribute("log_message", message);

        // Terminar o span
        span->End();
    }

private:
    std::shared_ptr<ot::sdk::trace::TracerProvider> provider_;
};

#endif // OPEN_TELEMETRY_LOGGER_H

