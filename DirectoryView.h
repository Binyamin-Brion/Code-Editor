//
// Created by Biny Brion on 10/19/2018.
//

#ifndef PERFORMANCEMONITOR_DIRECTORYVIEW_H
#define PERFORMANCEMONITOR_DIRECTORYVIEW_H

#include <QtWidgets/QTreeWidget>
#include "ParentChildTree.h"

// Provides a GUI view for the file structure for the given root path

class DirectoryView : public QTreeWidget
{
    Q_OBJECT

public:

    explicit DirectoryView(QWidget *parent = nullptr);
    QString getSaveLocation();
    void loadProject(QString projectLocation, QString newSaveLocation);

public slots:
    void openNewProject();

signals:
    void readCmakeFile(QString fileLocation);
    void readFile(QString fileLocation);
    void showFile(QString fileName);
    void hideFile(QString fileName);

private:

    void loadCMakeFile(QString directory);
    void loadDirectoryInformation(QString directory,  QString newSaveDirectory, QTreeWidgetItem *parent);

    QList<QTreeWidgetItem*> items;
    std::vector<std::pair<int, int>> childItems;

    QString rootPath;
    QString savedPath;

    ParentChildTree parentChildTree;

    std::array<QString, 4> acceptedFileFormats{{".c", ".cpp", ".h", ".hpp"}};

    QStringList readableFiles;
};

#endif //PERFORMANCEMONITOR_DIRECTORYVIEW_H
