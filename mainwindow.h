#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <../libtaskio/task_list.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void selectItem(int row);

    void addTask();

    void changeText();

    void deleteTask();

    void setOverdue(int state);

    void setCompleted(int state);

    void setImportance(int state);

private:
    Ui::MainWindow *ui;

    TaskList tasks;

    int cur_row = -1;
    Task *cur_task;

    bool edit_state = false;

    void clearForm();

    void setCurTask(int row);
};
#endif // MAINWINDOW_H
