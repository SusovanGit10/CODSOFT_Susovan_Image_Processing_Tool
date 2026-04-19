#include "imageview.h"
#include <QMimeData>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QUrl>
#include <QPainter>
#include <QEnterEvent>

ImageView::ImageView(QWidget *parent) : QLabel(parent)
{
    setAlignment(Qt::AlignCenter);
    setAcceptDrops(true);
    setCursor(Qt::PointingHandCursor);
}

void ImageView::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls())
    {
        isDragging = true;
        event->acceptProposedAction();
        update();
    }
}

void ImageView::dropEvent(QDropEvent *event)
{
    isDragging = false;

    QList<QUrl> urls = event->mimeData()->urls();
    if(urls.isEmpty()) return;

    QString path = urls.first().toLocalFile();
    emit imageDropped(path);

    update();
}

void ImageView::dragLeaveEvent(QDragLeaveEvent *event)
{
    isDragging = false;
    update();
}

void ImageView::setImage(const cv::Mat &img)
{
    image = img.clone();
    if(image.empty()) return;

    QImage qimg(image.data, image.cols, image.rows, image.step,
                image.channels()==3 ? QImage::Format_BGR888 : QImage::Format_Grayscale8);

    QPixmap pix = QPixmap::fromImage(qimg);

    QPixmap scaled = pix.scaled(
        this->size(),
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation
        );

    setPixmap(scaled);
    setAlignment(Qt::AlignCenter);
}

void ImageView::mousePressEvent(QMouseEvent *event)
{
    if(image.empty())
    {
        emit browseRequested();
        return;
    }


    drawing = true;
    startPoint = event->pos();
    endPoint = startPoint;
}

void ImageView::mouseMoveEvent(QMouseEvent *event)
{
    if(drawing){
        endPoint = event->pos();
        update();
    }
}

void ImageView::mouseReleaseEvent(QMouseEvent *event)
{
    if(!drawing) return;

    drawing = false;
    endPoint = event->pos();

    QRect rect(startPoint, endPoint);


    QSize pixSize = pixmap().size();
    QSize lblSize = size();

    int xOffset = (lblSize.width() - pixSize.width()) / 2;
    int yOffset = (lblSize.height() - pixSize.height()) / 2;


    int x = rect.x() - xOffset;
    int y = rect.y() - yOffset;

    int w = rect.width();
    int h = rect.height();

    if(x < 0 || y < 0) return;

    double scaleX = (double)image.cols / pixSize.width();
    double scaleY = (double)image.rows / pixSize.height();

    cv::Rect roi(x*scaleX, y*scaleY, w*scaleX, h*scaleY);

    roi &= cv::Rect(0,0,image.cols,image.rows);

    if(roi.width > 0 && roi.height > 0)
        emit cropFinished(roi);

    update();
}

void ImageView::paintEvent(QPaintEvent *event)
{

    QLabel::paintEvent(event);

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    QRect r = rect().adjusted(20,20,-20,-20);

    // ---------- EMPTY STATE ----------
    if(image.empty())
    {
        // background
        QColor bg = QColor(30,30,30);
        if(isHovering) bg = QColor(40,40,40);
        if(isDragging) bg = QColor(20,40,70);

        p.fillRect(rect(), bg);

        // dashed border
        QPen pen;
        pen.setWidth(2);

        if(isDragging)
        {
            pen.setColor(QColor(0,150,255));
            pen.setWidth(3);
        }
        else
        {
            pen.setColor(QColor(90,90,90));
            pen.setWidth(2);
        }

        pen.setStyle(Qt::DashLine);
        p.setPen(pen);
        p.drawRoundedRect(r, 12, 12);

        // text
        p.setPen(QColor(180,180,180));
        p.setFont(QFont("Segoe UI", 13, QFont::DemiBold));

        QString text = isDragging ?
                           "Drop Image Here" :
                           "Click to Browse or Drag & Drop Image";

        p.drawText(rect(), Qt::AlignCenter, text);

        p.setFont(QFont("Segoe UI", 10));
        p.setPen(QColor(120,120,120));

        p.drawText(rect().adjusted(0,40,0,0),
                   Qt::AlignCenter,
                   "Supports JPG, PNG, BMP");
    }
}

void ImageView::resizeEvent(QResizeEvent *event)
{
    QLabel::resizeEvent(event);

    if(!image.empty())
        setImage(image);
}

void ImageView::enterEvent(QEnterEvent *event)
{
    isHovering = true;
    update();
}

void ImageView::leaveEvent(QEvent *event)
{
    isHovering = false;
    update();
}