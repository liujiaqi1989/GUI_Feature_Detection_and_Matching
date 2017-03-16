#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QtCore>
#include <QtGui>
#include <QMessageBox>

#include <opencv/cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "detection_matching.h"
#include "matching.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_actionNew_triggered();

    void on_pushButton_4_clicked();

    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;
    cv::Mat image_left;
    cv::Mat image_right;
    QImage img_left;
    QImage img_right;

    Detection_Matching *dm;
    matching *m;
};

#endif // MAINWINDOW_H
