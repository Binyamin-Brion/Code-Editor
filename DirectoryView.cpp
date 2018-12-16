//
// Created by Biny Brion on 10/19/2018.
//

#include <QDir>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QInputDialog>
#include <QMessageBox>
#include <fstream>
#include "DirectoryView.h"

DirectoryView::DirectoryView(QWidget *parent) : QTreeWidget{parent}
{
    // Avoid a number showing at top of widget
    setHeaderHidden(true);

    // If a QTreeWidgetItem is clicked, change its checkbox and all of its children checkboxes

    connect(this, &QTreeWidget::itemClicked, [this](QTreeWidgetItem *item, int column)
    {
        auto isCheckable = std::find_if(readableFiles.begin(), readableFiles.end(), [item](const QString &fileName)
        {
            return item->text(0) == fileName;
        });

        if(isCheckable != readableFiles.end())
        {
            parentChildTree.checkRelatedEntries(item);

            if(item->checkState(0) == Qt::Checked)
            {
                emit showFile(item->text(0));
            }
            else
            {
                emit hideFile(item->text(0));
            }
        }

    });
}

void DirectoryView::loadProject(QString projectLocation, QString newSaveLocation)
{
    // TODO: Release these hard-coded root paths for release

    if(projectLocation.isEmpty())
    {
        QMessageBox::critical(this, tr("Code Editor"), tr("Invalid project location. Please specify a folder."), QMessageBox::Ok);

        return;
    }

    this->rootPath = projectLocation;

    // QDir{}.mkdir("C:/Users/Biny Brion/PerformanceMonitorTest");

    this->savedPath = newSaveLocation;

    loadCMakeFile(rootPath);

    if(readableFiles.empty())
    {
        QMessageBox::critical(this, tr("Performance Counter"), tr("Unable to load a find a CMakeLists.txt file. Features may not work as expected"));
    }

    loadDirectoryInformation(projectLocation, newSaveLocation, nullptr);

    // Construct a hierarchy of the file structure using the loaded directory information

    for(const auto &i : items)
    {
        parentChildTree.addItem(i->parent(), i);
    }

    // Add loaded data to widget to be displayed

    insertTopLevelItems(0, items);
}

void DirectoryView::loadCMakeFile(QString directory)
{
    // This function recursively calls itself in order to load all directory contents, including those in sub-folders

    QDir currentDirectory{directory};

    // Get a list of all the content in the current directory, with folders listed first

    QFileInfoList directoryContent = currentDirectory.entryInfoList(QDir::AllEntries, QDir::DirsLast);

    // Iterate over contents of the directory, to check for a cmake file

    for(const auto &i : directoryContent)
    {
        if(i.fileName() == "CMakeLists.txt")
        {
            // Get the full path directory to the cmake file

            QString currentFile = directory + "/" + i.fileName();

            // Read the cmake file so it can be edited later (connected to CodeViewer object)

            emit readFile(currentFile);

            // Specially read information to extract project information (connected to BuildCommand object)

            emit readCmakeFile(currentFile);

            // Open file and read its contents

            std::fstream cmakeFile;

            cmakeFile.open(currentFile.toStdString());

            if(!cmakeFile.is_open())
            {
                throw std::runtime_error{"Unable to open the cmake file"};
            }

            std::string fileContent;

            std::string temp;

            while(std::getline(cmakeFile, temp))
            {
                fileContent += temp;

                fileContent += '\n';

                temp.clear();
            }

            // Find line where project files are listed
            // TODO: Add support for file names being listed in a different location in a Cmake file

            unsigned int fileNamesLocations = fileContent.find("SOURCE_FILES ");

            if(0 == fileNamesLocations)
            {
                throw std::runtime_error{"Unable to find project code file names"};
            }

            // Find where in file the list of project files ends

            unsigned int endFileNamesLocation = fileContent.find(')', fileNamesLocations);

            if(std::string::npos == endFileNamesLocation)
            {
                throw std::runtime_error{"Unable to find end of project code file names"};
            }

            // Extract the line with just the project files

            fileContent = fileContent.substr(fileNamesLocations, endFileNamesLocation - fileNamesLocations);

            // Split the line by whitespace to get a list of individual project code file names

            readableFiles = QString::fromStdString(fileContent).split(' ');

            // Add name of cmake file as it will not be listed in the the cmake file itself

            readableFiles.push_back("CMakeLists.txt");

            return;
        }

        // If the current content is a folder, check if cmake file is located in that folder

        if(i.isDir())
        {
            QString subDirectory{directory + "/" + i.fileName()};

            readCmakeFile(subDirectory);
        }
    }
}

void DirectoryView::loadDirectoryInformation(QString directory, QString newSaveDirectory, QTreeWidgetItem *parent)
{
    // This function recursively calls itself in order to load all directory contents, including those in sub-folders

    QDir currentDirectory{directory};

    // Get a list of all the content in the current directory, with folders listed first

    QFileInfoList directoryContent = currentDirectory.entryInfoList(QDir::AllEntries, QDir::DirsFirst);

    // Remove first two results of list of contents. They (try to) show relative paths using dots, which is not needed

    directoryContent.removeAt(0);
    directoryContent.removeAt(0);

    // Iterate over contents of the directory, and give each content a visual representation with a QTreeWidgetItem

    for(const auto &i : directoryContent)
    {
        items.push_back(new QTreeWidgetItem(parent));

        items.back()->setText(0, i.fileName());

        std::find_if(readableFiles.begin(), readableFiles.end(), [this](const QString &fileFormat)
        {
            if(items.back()->text(0) == fileFormat)
            {
                items.back()->setCheckState(0, Qt::Unchecked);

                return true;
            }

            return false;
        });

        // If the current content is a folder, read its contents before continuing with the current directory.

        if(i.isDir())
        {
            QString subDirectory{directory + "/" + i.fileName()};

            QString saveSubDirectory{newSaveDirectory + "/" + i.fileName()};

            QDir{}.mkdir(saveSubDirectory);

            loadDirectoryInformation(subDirectory, saveSubDirectory, items.back());
        }

        QFile::copy(directory + "/" + i.fileName(), newSaveDirectory + "/" + i.fileName());

        QString currentFile{newSaveDirectory + "/" + i.fileName()};

        std::find_if(readableFiles.begin(), readableFiles.end(), [this, &currentFile](const QString &fileFormat)
        {
            if(currentFile.endsWith(fileFormat))
            {
                // Read the file so it can be edited later (connected to CodeViewer object)

                emit readFile(currentFile);

                return true;
            }

            return false;
        });

    }
}

QString DirectoryView::getSaveLocation()
{
    return savedPath;
}
