#ifndef PLOTTER_H
#define PLOTTER_H
#define _USE_MATH_DEFINES // Добавить перед include
#include <QWidget>
#include <QList>

class Plotter : public QWidget {
    Q_OBJECT
public:
    void setValues(float phys, float emot, float intel);
    explicit Plotter(QWidget *parent = nullptr);
    void setBaseDays(quint16 days);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    float m_physValue = 0;
    float m_emotValue = 0;
    float m_intelValue = 0;
    quint16 m_baseDays;
    QList<float> m_phys;
    QList<float> m_emot;
    QList<float> m_intel;
};

#endif // PLOTTER_H
