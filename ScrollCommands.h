//
// Created by Biny Brion on 11/16/2018.
//

#ifndef PERFORMANCEMONITOR_SCROLLCOMMANDS_H
#define PERFORMANCEMONITOR_SCROLLCOMMANDS_H

#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>

// Class to display PDH commands and to toggle displaying the command's associated values

class ScrollCommands : public QScrollArea
{
    Q_OBJECT

public:
    explicit ScrollCommands(QWidget *parent = nullptr);

    // Required to add scroll functionality; see constructor definition for explanation
    void setCentralWidget();

    // Show PDH commands and the ability to toggle whether or not to display associated values
    void setupCommands();

signals:
    // Add the command values to the "ScrollCommandValues" class
    void setCommandValues(const std::vector<QPushButton*> commandValues);
    void showCommandValues(const std::vector<QPushButton*> commandValues);
    void hideCommandValues(const std::vector<QPushButton*> commandValues);

private:

    // Object to manage displaying the PDH commands along with a checkbox that the user cn toggle in order to show
    // the command's associated values. The formatting is as follows:
    // HBoxLayout[QLabel (to hold the PDH command name) | QCheckBox(to toggle displaying associated values)]
    struct DisplayCommand : public QWidget
    {
        explicit DisplayCommand(QWidget *parent = nullptr)
        {
            hBoxLayout = new QHBoxLayout(this);
            commandName = new QLabel(this);
            checkBox = new QCheckBox(this);

            hBoxLayout->addWidget(commandName);
            hBoxLayout->addStretch(0);
            hBoxLayout->addWidget(checkBox);
        }

        void setName(QString name)
        {
            // Set the name of the command in the QLabel
            commandName->setText(name);
            commandName->setStyleSheet("font-style: Arial; font-size: 8pt");
        }

        QHBoxLayout *hBoxLayout = nullptr;
        QLabel *commandName = nullptr;
        QCheckBox *checkBox = nullptr;
    };

    // These widgets are needed in order to make this area scrollable- see constructor

    QWidget *scrollWidget = nullptr;
    QVBoxLayout *vBoxLayout = nullptr;

    // Vector of pairs to hold the name of the PDH command, as well as push buttons that hold the name of associated
    // values that the user can press in order to copy the associated value into the system clipboard

    std::vector<std::pair<QString, std::vector<QPushButton*>>> commands;
};


#endif //PERFORMANCEMONITOR_SCROLLCOMMANDS_H
