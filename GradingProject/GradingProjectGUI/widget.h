#ifndef WIDGET_H
#define WIDGET_H
#include <QFile>
#include <QTextStream>
#include <QWidget>
#include "../DataContainers/rubricitem.h"
#include <string>
#include <QStackedWidget>
#include <QMessageBox>
#include <iostream>
#include "../DataContainers/rubricitem.h"
#include "../DataContainers/comment.h"
#include <QVBoxLayout>
#include <QSpinBox>
#include <QGroupBox>

class RubricItem;
class Comment;

using namespace std;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_searchButton_clicked();

    void on_itemButton_clicked();

    void on_commentButton_clicked();

    void on_openCodeButton_clicked();

    void on_cancelButton_clicked();

    void on_okButton_clicked();

private:
    Ui::Widget *ui;

    QString subjectQ;
    QString pointsQ;
    QString commentQ;

    string subject;
    int points;
    string comment;
};

#endif // WIDGET_H
