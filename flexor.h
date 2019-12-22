#ifndef FLEXOR_H
#define FLEXOR_H

#include <QWidget>
#include <QDebug>
#include <QVector>
#include <QCheckBox>
#include "packet.h"
#include <math.h>

#define STEPS_PER_ROTATE 1600

#define VAL_N_m ui->value_N_m->value()

#define VAL_alpha_m ui->value_alpha_m->value()
#define VAL_R_sup ui->value_R_sup->value()
#define VAL_N_work ui->value_N_work->value()

#define VAL_C_N ui->value_C_N->value()
#define VAL_n_phi ui->value_n_phi->value()
#define VAL_l ui->value_l->value()
#define VAL_b ui->value_b->value()
#define VAL_c ui->value_c->value()
#define VAL_d_0 ui->value_d_0->value()
#define VAL_P_w ui->value_P_w->value()
#define VAL_P1 ui->value_P1->value()
#define VAL_P2 ui->value_P2->value()

#define VAL_phi ui->value_phi->value()
#define VAL_R_Fl ui->value_R_Fl->value()
#define VAL_delta_phi ui->value_delta_phi->value()



namespace Ui {
class Flexor;
}

class Flexor : public QWidget
{
    Q_OBJECT

public:
    explicit Flexor(QWidget *parent = nullptr);
    ~Flexor();

signals:
    void readyToSendPacket(Packet &packet);

private:
    Ui::Flexor *ui;
    QVector <double> xi, yi;
    QVector <int> xi_steps, yi_steps;
    QVector <QCheckBox> check_widgets;

private slots:
    void slot_calc();
};

#endif // FLEXOR_H
