#pragma once
#include <QFileDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>

class GameOptionWidget : public QWidget {
  Q_OBJECT
private:
  QLineEdit *ledit;
  QLabel *lbl;
  QString first_text;
  bool has_file_dialog;
private slots:
  void open_file();

public:
  GameOptionWidget(const QString &label, const QString &text,
                   QWidget *parent = nullptr);
  GameOptionWidget(const QString &label, const QString &text,
                   bool _has_file_dialog, QWidget *parent = nullptr);
  QString text() const { return ledit->text(); }
  bool isChanged() const { return ledit->text() != first_text; }
signals:
  void gameChanged();
};
