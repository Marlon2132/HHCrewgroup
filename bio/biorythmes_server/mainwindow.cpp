#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "painter.h"
#include <QtMath>
#include <QString>
#include <QMouseEvent>
#include <QMessageBox>
#include <QNetworkInterface>
#include "server.h"
#include <QTimer>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    server(new Server(this))
{


    ui->setupUi(this);

    connect(server, &Server::logMessage, this, &MainWindow::appendLog);
    displayLocalIp();

    ui->gridLayout->addWidget(paintel, 0, 0);
    this->setWindowTitle("БИОРИТМЫ SERVER | HHCrewgroup");
    ui->physBiorythmName->setStyleSheet("color: rgb(255, 0, 0)");
    ui->psychoBiorythmName->setStyleSheet("color: rgb(0, 0, 255)");
    ui->intellBiorythmName->setStyleSheet("color: rgb(0, 255, 0)");

    connect(this->paintel, &painter::updateInfoSignal, this, &MainWindow::updateInfo);
    connect(server, &Server::datesReceived, this, &MainWindow::buildGraphic);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnStart_clicked() {
    constexpr quint16 port = 12345;
    if (server->start(port)) {
        ui->btnStart->setEnabled(false);
    }
}

void MainWindow::appendLog(const QString &msg) {
    ui->txtLog->append(msg);
}

void MainWindow::displayLocalIp() {
    for (auto iface : QNetworkInterface::allInterfaces()) {
        if (iface.flags().testFlag(QNetworkInterface::IsUp)
            && !iface.addressEntries().isEmpty()) {
            for (auto entry : iface.addressEntries()) {
                if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol
                    && !entry.ip().isLoopback()) {
                    ui->lblIp->setText(entry.ip().toString());
                    return;
                }
            }
        }
    }
    ui->lblIp->setText("IP не найден");
}

void MainWindow::buildGraphic(QString bDate, QString cDate){
    birth.inputDate(bDate);
    if (!birth.checkDate()) {
        QMessageBox::warning(this, "Неверная дата", "Неверный формат даты рождения.");
        return;
    }

    // Обработка текущей даты
    currDate.inputDate(cDate);
    if (!currDate.checkDate()) {
        QMessageBox::warning(this, "Неверная дата", "Неверный формат даты для расчёта.");
        return;
    }

    // Проверка хронологии
    if (currDate < birth) {
        QMessageBox::warning(this, "Ошибка даты", "Дата расчёта не может быть раньше даты рождения.");
        return;
    }

    // Обновление интерфейса
    ui->birthdayLabel->setText(birth.outputDate());
    ui->currDayLabel->setText(currDate.outputDate());
    ui->daysLivedNumberLbl->setText(QString::number(currDate.differenceInDays(birth)));

    // Расчёт биоритмов
    const double pi = 3.141592653589793;
    auto calcPercent = [&](int period) {
        return qRound(qSin(2*pi*currDate.differenceInDays(birth)/period)*100);
    };

    physBiorythmPercent = calcPercent(23);
    psychoBiorythmPercent = calcPercent(28);
    intellBiorythmPercent = calcPercent(33);

    auto showValue = [&](QLabel* label, int value) {
        label->setText(QString::number(value) + "%");
    };

    showValue(ui->physBiorythm, physBiorythmPercent);
    showValue(ui->psychoBiorythm, psychoBiorythmPercent);
    showValue(ui->intellBiorythm, intellBiorythmPercent);

    // Обновление графика
    paintel->getDates(currDate, birth);
    paintel->firstLaunch = true;
    paintel->update();
}


void MainWindow::on_standartFormat_triggered()
{
    currDate.changeFormat(1);
    birth.changeFormat(1);
    paintel->changeFormat(1);
    ui->birthdayLabel->setText(birth.outputDate());
    ui->currDayLabel->setText(currDate.outputDate());
    ui->textFormat->setChecked(0);
    ui->reverseFormat->setChecked(0);
    paintel->update();
}


