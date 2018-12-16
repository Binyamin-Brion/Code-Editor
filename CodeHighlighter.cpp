//
// Created by Biny Brion on 10/24/2018.
//

#include <QtCore/QRegularExpression>
#include "CodeHighlighter.h"

CodeHighlighter::CodeHighlighter(QTextDocument *parent) : QSyntaxHighlighter{parent}
{
    loadKeyWords(codeStandard);
}

void CodeHighlighter::loadKeyWords(CodeHighlighter::CodeStandard requestStandard)
{
    if(CodeStandard::C89 == requestStandard)
    {
        loadC89KeyWords();
    }
    else if(CodeStandard::C99 == requestStandard)
    {
        loadC99KeyWords();
    }
    else if(CodeStandard::Cpp98 == requestStandard)
    {
        loadCpp98KeyWords();
    }
    else if(CodeStandard::Cpp11 == requestStandard)
    {
        loadCpp11KeyWords();
    }
}

void CodeHighlighter::loadC89KeyWords()
{
    // Reference: A C Reference Manual 4th Edition. Authors: Samuel P. Harbison and Guy L. Steele Jr.

    regexPatterns.push_back("auto");
    regexPatterns.push_back("break");
    regexPatterns.push_back("case");
    regexPatterns.push_back("char");
    regexPatterns.push_back("const");
    regexPatterns.push_back("continue");
    regexPatterns.push_back("default");
    regexPatterns.push_back("do");
    regexPatterns.push_back("double");
    regexPatterns.push_back("else");
    regexPatterns.push_back("enum");
    regexPatterns.push_back("extern");
    regexPatterns.push_back("float");
    regexPatterns.push_back("for");
    regexPatterns.push_back("goto");
    regexPatterns.push_back("if");
    regexPatterns.push_back("int");
    regexPatterns.push_back("long");
    regexPatterns.push_back("register");
    regexPatterns.push_back("return");
    regexPatterns.push_back("short");
    regexPatterns.push_back("signed");
    regexPatterns.push_back("sizeof");
    regexPatterns.push_back("static");
    regexPatterns.push_back("struct");
    regexPatterns.push_back("switch");
    regexPatterns.push_back("typedef");
    regexPatterns.push_back("union");
    regexPatterns.push_back("unsigned");
    regexPatterns.push_back("void");
    regexPatterns.push_back("volatile");
    regexPatterns.push_back("while");


    addWordBoundaries();


}

void CodeHighlighter::loadC99KeyWords()
{
    // Reference: https://en.cppreference.com/w/c/keyword

    loadC89KeyWords();

    regexPatterns.push_back("inline");
    regexPatterns.push_back("restrict");
    regexPatterns.push_back("_Bool");
    regexPatterns.push_back("_Complex");
    regexPatterns.push_back("_Imaginary");

    addWordBoundaries();
}

void CodeHighlighter::loadCpp98KeyWords()
{
    // Note: Some keywords not seen often are omitted
    // Reference: https://en.cppreference.com/w/cpp/keyword

    loadC89KeyWords();

    regexPatterns.push_back("catch");
    regexPatterns.push_back("class");
    regexPatterns.push_back("const_cast");
    regexPatterns.push_back("delete");
    regexPatterns.push_back("dynamic_cast");
    regexPatterns.push_back("friend");
    regexPatterns.push_back("inline");
    regexPatterns.push_back("mutable");
    regexPatterns.push_back("namespace");
    regexPatterns.push_back("new");
    regexPatterns.push_back("operator");
    regexPatterns.push_back("private");
    regexPatterns.push_back("protected");
    regexPatterns.push_back("public");
    regexPatterns.push_back("reinterpret_cast");
    regexPatterns.push_back("template");
    regexPatterns.push_back("this");
    regexPatterns.push_back("typeid");
    regexPatterns.push_back("virtual");

    addWordBoundaries();
}

void CodeHighlighter::loadCpp11KeyWords()
{
    // Note: Some keywords not seen often are omitted
    // Reference: https://en.cppreference.com/w/cpp/keyword

    loadCpp98KeyWords();

    regexPatterns.push_back("alignas");
    regexPatterns.push_back("alingof");
    regexPatterns.push_back("char16_t");
    regexPatterns.push_back("char32_t");
    regexPatterns.push_back("constexpr");
    regexPatterns.push_back("explicit");
    regexPatterns.push_back("noexcept");
    regexPatterns.push_back("nullptr");
    regexPatterns.push_back("static_assert");
    regexPatterns.push_back("thread_local");

    addWordBoundaries();
}

