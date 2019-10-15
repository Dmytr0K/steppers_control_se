#ifndef ENGINEWIDGET_H
#define ENGINEWIDGET_H

#include <QWidget>
#include <math.h>

#define OFFPER 10

namespace Ui {
class EngineWidget;
}

class EngineWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EngineWidget(int engine_num, QWidget *parent = nullptr);
    ~EngineWidget();

    void setMinSpeed(int value);
    void setMaxSpeed(int value);

private:
    Ui::EngineWidget *ui;
    int minSpeed = -100;
    int maxSpeed = 100;
    QString offStyle;
    QString onStyle;
};

#endif // ENGINEWIDGET_H
