#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGridLayout *layout=new QGridLayout;

    ui->label->setStyleSheet("QLabel { background-color : lightGray;}");
    ui->label_2->setStyleSheet("QLabel { background-color : lightGray;}");

    layout->addWidget(ui->label,0,0);
    layout->addWidget(ui->label_2,0,1);
    ui->statusBar->showMessage("Please input images...");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    QString fileName_left = QFileDialog::getOpenFileName(this,tr("Open Left Image"), ".",
                                                    tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));
    image_left=cv::imread(fileName_left.toLatin1().data());

    if (image_left.channels()==3)
    {
        cv::cvtColor(image_left,image_left,CV_BGR2RGB);
        img_left=QImage((const unsigned char*)(image_left.data),
                          image_left.cols, image_left.rows, image_left.step, QImage::Format_RGB888);
        img_left.bits();
    }
    else
    {
        img_left=QImage((const unsigned char*)(image_left.data),
                          image_left.cols, image_left.rows,image_left.step, QImage::Format_Grayscale8);
        img_left.bits();
    }
    ui->label->setPixmap(QPixmap::fromImage(img_left));
    ui->label->resize(ui->label->pixmap()->size());
    ui->statusBar->showMessage("Left image is inputed. Please input the right image.");
}

void MainWindow::on_pushButton_3_clicked()
{

    QString fileName_right = QFileDialog::getOpenFileName(this,tr("Open Right Image"), ".",
                                                    tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));
    image_right=cv::imread(fileName_right.toLatin1().data());
    if (image_right.channels()==3)
    {
        cv::cvtColor(image_right,image_right,CV_BGR2RGB);
        img_right=QImage((const unsigned char*)(image_right.data),
                          image_right.cols, image_right.rows, image_right.step, QImage::Format_RGB888);
        img_right.bits();
    }
    else
    {
        img_right=QImage((const unsigned char*)(image_right.data),
                          image_right.cols, image_right.rows, image_right.step,QImage::Format_Grayscale8);
        img_right.bits();
    }

    ui->label_2->setPixmap(QPixmap::fromImage(img_right));
    ui->label_2->resize(ui->label_2->pixmap()->size());
    ui->statusBar->showMessage("Right image is inputed. Please choose the detector and matcher.");

}

void MainWindow::on_pushButton_2_clicked()
{

    if(image_left.empty()||image_right.empty())
    {
    QMessageBox::critical(this,"Error","Please input left and right images !");
    }
    else
    {
    QImage QKimg_left,QKimg_right;
    dm=new Detection_Matching(ui->comboBox->currentText().toLatin1().data(),
                              ui->comboBox->currentText().toLatin1().data(),ui->comboBox_2->currentText().toLatin1().data(),
                              image_left, image_right);
    ui->statusBar->showMessage("Feature points are being detected...");
    dm->Detecting();
    cv::Mat kimage_left=dm->getKimage_left();
    cv::Mat kimage_right=dm->getKimage_right();

    if (kimage_left.channels()==3)
    {
        cv::cvtColor(kimage_left,kimage_left,CV_BGR2RGB);
        QKimg_left=QImage((const unsigned char*)(kimage_left.data),
                          kimage_left.cols, kimage_left.rows, kimage_left.step, QImage::Format_RGB888);
        QKimg_left.bits();
    }
    else
    {
        QKimg_left=QImage((const unsigned char*)(kimage_left.data),
                          kimage_left.cols, kimage_left.rows, kimage_left.step, QImage::Format_Grayscale8);
        QKimg_left.bits();
    }


    if (kimage_right.channels()==3)
    {
        cv::cvtColor(kimage_right,kimage_right,CV_BGR2RGB);
        QKimg_right=QImage((const unsigned char*)(kimage_right.data),
                          kimage_right.cols, kimage_right.rows, kimage_right.step, QImage::Format_RGB888);
        QKimg_right.bits();
    }
    else
    {
        QKimg_right=QImage((const unsigned char*)(kimage_right.data),
                          kimage_right.cols, kimage_right.rows, kimage_right.step, QImage::Format_Grayscale8);
        QKimg_right.bits();
    }
    ui->label->clear();
    ui->label_2->clear();
    ui->label->setPixmap(QPixmap::fromImage(QKimg_left));
    ui->label->resize(ui->label->pixmap()->size());
    ui->label_2->setPixmap(QPixmap::fromImage(QKimg_right));
    ui->label_2->resize(ui->label_2->pixmap()->size());
    ui->statusBar->showMessage("Feature points are detected successfully ! ");
    }

}

void MainWindow::on_pushButton_4_clicked()
{

    if(dm->getDescriptors_left().empty()||dm->getDescriptors_right().empty()){
        QMessageBox::critical(this,"Error", "Please detect the feature points for left and right images !");
    }
    else
    {
    ui->statusBar->showMessage("Looking for matchings...");
    dm->Matching();
    cv::Mat mResult=dm->getmatchResult();
    QImage QmResult;
    if (mResult.channels()==3)
    {
        cv::cvtColor(mResult,mResult,CV_BGR2RGB);
        QmResult=QImage((const unsigned char*)(mResult.data),
                          mResult.cols, mResult.rows, mResult.step, QImage::Format_RGB888);
        QmResult.bits();
    }
    else
    {
        QmResult=QImage((const unsigned char*)(mResult.data),
                          mResult.cols, mResult.rows, mResult.step, QImage::Format_Grayscale8);
        QmResult.bits();
    }

    m=new matching(QmResult,this);
    m->show();
    ui->statusBar->showMessage("Matched points are found successfully !");
    }

}

void MainWindow::on_actionNew_triggered()
{
    image_left.release();
    image_right.release();
    img_left=QImage();
    img_right=QImage();
    ui->label->clear();
    ui->label_2->clear();
}



void MainWindow::on_actionSave_triggered()
{
    ui->statusBar->showMessage("Saving the descriptors for left and right images...");
    QString fileName_LD = QFileDialog::getSaveFileName(this,tr("Saving left descriptors"),".",
                                                         tr("Files(*.yml)"));
    cv::FileStorage save_left(fileName_LD.toLatin1().data(), cv::FileStorage::WRITE);
    save_left<<"left_descriptors"<<dm->getDescriptors_left();

    QString fileName_RD = QFileDialog::getSaveFileName(this,tr("Saving right descriptors"),".",
                                                         tr("Files(*.yml)"));
    cv::FileStorage save_right(fileName_RD.toLatin1().data(), cv::FileStorage::WRITE);
    save_right<<"right_descriptors"<<dm->getDescriptors_right();
    ui->statusBar->showMessage("Descriptors are saved !");

}
