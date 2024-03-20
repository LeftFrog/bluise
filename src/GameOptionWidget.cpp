#include "GameOptionWidget.h"
#include "QPushButton"
#include "FileValidator.h"


GameOptionWidget::GameOptionWidget(const QString & label, const QString & text, QWidget * parent)
{
    QHBoxLayout* layout = new QHBoxLayout();
    lbl = new QLabel(label);
    ledit = new QLineEdit(text);
    layout->addWidget(lbl);
    layout->addWidget(ledit);
    setLayout(layout);
}

GameOptionWidget::GameOptionWidget(const QString & label, const QString & text, bool _has_file_dialog, QWidget * parent) : QWidget(parent), has_file_dialog(_has_file_dialog) {
    QHBoxLayout* layout = new QHBoxLayout();
    lbl = new QLabel(label);
    ledit = new QLineEdit(text);
    layout->addWidget(lbl);
    layout->addWidget(ledit);
    ledit->setValidator(new FileValidator(!has_file_dialog, ledit));
    QPushButton* pbutton = new QPushButton("open");
    connect(pbutton, &QPushButton::clicked, this, &GameOptionWidget::open_file);
    layout->addWidget(pbutton);
    setLayout(layout);
}

void GameOptionWidget::open_file() {
    QString file = has_file_dialog ? QFileDialog::getOpenFileName(this, "Open file") : QFileDialog::getExistingDirectory(this, "Open directory");
    if(!file.isEmpty()) {
        ledit->setText(file);
    }
}