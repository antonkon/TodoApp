#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    connect(ui->butOk, SIGNAL(clicked()), SLOT(accept()));
    connect(ui->butCan, SIGNAL(clicked()), SLOT(reject()));

}

Dialog::~Dialog()
{
    delete ui;
}

QString Dialog::getTitle() const {
    return this->ui->editTitle->text();
}

QString Dialog::getText() const {
    return this->ui->editText->toPlainText();
}
