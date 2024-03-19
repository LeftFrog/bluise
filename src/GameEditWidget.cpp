#include "GameEditWidget.h"
#include "ChoosePictureWidget.h"
#include "FileValidator.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QLineEdit>

GameEditWidget::GameEditWidget(Game* _game, QWidget* parent) : QWidget(parent), game(_game) {
    QLabel* lbl = new QLabel("Name: ");
    QLineEdit* ledit = new QLineEdit(QString::fromStdString(game->get_name()));
    QHBoxLayout* HBL = new QHBoxLayout;
    HBL->addWidget(lbl);
    HBL->addWidget(ledit);

    QLabel* lbl1 = new QLabel("Working directory: ");
    QPushButton* pbutton1 = new QPushButton("open");
    connect(pbutton1, &QPushButton::clicked, this,&GameEditWidget::open_file);
    QLineEdit* ledit1 = new QLineEdit(QString::fromStdString(game->get_working_directory()));
    ledit1->setValidator(new FileValidator(true, ledit1));
    QHBoxLayout* HBL1 = new QHBoxLayout;
    HBL1->addWidget(lbl1);
    HBL1->addWidget(ledit1);
    HBL1->addWidget(pbutton1);

    QLabel* lbl2 = new QLabel("Executable: ");
    QLineEdit* ledit2 = new QLineEdit(QString::fromStdString(game->get_executable()));
    ledit2->setValidator(new FileValidator(false, ledit2));
    QHBoxLayout* HBL2 = new QHBoxLayout;
    HBL2->addWidget(lbl2);
    HBL2->addWidget(ledit2);

    QLabel* lbl3 = new QLabel("Save path: ");
    QLineEdit* ledit3 = new QLineEdit(QString::fromStdString(game->get_save_path()));
    ledit3->setValidator(new FileValidator(true, ledit3));
    QHBoxLayout* HBL3 = new QHBoxLayout;
    HBL3->addWidget(lbl3);
    HBL3->addWidget(ledit3);

    QPushButton* apply = new QPushButton("Apply");
    apply->setDefault(true);
    QPushButton* cancel = new QPushButton("Cancel");
    connect(cancel, &QPushButton::clicked, this, &GameEditWidget::closeWin);
    QHBoxLayout* HBL4 = new QHBoxLayout;
    HBL4->addWidget(cancel);
    HBL4->addWidget(apply);

    QVBoxLayout* VBL = new QVBoxLayout;
    ChoosePictureWidget* choose = new ChoosePictureWidget();
    choose->setPicture(game->get_header_path());
    VBL->addWidget(choose);
    VBL->addLayout(HBL);
    VBL->addLayout(HBL1);
    VBL->addLayout(HBL2);
    VBL->addLayout(HBL3);
    VBL->addLayout(HBL4);
    setLayout(VBL);
}

void GameEditWidget::closeWin()
{
    close();
}

void GameEditWidget::open_file() {
    QFileDialog* fd = new QFileDialog();
    //fd->
}