void MainWindow::on_textFormat_triggered()
{
    currDate.changeFormat(2);
    birth.changeFormat(2);
    paintel->changeFormat(2);
    ui->birthdayLabel->setText(birth.outputDate());
    ui->currDayLabel->setText(currDate.outputDate());
    ui->standartFormat->setChecked(0);
    ui->reverseFormat->setChecked(0);
    paintel->update();
}

void MainWindow::on_reverseFormat_triggered()
{
    currDate.changeFormat(3);
    birth.changeFormat(3);
    paintel->changeFormat(3);
    ui->birthdayLabel->setText(birth.outputDate());
    ui->currDayLabel->setText(currDate.outputDate());
    ui->standartFormat->setChecked(0);
    ui->textFormat->setChecked(0);
    paintel->update();
}


void MainWindow::on_action_3_triggered()
{
    if(!isFullScreen()) showFullScreen();
    else showNormal();
}


void MainWindow::on_action_4_triggered()
{
    close();
}


void MainWindow::on_physShowSwitch_triggered()
{
    if (paintel->physShow)
    {
        paintel->physShow = false;
        ui->physBiorythmName->clear();
        ui->physBiorythm->clear();
    }
    else
    {
        double pi = 3.14159265359;
        ui->physBiorythmName->setText("Физиологический биоритм");
        physBiorythmPercent = qRound(qSin(2*pi*currDate.differenceInDays(birth)/23)*100);
        QString inc = QString::number(physBiorythmPercent);
        inc += "%";
        if (currDate >= birth) ui->physBiorythm->setText(inc);
        else ui->physBiorythm->clear();
        paintel->physShow = true;
    }
    paintel->update();
}


void MainWindow::on_psychoShowSwitcch_triggered()
{
    if (paintel->psychoShow)
    {
        paintel->psychoShow = false;
        ui->psychoBiorythmName->clear();
        ui->psychoBiorythm->clear();
    }
    else
    {
        double pi = 3.14159265359;
        ui->psychoBiorythmName->setText("Психологический биоритм");
        psychoBiorythmPercent = qRound(qSin(2*pi*currDate.differenceInDays(birth)/28)*100);
        QString inc = QString::number(psychoBiorythmPercent);
        inc += "%";
        if (currDate >= birth) ui->psychoBiorythm->setText(inc);
        else ui->psychoBiorythm->clear();
        paintel->psychoShow = true;
    }
    paintel->update();
}


void MainWindow::on_intellShowSwitch_triggered()
{
    if (paintel->intellShow)
    {
        paintel->intellShow = false;
        ui->intellBiorythmName->clear();
        ui->intellBiorythm->clear();
    }
    else
    {
        double pi = 3.14159265359;
        ui->intellBiorythmName->setText("Интеллектуальный биоритм");
        intellBiorythmPercent = qRound(qSin(2*pi*currDate.differenceInDays(birth)/33)*100);
        QString inc = QString::number(intellBiorythmPercent);
        inc += "%";
        if (currDate >= birth) ui->intellBiorythm->setText(inc);
        else ui->intellBiorythm->clear();
        paintel->intellShow = true;
    }
    paintel->update();
}


void MainWindow::on_setCurrDate_triggered()
{
    currDate.setCurrentDate();
    ui->birthdayLabel->setText(birth.outputDate());
    ui->currDayLabel->setText(currDate.outputDate());
    birth.inputDate("03.03.2003"/*ui->birthdayLineEdit->text()*/);
    currDate.inputDate("04.04.2004"/*ui->currDayLineEdit->text()*/);
    ui->birthdayLabel->setText(birth.outputDate());
    ui->currDayLabel->setText(currDate.outputDate());
    paintel->getDates(currDate, birth);
    updateInfoF();
}


void MainWindow::on_pushButton_2_clicked()
{
    currDate.addDays(1);
    updateInfoF();
}


