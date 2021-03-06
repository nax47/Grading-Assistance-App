#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(2);
    //builds engine and sets up drop boxes with data base info
    GUIEngine = new Engine();
    vector <int> sec = GUIEngine->section_Drop_SetUp();
    for(int i = 0; i < sec.size(); i++)
    {
        QString t = QString::number(sec.at(i));
        ui->sectionDrop->addItem(t);
    }


    //attaches main code display window scroll bar to the line number one
    scrollWidget = new QWidget();
    currSliderVal = 0;
    codeBar = ui->codeDisp->verticalScrollBar();
    numBar = ui->linNumBox->verticalScrollBar();
    connect(codeBar, &QAbstractSlider::valueChanged, [=](int aSliderPosition){if(aSliderPosition != currSliderVal)
    {
            numBar->setValue(aSliderPosition);
            currSliderVal = aSliderPosition;
        }
    });
}

//default destuctor
Widget::~Widget()
{
    delete GUIEngine;
    delete codeBar;
    delete numBar;
    delete RIBar;
    delete scrollWidget;
    delete ui;
}

//Clears line for subject and points and
//sets ui to page for adding new rubric item.
void Widget::on_itemButton_clicked()
{
    ui->subjectLine->clear();
    ui->pointsLine->clear();
    ui->stackedWidget->setCurrentIndex(1);
}

//Adds new comment.
void Widget::on_commentButton_clicked()
{
    //Checks that code file is open. Code file must be open
    //for comment to be added as the open file is associated
    //with the comment and used later.
    if(currFileName.empty()) {
        QMessageBox::information(this, "Warning", "Please Select Code File Before Adding Comment.");
        ui->stackedWidget->setCurrentIndex(0);
    } else {
    //If code file is open, goes to page for creating new comment.
    ui->newComText->clear();
    ui->lNumNewCom->clear();
    ui->RIScombo->clear();
    for(int i = 0; i < rubricItemsDisplayed.size(); i++)
    {
        QGroupBox * temp = rubricItemsDisplayed.at(i);
        ui->RIScombo->addItem(temp->title());
    }
    ui->stackedWidget->setCurrentIndex(3);
    }
}

//Searches through rubric items. Moves it
//to the top if it present.
void Widget::on_searchButton_clicked()
{
    QString search = ui->searchBar->text();
    int gbNum = -1;
    //Iterates through list of displayed rubric items.
    for(int i=0; i<rubricItemsDisplayed.size(); i++)
    {
        QGroupBox * tmpPtr = rubricItemsDisplayed.at(i);
        //if the search text matches the subject update gbnum to the index
        if(search == tmpPtr->title())
        {
            gbNum = i;
        }
    }
    //if gbnum is still -1 no rubric item was found so nothing should be updated
    if(gbNum != -1)
    {
        //if it was found place the found item at the top of the scroll area then re write the rest
        QVBoxLayout * scrollLayout = new QVBoxLayout;
        scrollLayout->addWidget(rubricItemsDisplayed.at(gbNum));
        for(int i=0; i<rubricItemsDisplayed.size(); i++)
        {
            if(i != gbNum)
            {
                scrollLayout->addWidget(rubricItemsDisplayed.at(i));
            }
        }
        delete scrollWidget->layout();
        scrollWidget->setLayout(scrollLayout);
        ui->rubricScroll->setWidget(scrollWidget);
    }

}


//Opens code file.
void Widget::on_openCodeButton_clicked()
{
    //Total lines of code
    totalLines = 0;

    //Opens file explorer.
    QFileDialog dialog;

    //QList of string of files that are selected.
    QStringList fileNames;

    //Allows any type of file to be chosen.
    dialog.setFileMode(QFileDialog::AnyFile);
    if(dialog.exec())
    {
        fileNames = dialog.selectedFiles();
    }

    //Sets file as the first file in list
    QString FName = fileNames.at(0);

    //Converts file name to string
    string FNamestr = FName.toStdString();

    //Finds last instance of '/' character.
    int pos = FNamestr.find_last_of('/');

    //Sets name of code file
    currFileName = FNamestr.substr(pos + 1, FNamestr.length() - 1);

    //Sets file path of code file
    currPathName = FNamestr.substr(0,pos + 1);

    //Opens file and checks that it is open.
    //Error message appears if it is not open.
    QFile file(fileNames.at(0));
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0,"info",file.errorString());
    }

    //Converts file data to QTextStream and displays in code display on ui.
    QTextStream in(&file);
    QString fileData = in.readAll();
    ui->codeDisp->setText(fileData);

    //Calculates total number of lines in code file
    //and shows line numbers on side of code.
    totalLines = fileData.count('\n');
    file.close();
    QString ln = "\n";
    QString nums;
    for(int i = 0; i < totalLines*2; i++)
    {
        QString tmp = QString::number(i);
        nums = nums.append(tmp);
        nums = nums.append(ln);
    }
    ui->linNumBox->setText(nums);
}

