//
// Created by Leonov Oleksandr on 11/24/24.
//

#include "UploadWorker.h"

#include "GoogleDriveManager.h"

UploadWorker::UploadWorker(const QString localFilePath, const QString folderId, QObject* parent) : QObject(parent), localFilePath(localFilePath), folderId(folderId) {}

void UploadWorker::process() {
    GoogleDriveManager::instance().uploadFile(localFilePath, folderId);
    emit finished();
}