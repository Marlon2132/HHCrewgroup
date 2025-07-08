#include "plotter.h"
#include <QPainter>
#include <cmath>

Plotter::Plotter(QWidget *parent) : QWidget(parent), m_baseDays(0) {}

void Plotter::setBaseDays(quint16 days) {
    m_baseDays = days;
    m_phys.clear();
    m_emot.clear();
    m_intel.clear();

    for (int i = 0; i < 30; i++) {
        float p = std::sin(2 * M_PI * (m_baseDays + i) / 23.0f);
        float e = std::sin(2 * M_PI * (m_baseDays + i) / 28.0f);
        float in = std::sin(2 * M_PI * (m_baseDays + i) / 33.0f);
        m_phys.append(p);
        m_emot.append(e);
        m_intel.append(in);
    }
    update();
}

void Plotter::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    int w = width();
    int h = height();
    int margin = 40;
    int graphWidth = w - 2 * margin;
    int graphHeight = h - 2 * margin;

    // Оси координат
    painter.setPen(Qt::black);
    painter.drawLine(margin, margin, margin, h - margin); // Y
    painter.drawLine(margin, h/2, w - margin, h/2);       // X

    if (m_phys.isEmpty()) return;

    // Шаг по X (дни)
    float stepX = static_cast<float>(graphWidth) / 30.0f;

    // Физический цикл (красный)
    painter.setPen(QPen(Qt::red, 2));
    for (int i = 0; i < 29; i++) {
        painter.drawLine(
            margin + i * stepX,
            h/2 - m_phys[i] * graphHeight/2,
            margin + (i+1) * stepX,
            h/2 - m_phys[i+1] * graphHeight/2
            );
    }

    // Эмоциональный цикл (синий)
    painter.setPen(QPen(Qt::blue, 2));
    for (int i = 0; i < 29; i++) {
        painter.drawLine(
            margin + i * stepX,
            h/2 - m_emot[i] * graphHeight/2,
            margin + (i+1) * stepX,
            h/2 - m_emot[i+1] * graphHeight/2
            );
    }

    // Интеллектуальный цикл (зеленый)
    painter.setPen(QPen(Qt::green, 2));
    for (int i = 0; i < 29; i++) {
        painter.drawLine(
            margin + i * stepX,
            h/2 - m_intel[i] * graphHeight/2,
            margin + (i+1) * stepX,
            h/2 - m_intel[i+1] * graphHeight/2
            );
    }

    painter.setBrush(Qt::red);
    painter.drawEllipse(margin + 29 * stepX, h/2 - m_physValue * graphHeight/2, 8, 8);

    painter.setBrush(Qt::blue);
    painter.drawEllipse(margin + 29 * stepX, h/2 - m_emotValue * graphHeight/2, 8, 8);

    painter.setBrush(Qt::green);
    painter.drawEllipse(margin + 29 * stepX, h/2 - m_intelValue * graphHeight/2, 8, 8);

    // Подписи
    painter.setPen(Qt::black);
    painter.drawText(10, 20, "Уровень");
    painter.drawText(w - 60, h/2 + 20, "Дни");
}

void Plotter::setValues(float phys, float emot, float intel) {
    m_physValue = phys;
    m_emotValue = emot;
    m_intelValue = intel;
    update();
}
