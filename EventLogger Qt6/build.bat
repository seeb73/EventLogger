@echo off
REM Skrypt kompilacji dla projektu EventLogger

REM Ustaw zmienne środowiskowe
set QTDIR=V:\Qt5.14\5.14.2\mingw73_64  REM Ścieżka do instalacji Qt
set CMAKE_PREFIX_PATH=%QTDIR%

REM Dodaj ścieżkę do mingw do PATH, jeśli nie jest już tam
set PATH=%PATH%;%QTDIR%\bin;%QTDIR%\..\Tools\mingw730_64\bin

REM Utwórz katalog build, jeśli nie istnieje
if not exist build mkdir build

REM Przejdź do katalogu build
cd build

REM Uruchom cmake
cmake -G "MinGW Makefiles" ..

REM Kompiluj projekt
mingw32-make -j4

REM Powrót do pierwotnego katalogu
cd ..
pause