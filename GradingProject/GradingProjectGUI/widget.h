#ifndef WIDGET_H
#define WIDGET_H
#include <QFile>
#include <QTextStream>
#include <QWidget>
#include "../DataContainers/rubricitem.h"
#include <string>
#include <QStackedWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void display_code();

private slots:
    void on_searchButton_clicked();

    void on_newItem_clicked();

    void on_newComment_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
