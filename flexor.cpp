#include "flexor.h"
#include "ui_flexor.h"

Flexor::Flexor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Flexor)
{
    ui->setupUi(this);

    slot_calc();

    connect(ui->dial_flexor, &QDial::valueChanged, [this](int value) -> void {
        ui->value_N_m->setValue(value);
        slot_calc();
    });

    connect(ui->button_start, &QPushButton::clicked, [this]() -> void {
        QVector<Packet *>flexor_engines;
        for (int i = 0; i < 5; i++) {
            flexor_engines.append(new Packet);
            flexor_engines[i]->setCommand(MOVE);
            flexor_engines[i]->setEngine_number(static_cast<char>(i));
            flexor_engines[i]->setEngine_speed(1000 * (!(i % 2) ? 1 : -1));
            flexor_engines[i]->setEngine_steps(static_cast<int>(VAL_N_m * STEPS_PER_ROTATE));
        }
        for (auto pack : flexor_engines) {
            emit readyToSendPacket(*pack);
        }
    });

    connect(ui->button_stop, &QPushButton::clicked, [this]() -> void {
        QVector<Packet *>flexor_engines;
        for (int i = 0; i < 5; i++) {
            flexor_engines.append(new Packet);
            flexor_engines[i]->setCommand(STOP);
        }
        for (auto pack : flexor_engines) {
            emit readyToSendPacket(*pack);
        }
    });

    connect(ui->value_N_m, QOverload<double>::of(&QDoubleSpinBox::valueChanged), [this](double value) -> void {
        ui->dial_flexor->setValue(static_cast<int>(value));
    });
}

void Flexor::slot_calc() {
    ui->value_alpha_m->setValue(VAL_N_m / (2 * M_PI));
    ui->value_alpha_work->setValue(VAL_alpha_m /1.6);
    ui->value_N_work->setValue(VAL_N_m/1.6);
    double d = VAL_d_0 + VAL_N_m * VAL_P_w;
    //        qDebug() << d;
    double gamma = 2*asin((VAL_b/2 - d/2)/VAL_c);
    //        qDebug() << (gamma * 360) / (2 * M_PI);
    ui->value_R_sup->setValue((VAL_b / 2) / sin(gamma/2));
    ui->value_R_Fl->setValue(VAL_R_sup + VAL_C_N);
    ui->value_phi->setValue(VAL_l / VAL_R_sup);
    //    qDebug() << (VAL_phi * 360) / (2 * M_PI);
    ui->value_delta_phi->setValue(VAL_phi / VAL_n_phi);

    xi.clear();
    yi.clear();
    xi_steps.clear();
    yi_steps.clear();

    for (int i = 0; i < VAL_C_N; i++) {
        xi.append(VAL_R_Fl - VAL_R_Fl*cos(VAL_delta_phi * i));
        xi_steps.append(static_cast<int>((xi[i] * VAL_P1) / (2 * M_PI) * STEPS_PER_ROTATE));
        yi.append(VAL_R_Fl * sin(VAL_delta_phi * i));
        yi_steps.append(static_cast<int>((yi[i] * VAL_P2) / (2 * M_PI) * STEPS_PER_ROTATE));
    }
//    qDebug() << xi;
//    qDebug() << yi;
//    qDebug() << xi_steps;
//    qDebug() << yi_steps;
}

Flexor::~Flexor()
{
    delete ui;
}
