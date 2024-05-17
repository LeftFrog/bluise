#include "GameAddWidget.h"
#include "../BluiseCore/bluise.h"
#include <QFile>
#include <QMessageBox>
#include <filesystem>

GameAddWidget::GameAddWidget(QWidget *parent) : GameOptionsWidget(parent) {
  applyButton->setText("Add");
}

void GameAddWidget::changed() {
  if (options["name"]->isChanged() && options["exec"]->isChanged() &&
      choose->isChanged() && runner->isChanged()) {
    applyButton->setEnabled(true);
  } else {
      applyButton->setDisabled(true);
  }
}

void GameAddWidget::apply() {
  try {
    Game g = Game(options["name"]->text(),
                                      options["exec"]->text(),
                                      options["workingDirectory"]->text(),
                                      options["savePath"]->text(), setCover());
    if(choose->path().isEmpty()) {
      g.setCover("");
    } else {
      g.setCover(setCover());
    }
    g.setRunner(static_cast<Game::Runner>(runner->currentIndex()));
    bluise_core::games.push_back(g);
  } catch (bluise_error &err) {
    QMessageBox::critical(this, "Error", QString::fromStdString(err.what()));
    return;
  }
  emit added();
  close();
}
