// Radio.cpp
//
// Uwaga:
// Ten plik nie pochodzi z oryginalnego projektu JTDX/WSJT-X.
// Został utworzony lokalnie w celu zachowania kompatybilności
// z istniejącym kodem (np. MessageAggregator), który odwołuje się
// do klasy `Radio`. Nie należy jej nadpisywać oryginalną klasą.
//
// Klasa zapewnia tylko metodę pretty_frequency_MHz_string, używającą
// lokalnej wartości częstotliwości – obecnie pobieranej z GUI.

#include "include/utils/Radio.hpp"
#include "include/mainwindow.h"  // dostęp do MainWindow::instance()

QString Radio::pretty_frequency_MHz_string(quint64 freq_hz)
{
    // Użyj częstotliwości z formularza GUI, jeśli dostępna
    if (auto* mw = MainWindow::instance()) {
        QString value = mw->getFreqField();  // powinno zwracać np. "14074"
        bool ok = false;
        double freq_mhz = value.toDouble(&ok) / 1000.0;
        if (ok)
            return QString::number(freq_mhz, 'f', 3);
    }

    // fallback jeśli GUI nie działa
    return QString::number(freq_hz / 1e6, 'f', 3);
}
