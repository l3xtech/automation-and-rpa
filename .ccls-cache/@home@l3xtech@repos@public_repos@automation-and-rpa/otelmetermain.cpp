#include <opentelemetry/sdk/trace/tracer_provider.h>
#include <opentelemetry/sdk/metrics/metric_provider.h>
#include <opentelemetry/sdk/metrics/export/console_metric_exporter.h>
#include <opentelemetry/sdk/metrics/export/otlp_metric_exporter.h>
#include <opentelemetry/sdk/resources/resource.h>
#include <opentelemetry/sdk/common/global_provider.h>

using namespace opentelemetry::sdk::metrics;
using namespace opentelemetry::sdk::trace;

int main() {
  // Definir o Resource
  Resource resource{
      {{SERVICE_NAME, "meu-app-dahora"},
       {SERVICE_VERSION, "0.1.3"}}};

  // Criar um MeterProvider
  MeterProvider meter_provider;
  meter_provider.set_resource(resource);

  // Criar Exporters
  ConsoleMetricExporter console_exporter;
  OTLPMetricExporter otlp_exporter("batatinhas_fritas_otlp:9999");

  // Criar PeriodicExportingMetricReaders
  PeriodicExportingMetricReader console_reader{console_exporter};
  PeriodicExportingMetricReader otlp_reader{otlp_exporter};

  // Registrar os Readers no MeterProvider
  meter_provider.add_metric_reader(console_reader);
  meter_provider.add_metric_reader(otlp_reader);

  // Obter o Meter
  auto meter = get_meter("meter", &meter_provider);

  // Criar um Counter
  auto counter = meter->create_counter("carros.passando", "Carros passando na minha rua", "1");

  // Adicionar dados ao Counter
  counter->add(1, {{"modelo", "Monza"}, {"cor", "preto"}});
  counter->add(3, {{"modelo", "Fusca"}, {"cor", "preto"}});
  counter->add(6, {{"modelo", "Marea"}, {"cor", "prata"}});

  return 0;
}
