# 02 - Programming without Delay

Möchte man eine bestimmte Aufgabe alle x Millisekunden abarbeiten, so kann man nicht mehr mit

```
delay(MS)
```
arbeiten.

## Grundlagenwissen

Ein Mikrocontroller, wie der ESP8266 oder auch Arduinos, können keine Nebenläufigkeit (Threads) verarbeiten. Es können also keine Aufgaben parallel abgearbeitet werden, denn es wird immer wieder nur die loop-Funktion durchlaufen. Wenn man diese jetzt mittels der delay-Funktion für x Millisekunden anhält, pausiert der gesamte Mikrocontroller für diese Zeit und es können keine anderen Aufgaben ausgeführt werden. Das wäre vergleichbar mit dem Stop-And-Go im Straßenverkehr. Ihr kennt das, nervig, stressig und nicht zielführend. Daher müssen wir uns nun einen neuen Weg überlegen unseren Sketch aufzubauen.

## Vorüberlegung


## Built With

* [Dropwizard](http://www.dropwizard.io/1.0.2/docs/) - The web framework used
* [Maven](https://maven.apache.org/) - Dependency Management
* [ROME](https://rometools.github.io/rome/) - Used to generate RSS Feeds

## Autor

* **Christian Schneider** - *Initial work* - [schneiderEDU](https://github.com/schneiderEDU)

## Lizenz

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
