//
// Created by Biny Brion on 10/25/2018.
//

#include <QtGui/QTextBlock>
#include <QtGui/QPainter>
#include "FileViewer.h"

FileViewer::FileViewer(QWidget *parent) : QPlainTextEdit{parent}
{
    lineNumberArea = new CodeLineNumber(this);

    connect(this, &QPlainTextEdit::blockCountChanged, [this](int newBlockCount)
    {
        setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
    });

    connect(this, &QPlainTextEdit::updateRequest, [this](const QRect &rect, int dy)
    {
        if (dy)
            lineNumberArea->scroll(0, dy);
        else
            lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

        if (rect.contains(viewport()->rect()))
            updateLineNumberAreaWidth(0);
    });

    connect(this, &QPlainTextEdit::cursorPositionChanged, [this]()
    {
        QList<QTextEdit::ExtraSelection> extraSelections;

        if (!isReadOnly()) {
            QTextEdit::ExtraSelection selection;

            QColor lineColor = QColor::fromRgb(60, 60, 60);

            selection.format.setBackground(lineColor);
            selection.format.setProperty(QTextFormat::FullWidthSelection, true);
            selection.cursor = textCursor();
            selection.cursor.clearSelection();
            extraSelections.append(selection);
        }

        setExtraSelections(extraSelections);
    });

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
}

int FileViewer::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space;
}

void FileViewer::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);


    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);

            if(std::find(selectedLineNumbers.begin(), selectedLineNumbers.end(), blockNumber + 1) != selectedLineNumbers.end())
            {
                painter.setPen(Qt::red);
            }
            else
            {
                painter.setPen(Qt::black);
            }

            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}

void FileViewer::updateLineNumberAreaWidth(int newBlockCount)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void FileViewer::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor::fromRgb(60, 60, 60);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void FileViewer::resizeEvent(QResizeEvent *event)
{
    QPlainTextEdit::resizeEvent(event);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void FileViewer::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        int currentLineNumber = findCurrentLineNumber();

        auto lineNumberLocation = std::find(selectedLineNumbers.begin(), selectedLineNumbers.end(), currentLineNumber);

        if(lineNumberLocation == selectedLineNumbers.end())
        {
            selectedLineNumbers.push_back(currentLineNumber);

            QTextCursor cur = textCursor();

            QTextBlockFormat f;
            f.setBackground(QColor::fromRgb(255, 0, 0, 25));
            cur.select(QTextCursor::LineUnderCursor);
            cur.setBlockFormat(f);
            setTextCursor(cur);
        }
    }
}

int FileViewer::findCurrentLineNumber()
{
    QTextCursor cursor = textCursor();
    cursor.movePosition(QTextCursor::StartOfLine);

    int lines = 1;

    while(cursor.positionInBlock()>0) {
        cursor.movePosition(QTextCursor::Up);
        lines++;
    }
    QTextBlock block = cursor.block().previous();

    while(block.isValid()) {
        lines += block.lineCount();
        block = block.previous();
    }

    selectedCharacters.push_back(textCursor().position());

    return lines;
}

const std::vector<int>& FileViewer::getSelectedCharacters()
{
    return selectedCharacters;
}

CodeLineNumber::CodeLineNumber(FileViewer *codeViewer) : QWidget{codeViewer}
{
    this->codeViewer = codeViewer;
}

void CodeLineNumber::paintEvent(QPaintEvent *event)
{
    codeViewer->lineNumberAreaPaintEvent(event);
}

QSize CodeLineNumber::sizeHint() const
{
    return QSize(codeViewer->lineNumberAreaWidth(), 0);
}
