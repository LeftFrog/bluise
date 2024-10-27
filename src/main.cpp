#include <QApplication>
#include "MainWindow.h"
#include "BluiseCore/Settings.h"
#include "Sync/GoogleDriveManager.h"

int main(int argc, char** argv) {
    QApplication a(argc, argv);
    GoogleDriveManager::getInstance(&a);

    a.setOrganizationName("BasedFrogs");
    a.setApplicationName("Bluise");
    a.setOrganizationDomain("basedfrogs.com");
    Settings::getInstance(&a);

    a.setWindowIcon(QIcon("/Users/leftfrog/Projects/bluise/res/1024-mac-1024.png"));
    MainWindow w;
    w.show();
    return a.exec();
}
