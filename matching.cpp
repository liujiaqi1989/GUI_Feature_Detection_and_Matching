#include "matching.h"
#include "ui_matching.h"

matching::matching(QImage mResult, QWidget *parent) :
    QDialog(parent), matchResult(mResult),
    ui(new Ui::matching)
{
    ui->setupUi(this);
    ui->label->setPixmap(QPixmap::fromImage(matchResult));
    ui->label->resize(ui->label->pixmap()->size());
}


matching::~matching()
{
    delete ui;
}
