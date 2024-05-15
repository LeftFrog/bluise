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
  connect(runner, &BoxOptionWidget::changed, this, &GameAddWidget::changed);
}

void GameAddWidget::changed() {
  if (!applyButton->isEnabled()) {
    if (options["name"]->isChanged() && options["exec"]->isChanged() &&
        choose->isChanged() && runner->isChanged()) {
      applyButton->setEnabled(true);
    }
  } else {
    if (!options["name"]->isChanged() || !options["exec"]->isChanged() ||
        !choose->isChanged() && runner->isChanged()) {
      applyButton->setDisabled(true);
    }
  }
}

void GameAddWidget::apply() {
  try {
    Game g = Game(options["name"]->text(),
                                      options["exec"]->text(),
                                      options["workingDirectory"]->text(),
                                      options["savePath"]->text(), setCover());
    g.setRunner(static_cast<Game::Runner>(runner->currentIndex()));
    bluise_core::games.push_back(g);
  } catch (bluise_error &err) {
    QMessageBox::critical(this, "Error", QString::fromStdString(err.what()));
    return;
  }
  emit added();
  close();
}
