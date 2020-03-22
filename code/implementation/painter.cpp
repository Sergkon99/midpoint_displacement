#include "../painter.h"

void Painter::init()
{
    // for example
    xMax = yMax = 10;
    xMin = yMin = -10;
    oX = fabs(xMin);
    oY = yMax;
    //step = 2;
    //r = 0.2;
    points.resize(label->width() / step / scale + 1);
    scale = 1;
    normalize = false;
    // end

    pOy = label->height() / 2;
    curLeftX = 0;
    scaleX = static_cast<double>(label->width()) / (xMax - xMin);
    scaleY = static_cast<double>(label->height()) / (yMax - yMin);

    //points.resize(label->width());
}

void Painter::clear()
{
    painter->eraseRect(0, 0, label->width(), label->height());
    painter->fillRect(0, 0, label->width(), label->height(), QColor(2, 189, 222));
}

void Painter::drawAxes()
{
    QLine l1(oX * scaleX, 0, oX * scaleX, label->height());
    QLine l2(0, oY * scaleY, label->width(), oY * scaleY);

    painter->drawLine(l1);
    painter->drawLine(l2);
}

void Painter::midpointDisplacement(QPoint a, QPoint b)
{
    if(fabs(a.x() - b.x()) < 3){
        painter->drawLine(a, b);
        return;
    }
    const double r = 0.2;

    QPoint t((a.x() + b.x()) / 2, (a.y() + b.y()) / 2 +
              r * (rand() % 3 - 1) * fabs(a.x() - b.x()));

    //qDebug() << t;

    midpointDisplacement(a, t);
    midpointDisplacement(t, b);
}

void Painter::midpoint(int left, int right, double r)
{
    //qDebug() << left << ' ' << right << ' ';
    if(right - left < 2)
        return;

    int hl = points[left];
    int hr = points[right];
    //qDebug() << hl << ' ' << hr << endl;

    int h = (hl + hr) / 2 + r * (rand() % 3 - 1) * fabs(right - left);
    int mid = (right + left) / 2;
    points[mid] = h;

    midpoint(left, mid, r);
    midpoint(mid, right, r);
}

void Painter::generate()
{
    f = true;
    init();
    points.front() = 0;
    points.back() = 0;
    midpoint(0, points.size() - 1, r);
}

void Painter::update()
{
    if(curLeftX + label->width() + 5 > getSizePixel())
        addPoints();

    draw();
}

QPoint Painter::toPixels(QPointF p)
{
    return QPoint((p.x() + oX) * scaleX, (p.y() + oY) * scaleY);
}

Painter::Painter()
{

}

Painter::Painter(QLabel *lbl)
{
    pixmap = new QPixmap(lbl->width(), lbl->height());
    painter = new QPainter(pixmap);
    label = lbl;

    init();

    QMatrix m;
    m.translate(0, lbl->height());
    m.scale(1, -1);

    painter->setMatrix(m);
}

void Painter::setPen(QColor c)
{
    painter->setPen(c);
}

void Painter::setPen(QPen p)
{
    painter->setPen(p);
}

void Painter::setLeftCoord(int d)
{
    curLeftX = d;
    if(curLeftX < 0) curLeftX = 0;
}

void Painter::setScale(double s)
{
    if(s >= 0.1)
        scale = s;
}

void Painter::setNormalize(bool f)
{
    normalize = f;
}

void Painter::setR(double val)
{
    r = val;
}

void Painter::setStep(int val)
{
    step = val;
}

int Painter::getSizePixel()
{
    return points.size() * step * scale;
}

double Painter::getScale()
{
    return scale;
}

QVector<int> Painter::getPoints()
{
    return points;
}

void Painter::addPoints()
{
    srand(QTime::currentTime().msec());
    int start = points.size() - 1;
    int lastPoint = points.back();
    points.append(QVector<int>(label->width() / step + 1, 0));
    points.back() = rand() % label->height() - pOy;
    midpoint(start - 1, points.size() - 1, r);
    qDebug() << points.size() << endl;
}

void Painter::draw()
{   
    clear();
    setPen(Qt::blue);

    auto cur_time = QTime::currentTime().msec();
    srand(cur_time);

    int maxHeight = *std::max_element(points.begin(), points.end());
    double k = 1;
    if(normalize){
        k = 1.0 / fabs(maxHeight) * pOy;
    }

    painter->setBrush(QColor(19, 212, 38));
    QPolygon polygon;
    polygon.append(QPoint(-1, -1));
    for(int i = curLeftX / step; i < points.size(); i++){
        QPoint p((i - curLeftX / step) * step * scale, 1.0 * (points[i] * scale) * k + pOy);
        polygon.append(p);
    }
    polygon.append(QPoint(label->width() + 1, -1));
    painter->drawPolygon(polygon);
    if(false){
        painter->setPen(Qt::black);
        painter->drawLine(0, pOy, label->width(), pOy);
    }
    label->setPixmap(*pixmap);
}

Painter::~Painter()
{
    delete pixmap;
    delete painter;
    delete label;
}
