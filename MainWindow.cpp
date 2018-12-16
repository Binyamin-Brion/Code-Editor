//
// Created by Biny Brion on 10/19/2018.
//

#include <QtWidgets/QMessageBox>
#include <QFileDialog>
#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow{parent}, ui{new Ui::MainWindow}
{
    setWindowTitle("Code Editor");

    ui->setupUi(this);

    // Setup connections for loading and viewing files

    connect(ui->treeWidget, SIGNAL(readFile(QString)), ui->tabWidget, SLOT(loadCodeFile(QString)));

    connect(ui->treeWidget, SIGNAL(showFile(QString)), ui->tabWidget, SLOT(showCodeFile(QString)));

    connect(ui->treeWidget, SIGNAL(hideFile(QString)), ui->tabWidget, SLOT(hideCodeFile(QString)));

    // Load requested files into the specified location

    connect(ui->actionNew_Project_2, &QAction::triggered, [this]()
    {
        QString projectLocation = QFileDialog::getExistingDirectory(this, tr("Select Project Location"), "C:/", QFileDialog::ShowDirsOnly | QFileDialog::DontUseNativeDialog);

        QString newSaveLocation = QFileDialog::getExistingDirectory(this, tr("Select Location To Save To"), "C:/", QFileDialog::ShowDirsOnly | QFileDialog::DontUseNativeDialog);

        ui->treeWidget->loadProject(projectLocation, newSaveLocation);
    });

    connect(ui->actionOpen_Project_2, &QAction::triggered, [this]()
    {
        QString projectLocation = QFileDialog::getExistingDirectory(this, tr("Select Location To Save To"), "C:/", QFileDialog::ShowDirsOnly | QFileDialog::DontUseNativeDialog);

        ui->treeWidget->loadProject(projectLocation, projectLocation);
    });

    // Reason for these calls explained in their respective classes

    ui->scrollArea->setCentralWidget();

    ui->scrollArea_3->setCentralWidget();

    ui->scrollArea_2->setCentralWidget();

    // Allow the combox box to control content of scroll area showing counters

    ui->comboBox->setScrollAreaPtr(ui->scrollArea);

    ui->comboBox->loadCounters();

    // Necessary connections to control when related counter information should be displayed

    connect(ui->scrollArea_3, SIGNAL(setCommandValues(const std::vector<QPushButton*>)), ui->scrollArea_2, SLOT(setItems(const std::vector<QPushButton*>)));

    connect(ui->scrollArea_3, SIGNAL(showCommandValues(const std::vector<QPushButton*>)), ui->scrollArea_2, SLOT(showItems(const std::vector<QPushButton*>)));

    connect(ui->scrollArea_3, SIGNAL(hideCommandValues(const std::vector<QPushButton*>)), ui->scrollArea_2, SLOT(hideItems(const std::vector<QPushButton*>)));

    // Load necessary content

    ui->scrollArea_3->setupCommands();

    connect(ui->actionSave_2, &QAction::triggered, [this]()
    {
        ui->tabWidget->writeChanges(ui->treeWidget->getSaveLocation());
    });
}


