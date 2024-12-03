#include <QApplication>
#include <QPushButton>
#include "MainWindow.h"
#include "BluiseCore/Settings.h"
#include "Sync/GoogleDriveManager.h"

int main(int argc, char** argv) {
    QApplication a(argc, argv);
    GoogleDriveManager::instance();

    a.setOrganizationName("BasedFrogs");
    a.setApplicationName("Bluise");
    a.setOrganizationDomain("basedfrogs.com");
    Settings::getInstance(&a);

    a.setWindowIcon(QIcon("/Users/leftfrog/Projects/bluise/res/1024-mac-1024.png"));
    MainWindow w;

    QPushButton button("LOL");
    QObject::connect(&button, &QPushButton::clicked, [] {
        GoogleDriveManager::instance().uploadFolder("/Users/leftfrog/Downloads/ddd", GoogleDriveManager::instance().findFolder("Bluise"));
    });
    button.show();
    w.show();
    return a.exec();
}
