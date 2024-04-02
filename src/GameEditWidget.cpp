#include "GameEditWidget.h"
#include "bluise_error.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QVBoxLayout>

GameEditWidget::GameEditWidget(Game *_game, QWidget *parent)
    : GameOptionsWidget(*_game, parent), game(_game) {
  connect(name, &GameOptionWidget::gameChanged, this, &GameEditWidget::changed);
  connect(working_directory, &GameOptionWidget::gameChanged, this,
          &GameEditWidget::changed);
  connect(exec, &GameOptionWidget::gameChanged, this, &GameEditWidget::changed);
  connect(save_path, &GameOptionWidget::gameChanged, this,
          &GameEditWidget::changed);
  connect(choose, &ChoosePictureWidget::changed, this,
          &GameEditWidget::changed);
}

void GameEditWidget::apply() {
  try {
    game->setName(name->text());
    game->setWorkingDirectory(working_directory->text());
    game->setExecutable(exec->text());
    game->setSavePath(save_path->text());
  } catch (bluise_error &err) {
    QMessageBox::critical(this, "Error", QString::fromStdString(err.what()));
    return;
  }
  emit gameChanged();
  close();
}

void GameEditWidget::changed() {
  if (!applyButton->isEnabled()) {
    if (name->isChanged() || exec->isChanged() || choose->isChanged()) {
      applyButton->setEnabled(true);
    }
  } else {
    if (!name->isChanged() && !exec->isChanged() && !choose->isChanged()) {
      applyButton->setDisabled(true);
    }
  }
}
