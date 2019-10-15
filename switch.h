#ifndef SWITCH_H
#define SWITCH_H

#include <QWidget>

namespace Ui {
class Switch;
}

class Switch : public QWidget
{
    Q_OBJECT

public:
    explicit Switch(int num, QWidget *parent = nullptr);
    ~Switch();

private:
    Ui::Switch *ui;
    bool activated = false;
    QString onStyle;
    QString offStyle;
};

#endif // SWITCH_H
