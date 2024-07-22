#include "AddLocalInstalledGameWidget.h"
#include "../BluiseCore/bluise.h"
#include "../BluiseCore/bluise_error.h"
#include <QMessageBox>
#include <filesystem>

AddLocalInstalledGameWidget::AddLocalInstalledGameWidget(QWidget* parent) : GameOptionsWidget(parent) {
    applyButton->setText("Add");
}

void AddLocalInstalledGameWidget::closeEvent(QCloseEvent* event) {
    emit closed();
    GameOptionsWidget::closeEvent(event);
}

void AddLocalInstalledGameWidget::changed() {
    if (options["name"]->isChanged() && options["exec"]->isChanged() &&
        runner->isChanged()) {
        applyButton->setEnabled(true);
    } else {
        applyButton->setDisabled(true);
    }
}

void AddLocalInstalledGameWidget::apply() {
    try {
        Game g = Game(options["name"]->text(),
                      options["exec"]->text(),
                      options["workingDirectory"]->text(),
                      options["savePath"]->text(), choose->path().isEmpty() ? "" : getCoverName());
        g.setRunner(static_cast<Game::Runner>(runner->currentIndex()));
        gameManager.addGame(g);
    } catch (bluise_error& err) {
        QMessageBox::critical(this, "Error", QString::fromStdString(err.what()));
        return;
    }
    emit added();
    close();
}
