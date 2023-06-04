# SensorCommunications
Die Anwendung basiert auf der Verwendung von batteriebetriebenen Temperatur- und Luftfeuchtigkeitssensoren zur Überwachung der Kühlgeräte in einem Laden. Die Sensoren nutzen die Kommunikationstechnologien ESPnow und LoRa, um mit einem zentralen Gateway zu kommunizieren. Das Gateway ist verantwortlich für die Erfassung der Messdaten und deren Weiterleitung an eine InfluxDB-Datenbank.

Die Sensoren werden strategisch in verschiedenen Bereichen des Ladens platziert, um eine umfassende Überwachung der Temperatur und Luftfeuchtigkeit sicherzustellen. Sie sind mit Batterien betrieben, um eine einfache Installation und flexible Positionierung zu ermöglichen. Die Sensoren erfassen kontinuierlich die aktuellen Werte für Temperatur und Luftfeuchtigkeit und senden diese Daten über ESPnow oder LoRa an das Gateway.

Das Gateway dient als zentraler Hub für die Datenkommunikation. Es empfängt die Messdaten von den Sensoren und leitet sie an die InfluxDB-Datenbank weiter. Die InfluxDB ist eine spezielle Zeitreihendatenbank, die sich gut für die Speicherung und Analyse von Sensordaten eignet. Dort werden die Messwerte in Echtzeit gespeichert und können für weitere Analysen und Auswertungen verwendet werden.

Zusätzlich zur Datenspeicherung bietet die Anwendung ein Dashboard, das Grafana verwendet. Grafana ist ein leistungsstarkes Open-Source-Tool zur Visualisierung und Analyse von Daten. Das Dashboard ermöglicht es den Benutzern, die aktuellen und historischen Messwerte der Temperatur und Luftfeuchtigkeit in Form von Grafiken und Diagrammen zu überwachen. Es bietet eine benutzerfreundliche Oberfläche, um die Daten in Echtzeit zu visualisieren und relevante Erkenntnisse daraus zu ziehen.

Um die Sicherheit und Zuverlässigkeit der Kühlgeräte zu gewährleisten, werden bei bestimmten Messwertüberschreitungen Alarmmeldungen generiert. Diese Meldungen werden über den Instant-Messaging-Dienst Telegram an die relevanten Benutzer gesendet. Benutzer können ihre Telegram-Konten mit der Anwendung verbinden, um Alarmmeldungen zu erhalten, wenn zum Beispiel die Temperatur in einem Kühlgerät einen kritischen Wert überschreitet. Diese Alarme ermöglichen es dem Ladenpersonal, schnell zu reagieren und potenzielle Probleme mit den Kühlgeräten zu beheben, um die Qualität und Sicherheit der gelagerten Waren zu gewährleisten.

Die Sensoren sind so konfiguriert, dass sie alle 30 Minuten eine Messung der Temperatur und Luftfeuchtigkeit durchführen. Zwischen den Messungen wechseln sie automatisch in einen Stromsparmodus, um Energie zu sparen. Dieser Modus reduziert den Energieverbrauch der Sensoren erheblich, indem sie in einen schlafenden Zustand versetzt werden. In diesem Zustand verbrauchen die Sensoren nur sehr wenig Strom und maximieren so die Lebensdauer der Batterien.

Die Zeitintervalle zwischen den Messungen können je nach den Anforderungen und der Sensorkonfiguration angepasst werden. In diesem Fall wurde eine Intervallzeit von 30 Minuten gewählt, um regelmäßige Messungen der Temperatur und Luftfeuchtigkeit sicherzustellen. Dieses Intervall kann jedoch entsprechend den spezifischen Anforderungen der Anwendung angepasst werden, z. B. wenn eine höhere oder niedrigere Frequenz der Messungen erforderlich ist.

Der Wechsel in den Stromsparmodus zwischen den Messungen hilft dabei, die Batterielebensdauer der Sensoren zu verlängern. Da die Sensoren normalerweise für eine längere Zeit im Ruhemodus verbringen, bevor sie wieder aktiv werden, können sie über einen längeren Zeitraum betrieben werden, ohne dass die Batterien ausgetauscht oder aufgeladen werden müssen. Dies ist besonders vorteilhaft in Situationen, in denen der Zugang zu den Sensoren erschwert sein kann oder in Umgebungen, in denen eine regelmäßige Wartung der Batterien nicht praktikabel ist.

