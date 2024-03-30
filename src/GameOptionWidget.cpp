#include "GameOptionWidget.h"
#include "FileValidator.h"
#include "QPushButton"

GameOptionWidget::GameOptionWidget(const QString &label, const QString &text,
                                   QWidget *parent)
    : QWidget(parent), first_text(text) {
  QHBoxLayout *layout = new QHBoxLayout();
  lbl = new QLabel(label);
  ledit = new QLineEdit(text);
  layout->addWidget(lbl);
  layout->addWidget(ledit);
  connect(ledit, &QLineEdit::textChanged, this, &GameOptionWidget::gameChanged);
  setLayout(layout);
}

GameOptionWidget::GameOptionWidget(const QString &label, const QString &text,
                                   bool _has_file_dialog, QWidget *parent)
    : QWidget(parent), has_file_dialog(_has_file_dialog), first_text(text) {
  QHBoxLayout *layout = new QHBoxLayout();
  lbl = new QLabel(label);
  ledit = new QLineEdit(text);
  layout->addWidget(lbl);
  layout->addWidget(ledit);
  ledit->setValidator(new FileValidator(!has_file_dialog, ledit));
  QPushButton *pbutton = new QPushButton("...");
  connect(pbutton, &QPushButton::clicked, this, &GameOptionWidget::open_file);
  connect(ledit, &QLineEdit::textChanged, this, &GameOptionWidget::gameChanged);
  layout->addWidget(pbutton);
  setLayout(layout);
}

void GameOptionWidget::open_file() {
  QString file =
      has_file_dialog
          ? QFileDialog::getOpenFileName(this, "Open file")
          : QFileDialog::getExistingDirectory(this, "Open directory");
  if (!file.isEmpty()) {
    ledit->setText(file);
  }
}