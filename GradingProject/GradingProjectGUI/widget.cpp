#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    display_code();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_searchButton_clicked()
{

}

void Widget::on_newItem_clicked()
{

}

void Widget::on_newComment_clicked()
{

}

void Widget::display_code() {
    QString fileName = ("test.txt");
    QFile file(fileName);
    QString line;
    ui->codeDisp->clear();

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream stream(&file);
        while(!stream.atEnd()) {
            line = stream.readLine();
            ui->codeDisp->setText(ui->codeDisp->toPlainText()+line+"\n");
        }
    }
    file.close();
}
