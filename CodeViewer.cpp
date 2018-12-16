//
// Created by Biny Brion on 10/21/2018.
//

#include "CodeViewer.h"

#include <fstream>
#include <QtWidgets/QMessageBox>

CodeViewer::CodeViewer(QWidget *parent) : QTabWidget(parent)
{
}

void CodeViewer::loadCodeFile(QString fileLocations)
{
    // Open and read the contents of the selected file
    std::string fileContent;

    std::ifstream fileReader{fileLocations.toStdString()};

    std::string currentLine;

    while(std::getline(fileReader, currentLine))
    {
        fileContent += currentLine;

        fileContent += '\n';
        currentLine.clear();
    }

    // Create a new instance of a file viewer associated with the just read file

    codeFiles.push_back({new FileViewer{this}, false});

    // Set the text style and background colour the file viewer will use

    codeFiles.back().first->setStyleSheet("background: rgb(50, 50, 50); font-size: 12pt; font-style: Monospaced");

    // Set the default text colour for the file viewer (text not covered by CodeHighlighter class)

    QPalette textEditPalette = codeFiles.back().first->palette();

    textEditPalette.setColor(QPalette::Text, QColor::fromRgb(200, 200, 200));

    codeFiles.back().first->setPalette(textEditPalette);

    // Set the text of the file viewer to that of the code that was just read

    codeFiles.back().first->document()->setPlainText(QString::fromStdString(fileContent));

    // Add a tab to this class that when pressed will show the file that was read

    addTab(codeFiles.back().first, "");

    // Set the tab name to that of the file name (i.e. from the example location C:/Users/Me/File.cpp, extract File.cpp)

    QString fileName = fileLocations.split('/').back();

    codeFiles.back().first->setWindowTitle(fileName);

    setTabText(currentIndex(), fileName);

    // Needed for some reason (causes this class to load all other tabs at once if not used)
    removeTab(0);
}

void CodeViewer::showCodeFile(QString fileName)
{
    // Iterate over read files to see which one has the requested fileName

    for(auto &i : codeFiles)
    {
        // Found the requested file

        if(fileName == i.first->windowTitle())
        {
            // Insert tab with that shows the file name into the back of the area containing tabs

            insertTab(fileIndexes.size(), i.first, i.first->windowTitle());

            // Open the tab that was just inserted (and thus open the code of that file)

            setCurrentIndex(fileIndexes.size());

            // Keep track of what index this tab occupies

            std::pair<int, QString> temp{fileIndexes.size(), i.first->windowTitle()};

            fileIndexes.push_back(temp);

            // If this is the first time opening the file, find which words need to be highlighted

            if(!i.second)
            {
                codeHighlighter.push_back(new CodeHighlighter{i.first->document()});

                i.second = true;
            }

            break;
        }
    }
}

void CodeViewer::hideCodeFile(QString fileName)
{
    // To keep track of what index the requested file (and its associated tab) is at for use at the end of this function

    int counter = 0;

    for(const auto &i : fileIndexes)
    {
        // File requested has been opened and still is open

        if(fileName == i.second)
        {
            // Hide the requested file by removing the tab associated with it

            removeTab(i.first);

            // Update the (tab) indexes of the files opened after the requested file (files opened before are not affected)

            for(int j = counter; j < fileIndexes.size(); ++j)
            {
                --fileIndexes[j].first;
            }

            break;
        }

        ++counter;
    }

    // Internally set the requested file as closed (the above code hides it visually) so that file can be opened and closed properly later

    fileIndexes.erase(fileIndexes.begin() + counter);
}

void CodeViewer::writeChanges(QString saveDirectory)
{
    // Note: This code is not totally safe, as if there is an error when writing to disk, everything is lost as files are truncated when written to.
    // Note: Attempt to remedy this issue by temporarily renaming files as well as copying lead to program crashes for unknown reasons. This method below is faster however to do.

    // Write files to disk to save changes

    std::ofstream fileWriter;

    for(const auto &i : codeFiles)
    {
        // Try to open the file; if it doesn't succeed, display an error message and move onto next file

        fileWriter.open((saveDirectory + "/" + i.first->windowTitle()).toStdString(), std::ofstream::trunc);

        if(!fileWriter.is_open())
        {
            displaySaveError(QString{"Error: Could not open file for saving: "} + i.first->windowTitle());

            continue;
        }

        // Try to write to file, and display an error message if it does not

        try
        {
            fileWriter << i.first->toPlainText().toStdString();
        }
        catch(std::exception &e)
        {
            displaySaveError(QString{"Error when writing to file: "} + i.first->windowTitle());
        }

        // Prepare for next iteration where more files will be written to

        fileWriter.close();

    }

}

void CodeViewer::displaySaveError(QString errorMessage)
{
    // Display an error message box with the appropriate message

    QMessageBox::warning(this, tr("Code Editor"),
                         tr("Unable to save work.\n",
                            errorMessage.toStdString().c_str()),
                         QMessageBox::Ok);
}

