#include "mainwindow.h"
#include "qvapplication.h"

#include <QCommandLineParser>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setOrganizationName("qView");
    QCoreApplication::setApplicationName("qView");
    QCoreApplication::setApplicationVersion(QString::number(VERSION));
    QVApplication app(argc, argv);

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument(QObject::tr("file"), QObject::tr("The file to open."));
    parser.process(app);

    auto *window = QVApplication::newWindow();
    // window->setWindowFlags((window->windowFlags()) & Qt::WindowDoesNotAcceptFocus);
    // window->setWindowState((window->windowState()) & ~Qt::WindowActive);
    // app.setActivationWindow(window, false);
    if (!parser.positionalArguments().isEmpty()) {
        // QVApplication::openFile(window, parser.positionalArguments().constFirst(), true);
        if (app.sendMessage(parser.positionalArguments().constFirst())) {
            // window->setWindowState((window->windowState()) & ~Qt::WindowActive);
            // window->setWindowFlags((window->windowFlags()) & Qt::WindowStaysOnBottomHint & Qt::FramelessWindowHint);
            return 0;
        } else {
            QVApplication::openFile(window, parser.positionalArguments().constFirst(), true);
            // window->setWindowState((window->windowState()) & ~Qt::WindowActive);
            // window->setWindowFlags(Qt::WindowDoesNotAcceptFocus);
            // Qt::WindowStaysOnBottomHint
        }
    } else {
        if (app.sendMessage("k")) {
            return 0;
        }
    }
    // window->setWindowState((window->windowState()) & ~Qt::WindowActive);
    // QObject::connect(&app, SIGNAL(messageReceived(const QString&)), window, SLOT(openFileF(const QString&)));
    QObject::connect(&app, &QVApplication::messageReceived, &app, &QVApplication::openFileF);
    return QApplication::exec();
}
