#ifndef PAINTER_H
#define PAINTER_H

#include <QPixmap>
#include <QPainter>
#include <QLabel>
#include <QTime>
#include <QDebug>

#include <math.h>
#include <time.h>
#include <climits>
#include <algorithm>

class Painter
{
    QPixmap *pixmap;
    QPainter *painter;
    QLabel *label;
    QVector<int> points;
    int step = 3;
    double r = 0.5;
    bool f = false;

    double globalMinX, globalMaxX;
    double globalMinY, globalMaxY;
    double xMin, xMax;
    double yMin, yMax;
    double scaleX, scaleY;
    double oX, oY;
    int curLeftX;
    double scale = 1;
    int pOy;
    bool normalize = false;

    void init();
    void clear();

    void drawAxes();
    void midpointDisplacement(QPoint, QPoint);
    void midpoint(int, int, double);

    QPoint toPixels(QPointF);
public:
    Painter();
    Painter(QLabel *);

    void setPen(QColor);
    void setPen(QPen);
    void setLeftCoord(int);
    void setScale(double);
    void setNormalize(bool);
    void setR(double);
    void setStep(int);

    int getSizePixel();
    double getScale();

    QVector<int> getPoints();
    void addPoints();
    void draw();
    void generate();
    void update();

    ~Painter();
};

#endif // PAINTER_H
