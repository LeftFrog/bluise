#include "GameAddWidget.h"
#include "bluise.h"
#include <QFile>
#include <filesystem>

GameAddWidget::GameAddWidget(QWidget *parent) : GameOptionsWidget(parent) {
  connect(name, &GameOptionWidget::gameChanged, this, &GameAddWidget::changed);
  connect(working_directory, &GameOptionWidget::gameChanged, this,
          &GameAddWidget::changed);
  connect(exec, &GameOptionWidget::gameChanged, this, &GameAddWidget::changed);
  connect(save_path, &GameOptionWidget::gameChanged, this,
          &GameAddWidget::changed);
  applyButton->setText("Add");
}

void GameAddWidget::changed()
{
  if(!applyButton->isEnabled())
  {
    if(name->isChanged() && working_directory->isChanged() && exec->isChanged() && save_path->isChanged() && choose->isChanged())
    {
      applyButton->setEnabled(true);
    }
  }
  else
  {
    if(!name->isChanged() || !working_directory->isChanged() || !exec->isChanged() || !save_path->isChanged() || !choose->isChanged())
    {
      applyButton->setDisabled(true);
    }
  }
}

void GameAddWidget::apply() {
  std::filesystem::copy(choose->path().toStdString(),
                        (bluise_core::DOCS + "res/").toStdString());
  QString header = QFile(choose->path()).fileName();
  bluise_core::games.push_back(Game(name->text(), working_directory->text(),
                                    exec->text(), save_path->text(), header));
  emit added();
  close();
}
