#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QCheckBox>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->butAdd, &QPushButton::clicked, this, &MainWindow::addTask);
    connect(ui->butChange, &QPushButton::clicked, this, &MainWindow::changeText);
    connect(ui->butDel, &QPushButton::clicked, this, &MainWindow::deleteTask);
    connect(ui->checkDue, &QCheckBox::stateChanged, this, &MainWindow::setOverdue);
    connect(ui->checkCompl, &QCheckBox::stateChanged, this, &MainWindow::setCompleted);
    connect(ui->listTask, &QListWidget::currentRowChanged, this, &MainWindow::selectItem);

    ui->listTask->clear();
    ui->listTask->setSortingEnabled(true);
    ui->listTask->addItems(this->tasks.getListTitle());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::selectItem(int row) {
    QString task_name = this->ui->listTask->item(row)->text();
    Task *task = this->tasks.getTask(task_name);
    this->ui->textAbout->setText(task->getText());
    this->ui->checkDue->setChecked(task->getOverdue());
    this->ui->checkCompl->setChecked(task->getCompleted());
}

void MainWindow::addTask() {
    qDebug() << "addTask()";
}

void MainWindow::changeText() {
    qDebug() << "changeText()";
}

void MainWindow::deleteTask() {
    qDebug() << "deleteTask()";
}

void MainWindow::setOverdue(int state) {
    qDebug() << "setOverdue() = " << state;
}

void MainWindow:: setCompleted(int state) {
    qDebug() << "setCompleted() = " << state;
}
