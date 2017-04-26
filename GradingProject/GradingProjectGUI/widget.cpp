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

Widget::~Widget()
{
    delete ui;
}

void Widget::on_itemButton_clicked()
{
    ui->subjectLine->clear();
    ui->pointsLine->clear();
    ui->stackedWidget->setCurrentIndex(1);
}

void Widget::on_commentButton_clicked()
{
    if(currFileName.empty()) {
        QMessageBox::information(this, "Warning", "Please Select Code File Before Adding Comment.");
        ui->stackedWidget->setCurrentIndex(0);
    } else {
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

void Widget::on_searchButton_clicked()
{
    QString search = ui->searchBar->text();
    int gbNum = -1;
    for(int i=0; i<rubricItemsDisplayed.size(); i++)
    {
        QGroupBox * tmpPtr = rubricItemsDisplayed.at(i);
        if(search == tmpPtr->title())
        {
            gbNum = i;
        }
    }
    if(gbNum != -1)
    {
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

void Widget::on_openCodeButton_clicked()
{
    totalLines = 0;
    QFileDialog dialog;
    QStringList fileNames;

    dialog.setFileMode(QFileDialog::AnyFile);
    if(dialog.exec())
    {
        fileNames = dialog.selectedFiles();
    }
    QString FName = fileNames.at(0);
    string FNamestr = FName.toStdString();
    int pos = FNamestr.find_last_of('/');
    currFileName = FNamestr.substr(pos + 1, FNamestr.length() - 1);
    currPathName = FNamestr.substr(0,pos + 1);
    fileVec.push_back(currFileName);

    QFile file(fileNames.at(0));
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0,"info",file.errorString());
    }

    QTextStream in(&file);
    QString fileData = in.readAll();
    ui->codeDisp->setText(fileData);

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

    QString out;
    out = ui->outofText->text();

    if(points == NULL) {
        QMessageBox::information(this, "Warning", "Points value must be a number.");
    } else if(subject.empty() || points == NULL) {
        QMessageBox::information(this, "Warning", "Please populate all fields.");
    } else {

        GUIEngine->add_Rubric_Item(subject, points);

        QGroupBox * rubricItemBox = new QGroupBox (subjectQ);
        rubricItemBox->setFixedWidth(220);
        rubricItemBox->setMinimumHeight(150);
        rubricItemBox->setStyleSheet("QGroupBox { color: rgb(255, 255, 255); font: 10pt\"DejaVu Sans\"; } ");

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


        rubricItemBox->setLayout(boxLayout);
        rubricItemsDisplayed.push_back(rubricItemBox);




        QVBoxLayout * scrollLayout = new QVBoxLayout;
        for(int i=0; i<rubricItemsDisplayed.size(); i++){
            scrollLayout->addWidget(rubricItemsDisplayed.at(i));
        }
        delete scrollWidget->layout();
//        delete scrollWidget;
//        scrollWidget = new QWidget();
        scrollWidget->setLayout(scrollLayout);
        ui->rubricScroll->setWidget(scrollWidget);
        ui->stackedWidget->setCurrentIndex(0);
    }
}


void Widget::on_studentAdd_clicked()
{
    QString tmp = ui->newStudentName->text();
    GUIEngine->add_Student(tmp.toStdString());
    ui->studentDrop->addItem(tmp);
    ui->newStudentName->clear();
}

void Widget::on_labAdd_clicked()
{
    QString tmp = ui->newLabNum->text();
    int temp = tmp.toInt();
    GUIEngine->add_Lab(temp);
    ui->labDrop->addItem(tmp);
    ui->newLabNum->clear();
}

void Widget::on_sectionAdd_clicked()
{
    QString tmp = ui->newIDVal->text();
    GUIEngine->add_Section(tmp.toInt());
    ui->sectionDrop->addItem(tmp);
    ui->newIDVal->clear();
}

void Widget::on_StartGrading_clicked()
{
    if(GUIEngine->get_currStu() == nullptr) {
        QMessageBox::information(this, "Warning", "Please Select Student.");
    } else if(GUIEngine->get_currL() == nullptr) {
        QMessageBox::information(this, "Warning", "Please Select Lab");
    } else if(GUIEngine->get_currSec() == nullptr) {
        QMessageBox::information(this, "Warning", "Please Select Section.");
    } else {
        GUIEngine->start_Grading();
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
        grade = grade.append(tem);
        QString final = name.append(grade);
        ui->studentgrade->setText(final);
        ui->stackedWidget->setCurrentIndex(0);

    }
}

void Widget::on_sectionDrop_currentIndexChanged(const QString &arg1)
{
    GUIEngine->set_currSection(arg1.toInt());

    ui->labDrop->clear();
    ui->studentDrop->clear();
    vector <int> temp = GUIEngine->labNum_Drop_SetUp();
    for(int i = 0; i < temp.size(); i++)
    {
        QString t = QString::number(temp.at(i));
        ui->labDrop->addItem(t);
    }
    string five = "5";
    vector <string> t2 = GUIEngine->student_Drop_SetUp();
    for(int i = 0; i < t2.size(); i++)
    {
        QString t = QString::fromStdString(t2.at(i));
        ui->studentDrop->addItem(t);
    }
}

void Widget::on_labDrop_currentIndexChanged(const QString &arg1)
{
    if(!arg1.isEmpty() && !arg1.isNull())
    {
        GUIEngine->set_currLab(arg1.toInt());
    }
}

void Widget::on_studentDrop_currentIndexChanged(const QString &arg1)
{
    GUIEngine->set_currStudent(arg1.toStdString());
}

void Widget::on_doneButton_clicked()
{
    vector <RubricItem *> rubricItems;
    //rubricItems.clear();
    rubricItems = GUIEngine->get_currLA()->get_rubricItems();
    cout << comments.size() << endl;
    cout << rubricItems.size() << endl;
    Student *currStudent = GUIEngine->get_currStu();
    Section *currSection = GUIEngine->get_currSec();
    Lab *currLab = GUIEngine->get_currL();

    //studentName = currStudent->get_Name();
    studentName = GUIEngine->get_currLA()->get_Student()->get_Name();
    fileName = currPathName + studentName +".pdf";
    qFileName = QString::fromStdString(fileName);

    studentName = "<h1>" + studentName + "</h1>";
    section = currSection->get_Id();
    sectionString = to_string(section);
    sectionString = "<h2> Section: " + sectionString + "</h2>";

    lab = currLab->get_labNum();
    labString = to_string(lab);
    labString = "<h2> Lab Number: " + labString + "</h2>";

    LabAssignment *currLabAssignment = currStudent->get_Lab(lab - 1);
    score = currLabAssignment->get_Grade();
    scoreString = to_string(score);
    scoreString = "<h3> Final Grade: " + scoreString + "</h3>";

    html = studentName + sectionString + labString + scoreString;

    for(rubricIter = rubricItems.begin(); rubricIter != rubricItems.end(); rubricIter++) {
        RubricItem *currItem = *rubricIter;
        if(currItem->get_Applied()) {
            subj = currItem->get_Subject();
            subj = "<h2>" + subj + "</h2>";

            rubricPoint = currItem->get_Points();
            maxPnt = currItem->get_maxP();
            rubricPoints = to_string(rubricPoint);
            maxPntStr = to_string(maxPnt);
            rubricPoints = "<h3> Points: " + rubricPoints + " out of " + maxPntStr + "</h3>";

            comments = currItem->get_comments();
            rubric = rubric + empty + subj + rubricPoints;

            for(commIter = comments.begin(); commIter != comments.end(); commIter++) {
                Comment *currComm = *commIter;
                    comm = currComm->get_Comment();
                    comm = "<h3>" + comm + "</h3>";

                    commLine = currComm->get_line();
                    commLineString = to_string(commLine);
                    commLineString = "<h3> Line Number: " + commLineString + "</h3>";

                    commFile = currComm->get_fileName();
                    commFile = "<h3> File: " + commFile + "</h3>";

                    rubric = rubric + commFile + commLineString + comm + empty;
            }
        }
    }

    html = html + rubric;
    qhtml = QString::fromStdString(html);

    QTextDocument doc;
    doc.setHtml(qhtml);
    QPrinter printer;
    printer.setOutputFileName(qFileName);
    printer.setOutputFormat(QPrinter::PdfFormat);
    doc.print(&printer);
    printer.newPage();

    ui->codeDisp->clear();
    ui->linNumBox->clear();
//    delete scrollWidget->layout();
//    delete scrollWidget;
//    QWidget * scrollWidget = new QWidget();
//    QVBoxLayout * emp = new QVBoxLayout;
//    scrollWidget->setLayout(emp);
//    ui->rubricScroll->setWidget(scrollWidget);
    for(rubrDispIter = rubricItemsDisplayed.begin(); rubrDispIter != rubricItemsDisplayed.end(); rubrDispIter++) {
        QGroupBox *currQBox = *rubrDispIter;
        delete currQBox;
    }

    for(rubricIter = rubricItems.begin(); rubricIter != rubricItems.end(); rubricIter++) {
        RubricItem *currItem = *rubricIter;
        delete currItem;
    }

    rubricItemsDisplayed.clear();
    selectedBoxes.clear();
    pointBoxes.clear();
    maxPoints.clear();
    rubricItems.clear();
    comments.clear();
    currFileName.clear();
    html.clear();
    qhtml.clear();
    rubric.clear();
    ui->stackedWidget->setCurrentIndex(2);
}

void Widget::on_commentCancel_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Widget::on_commentOK_clicked()
{
    string in = ui->newComText->text().toStdString();
    int in2 = ui->lNumNewCom->text().toInt();
    Comment * com = GUIEngine->add_Comment(in, in2, currFileName);
    GUIEngine->get_currLA()->get_RI(ui->RIScombo->currentText().toStdString())->add_Comment(com);
    QString sub = ui->RIScombo->currentText();
    int gbNum = -1;
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

void Widget::on_applyButton_clicked()
{
    QGroupBox * tmpPtr;
    QCheckBox * selected;
    QSpinBox * pointPTR;
    QSpinBox * mpointPTR;
    int pointsOff = 0;
    for(int i=0; i<rubricItemsDisplayed.size(); i++)
    {//    for(int i = 0; i < fileVec.size(); i++) {
        //        countStr = to_string(i);
        //        currFile = fileVec.at(i);
        //        currFile = "<h4> File Name : " + currFile255 + "</h4>";
        //        html = html + currFile;
        //    }

        //    for(commIter = comments.begin(); commIter != comments.end(); commIter++) {
        //        Comment *currComm = *commIter;
        //            comm = currComm->get_Comment();
        //            comm = "<h3>" + comm + "</h3>";

        //            commLine = currComm->get_line();
        //            commLineString = to_string(commLine);
        //            commLineString = "<h3> Line Number: " + commLineString + "</h3>";

        //            commFile = currComm->get_fileName();
        //            commFile = "<h3> File: " + commFile + "</h3>";

        //            commTotal = commTotal + empty + commFile + commLineString + comm;
        //    }
        tmpPtr = rubricItemsDisplayed.at(i);
        selected = selectedBoxes.at(i);
        pointPTR = pointBoxes.at(i);
        mpointPTR = maxPoints.at(i);
        //comments.push_back(com);
        if(selected->isChecked() && !(GUIEngine->get_currLA()->get_RI(tmpPtr->title().toStdString())->get_Applied()))
        {
            GUIEngine->get_currLA()->get_RI(tmpPtr->title().toStdString())->set_Applied(true);
            //cout << "applied set : " << GUIEngine->get_currLA()->get_RI(tmpPtr->title().toStdString())->get_Applied() << endl;
            GUIEngine->get_currLA()->get_RI(tmpPtr->title().toStdString())->set_Points(pointPTR->value());
            GUIEngine->get_currLA()->get_RI(tmpPtr->title().toStdString())->set_maxP(mpointPTR->value());
            pointsOff = pointsOff + pointPTR->value();
            GUIEngine->get_currLA()->set_Grade(GUIEngine->get_currLA()->get_Grade() - pointPTR->value());

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
            grade = grade.append(tem);
            QString final = name.append(grade);
            ui->studentgrade->setText(final);
        }
    }

}
