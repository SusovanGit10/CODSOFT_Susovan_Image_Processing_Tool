#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stack>
#include <opencv2/opencv.hpp>
#include "imageview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnOpen_clicked();
    void on_btnSave_clicked();
    void on_btnReset_clicked();
    void on_btnExit_clicked();

    void on_btnGray_clicked();
    void on_btnBlur_clicked();
    void on_btnSharpen_clicked();
    void on_btnResize_clicked();
    void on_btnRotate_clicked();
    void on_btnFlipH_clicked();
    void on_btnFlipV_clicked();
    void on_btnEdge_clicked();
    void on_btnCropManual_clicked();

    void on_btnUndo_clicked();
    void on_btnRedo_clicked();

    void on_sliderBrightness_valueChanged(int value);
    void on_sliderContrast_valueChanged(int value);
    void adjustColor();
    void ensureApplied();
    void updatePreview();

    void applyPreview();

protected:

private:
    Ui::MainWindow *ui;

    cv::Mat currentImage;
    cv::Mat originalImage;
    cv::Mat previewImage;
    cv::Mat baseImage;

    std::stack<cv::Mat> undoStack;
    std::stack<cv::Mat> redoStack;

    bool isPreviewing = false;

    void showImage(const cv::Mat &img);
};

#endif