#pragma once
#include <QComboBox>

class BoxOptionWidget : public QWidget {
  Q_OBJECT
public:
  BoxOptionWidget(QString name, int runnerIndex = 0, QWidget* parent = nullptr);
  bool isChanged() { return firstValue != runner->currentIndex(); }
  int currentIndex() { qDebug() <<  runner->currentIndex(); return runner->currentIndex(); }
signals:
  void changed();
private:
  QComboBox* runner;
  int firstValue;
};