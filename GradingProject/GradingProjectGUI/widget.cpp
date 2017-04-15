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
    ui->studentDrop->addItem(tmp);
}

void Widget::on_labAdd_clicked()
{
    QString tmp = ui->newLabNum->text();
    ui->labDrop->addItem(tmp);
}

void Widget::on_sectionAdd_clicked()
{
    QString tmp = ui->newIDVal->text();
    ui->sectionDrop->addItem(tmp);
}

void Widget::on_StartGrading_clicked()
{

}
