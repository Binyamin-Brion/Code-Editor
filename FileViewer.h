//
// Created by Biny Brion on 10/25/2018.
//

#ifndef PERFORMANCEMONITOR_FILEVIEWER_H
#define PERFORMANCEMONITOR_FILEVIEWER_H

// Shamelessly taken from Qt tutorials (changed connection to use lambdas as the way shown in tutorial gave errors)

#include <QtWidgets/QPlainTextEdit>

class FileViewer : public QPlainTextEdit
{
public:

    explicit FileViewer(QWidget *parent = nullptr);

    const std::vector<int>& getSelectedCharacters();

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();
    void mouseDoubleClickEvent(QMouseEvent *event) override;

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();

private:

    int findCurrentLineNumber();

    QWidget *lineNumberArea = nullptr;

    std::vector<int> selectedLineNumbers;
    std::vector<int> selectedCharacters;
};


class CodeLineNumber : public QWidget
{
public:
    explicit CodeLineNumber(FileViewer *codeViewer);

    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;
private:

    FileViewer *codeViewer = nullptr;
};


#endif //PERFORMANCEMONITOR_FILEVIEWER_H