//Cancels adding new comment and goes back
//to main scren of gui.
void Widget::on_cancelButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void Widget::on_okButton_clicked()
{
    //gets data for subject points and max points
    subjectQ = ui->subjectLine->text();
    subject = subjectQ.toStdString();

    pointsQ = ui->pointsLine->text();
    points = pointsQ.toInt();

    int max = ui->outofText->text().toInt();
    QString out;
    out = ui->outofText->text();

    if(subject.empty() || points == NULL || max == NULL) {
        QMessageBox::information(this, "Warning", "Please populate all fields. Points must be a number.");
    }else if(points > max) {
        QMessageBox::information(this, "Warning", "Max points must not be smaller than points.");
    } else {
    //assures nothing is empty
    if(points == NULL) {
        QMessageBox::information(this, "Warning", "Points value must be a number.");
    } else if(subject.empty() || points == NULL) {
        QMessageBox::information(this, "Warning", "Please populate all fields.");
    } else {
        //has the gui engine create and properly store the rubric item in the data containers
        GUIEngine->add_Rubric_Item(subject, points, max);
        //creates the holder for one rubric item
        QGroupBox * rubricItemBox = new QGroupBox (subjectQ);
        rubricItemBox->setFixedWidth(220);
        rubricItemBox->setMinimumHeight(150);
        rubricItemBox->setMaximumHeight(200);
        rubricItemBox->setStyleSheet("QGroupBox { color: rgb(255, 255, 255); font: 10pt\"DejaVu Sans\"; } ");
        //creates a layout to add all the parts of the rubric item to
        QVBoxLayout * boxLayout = new QVBoxLayout;


        QLabel * pointsLabel = new QLabel(tr("Points"));
        QHBoxLayout * pointsBoxLayout = new QHBoxLayout();
        pointsLabel->setStyleSheet("QLabel { color: rgb(255, 255, 255); font: 10pt\"DejaVu Sans\"; } ");
        pointsLabel->setFixedSize(50,20);
        pointsBoxLayout->addWidget(pointsLabel);


        QSpinBox * pointsVal = new QSpinBox();
        pointsVal->setValue(points);
        pointsVal->setStyleSheet("QSpinBox { color: rgb(255, 255, 255); font: 10pt\"DejaVu Sans\"; } ");
        pointsVal->setMaximum(out.toInt());
        pointsBoxLayout->addWidget(pointsVal);
        pointBoxes.push_back(pointsVal);

        QLabel * div = new QLabel(tr("Out of"));
        div->setStyleSheet("QLabel { color: rgb(255, 255, 255); font: 10pt\"DejaVu Sans\"; }");
        pointsBoxLayout->addWidget(div);

        QSpinBox * outof = new QSpinBox();
        outof->setValue(out.toInt());
        outof->setStyleSheet("QSpinBox { color: rgb(255, 255, 255); font: 10pt\"DejaVu Sans\"; }");
        pointsBoxLayout->addWidget(outof);
        boxLayout->addLayout(pointsBoxLayout);
        maxPoints.push_back(outof);

        QCheckBox * applyBox = new QCheckBox();
        applyBox->setStyleSheet("QCheckBox { color: rgb(255, 255, 255); font: 8pt\"DejaVu Sans\"; } ");
        applyBox->setText("Select");
        boxLayout->addWidget(applyBox);
        selectedBoxes.push_back(applyBox);

        //all rubric item peices have been creates set and placed in a layout
        //add the layout to the group box
        rubricItemBox->setLayout(boxLayout);
        rubricItemsDisplayed.push_back(rubricItemBox);



        // make the layout to hold all rubric items
        QVBoxLayout * scrollLayout = new QVBoxLayout;
        //add each item to the new layout
        for(int i=0; i<rubricItemsDisplayed.size(); i++){
            scrollLayout->addWidget(rubricItemsDisplayed.at(i));
        }
        //delete the old layout from the widget
        delete scrollWidget->layout();
        //place the new layout in the widget
        scrollWidget->setLayout(scrollLayout);
        //make the widget scrollable
        ui->rubricScroll->setWidget(scrollWidget);
        ui->stackedWidget->setCurrentIndex(0);
    }
}
}

