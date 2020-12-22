#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QCheckBox>
#include <QDebug>
#include <dialog.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->butAdd, &QPushButton::clicked, this, &MainWindow::addTask);
    connect(ui->butChange, &QPushButton::clicked, this, &MainWindow::changeText);
    connect(ui->butDel, &QPushButton::clicked, this, &MainWindow::deleteTask);
    connect(ui->butExit, &QPushButton::clicked, this, &MainWindow::close);
    connect(ui->checkDue, &QCheckBox::clicked, this, &MainWindow::setOverdue);
    connect(ui->checkCompl, &QCheckBox::clicked, this, &MainWindow::setCompleted);
    connect(ui->listTask, &QListWidget::currentRowChanged, this, &MainWindow::selectItem);


    ui->listTask->setSortingEnabled(true);
    ui->listTask->addItems(this->tasks.getListTitle());
    ui->listTask->setCurrentRow(this->cur_row);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::selectItem(int row) {
    if (row < 0) return;

    this->setCurTask(row);

    this->ui->textAbout->setText(cur_task->getText());
    this->ui->checkDue->setChecked(cur_task->getOverdue());
    this->ui->checkCompl->setChecked(cur_task->getCompleted());
}

void MainWindow::addTask() {

    Dialog* dialog = new Dialog;
    if (dialog->exec() == QDialog::Accepted) {
        this->tasks.addTask(dialog->getTitle(), dialog->getText());
        ui->listTask->clear();
        ui->listTask->addItems(this->tasks.getListTitle());
    }

    delete dialog;
}

void MainWindow::changeText() {
    if (this->cur_row < 0) return;

    if (!this->edit_state) {
        this->edit_state = true;
        this->ui->textAbout->setReadOnly(false);
        this->ui->textAbout->setFocus();
        this->ui->butChange->setText("Сохранить");
        return;
    } else {
        this->edit_state = true;
        this->cur_task->changeText(this->ui->textAbout->toPlainText());
        this->ui->textAbout->setReadOnly(true);
        this->ui->butChange->setText("Редактировать");
    }
}

void MainWindow::deleteTask() {
    if (this->cur_row < 0) return;

    this->tasks.removeTask(this->cur_task->getTitle());
    this->ui->listTask->takeItem(this->cur_row);

    this->setCurTask(this->ui->listTask->currentRow());

    if (this->cur_row == -1) this->clearForm();
}

void MainWindow::setOverdue(int state) {
    if (this->cur_row < 0) return;

    this->cur_task->setOverdue(state == 0 ? false : true);
}

void MainWindow:: setCompleted(int state) {
    if (this->cur_row < 0) return;

    this->cur_task->setCompleted(state == 0 ? false : true);
}

void MainWindow::setCurTask(qint32 row) {
    this->cur_row = row;

    if (this->cur_row < 0) return;

    QString task_name = this->ui->listTask->item(this->cur_row)->text();
    this->cur_task = this->tasks.getTask(task_name);
}

void MainWindow::clearForm() {
    this->ui->listTask->clear();
    this->ui->textAbout->clear();
    this->ui->checkDue->setChecked(false);
    this->ui->checkCompl->setChecked(false);
}
