#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void launchGameExe(const QString &exePath);
    void setGameLaunchInfo(char *argv[]);
    void refreshGameInfoBox();
    void changeGameExe();

private:
    std::string gameExe;
    std::string gameParams;
    std::string slrPath = "/home/user/.local/share/Steam/steamapps/common/SteamLinuxRuntime_sniper/_v2-entry-point";
    std::string protonExe = "/home/user/.local/share/Steam/steamapps/common/Proton - Experimental/proton";

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