Durch die Kombination der regelmäßigen Messungen mit dem Stromsparmodus wird eine effiziente und zuverlässige Überwachung der Kühlgeräte im Laden gewährleistet, während gleichzeitig die Lebensdauer der Sensorenbatterien maximiert wird.

Die Sensormodule basieren auf dem ESP8266 Mikrocontroller, einem weit verbreiteten und leistungsstarken Mikrocontroller für IoT-Anwendungen. Sie sind mit DHT11 Sensoren ausgestattet, die speziell für die Erfassung von Temperatur- und Luftfeuchtigkeitsdaten entwickelt wurden. Der ESP8266 Mikrocontroller ermöglicht die einfache Kommunikation mit den Sensoren und die Übertragung der erfassten Daten über ESPnow oder LoRa zum Gateway.

Für die Stromversorgung der Sensormodule werden 3,7V LiIon Akkus und 1,5V AAA LiIon Akkus verwendet. Diese Akkus bieten eine zuverlässige und langlebige Stromversorgung für die Sensoren. Die Verwendung von wiederaufladbaren LiIon Akkus ermöglicht es, die Batterien wiederholt aufzuladen und somit den Bedarf an häufigem Batteriewechsel zu reduzieren.

Das Gateway, das die Kommunikation zwischen den Sensormodulen und der InfluxDB-Datenbank ermöglicht, ist ebenfalls auf dem ESP8266 Mikrocontroller basiert. Es fungiert als zentraler Knotenpunkt, der die Messdaten von den Sensoren empfängt und sie zur weiteren Verarbeitung und Speicherung an die Datenbank sendet.

Die InfluxDB-Datenbank und die Dashboards werden auf einem Raspberry Pi installiert. Der Raspberry Pi ist ein beliebter und vielseitiger Einplatinencomputer, der häufig in IoT-Anwendungen eingesetzt wird. Er bietet genügend Rechenleistung und Speicherplatz, um die InfluxDB-Datenbank zu hosten und die Grafana-Dashboards auszuführen.

Die Entwicklungsumgebung für die Programmierung der Sensormodule und des Gateways ist Visual Studio Code, eine weit verbreitete und leistungsstarke Code-Editor-Plattform. Die Entwicklungsumgebung wird mit dem Plugin PlatformIO erweitert, das speziell für die Entwicklung von Mikrocontroller-basierten Projekten entwickelt wurde. PlatformIO bietet eine integrierte Entwicklungsumgebung mit Tools zur Programmierung, Fehlerbehebung und Überwachung von Mikrocontrollern.

Durch die Kombination von ESP8266 Mikrocontrollern, DHT11 Sensoren, LiIon Akkus, Raspberry Pi, InfluxDB, Grafana und der Entwicklungsumgebung Visual Studio Code mit PlatformIO entsteht eine robuste und leistungsstarke Anwendung zur Überwachung der Kühlgeräte in einem Laden.

Zum Erstellen dieser Beschreibung wurde ChatGPT verwendet.

Folgende Prompts führten zu dem Ergebnis:

- beschreibe eine Anwendung, die mit Hilfe von batteriebetriebenen Temperatur- und Luftfeuchtigkeitsensoren die Kühlgeräte in einem Laden aufzeichnet. Die Sensoren verwenden ESPnow und LoRa um mit einem Gateway zu kommunizieren. Das Gateway sendet die Messdaten an eine InfluxDB Datenbank. Es gibt ein Dashboard dass Grafana verwendet. Bei bestimmten Messwertüberschreitungen werden Alarm Meldungen über Telegram gesendet.

- ergänze: Die Sensoren messen alle 30 Minuten. Dazwischen gehen sie in einen Stromsparmodus.

- ergänze: die Sensormodule verwenden ESP8266 Mikrocontroller und DHT11 Sensoren. Als Batterien werden  3,7V  LiIon Akkus und 1,5V AAA LiIon Akkus verwendet. Das Gateway ist ebenfalls ESP8266 basiert. Die Datenbank und die Dashboards sind auf einem Raspberry Pi installiert. Die Entwicklungsplattform ist Visual Studio Code mit dem Plugin PlatformIO. 