//Adds new student to be graded.
void Widget::on_studentAdd_clicked() {

    if(GUIEngine->get_sections().size() == 0) {
        QMessageBox::information(this, "Warning", "Please Select Section.");
    } else {
        //Grabs student name from gui, converts to string,
        //and adds student to engine, and displays on gui.
        QString tmp = ui->newStudentName->text();
        GUIEngine->add_Student(tmp.toStdString());
        ui->studentDrop->addItem(tmp);
        ui->newStudentName->clear();
    }
}

//Adds new lab number.
void Widget::on_labAdd_clicked()
{
    if(GUIEngine->get_sections().size() == 0) {
        QMessageBox::information(this, "Warning", "Please Select Section.");
    } else {
        //Grabs lab number from gui, converts to int,
        //and adds to engine, and displays on gui.
        QString tmp = ui->newLabNum->text();
        int temp = tmp.toInt();
        GUIEngine->add_Lab(temp);
        ui->labDrop->addItem(tmp);
        ui->newLabNum->clear();
    }
}

//Adds new section.
void Widget::on_sectionAdd_clicked()
{
    if(ui->newIDVal->text() == "") {
        QMessageBox::information(this, "Warning", "Please Input Section.");
    } else {
    //Grabs section number from gui, converts to int,
    //adds to engine, and displays on gui.
    QString tmp = ui->newIDVal->text();
    GUIEngine->add_Section(tmp.toInt());
    ui->sectionDrop->addItem(tmp);
    ui->newIDVal->clear();
    }
}

//Begins grading current student.
void Widget::on_StartGrading_clicked()
{
    pointsTot = 0;
    //Checks that a student, section, and lab have been chosen.
    //If one or more have been let blank, error message is displayed.
    if(GUIEngine->get_currStu() == nullptr) {
        QMessageBox::information(this, "Warning", "Please Select Student.");
    } else if(GUIEngine->get_currL() == nullptr) {
        QMessageBox::information(this, "Warning", "Please Select Lab");
    } else if(GUIEngine->get_currSec() == nullptr) {
        QMessageBox::information(this, "Warning", "Please Select Section.");
    } else {
        //Checks if rubric item is checked.
        if(ui->loadRub->isChecked())
        {
            // gets the rubric items from the previous lab
            vector <RubricItem *> prevTemplate = GUIEngine->get_currL()->get_Template()->getItems();
            //creates the rubric items and adds them tp the gui like in on_okButton_clicked()
            for(int i = 0; i < prevTemplate.size(); i++)
            {
                RubricItem * tmpPtr = prevTemplate.at(i);
                QGroupBox * rubricItemBox = new QGroupBox (QString::fromStdString(tmpPtr->get_Subject()));
                rubricItemBox->setFixedWidth(220);
                rubricItemBox->setMinimumHeight(150);
                rubricItemBox->setMaximumHeight(200);
                rubricItemBox->setStyleSheet("QGroupBox { color: rgb(255, 255, 255); font: 10pt\"DejaVu Sans\"; } ");

                QVBoxLayout * boxLayout = new QVBoxLayout;

                QLabel * pointsLabel = new QLabel(tr("Points"));
                QHBoxLayout * pointsBoxLayout = new QHBoxLayout();
                pointsLabel->setStyleSheet("QLabel { color: rgb(255, 255, 255); font: 10pt\"DejaVu Sans\"; } ");
                pointsLabel->setFixedSize(50,20);
                pointsBoxLayout->addWidget(pointsLabel);


                QSpinBox * pointsVal = new QSpinBox();
                pointsVal->setValue(tmpPtr->get_Points());
                pointsVal->setStyleSheet("QSpinBox { color: rgb(255, 255, 255); font: 10pt\"DejaVu Sans\"; } ");
                pointsVal->setMaximum(tmpPtr->get_maxP());
                pointsBoxLayout->addWidget(pointsVal);
                pointBoxes.push_back(pointsVal);

                QLabel * div = new QLabel(tr("Out of"));
                div->setStyleSheet("QLabel { color: rgb(255, 255, 255); font: 10pt\"DejaVu Sans\"; }");
                pointsBoxLayout->addWidget(div);

                QSpinBox * outof = new QSpinBox();
                outof->setValue(tmpPtr->get_maxP());
                outof->setStyleSheet("QSpinBox { color: rgb(255, 255, 255); font: 10pt\"DejaVu Sans\"; }");
                pointsBoxLayout->addWidget(outof);
                boxLayout->addLayout(pointsBoxLayout);
                maxPoints.push_back(outof);

                QCheckBox * applyBox = new QCheckBox();

                applyBox->setStyleSheet("QCheckBox { color: rgb(255, 255, 255); font: 8pt\"DejaVu Sans\"; } ");
                applyBox->setText("Select");
                boxLayout->addWidget(applyBox);
                selectedBoxes.push_back(applyBox);


                rubricItemBox->setLayout(boxLayout);
                rubricItemsDisplayed.push_back(rubricItemBox);




                QVBoxLayout * scrollLayout = new QVBoxLayout;
                for(int i=0; i<rubricItemsDisplayed.size(); i++){
                    scrollLayout->addWidget(rubricItemsDisplayed.at(i));
                }
                delete scrollWidget->layout();
                scrollWidget->setLayout(scrollLayout);
                ui->rubricScroll->setWidget(scrollWidget);

            }

        }
        //updates data containers if load last rubric is checked
        GUIEngine->start_Grading(ui->loadRub->isChecked());
        //displays student name lab number and grade in the top right label
        string studentName = GUIEngine->get_currStu()->get_Name();
        QString name = QString::fromStdString(studentName);
        int t = GUIEngine->get_currL()->get_labNum();
        QString lab = " Lab #: ";
        QString labnum = QString::number(t);
        lab = lab.append(labnum);
        name = name.append(lab);
        int g = GUIEngine->get_currLA()->get_Grade();
        QString outOf = " / ";
        QString grade = " Grade: ";
        QString tem = QString::number(g);
        grade = grade.append(tem);
        grade = grade.append(outOf);
        QString final = name.append(grade);
        ui->studentgrade->setText(final);
        ui->stackedWidget->setCurrentIndex(0);


    }
}

