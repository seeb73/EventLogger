# EventLogger.pro

QT += core gui widgets network

TEMPLATE = app

CONFIG += c++17  # Użyj C++17 lub wyższej wersji, jeśli potrzebujesz

# Źródła
SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/QrzSessionManager.cpp \
    src/settings/settingsdialog.cpp \
    src/settings/SettingsManager.cpp \
    src/debugwindow/debugwindow.cpp \
    src/utils/ADIF.cpp \
    src/utils/ADIFfile.cpp \
    src/utils/Crypto.cpp \
    src/utils/Logger.cpp \
    src/utils/MessageAggregator.cpp \
    src/utils/MessageClient.cpp \
    src/utils/NetworkMessage.cpp \
    src/utils/Radio.cpp
# src/utils/MessageClient_impl.cpp \	
	
# Nagłówki
HEADERS += \
    include/mainwindow.h \
    include/QrzSessionManager.h \
    include/settings/settingsdialog.h \
    include/settings/SettingsManager.h \
    include/debugwindow/debugwindow.h \
    include/utils/Crypto.h \
    include/utils/Logger.h \
    include/utils/MessageClient.hpp \
    include/utils/NetworkMessage.hpp\
    include/utils/ADIF.h \
    include/utils/ADIFfile.h \
    include/utils/Radio.hpp \
	include/utils/MessageClient_impl.hpp \
    include/utils/pimpl_h.hpp \
    include/utils/MessageServer.hpp

# include/utils/MessageClient_impl.hpp \

# Pliki UI
FORMS += \
    ui/mainwindow.ui \
    ui/settings/settingsdialog.ui \
    ui/debugwindow/debugwindow.ui

# Zasoby
RESOURCES += res/icons/resources.qrc

# Dodatkowe opcje kompilacji (opcjonalne)
QMAKE_CXXFLAGS += -Wall -O2

QMAKE_CXXFLAGS += -std=c++17
QMAKE_LFLAGS += -lstdc++fs
DEFINES += QT_NO_FILESYSTEM

INCLUDEPATH += Z:/Qt6/Tools/mingw1310_64/opt/include
LIBS += -LZ:/Qt6/Tools/mingw1310_64/opt/lib -lssl -lcrypto
