#ifndef RADIO_HPP
#define RADIO_HPP

#include <QString>

/*
 * Uwaga:
 * Ten plik nie pochodzi z oryginalnego projektu JTDX/WSJT-X.
 * Został utworzony lokalnie w celu zachowania kompatybilności
 * z istniejącym kodem (np. MessageAggregator), który odwołuje się
 * do klasy `Radio`. Ta wersja dostarcza tylko minimalne API wymagane
 * przez nasze komponenty. Nie należy jej nadpisywać oryginalną klasą.
 */

class Radio
{
public:
    // Zwraca częstotliwość w MHz jako sformatowany QString, np. "14.074"
    static QString pretty_frequency_MHz_string(quint64 freq_hz);
    using Frequency = double;  // lub inny odpowiedni typ

    static QString frequency_MHz_string(quint64 freq_hz) {
        return pretty_frequency_MHz_string(freq_hz);
    }
    // static frequency_MHz_string
    // W przyszłości: można dodać inne metody/atrybuty potrzebne dla GUI/Hamlib

};


#endif // RADIO_HPP
