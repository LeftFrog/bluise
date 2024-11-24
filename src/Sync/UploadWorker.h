//
// Created by Leonov Oleksandr on 11/24/24.
//

#pragma once
#include <QObject>

class UploadWorker : public QObject {
    Q_OBJECT

public:
    explicit UploadWorker(QObject* parent = nullptr);
    ~UploadWorker() override = default;

public slots:
    void process();

signals:
    void finished();

private:
    QString localFilePath;
    QString folderId;
};