//
// Created by Biny Brion on 10/19/2018.
//

#ifndef PERFORMANCEMONITOR_MAINWINDOW_H
#define PERFORMANCEMONITOR_MAINWINDOW_H

#include <QtWidgets/QMainWindow>

#include "ui_mainwindow.h"
#include "CounterWriter.h"

// Represents the main window of the program

class MainWindow : public QMainWindow
{
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:

    Ui::MainWindow *ui = nullptr;
    CounterWriter counterWriter;

};


#endif //PERFORMANCEMONITOR_MAINWINDOW_H