void Widget::on_sectionDrop_currentIndexChanged(const QString &arg1)
{
    //updates current section to the new selection
    GUIEngine->set_currSection(arg1.toInt());

    ui->labDrop->clear();
    ui->studentDrop->clear();
    //gets all labnumbrs for the new section
    vector <int> temp = GUIEngine->labNum_Drop_SetUp();
    //places each lab number into the cleared lab number combo box
    for(int i = 0; i < temp.size(); i++)
    {
        QString t = QString::number(temp.at(i));
        ui->labDrop->addItem(t);
    }
    //gets all student names for the new section
    vector <string> t2 = GUIEngine->student_Drop_SetUp();
    //displays all students in the combo box
    for(int i = 0; i < t2.size(); i++)
    {
        QString t = QString::fromStdString(t2.at(i));
        ui->studentDrop->addItem(t);
    }
}
//updates currLab when the gui combo box is changed
void Widget::on_labDrop_currentIndexChanged(const QString &arg1)
{
    if(!arg1.isEmpty() && !arg1.isNull())
    {
        GUIEngine->set_currLab(arg1.toInt());
    }
}
//updates curr student when gui combo box is changed
void Widget::on_studentDrop_currentIndexChanged(const QString &arg1)
{
    GUIEngine->set_currStudent(arg1.toStdString());
}

