#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->cb_normalize->setVisible(false);
    painter = new Painter(ui->Graph);

    painter->generate();
    painter->update();
    qDebug() << leftCoord + ui->Graph->width() << " " << painter->getSizePixel() << endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::checkArea(QPoint pos, QRect rect)
{
    if(pos.x() >= rect.x() && pos.x() <= rect.x() + rect.width() &&
                pos.y() >= rect.y() && pos.y() <= rect.y() + rect.height()){
            return true;
        }

        return false;
}

void MainWindow::on_pb_Draw_clicked()
{
    qDebug() << leftCoord + ui->Graph->width() << " " << painter->getSizePixel() << endl;
    painter->generate();
    leftCoord = 0;
    painter->setLeftCoord(leftCoord);
    painter->update();
    ui->horizontalScrollBar->setMaximum(0);
    ui->cb_normalize->setChecked(false);
    ui->sb_scale->setValue(100);
}

void MainWindow::on_pb_shift_right_clicked()
{
    leftCoord += 100;
    qDebug() << leftCoord + ui->Graph->width()<< " " << painter->getSizePixel() << endl;
    painter->setLeftCoord(leftCoord);
    painter->update();

    ui->horizontalScrollBar->setValue(leftCoord);
    int maxVal = painter->getSizePixel() - ui->Graph->width();
    ui->horizontalScrollBar->setMaximum(maxVal);
}

void MainWindow::on_pb_shift_left_clicked()
{
    leftCoord -= 100;
    if(leftCoord < 0)leftCoord = 0;
    qDebug() << leftCoord + ui->Graph->width()<< " " << painter->getSizePixel() << endl;
    ui->horizontalScrollBar->setValue(leftCoord);
    painter->setLeftCoord(leftCoord);
    painter->update();
}

void MainWindow::on_sb_scale_valueChanged(int arg1)
{
    painter->setScale(1.0 * ui->sb_scale->value() / 100);
    painter->update();
}

void MainWindow::on_cb_normalize_stateChanged(int arg1)
{
    painter->setNormalize(ui->cb_normalize->isChecked());
    painter->update();
}

void MainWindow::on_horizontalScrollBar_valueChanged(int value)
{
    leftCoord = value - 6;
    if(leftCoord < 0)leftCoord = 0;
    painter->setLeftCoord(leftCoord);
    painter->update();
    ui->statusBar->showMessage(QString::number(value));
}

void MainWindow::on_sb_r_valueChanged(double arg1)
{
    painter->setR(ui->sb_r->value());
}

void MainWindow::on_sb_step_valueChanged(int arg1)
{
    painter->setStep(ui->sb_step->value());
}

void MainWindow::wheelEvent(QWheelEvent *e)
{
    auto geom = ui->Graph->geometry();
    if(checkArea(e->pos(), geom)){
        if(e->delta() > 0){
            painter->setScale(painter->getScale() + 0.1);
        }else{
            painter->setScale(painter->getScale() - 0.1);
        }
        painter->update();
    }

    ui->statusBar->showMessage(QString::number(painter->getScale() * 100) + "%");
    ui->sb_scale->setValue(painter->getScale() * 100);
}
