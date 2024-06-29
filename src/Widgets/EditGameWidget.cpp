#include "EditGameWidget.h"
#include "../BluiseCore/bluise_error.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QVBoxLayout>

EditGameWidget::EditGameWidget(Game *_game, QWidget *parent)
    : GameOptionsWidget(*_game, parent), game(_game) {

}

void EditGameWidget::apply() {
  try {
    game->setName(options["name"]->text());
    game->setWorkingDirectory(options["workingDirectory"]->text());
    game->setExecutable(options["exec"]->text());
    game->setSavePath(options["savePath"]->text());
    game->setReleaseYear(options["releaseYear"]->text().toInt());
    game->setRunner(static_cast<Game::Runner>(runner->currentIndex()));
    if(choose->isChanged()) {
      game->setCover(setCover());
    }
  } catch (bluise_error &err) {
    QMessageBox::critical(this, "Error", QString::fromStdString(err.what()));
    return;
  }
  emit gameChanged();
  close();
}

bool EditGameWidget::optionsHaveChanged() {
    for(auto opt : options) {
      if(opt->isChanged()) {
        return true;
      }
    }
    return false;
}

void EditGameWidget::changed() {
  if(optionsHaveChanged() || choose->isChanged() || runner->isChanged()) {
    applyButton->setEnabled(true);
  } else {
    applyButton->setDisabled(true);
  }
}