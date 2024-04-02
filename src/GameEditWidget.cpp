#include "GameEditWidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include "bluise_error.h"
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
    game->set_name(name->text());
    game->set_working_directory(working_directory->text());
    game->set_executable(exec->text());
    game->set_save_path(save_path->text());
  }
  catch (bluise_error &err) {
    QMessageBox::critical(this, "Error", QString::fromStdString(err.what()));
    return;
  }
  emit gameChanged();
  close();
}

void GameEditWidget::changed() {
  if (!applyButton->isEnabled()) {
    if (name->isChanged() || working_directory->isChanged() ||
        exec->isChanged() || save_path->isChanged() || choose->isChanged()) {
      applyButton->setEnabled(true);
    }
  } else {
    if (!name->isChanged() && !working_directory->isChanged() &&
        !exec->isChanged() && !save_path->isChanged() && !choose->isChanged()) {
      applyButton->setDisabled(true);
    }
  }
}