//Chosen when grader is done grading all of current student's code.
//HTML is used to output to pdf.
//<h1> denotes header  1, <h2> denoted header 2, etc.
//</h1> denotes end of header one, etc.
//Added to beginning and end of string to print to pdf.
//All ints converted to string and all strings converted to QString.
//Deletes pointers for current student so next student can be graded.
void Widget::on_doneButton_clicked()
{
    //Initializes vector for holding rubric items.
    //Gets current student, current section, and current lab.
    vector <RubricItem *> rubricItems;
    rubricItems = GUIEngine->get_currLA()->get_rubricItems();
    Student *currStudent = GUIEngine->get_currStu();
    Section *currSection = GUIEngine->get_currSec();
    Lab *currLab = GUIEngine->get_currL();

    //Sets studentName, file name as current student by going through engine.
    //Converts file name to QString to output to pdf.
    studentName = GUIEngine->get_currLA()->get_Student()->get_Name();
    string fileLab = "_L" + to_string(GUIEngine->get_currL()->get_labNum());
    fileName = currPathName + studentName + fileLab +".pdf";
    qFileName = QString::fromStdString(fileName);

    //Sets student name.
    studentName = "<h1>" + studentName + "</h1>";

    //Sets current section.
    section = currSection->get_Id();
    sectionString = to_string(section);
    sectionString = "<h2> Section: " + sectionString + "</h2>";

    //Sets current lab.
    lab = currLab->get_labNum();
    labString = to_string(lab);
    labString = "<h2> Lab Number: " + labString + "</h2>";

    //Gets current lab assingment to set final score.
    LabAssignment *currLabAssignment = currStudent->get_Lab(lab - 1);
    score = currLabAssignment->get_Grade();
    scoreString = to_string(score);
    scoreString = "<h3> Final Grade: " + scoreString + " / " + to_string(pointsTot) + "</h3>";

    //Combines student name, section, lab, and grade to one string.
    html = studentName + sectionString + labString + scoreString;

    //Iterates through vector of rubic items.
    //Nested loops to get all comments associated with each rubric item.
    //Gets applied rubric items and comments to print to pdf.
    for(rubricIter = rubricItems.begin(); rubricIter != rubricItems.end(); rubricIter++) {
        RubricItem *currItem = *rubricIter;
        //Checks if current rubric item was applied.
        if(currItem->get_Applied()) {

            //Sets subject of rubric item.
            subj = currItem->get_Subject();
            subj = "<h2>" + subj + "</h2>";

            //Sets current points.
            rubricPoint = currItem->get_Points();
            maxPnt = currItem->get_maxP();
            rubricPoints = to_string(rubricPoint);
            maxPntStr = to_string(maxPnt);
            rubricPoints = "<h3> Points: " + rubricPoints + " out of " + maxPntStr + "</h3>";

            //Gets comments associated with current rubric item.
            comments = currItem->get_comments();
            string commentStart = "<h3> Comments:  </h3>";
            //Combines rubric item with subject and points.
            rubric = rubric + empty + subj + rubricPoints + commentStart;

            //Iterates through vector of comments.
            for(commIter = comments.begin(); commIter != comments.end(); commIter++) {
                Comment *currComm = *commIter;

                    //Sets comment.
                    comm = currComm->get_Comment();
                    comm = "<h3>" + comm + "</h3>";

                    //Sets line of code comment is to be applied to.
                    commLine = currComm->get_line();
                    commLineString = to_string(commLine);
                    commLineString = "<h3> Line Number: " + commLineString + "</h3>";

                    //Sets file that comment is associated with.
                    commFile = currComm->get_fileName();
                    commFile = "<h3> File: " + commFile + "</h3>";

                    //Combines rubric, file, comment line, and comment.
                    rubric = rubric + commFile + commLineString + comm + empty;
            }
        }
    }

    //Sets final output string and converts to QString.
    html = html + rubric;
    qhtml = QString::fromStdString(html);

    //Code for printing to pdf document.
    QTextDocument doc;
    doc.setHtml(qhtml);
    QPrinter printer;
    printer.setOutputFileName(qFileName);
    printer.setOutputFormat(QPrinter::PdfFormat);
    doc.print(&printer);
    printer.newPage();

    //Clears the code display
    ui->codeDisp->clear();
    ui->linNumBox->clear();

    //Iterates through vector of displayed rubric items and deletes.
    for(rubrDispIter = rubricItemsDisplayed.begin(); rubrDispIter != rubricItemsDisplayed.end(); rubrDispIter++) {
        QGroupBox *currQBox = *rubrDispIter;
        delete currQBox;
    }

    //Iterates through vector of rubric items and deletes each.
    for(rubricIter = rubricItems.begin(); rubricIter != rubricItems.end(); rubricIter++) {
        RubricItem *currItem = *rubricIter;
        delete currItem;
    }

    //Clears vector of displayed rubric items.
    rubricItemsDisplayed.clear();

    //Clears vector of selected boxes.
    selectedBoxes.clear();

    //Clears vectors of point boxes, maxpoints, rubric items.
    pointBoxes.clear();
    maxPoints.clear();
    rubricItems.clear();

    //Clears strings of comments, curr file name, html output, qhtml, and rubric.
    comments.clear();
    currFileName.clear();
    html.clear();
    qhtml.clear();
    rubric.clear();

    //Sets gui back to main screen to add new student.
    ui->stackedWidget->setCurrentIndex(2);
}

