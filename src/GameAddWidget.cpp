#include "GameAddWidget.h"
#include "bluise.h"
#include <QFile>
#include <QMessageBox>
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

void GameAddWidget::changed() {
  if (!applyButton->isEnabled()) {
    if (name->isChanged() && exec->isChanged() && choose->isChanged()) {
      applyButton->setEnabled(true);
    }
  } else {
    if (!name->isChanged() || !exec->isChanged() || !choose->isChanged()) {
      applyButton->setDisabled(true);
    }
  }
}

void GameAddWidget::apply() {
  try {
    if (QFile::exists(bluise_core::DOCS + "res/" +
                      QString::fromStdString(
                          std::filesystem::path(choose->path().toStdString())
                              .filename()
                              .string()))) {
      int i = 1;
      while (
          QFile::exists(bluise_core::DOCS + "res/" +
                        QString::fromStdString(
                            std::filesystem::path(choose->path().toStdString())
                                .filename()
                                .string()))) {
        ++i;
      }
      std::filesystem::copy(
          choose->path().toStdString(),
          (bluise_core::DOCS + "res/").toStdString() +
              std::filesystem::path(choose->path().toStdString())
                  .filename()
                  .string() +
              std::to_string(i));
    } else {
      std::filesystem::copy(choose->path().toStdString(),
                            (bluise_core::DOCS + "res/").toStdString());
    }
    QString header = QString::fromStdString(
        std::filesystem::path(choose->path().toStdString())
            .filename()
            .string());
    bluise_core::games.push_back(Game(name->text(), exec->text(),
                                      working_directory->text(),
                                      save_path->text(), header));
  } catch (bluise_error &err) {
    QMessageBox::critical(this, "Error", QString::fromStdString(err.what()));
    return;
  }
  emit added();
  close();
}
