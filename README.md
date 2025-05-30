# EventLogger QRZ Integration — Stan prac (2025-05-27 15:52)

## ✅ Zrealizowane funkcje:

### 🔐 QRZSessionManager
- Obsługa logowania przez HTML (bez API, bez opłat)
- Wykrywanie istniejącej sesji (`xf_session`) — unikanie ponownego logowania
- Parsowanie danych `name`, `qth`, `grid` z HTML strony QRZ
- Obsługa przypadków z cudzysłowem w nazwisku (np. `"Kuba"`)
- Dodane logowanie (via `Logger`) całej komunikacji HTTP i danych sesji

### 🪵 Logger
- Singleton `LogSignalEmitter` z sygnałem `newLogMessage`
- Własny `customMessageHandler` do przechwytywania logów Qt
- Klasa `Logger` z metodami:
  - `logDebug()`
  - `logInfo()`
  - `logWarning()`
  - `logError()`
- Wszystkie logi przekierowane do `DebugWindow`

### 🪟 MainWindow
- Automatyczne dopasowanie `Band` po wpisaniu częstotliwości
- `onCallsignEntered()` aktywuje lookup QRZ
- Logowanie do QRZ uruchamiane przy kliknięciu w pole `Callsign` (prelogowanie)
- Obsługa pól RST domyślnie ustawionych na `59`
- Obsługa `SettingsManager` do pobierania loginu i hasła z `EventLogger.conf`
- Tłumienie logowania przy pustych danych

### ⚙️ SettingsManager
- Obsługa pliku INI (`EventLogger.conf`)
- Sekcja `[QRZ]` odczytuje `Username` i `Password`

---

## 🧪 Testy
- Testowane znaki: `SP3SEB`, `SP3Q`, `SP3X`
- Testy z cudzysłowem w polu imienia — OK
- DebugWindow aktywne, logi przechwytywane

---

## 📦 Struktura projektu
- `include/utils/Logger.h`
- `src/utils/Logger.cpp`
- `include/QrzSessionManager.h`
- `src/QrzSessionManager.cpp`
- `settings/SettingsManager.h`
- `settings/SettingsManager.cpp`
- `mainwindow.h`
- `mainwindow.cpp`

---

73, Seba 😉