void MainWindow::on_pushButton_clicked()
{
    currDate.addDays(-1);
    updateInfoF();
}





void MainWindow::on_action_triggered()
{
    if (paintel->antialiasing) paintel->antialiasing = false;
    else paintel->antialiasing = true;
    paintel->update();
}


void MainWindow::on_action_5_triggered()
{
    if (paintel->bold == true) paintel->bold = false;
    else paintel->bold = true;
    paintel->update();
}


void MainWindow::on_maxLineSwitch_triggered()
{
    if (paintel->maxLine) paintel->maxLine = false;
    else paintel->maxLine = true;
    paintel->update();
}


void MainWindow::on_maxCrossSwitch_triggered()
{
    if (paintel->maxCross) paintel->maxCross = false;
    else paintel->maxCross = true;
    paintel->update();
}


void MainWindow::on_minLineSwitch_triggered()
{
    if (paintel->minLine) paintel->minLine = false;
    else paintel->minLine = true;
    paintel->update();
}


void MainWindow::on_minCrossSwitch_triggered()
{
    if (paintel->minCross) paintel->minCross = false;
    else paintel->minCross = true;
    paintel->update();
}


void MainWindow::on_nullSwitch_triggered()
{
    if (paintel->nullCircle) paintel->nullCircle = false;
    else paintel->nullCircle = true;
    paintel->update();
}


void MainWindow::on_critMinSwitch_triggered()
{
    if (paintel->critMin) paintel->critMin = false;
    else paintel->critMin = true;
    paintel->update();
}


void MainWindow::on_critMaxSwitch_triggered()
{
    if (paintel->critMax) paintel->critMax = false;
    else paintel->critMax = true;
    paintel->update();
}


void MainWindow::on_critNullSwitch_triggered()
{
    if (paintel->critNull) paintel->critNull = false;
    else paintel->critNull = true;
    paintel->update();
}


void MainWindow::on_action_8_triggered()
{
    if (paintel->birthdaySwitch) paintel->birthdaySwitch = false;
    else paintel->birthdaySwitch = true;
    paintel->update();
}


void MainWindow::on_cursorTrackingSwitch_triggered()
{
    if (paintel->cursorTracking) paintel->cursorTracking = false;
    else paintel->cursorTracking = true;
    paintel->update();
}


void MainWindow::updateInfo()
{
    currDate = paintel->currDate;
    double pi = 3.14159265359;

    physBiorythmPercent = qRound(qSin(2*pi*currDate.differenceInDays(birth)/23)*100);
    QString inc = QString::number(physBiorythmPercent);
    inc += "%";
    if (currDate >= birth && paintel->physShow) ui->physBiorythm->setText(inc);
    else ui->physBiorythm->clear();
    psychoBiorythmPercent = qRound(qSin(2*pi*currDate.differenceInDays(birth)/28)*100);
    inc = QString::number(psychoBiorythmPercent);
    inc += "%";
    if (currDate >= birth && paintel->psychoShow) ui->psychoBiorythm->setText(inc);
    else ui->psychoBiorythm->clear();
    intellBiorythmPercent = qRound(qSin(2*pi*currDate.differenceInDays(birth)/33)*100);
    inc = QString::number(intellBiorythmPercent);
    inc += "%";
    if (currDate >= birth && paintel->intellShow) ui->intellBiorythm->setText(inc);
    else ui->intellBiorythm->clear();

    ui->birthdayLabel->setText(birth.outputDate());
    ui->currDayLabel->setText(currDate.outputDate());
    paintel->getDates(currDate, birth);
    paintel->update();

}

