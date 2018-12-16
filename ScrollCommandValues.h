//
// Created by Biny Brion on 11/16/2018.
//

#ifndef PERFORMANCEMONITOR_SCROLLCOMMANDVALUES_H
#define PERFORMANCEMONITOR_SCROLLCOMMANDVALUES_H


#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>

// Class to display PDH command values in the form of push buttons (class is closely related to "ScrollCommands"

class ScrollCommandValues : public QScrollArea
{
    Q_OBJECT

public:
    explicit ScrollCommandValues(QWidget *parent = nullptr);

    // Required to add scroll functionality; see constructor definition for explanation
    void setCentralWidget();

public slots:
    // Receive all items that can be displayed for a PDH command so to eliminate having to add and remove push buttons
    // every time a PDH command is selected
    void setItems(const std::vector<QPushButton*> &labels);
    void showItems(const std::vector<QPushButton*> &labels);
    void hideItems(const std::vector<QPushButton*> &labels);

private:

    // These widgets are needed in order to make this area scrollable- see constructor

    QWidget *scrollWidget = nullptr;
    QVBoxLayout *vBoxLayout = nullptr;
};


#endif //PERFORMANCEMONITOR_SCROLLCOMMANDVALUES_H