//Cancels adding new comment.
void Widget::on_commentCancel_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void Widget::on_commentOK_clicked()
{
    //gets all text box inputs
    string in = ui->newComText->text().toStdString();
    int in2 = ui->lNumNewCom->text().toInt();
    //creates a new comment
    if(in == "" || in2 == NULL) {
        QMessageBox::information(this, "Warning", "Please populate all fields.");
    } else {
        Comment * com = GUIEngine->add_Comment(in, in2, currFileName);
        //adds it to the correct rubric item in the curr lab assignment
        GUIEngine->get_currLA()->get_RI(ui->RIScombo->currentText().toStdString())->add_Comment(com);
        QString sub = ui->RIScombo->currentText();
        int gbNum = -1;
        //finds the proper rubric item Group box and adds the new label with comment to it
        for(int i=0; i<rubricItemsDisplayed.size(); i++)
        {
            QGroupBox * tmpPtr = rubricItemsDisplayed.at(i);
            if(sub == tmpPtr->title())
            {
                gbNum = i;
            }
        }
        if(gbNum == -1)
        {
            QMessageBox::information(this, "Warning", "Please enter a valid rubric item subject");
        }
        else
        {
            QLabel * newComment = new QLabel(ui->newComText->text());
            newComment->setStyleSheet("QLabel { background-color: rgb(255, 255, 255); font: 8pt\"DejaVu Sans\"; } ");
            newComment->setMinimumHeight(20);
            QGroupBox * tmpPtr = rubricItemsDisplayed.at(gbNum);
            tmpPtr->layout()->addWidget(newComment);
            tmpPtr->resize(220, tmpPtr->height() + 20);

            QVBoxLayout * scrollLayout = new QVBoxLayout;
            for(int i=0; i<rubricItemsDisplayed.size(); i++){
                scrollLayout->addWidget(rubricItemsDisplayed.at(i));
            }
            delete scrollWidget->layout();
            scrollWidget->setLayout(scrollLayout);
            ui->rubricScroll->setWidget(scrollWidget);
        }
        ui->stackedWidget->setCurrentIndex(0);
    }
}


void Widget::on_applyButton_clicked()
{
    QGroupBox * tmpPtr;
    QCheckBox * selected;
    QSpinBox * pointPTR;
    QSpinBox * mpointPTR;

    int pointsGot = 0;

    if(currFileName.empty()) {
        QMessageBox::information(this, "Warning", "Please Select Code File Before Adding Comment.");
    } else {
        //loops through all rubric item group boxes
        for(int i=0; i<rubricItemsDisplayed.size(); i++)
        {
            // gets temp pointes for the groupBox spin wheels and check box
            tmpPtr = rubricItemsDisplayed.at(i);
            selected = selectedBoxes.at(i);
            pointPTR = pointBoxes.at(i);
            mpointPTR = maxPoints.at(i);
            //if the selected box is checked and it has not been applied already
            if(selected->isChecked() && !(GUIEngine->get_currLA()->get_RI(tmpPtr->title().toStdString())->get_Applied()))
            {
                //sets the rubric item to applied
                GUIEngine->get_currLA()->get_RI(tmpPtr->title().toStdString())->set_Applied(true);
                //updates points in the lab assignment to what is in the spin boxes
                GUIEngine->get_currLA()->get_RI(tmpPtr->title().toStdString())->set_Points(pointPTR->value());
                GUIEngine->get_currLA()->get_RI(tmpPtr->title().toStdString())->set_maxP(mpointPTR->value());
                // tallys the proper amout of points to be deducted
                pointsTot = pointsTot +  mpointPTR->value();

                // sets the lab assignment grade to the new grade
                GUIEngine->get_currLA()->set_Grade(GUIEngine->get_currLA()->get_Grade() + pointPTR->value());

                //updates the main window with the new grade
                string studentName = GUIEngine->get_currStu()->get_Name();
                QString name = QString::fromStdString(studentName);
                int t = GUIEngine->get_currL()->get_labNum();
                QString lab = " Lab #: ";
                QString labnum = QString::number(t);
                lab = lab.append(labnum);
                name = name.append(lab);
                int g = GUIEngine->get_currLA()->get_Grade();
                QString grade = " Grade: ";
                QString tem = QString::number(g);
                QString outof = " / ";
                grade = grade.append(tem);
                grade = grade.append(outof);
                QString m = QString::number(pointsTot);
                grade = grade.append(m);
                QString final = name.append(grade);
                ui->studentgrade->setText(final);
            }
        }
    }

}

