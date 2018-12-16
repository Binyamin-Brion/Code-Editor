//
// Created by Biny Brion on 10/21/2018.
//

#ifndef PERFORMANCEMONITOR_CODEVIEWER_H
#define PERFORMANCEMONITOR_CODEVIEWER_H


#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QTabWidget>
#include <forward_list>
#include "CodeHighlighter.h"
#include "FileViewer.h"
#include "CounterWriter.h"

class CodeLineNumber;

// Show all the selected code files from the directory viewer
class CodeViewer : public QTabWidget
{
    Q_OBJECT

public:

    explicit CodeViewer(QWidget *parent = nullptr);

public slots:
    void loadCodeFile(QString fileLocations);
    void showCodeFile(QString fileName);
    void hideCodeFile(QString fileName);
    void writeChanges(QString saveDirectory);

private:

    void displaySaveError(QString errorMessage);

    CounterWriter counterWriter;

    std::vector<std::pair<int, QString>> fileIndexes;

    std::vector<std::pair<FileViewer*, bool>> codeFiles;

    std::vector<CodeHighlighter*> codeHighlighter;

    CodeLineNumber *codeLineNumber = nullptr;
};




#endif //PERFORMANCEMONITOR_CODEVIEWER_H
