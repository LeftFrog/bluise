#include "GameAddWidget.h"
#include "bluise.h"
#include <QFile>
#include <QMessageBox>
#include <filesystem>

GameAddWidget::GameAddWidget(QWidget *parent) : GameOptionsWidget(parent) {
  for (auto &option : options) {
    connect(option, &GameOptionWidget::gameChanged, this,
            &GameAddWidget::changed);
  }
  connect(choose, &ChoosePictureWidget::changed, this, &GameAddWidget::changed);
  applyButton->setText("Add");
}

void GameAddWidget::changed() {
  if (!applyButton->isEnabled()) {
    if (options["name"]->isChanged() && options["exec"]->isChanged() &&
        choose->isChanged()) {
      applyButton->setEnabled(true);
    }
  } else {
    if (!options["name"]->isChanged() || !options["exec"]->isChanged() ||
        !choose->isChanged()) {
      applyButton->setDisabled(true);
    }
  }
}

void GameAddWidget::apply() {
  try {
    bluise_core::games.push_back(Game(options["name"]->text(),
                                      options["exec"]->text(),
                                      options["workingDirectory"]->text(),
                                      options["savePath"]->text(), setCover()));
  } catch (bluise_error &err) {
    QMessageBox::critical(this, "Error", QString::fromStdString(err.what()));
    return;
  }
  emit added();
  close();
}
