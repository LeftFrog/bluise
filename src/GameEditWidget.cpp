#include "GameEditWidget.h"
#include "bluise_error.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QVBoxLayout>

GameEditWidget::GameEditWidget(Game *_game, QWidget *parent)
    : GameOptionsWidget(*_game, parent), game(_game) {
  for(auto &option : options) {
    connect(option, &GameOptionWidget::gameChanged, this, &GameEditWidget::changed);
  }
  connect(choose, &ChoosePictureWidget::changed, this,
          &GameEditWidget::changed);
}

void GameEditWidget::apply() {
  try {
    game->setName(options["name"]->text());
    game->setWorkingDirectory(options["workingDirectory"]->text());
    game->setExecutable(options["exec"]->text());
    game->setSavePath(options["savePath"]->text());
    game->setReleaseYear(options["releaseYear"]->text().toInt());
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

void GameEditWidget::changed() {
  if (!applyButton->isEnabled()) {
    for(auto opt : options) {
      if(opt->isChanged()) {
        applyButton->setEnabled(true);
      }
    }
    if(choose->isChanged()) {
      applyButton->setEnabled(true);
    }
  } else {
    int i = 0;
    for(auto opt : options) {
      if(!opt->isChanged()) {
        ++i;
      }
    }
    if(!choose->isChanged() && i == options.size()) {
      applyButton->setDisabled(true);
    }
  }
}
