#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWheelEvent>

#include "painter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Painter *painter;
    int leftCoord = 0;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool checkArea(QPoint pos, QRect rect);

private slots:
    void on_pb_Draw_clicked();

    void on_pb_shift_right_clicked();

    void on_pb_shift_left_clicked();

    void on_sb_scale_valueChanged(int arg1);

    void on_cb_normalize_stateChanged(int arg1);

    void on_horizontalScrollBar_valueChanged(int value);

    void on_sb_r_valueChanged(double arg1);

    void on_sb_step_valueChanged(int arg1);

protected:
    void wheelEvent(QWheelEvent*);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
