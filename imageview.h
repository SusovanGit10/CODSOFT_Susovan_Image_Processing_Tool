#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <opencv2/opencv.hpp>

class ImageView : public QLabel
{
    Q_OBJECT

public:
    explicit ImageView(QWidget *parent = nullptr);

    void setImage(const cv::Mat &img);

signals:
    void cropFinished(cv::Rect roi);
    void imageDropped(QString path);
    void browseRequested();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;

private:
    cv::Mat image;

    QPoint startPoint, endPoint;
    bool drawing = false;

    double scaleX = 1.0;
    double scaleY = 1.0;
    bool isHovering = false;
    bool isDragging = false;
};

#endif