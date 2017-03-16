#ifndef MATCHING_H
#define MATCHING_H

#include <QDialog>

namespace Ui {
class matching;
}

class matching : public QDialog
{
    Q_OBJECT

public:
    explicit matching(QImage mResult,QWidget *parent = 0);
    ~matching();

private:
    Ui::matching *ui;
    QImage matchResult;
};

#endif // MATCHING_H