void MainWindow::updateInfoF()
{
    double pi = 3.14159265359;

    physBiorythmPercent = qRound(qSin(2*pi*currDate.differenceInDays(birth)/23)*100);
    QString inc = QString::number(physBiorythmPercent);
    inc += "%";
    if (currDate >= birth && paintel->physShow) ui->physBiorythm->setText(inc);
    else ui->physBiorythm->clear();
    psychoBiorythmPercent = qRound(qSin(2*pi*currDate.differenceInDays(birth)/28)*100);
    inc = QString::number(psychoBiorythmPercent);
    inc += "%";
    if (currDate >= birth && paintel->psychoShow) ui->psychoBiorythm->setText(inc);
    else ui->psychoBiorythm->clear();
    intellBiorythmPercent = qRound(qSin(2*pi*currDate.differenceInDays(birth)/33)*100);
    inc = QString::number(intellBiorythmPercent);
    inc += "%";
    if (currDate >= birth && paintel->intellShow) ui->intellBiorythm->setText(inc);
    else ui->intellBiorythm->clear();

    ui->birthdayLabel->setText(birth.outputDate());
    ui->currDayLabel->setText(currDate.outputDate());
    paintel->getDates(currDate, birth);
    paintel->update();


}

void MainWindow::on_action_2_triggered()
{
    QMessageBox *about = new QMessageBox;
    about->setWindowTitle("О программе");
    about->setIcon(QMessageBox::Information);
    about->setText("БИОРИТМЫ\n\nС помощью этой программы можно построить графики физиологического, психологического и интеллектуального биоритмов и рассчитать биоритмы на конкретные даты.\n"
                   "Чтобы рассчитать фазы биоритмов, требуется ввести в поле для ввода даты рождения дату рождения и в поле для даты для рассчета дату,"
                   " для которой Вы хотите рассчитать фазу биоритмов. Ввод можно производить в трех форматах: стандартный(дд.мм.гггг), текстовый(число месяц гггг) и обратный(гггг.мм.дд). "
                   "Для выбора формата нажмите на \"Формат ввода-вывода\" и выберите интересущий Вас формат. После ввода даты рождения и даты для расчета нажмите на кнопку \"Построить график\". "
                   "После нажатия на кнопку построения графика на экране отобразятся 3 графика биоритмов. Над графиком будут отображаться фазы биоритмов в процентах. "
                   "Кнопками \"<\" и \">\" можно пролистывать рассматриваемую дату вперед и назад. "
                   "Выбрав \"Показать биоритмы\" можно отключить и включить интересующие Вас биоритмы. \n\n"
                   "МЕНЮ\nВ меню можно выбрать пункт \"Рассмотреть сегодняшнюю дату\". При нажатии на эту кнопку рассматриваться будет сегодняшняя дата.\n"
                   "В меню можно выбрать пункт \"Толстые линии биоритмов\", при выборе которого графики биоритмов будут отображаться более толстыми линиями.\n"
                   "При выборе пункта \"Отслеживание курсора\" около курсора будет отображаться дата, находящаяся под ним. При двойном нажатии правой клавиши мыши дата под курсоров станет рассматриваемой.\n"
                   "При выборе пункта \"Сглаживание\" график станет плавнее.\n"
                   "Нажав на пункт \"Полноэкранный режим\", Вы перейдете в полноэкранный режим. Для выхода из него надо нажать на эту кнопку еще раз.\n"
                   "Чтобы выйти из программы можно выбрать пункт \"Выйти\".\n\n"
                   "КРИТИЧЕСКИЕ ТОЧКИ\nВ разделе \"Критические точки\" можно выбрать обозначение интересующих Вас критических точек. Точки максимума - те дни, в которых биоритмы принимают свое максимальное значение."
                   " Точки минимума - те дни, в которых биоритмы принимают свое минимальное значение. Точки неустойчивости - те дни, когда биоритмы равны нулю, то есть не отрицательные и не положительные."
                   " Также есть соответствующие критические точки. Это те дни, в которые несколько биоритмов принимают одновременно максимальное, минимальное или нулевое значение. Они обозначаются желтым цветом\n"
                   "Также можно выбрать отображение на графике даты рождения. Она обозначается белым цветом.");
    about->exec();
}

