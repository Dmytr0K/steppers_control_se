#ifndef DIALFILTER_H
#define DIALFILTER_H

#include <QObject>
#include <QEvent>
#include <QMouseEvent>

class DialFilter : public QObject
{
    Q_OBJECT
public:
    explicit DialFilter(QObject *parent = nullptr);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

signals:
    void rightButtonClick();
};

#endif // DIALFILTER_H
