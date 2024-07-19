#include "EditGameWidget.h"
#include "../BluiseCore/bluise_error.h"
#include "../BluiseCore/bluise.h"
#include <QHBoxLayout>
#include <QMessageBox>

EditGameWidget::EditGameWidget(const Game& game, QWidget *parent)
    : GameOptionsWidget(game, parent), game(game) {

}

void EditGameWidget::apply() {
  try {
    gameManager.setData(game, options["name"]->text(), GameListModel::NameRole);
    gameManager.setData(game, options["executable"]->text(), GameListModel::ExecutableRole);
    gameManager.setData(game, options["workingDirectory"]->text(), GameListModel::WorkingDirectoryRole);
    gameManager.setData(game, options["savePath"]->text(), GameListModel::SavePathRole);
    gameManager.setData(game, options["releaseYear"]->text().toInt(), GameListModel::ReleaseYearRole);
    gameManager.setData(game, runner->currentIndex(), GameListModel::RunnerRole);
    if(choose->isChanged()) {
      gameManager.setData(game, setCover(), GameListModel::InstalledRole);
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
