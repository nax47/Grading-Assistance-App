#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_itemButton_clicked()
{
    ui->subjectLine->clear();
    ui->pointsLine->clear();
    ui->commentLine->clear();
    ui->stackedWidget->setCurrentIndex(1);
}

void Widget::on_commentButton_clicked()
{

}

void Widget::on_searchButton_clicked()
{

}

void Widget::on_openCodeButton_clicked()
{
    QFile file("/home/thomas/Documents/test.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0,"info",file.errorString());
    }

    QTextStream in(&file);
    ui->codeDisp->setText(in.readAll());
}

void Widget::on_cancelButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Widget::on_okButton_clicked()
{
    subjectQ = ui->subjectLine->text();
    subject = subjectQ.toStdString();

    pointsQ = ui->pointsLine->text();
    points = pointsQ.toInt();

    commentQ = ui->commentLine->text();
    comment = commentQ.toStdString();

    if(points == NULL) {
        QMessageBox::information(this, "Warning", "Points value must be a number.");
    } else if(subject.empty() || points == NULL || comment.empty()) {
        QMessageBox::information(this, "Warning", "Please populate all fields.");
    } else {
        //RubricItem *newItem = new RubricItem();
        ui->stackedWidget->setCurrentIndex(0);
    }
}
