//
// Created by Biny Brion on 11/16/2018.
//

#include "ScrollCommands.h"

#include <fstream>
#include <QApplication>
#include <QClipboard>

ScrollCommands::ScrollCommands(QWidget *parent) : QScrollArea{parent}
{
    setWidgetResizable(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn );

    /*
     *  In order to make this area scrollable, a widget needs to be set as the central widget of this class (hence scrollWidget)
     *  Before this is done, the widget to be set as the central widget needs to have a layout attached (hence vBoxLayout). Layout has to be set
     *  in the soon to be central widget before it is actually set as the central widget.
     *
     *  **Note**: The scrollWidget is set as the central widget in a separate function called later from the mainwindow constructor; if this is
     *            not done, the program crashes. Unclear why this happens. Will be mentioned below as this is important.
     */

    scrollWidget = new QWidget();
    vBoxLayout = new QVBoxLayout();

    scrollWidget->setLayout(vBoxLayout);

    // Open and read the text file containing the list of Pdh Functions and special constants for use with each function

    std::ifstream commandReader{"commands.txt"};

    if(!commandReader.is_open())
    {
        throw std::runtime_error{"Unable to find the list of commands!"};
    }

    std::string currentLine;

    // Variable to determine if the current line contains the PDH function name
    bool readingCommandValues = false;

    // I know the logic in the following loop is weird, but it works

    while(std::getline(commandReader, currentLine))
    {
        // If a "COMMAND" word is found in the current line, set the readingCommandValues variable to false so that
        // the command name that is about to be read does not get added as a command value in the next if
        // statement, which is dependent on readingCommandValues

        if(currentLine.find("COMMAND") != std::string::npos)
        {
            readingCommandValues = false;
        }

        // If a "COMMAND" word was found on the previous line, then it is time to add subsequent read lines as a
        // command value. Values are added to command values until the next line with the "COMMAND" is read.

        if(readingCommandValues)
        {
            if("VALUES" != currentLine && !currentLine.empty())
            {
                // A push button for the command value, and when it is pressed copy the command value to the clipboard

                QPushButton *commandLabel = new QPushButton;

                connect(commandLabel, &QPushButton::clicked, [commandLabel]()
                {
                    QApplication::clipboard()->setText(commandLabel->text());
                });

                // Set the pushbutton text to the command value

                commandLabel->setText("    " + QString::fromStdString(currentLine));

                commandLabel->setStyleSheet("font-style: Arial; font-size: 8pt");

                commands.back().second.push_back(commandLabel);
            }

        }

        // If the line contains the "COMMAND" value, add a tuple associated with the command name that will hold
        // the command's special values using push buttons, which will be read in subsequent lines

        if(currentLine.find("COMMAND") != std::string::npos)
        {
            QString qCurrentLine = QString::fromStdString(currentLine);

            std::pair<QString, std::vector<QPushButton*>> commandPair{qCurrentLine.split(": ")[1], std::vector<QPushButton*>{}};

            commands.push_back(commandPair);

            // Make sure that the next lines will be interpreted as command values
            readingCommandValues = true;
        }

        // Set clean state for next loop iteration

        currentLine.clear();
    }
}

void ScrollCommands::setCentralWidget()
{
    // Set the central widget as that of the scroll widget- reason for having a separate function discussed above in the constructor
    setWidget(scrollWidget);
}

void ScrollCommands::setupCommands()
{
    // Iterate through the commands, and for each one show it as a label displaying the command name, an beside it
    // a checkbox to show the command's special values

    for(const auto &i : commands)
    {
        DisplayCommand *command = new DisplayCommand(scrollWidget);

        // Set the DisplayCommand's label to the name of the command
        command->setName(i.first);

        vBoxLayout->addWidget(command);

        // Tie the lifetime of the push-buttons to that of the appropriate DisplayCommand. Since the lifetime of the push-buttons
        // are static (duration of entire lifetime), this is not necessary to specify but helps with clarity
        for(auto &j : i.second)
        {
            j->setParent(command);
        }

        // Add the command's special values to the scroll area designed to show them. They are added right now
        // so that they do not have to be added later
        emit setCommandValues(i.second);

        // If the command's checkbox is checked, show its special values; otherwise hide them
        connect(command->checkBox, &QCheckBox::stateChanged, [this, &i, command](int state)
        {
            if(Qt::Checked == state)
            {
                // Copy the PDH command name to clipboard so that it can be pasted into text
                QApplication::clipboard()->setText(command->commandName->text());

                emit showCommandValues(i.second);
            }
            else
            {
                emit hideCommandValues(i.second);
            }
        });
    }
}
