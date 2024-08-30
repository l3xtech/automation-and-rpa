#include <memory>
#include <thread>
#include "opentelemetry/exporters/ostream/metric_exporter_factory.h"
#include "opentelemetry/exporters/ostream/metric_exporter_factory.h"
#include "opentelemetry/metrics/provider.h"
#include "opentelemetry/sdk/metrics/aggregation/default_aggregation.h"
#include "opentelemetry/sdk/metrics/aggregation/histogram_aggregation.h"
#include "opentelemetry/sdk/metrics/export/periodic_exporting_metric_reader_factory.h"
#include "opentelemetry/sdk/metrics/meter.h"
#include "opentelemetry/sdk/metrics/meter_provider.h"
#include "opentelemetry/sdk/metrics/meter_provider_factory.h"
#include "opentelemetry/sdk/metrics/push_metric_exporter.h"
#include "opentelemetry/sdk/metrics/view/instrument_selector_factory.h"
#include "opentelemetry/sdk/metrics/view/meter_selector_factory.h"
#include "opentelemetry/sdk/metrics/view/view_factory.h"
#include "opentelemetry/exporters/otlp/otlp_http_metric_exporter_options.h"
#include "opentelemetry/exporters/otlp/otlp_http_metric_exporter_factory.h"

namespace metrics_sdk        = opentelemetry::sdk::metrics;
namespace common             = opentelemetry::common;
namespace exportermetrics    = opentelemetry::exporter::metrics;
namespace metrics_api        = opentelemetry::metrics;
namespace nostd              = opentelemetry::nostd;
namespace otlp               = opentelemetry::exporter::otlp;

void CleanupMetrics()
{
  std::shared_ptr<metrics_api::MeterProvider> none;
  metrics_api::Provider::SetMeterProvider(none);
}

int main(int argc, char **argv)
{
  auto exporter = exportermetrics::OStreamMetricExporterFactory::Create();

  auto opts = opentelemetry::exporter::otlp::OtlpHttpMetricExporterOptions();
  // opts.url = "http://opentelemetrycollector.core-dev.svc.cluster.local:4318";
  opts.url = argv[1];
  auto http_exporter = opentelemetry::exporter::otlp::OtlpHttpMetricExporterFactory::Create(opts);

  std::string version{argv[2]};
  std::string schema{argv[3]};

  // Initialize and set the global MeterProvider
  metrics_sdk::PeriodicExportingMetricReaderOptions options;
  options.export_interval_millis = std::chrono::milliseconds(1000);
  options.export_timeout_millis = std::chrono::milliseconds(500);

  auto reader =
    metrics_sdk::PeriodicExportingMetricReaderFactory::Create(std::move(exporter), options);
  auto httpReader = metrics_sdk::PeriodicExportingMetricReaderFactory::Create(std::move(http_exporter), options);

// #ifdef OPENTELEMETRY_DEPRECATED_SDK_FACTORY
  auto u_provider = opentelemetry::sdk::metrics::MeterProviderFactory::Create();
  auto *provider = static_cast<opentelemetry::sdk::metrics::MeterProvider *>(u_provider.get());
// #else
    // auto provider = opentelemetry::sdk::metrics::MeterProviderFactory::Create();
  // #endif /* OPENTELEMETRY_DEPRECATED_SDK_FACTORY */

  provider->AddMetricReader(std::move(reader));
  provider->AddMetricReader(std::move(httpReader));

  std::string name = "seila-http";

  // counter view
  std::string counter_name = name + "_counter";
  std::string unit         = "counter-unit";

  auto instrument_selector = metrics_sdk::InstrumentSelectorFactory::Create(metrics_sdk::InstrumentType::kCounter, counter_name, unit);
  auto meter_selector = metrics_sdk::MeterSelectorFactory::Create(name, version, schema);
  auto sum_view = metrics_sdk::ViewFactory::Create(name, "description", unit, metrics_sdk::AggregationType::kSum);

  provider->AddView(std::move(instrument_selector), std::move(meter_selector), std::move(sum_view));

  // observable counter view
  std::string observable_counter_name = name + "_observable_counter";

  auto observable_instrument_selector = metrics_sdk::InstrumentSelectorFactory::Create(metrics_sdk::InstrumentType::kObservableCounter, observable_counter_name, unit);
  auto observable_meter_selector = metrics_sdk::MeterSelectorFactory::Create(name, version, schema);
  auto observable_sum_view = metrics_sdk::ViewFactory::Create(name, "test_description", unit, metrics_sdk::AggregationType::kSum);

  provider->AddView(std::move(observable_instrument_selector), std::move(observable_meter_selector), std::move(observable_sum_view));

  // histogram view
  std::string histogram_name = name + "_histogram";
  unit                       = "histogram-unit";

  auto histogram_instrument_selector = metrics_sdk::InstrumentSelectorFactory::Create(metrics_sdk::InstrumentType::kHistogram, histogram_name, unit);
  auto histogram_meter_selector = metrics_sdk::MeterSelectorFactory::Create(name, version, schema);
  auto histogram_aggregation_config = std::unique_ptr<metrics_sdk::HistogramAggregationConfig>(new metrics_sdk::HistogramAggregationConfig);

  histogram_aggregation_config->boundaries_ = std::vector<double>{0.0, 50.0, 100.0, 250.0, 500.0, 750.0, 1000.0, 2500.0, 5000.0, 10000.0, 20000.0};

  std::shared_ptr<metrics_sdk::AggregationConfig> aggregation_config(std::move(histogram_aggregation_config));

  auto histogram_view = metrics_sdk::ViewFactory::Create(name, "description", unit, metrics_sdk::AggregationType::kHistogram, aggregation_config);

  provider->AddView(std::move(histogram_instrument_selector), std::move(histogram_meter_selector), std::move(histogram_view));

#ifdef OPENTELEMETRY_DEPRECATED_SDK_FACTORY
  std::shared_ptr<opentelemetry::metrics::MeterProvider> http_api_provider(std::move(u_provider));
#else
  std::shared_ptr<opentelemetry::metrics::MeterProvider> http_api_provider(std::move(provider));
#endif /* OPENTELEMETRY_DEPRECATED_SDK_FACTORY */

  metrics_api::Provider::SetMeterProvider(http_api_provider);

  auto provider2                                = metrics_api::Provider::GetMeterProvider();
  nostd::shared_ptr<metrics_api::Meter> meter   = provider2->GetMeter(name, "1.2.0");
  auto double_counter                           = meter->CreateDoubleCounter(counter_name);

  for (uint32_t i = 0; i < 20; ++i)
  {
    double val = (rand() % 700) + 1.1;
    double_counter->Add(val);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
  
  CleanupMetrics();


}
