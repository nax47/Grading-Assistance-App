#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(2);

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
    QString path = QString::fromStdString(currFileName);
    ui->testPath->setText(path);

    QString p = QString::fromStdString(currPathName);
    QString test = QString::number(lineNUM);
    ui->testLinenum->setText(test);
    ui->testname->setText(p);

    ui->stackedWidget->setCurrentIndex(3);

}

void Widget::on_searchButton_clicked()
{

}

void Widget::on_openCodeButton_clicked()
{
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

    QFile file(fileNames.at(0));
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

    QString out;
    out = ui->outofText->text();

    if(points == NULL) {
        QMessageBox::information(this, "Warning", "Points value must be a number.");
    } else if(subject.empty() || points == NULL || comment.empty()) {
        QMessageBox::information(this, "Warning", "Please populate all fields.");
    } else {
        RubricItem *newItem = new RubricItem(subject, points);
        newItem->add_Comment(new Comment(comment));

        QGroupBox * rubricItemBox = new QGroupBox (subjectQ);
        rubricItemBox->setFixedSize(220,150);
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
        pointsBoxLayout->addWidget(pointsVal);

        QLabel * div = new QLabel(tr("Out of"));
        div->setStyleSheet("QSpinBox { color: rgb(255, 255, 255); font: 10pt\"DejaVu Sans\"; }");
        pointsBoxLayout->addWidget(div);

        QSpinBox * outof = new QSpinBox();
        outof->setValue(out.toInt());
        div->setStyleSheet("QSpinBox { color: rgb(255, 255, 255); font: 10pt\"DejaVu Sans\"; }");
        pointsBoxLayout->addWidget(outof);
        boxLayout->addLayout(pointsBoxLayout);

        QLabel * commentsLabel = new QLabel(commentQ);
        commentsLabel->setStyleSheet("QLabel { background-color: rgb(255, 255, 255); font: 8pt\"DejaVu Sans\"; } ");
        boxLayout->addWidget(commentsLabel);

        QCheckBox * applyBox = new QCheckBox();
        applyBox->setStyleSheet("QCheckBox { color: rgb(255, 255, 255); font: 8pt\"DejaVu Sans\"; } ");
        applyBox->setText("Apply");
        boxLayout->addWidget(applyBox);

        rubricItemBox->setLayout(boxLayout);
        rubricItemsDisplayed.push_back(rubricItemBox);

        QVBoxLayout * scrollLayout = new QVBoxLayout;
        for(int i=0; i<rubricItemsDisplayed.size(); i++){
            scrollLayout->addWidget(rubricItemsDisplayed.at(i));
        }
        delete ui->rubricScroll->layout();
        ui->rubricScroll->setLayout(scrollLayout);

        ui->stackedWidget->setCurrentIndex(0);
    }
}

void Widget::on_studentAdd_clicked()
{
    QString tmp = ui->newStudentName->text();
    GUIEngine.add_Student(tmp.toStdString());
    ui->studentDrop->addItem(tmp);
}

void Widget::on_labAdd_clicked()
{
    QString tmp = ui->newLabNum->text();
    int temp = tmp.toInt();
    GUIEngine.add_Lab(temp);
    ui->labDrop->addItem(tmp);
}

void Widget::on_sectionAdd_clicked()
{
    QString tmp = ui->newIDVal->text();
    GUIEngine.add_Section(tmp.toInt());
    ui->sectionDrop->addItem(tmp);
}

void Widget::on_StartGrading_clicked()
{
    GUIEngine.start_Grading();
    string studentName = GUIEngine.get_currStu()->get_Name();
    QString name = QString::fromStdString(studentName);
    int t = GUIEngine.get_currL()->get_labNum();
    QString lab = " Lab #: ";
    QString labnum = QString::number(t);
    lab = lab.append(labnum);
    name = name.append(lab);
    int g = GUIEngine.get_currLA()->get_Grade();
    QString grade = " Grade: ";
    QString tem = QString::number(g);
    grade = grade.append(tem);
    QString final = name.append(grade);
    ui->studentgrade->setText(final);
    ui->studentgrade->setStyleSheet("QSpinBox { color: rgb(255, 255, 255); font: 10pt\"DejaVu Sans\"; }");
    ui->stackedWidget->setCurrentIndex(0);
}

void Widget::on_sectionDrop_currentIndexChanged(const QString &arg1)
{
    GUIEngine.set_currSection(arg1.toInt());

    ui->labDrop->clear();
    ui->studentDrop->clear();
    vector <int> temp = GUIEngine.labNum_Drop_SetUp();
    for(int i = 0; i < temp.size(); i++)
    {
        QString t = QString::number(temp.at(i));
        ui->labDrop->addItem(t);
    }
    vector <string> t2 = GUIEngine.student_Drop_SetUp();
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
        GUIEngine.set_currLab(arg1.toInt());
    }
}

void Widget::on_studentDrop_currentIndexChanged(const QString &arg1)
{
    GUIEngine.set_currStudent(arg1.toStdString());
}


void Widget::on_commentCancel_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Widget::on_commentOK_clicked()
{

}

void Widget::on_codeDisp_cursorPositionChanged()
{
    lineNUM = ui->codeDisp->cursor().pos().ry();
}
