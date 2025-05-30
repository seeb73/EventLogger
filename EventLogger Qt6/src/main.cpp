#include "include/mainwindow.h"

#include <QApplication>
#include <QDebug> // Wymagane dla qDebug
#include <QLoggingCategory>
#include "include/utils/Logger.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	qInstallMessageHandler(customMessageHandler);

    // Upewnij się, że logowanie SSL jest włączone, aby przechwytywać błędy
    // QLoggingCategory::set             (QStringLiteral("qt.network.ssl"), QtDebugMsg);
    // lub dla wszystkich kategorii
    //QLoggingCategory::set            (QStringLiteral("qt.*"), QtDebugMsg);
	QLoggingCategory::setFilterRules(QStringLiteral("qt.network.ssl=true\nqt.*=debug"));
	
    MainWindow w;
    w.show();
    return a.exec();
}
