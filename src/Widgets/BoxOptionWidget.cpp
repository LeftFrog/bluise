#include "BoxOptionWidget.h"
#include <QLabel>
#include <QHBoxLayout>

BoxOptionWidget::BoxOptionWidget(QString name, int runnerIndex, QWidget* parent) : QWidget(parent), firstValue(runnerIndex) {
  QLabel* lbl = new QLabel(name);

  runner = new QComboBox(this);
  runner->addItem("Native");
  runner->addItem("GamePortingToolkit");
  runner->setCurrentIndex(runnerIndex);
  connect(runner, &QComboBox::currentIndexChanged, this, &BoxOptionWidget::changed);

  QHBoxLayout* layout = new QHBoxLayout;
  layout->addWidget(lbl);
  layout->addWidget(runner);
  setLayout(layout);
}