from opentelemetry.metrics import get_meter
from opentelemetry.sdk.resources import (
  Resource, SERVICE_NAME, SERVICE_VERSION
)

from opentelemetry.sdk.metrics import MeterProvider
from opentelemetry.sdk.metrics.export import (
  ConsoleMetricExporter,
  PeriodicExportingMetricReader
)

from opentelemetry.exporter.otlp.proto.grpc.metric_exporter import OTLPMetricExporter

resource = Resource(                                     // Define um Resource
  attributes={
	SERVICE_NAME: 'meu-app-dahora',                      // Adicione os identificadores que julgar necessário
	SERVICE_VERSION: '0.1.3'                             // E que estão descriminados na biblioteca Resources
  }
)

reader_console = PeriodicExportingMetricReader(ConsoleMetricExporter())                 // Define o reader de console
reader_otlp = PeriodicExportingMetricReader(OTLPMetricExporter(endpoint='batatinhas_fritas_otlp:9999'))                       // Define o reader otlp

provider = MeterProvider(                                // Define um provider para esse resource
  resource=resource,
  metric_readers=[reader_console, reader_otlp]
)

meter = get_meter('meter', meter_provider=provider)      // Pegamos esse provider e colocamos na nossa aplicação

conter = meter.create_counter(                           // Criando uma métrica do tipo contador
  name='carros.passando',                                // Para contar os carros passando na rua
  unit='1',
  description='Carros passando na minha rua'
)

conter.add(                                             // Adicionamos o contador de carros
	amount=1,
	attributes={
      'modelo': 'Monza',
      'cor': 'preto'
	}
)

conter.add(                                             // Adicionamos o contador de carros
	amount=3,
	attributes={
      'modelo': 'Fusca',
      'cor': 'preto'
	}
)

conter.add(                                             // Adicionamos o contador de carros
	amount=6,
	attributes={
      'modelo': 'Marea',
      'cor': 'prata'
	}
)
