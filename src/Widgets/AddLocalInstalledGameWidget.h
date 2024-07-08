#pragma once
#include "GameOptionsWidget.h"

class AddLocalInstalledGameWidget : public GameOptionsWidget {
  Q_OBJECT
public:
  AddLocalInstalledGameWidget(QWidget *parent = nullptr);

signals:
  void added();
  void closed();

protected slots:
  virtual void apply() override;
  void changed() override;

protected:
  virtual void closeEvent(QCloseEvent* event) override;
};