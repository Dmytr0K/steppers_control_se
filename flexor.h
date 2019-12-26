#ifndef FLEXOR_H
#define FLEXOR_H

#include <QWidget>

namespace Ui {
class flexor;
}

class flexor : public QWidget
{
    Q_OBJECT

public:
    explicit flexor(QWidget *parent = nullptr);
    ~flexor();

private:
    Ui::flexor *ui;
};

#endif // FLEXOR_H
