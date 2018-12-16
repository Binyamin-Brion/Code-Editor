//
// Created by Biny Brion on 10/24/2018.
//

#ifndef PERFORMANCEMONITOR_CODEHIGHLIGHTER_H
#define PERFORMANCEMONITOR_CODEHIGHLIGHTER_H


#include <QtGui/QSyntaxHighlighter>
#include <QtWidgets/QPlainTextEdit>

// Highlights keyword in a code file

class CodeHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:

    explicit CodeHighlighter(QTextDocument *parent = nullptr);

protected:
    void highlightBlock(const QString &text) override;

private:

    void setTextColour(int startIndex, int highlightLength, QColor highlightColour);

    enum CodeStandard
    {
        C89,
        C99,
        Cpp98,
        Cpp11
    };

    // Default code standard is C++11
    CodeStandard codeStandard = CodeStandard::Cpp11;

    void loadKeyWords(CodeStandard requestStandard);
    void loadC89KeyWords();
    void loadC99KeyWords();
    void loadCpp98KeyWords();
    void loadCpp11KeyWords();

    // Adds \\b to the keyword patterns- see definition for why
    void addWordBoundaries();

    // Control to make sure additional patterns (in highlightBlock()) are only added once
    bool firstTimeHighlighting = true;

    // Hold all the patterns that need to be matched against
    QStringList regexPatterns;
};


#endif //PERFORMANCEMONITOR_CODEHIGHLIGHTER_H
