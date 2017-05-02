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
#include <QScrollBar>
#include <vector>
#include <QtPrintSupport/QPrinter>
#include <iostream>

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
    //button for searching through rubric items
    void on_searchButton_clicked();

    //button for adding new rubric item
    void on_itemButton_clicked();

    //button for adding new comment
    void on_commentButton_clicked();

    //button for opening student's code
    void on_openCodeButton_clicked();

    //button for cacnelling adding new rubric item
    void on_cancelButton_clicked();

    //button for adding new rubric item
    void on_okButton_clicked();

    //button for adding new student
    void on_studentAdd_clicked();

    //button for adding new lab
    void on_labAdd_clicked();

    //button for ading nwe section
    void on_sectionAdd_clicked();

    //button to start grading current student
    void on_StartGrading_clicked();

    //drop down menu to select section
    void on_sectionDrop_currentIndexChanged(const QString &arg1);

    //drop down menu to secelt lab
    void on_labDrop_currentIndexChanged(const QString &arg1);

    //drop down menu to select student
    void on_studentDrop_currentIndexChanged(const QString &arg1);

    //button that finishes current student
    void on_doneButton_clicked();

    //button that cancels adding new comment
    void on_commentCancel_clicked();

    //button that adds new comment
    void on_commentOK_clicked();

    //button that applies checked rubric items
    void on_applyButton_clicked();

private:
    Ui::Widget *ui; //ui for project

    //QStrings are used extensively to grab data from ui.
    //QStrings are converted to strings to use elsewhere.
    //ints for lab, section, etc. must be converted to strings for pdf output.

    QString subjectQ; //QString for new rubric item subject
    QString pointsQ; //QString for rubric item points
    QString commentQ; //QString for comment

    Engine * GUIEngine; //Engine object so the GUI can interact with ui

    string subject; //string for rubric item subject
    int points; //int for rubric item points
    string comment; //string for rubric item comment
    string fileName; //string to hold file name of code that is presently open
    QString qFileName; //QString for current file name
    string studentName; //string for the current student's name

    QString qhtml; //QString for final string that gets output to pdf
    string html; //string for final string that gets output to pdf
    int section; //int for section of current student
    string sectionString; //string for section of current student
    string labString; //string for lab of current student
    int lab; //int for lab of current student
    int score; //int for final score for assingment
    string scoreString; //string for final score for assingment
    string currPathName; //string for file path of open code file
    string currFileName; //string for file name of open code file
    int lineNUM; //int for line numbers for code
    int totalLines; //int for total number of lines in code
    vector<string> fileVec; //vector that holds strings of file names
    string currFile; //string for current code file
    string countStr; //string for number of files

    QScrollBar * codeBar; //scroll bar for code
    QScrollBar * numBar; //scroll bar for code number lines
    QScrollBar * RIBar; //scroll bar for rubric items
    QWidget * scrollWidget; //widget for scrolling
    int currSliderVal; //used in attaching code display with scroll for line number

    string subj; //string for rubric items subject
    string rubricPoints; //string for rubric item points
    int rubricPoint; //int for rubric item points
    string rubricComment; //string for rubric comment
    string rubric; //string for total rubric data
    int maxPnt; //int for max points for rubric item
    string maxPntStr; //string for max points for rubric item
    int pointsTot = 0;

    string comm; //string for comment
    int commLine; //int for line comment appears on
    string commLineString; //string for line comment appears on
    string commFile; //string for file comment is associated with
    string commTotal; //string for total comment data
    string empty = "<br>"; //string that enters blank line in output pdf

    vector <QCheckBox *> selectedBoxes; //vector that holds rubric items that are selected
    vector <QSpinBox *> pointBoxes; //vector that holds point boxes
    vector <QSpinBox *> maxPoints; //vector that holds max points
    vector <RubricItem*>::iterator rubricIter; //vector that iterates through vector of rubric items
    vector <Comment *> comments; //vector that holds comments
    vector <Comment*>::iterator commIter; //vector that iterates through vector of comments
    vector <QGroupBox *> rubricItemsDisplayed; //vector that holds all displayed rubric items
    vector <QGroupBox *>::iterator rubrDispIter; //vector that iterates through vector of displayed rubric items
};

#endif // WIDGET_H



