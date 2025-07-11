#include "mainwindow.h"

#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    const char* appIdStr = getenv("STEAM_COMPAT_APP_ID");
    if (!appIdStr || std::atoi(appIdStr) == 0) {
        return 0;
    }
    for (int i = 0; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg.find("iscriptevaluator.exe") != std::string::npos) {
            return 0;
        }
    }
    QApplication a(argc, argv);
    MainWindow w;
    w.setGameLaunchInfo(argv);
    w.show();
    return a.exec();
}
