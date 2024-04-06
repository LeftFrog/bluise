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
    QString header = "";
    QString fileName = QString::fromStdString(
        std::filesystem::path(choose->path().toStdString())
            .filename()
            .string()
            .substr(0, std::filesystem::path(choose->path().toStdString())
                               .filename()
                               .string()
                               .size() -
                           4));
    QString extension = QString::fromStdString(
        std::filesystem::path(choose->path().toStdString())
            .filename()
            .string()
            .substr(std::filesystem::path(choose->path().toStdString())
                        .filename()
                        .string()
                        .size() -
                    4));
    QString path = bluise_core::DOCS + "res/covers/";
    if (QFile::exists(path + fileName + extension)) {
      int i = 1;
      while (QFile::exists(path + fileName + QString::number(i) + extension)) {
        ++i;
      }
      std::filesystem::copy(
          choose->path().toStdString(),
          (path + fileName + QString::number(i) + extension).toStdString());
      header = fileName + QString::number(i) + extension;
    } else {
      std::filesystem::copy(choose->path().toStdString(),
                            (bluise_core::DOCS + "res/covers").toStdString());
      header = fileName + extension;
    }
    bluise_core::games.push_back(Game(options["name"]->text(),
                                      options["exec"]->text(),
                                      options["workingDirectory"]->text(),
                                      options["savePath"]->text(), header));
  } catch (bluise_error &err) {
    QMessageBox::critical(this, "Error", QString::fromStdString(err.what()));
    return;
  }
  emit added();
  close();
}