void CodeHighlighter::addWordBoundaries()
{
    // Function adds the needed regex symbols for code highlighting. This function is used to keep
    // the hard-coded keywords in the loadXKeyWords functions readable.

    // Has the potential to do unnecessary copies and work but the amount of keywords are small so that is not noticeable

    // Note: \\b represented word boundaries for regex expression. Allows for search of words only.
    // Note: Double backslash (\\) needed as C++ compiler interprets \b as an escape character

    QStringList regexKeyWordPatterns;

    for(const auto &i : regexPatterns)
    {
        QString temp{i};
        temp.remove("\\b");

        QString keyword{"\\b"};

        keyword += temp;

        keyword += "\\b";

        regexKeyWordPatterns.push_back(keyword);
    }

    regexPatterns = regexKeyWordPatterns;
}

void CodeHighlighter::highlightBlock(const QString &text)
{

    // Apologies in advance for such ugly variable names

    // Additional patterns to match against- these are used to improve code readability

    QString includePattern = "^#(([a-z]*))\\s+(([A-Z]|[a-z]|_|/|\\<|\\>|\\.|\\\")+)";
    QString singleLineCommentPattern = "//(.)*";
    QString startMultiLineCommentPattern = "/\\*(.)*";
    QString middleMultiLineCommentPattern = "\\*(.)*";
    QString endMultiLineCommentPattern = "(.)*\\*/";


    if(firstTimeHighlighting)
    {
        // Add the additional patterns only once. Due to the want of reusing the patterns declared above in
        // the push_back function, this code has to go here (another option is to put the above patterns in header file)

        regexPatterns.push_back(includePattern);
        regexPatterns.push_back(singleLineCommentPattern);
        regexPatterns.push_back(startMultiLineCommentPattern);
        regexPatterns.push_back(middleMultiLineCommentPattern);
        regexPatterns.push_back(endMultiLineCommentPattern);

        firstTimeHighlighting = false;
    }

    // Flag to make sure that text following a '*' is only considered a comment if a multi-line comment was declared
    bool multiLineCommentStarted = false;

    for(const auto &i : regexPatterns)
    {
        // Attempt to find each pattern in the code

        QRegularExpression regExp{i};

        QRegularExpressionMatchIterator matchIterator = regExp.globalMatch(text);

        // Found a match

        while(matchIterator.hasNext())
        {
            QRegularExpressionMatch match = matchIterator.next();

            // Pattern matched is "#include ..."

            if(includePattern == i)
            {
                // Set "#include" part to a yellow colour

                setTextColour(match.capturedStart(), match.capturedLength(), QColor::fromRgb(200, 200, 80));

                // Find "..." part of "#inlcude ..." and highlight it as green

                for(int j = 0; j < match.capturedLength(); ++j)
                {
                    if(text[match.capturedStart() + j] == ' ')
                    {
                        setTextColour(match.capturedStart() + j, match.capturedLength() - match.capturedStart() + j, QColor::fromRgb(60, 165, 20));
                    }
                }
            }
            else if(singleLineCommentPattern == i)
            {
                setTextColour(match.capturedStart(), match.capturedLength(), QColor::fromRgb(150, 150, 150));

            }
            else if(startMultiLineCommentPattern == i)
            {
                multiLineCommentStarted = true;

                setTextColour(match.capturedStart(), match.capturedLength(), QColor::fromRgb(150, 150, 150));
            }
            else if(middleMultiLineCommentPattern == i)
            {
                if(multiLineCommentStarted)
                {
                    setTextColour(match.capturedStart(), match.capturedLength(), QColor::fromRgb(150, 150, 150));
                }
            }
            else if(endMultiLineCommentPattern == i)
            {
                setTextColour(match.capturedStart(), match.capturedLength(), QColor::fromRgb(150, 150, 150));

                multiLineCommentStarted = false;
            }
            else
            {
                // A keyword was found

                setTextColour(match.capturedStart(), match.capturedLength(), QColor::fromRgb(255, 127, 80));
            }

        }
    }
}

void CodeHighlighter::setTextColour(int startIndex, int highlightLength, QColor highlightColour)
{
    // Highlight the matched text. Small function avoid code repetition.

    QTextCharFormat newTextColour;

    newTextColour.setForeground(QBrush{highlightColour});

    setFormat(startIndex, highlightLength, newTextColour);
}
