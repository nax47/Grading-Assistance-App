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
#include "../DataContainers/engine.h"
#include "../DataContainers/comment.h"
#include <QVBoxLayout>
#include <QSpinBox>
#include <QGroupBox>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QCheckBox>
#include <vector>

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

    void on_studentAdd_clicked();

    void on_labAdd_clicked();

    void on_sectionAdd_clicked();

    void on_StartGrading_clicked();

    void on_sectionDrop_currentIndexChanged(const QString &arg1);

    void on_labDrop_currentIndexChanged(const QString &arg1);

    void on_studentDrop_currentIndexChanged(const QString &arg1);

    void on_commentCancel_clicked();

    void on_commentOK_clicked();

    void on_codeDisp_cursorPositionChanged();

private:
    Ui::Widget *ui;

    QString subjectQ;
    QString pointsQ;
    QString commentQ;

    Engine GUIEngine;
    string subject;
    int points;
    string comment;
    string currPathName;
    string currFileName;
    int lineNUM;

    vector <QGroupBox *> rubricItemsDisplayed;
};

#endif // WIDGET_H
