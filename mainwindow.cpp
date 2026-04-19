#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // RGB preview
    connect(ui->sliderR, &QSlider::valueChanged, this, &MainWindow::adjustColor);
    connect(ui->sliderG, &QSlider::valueChanged, this, &MainWindow::adjustColor);
    connect(ui->sliderB, &QSlider::valueChanged, this, &MainWindow::adjustColor);

    //Drag & Drop
    connect(ui->imageView, &ImageView::browseRequested, this, [this]() {
        on_btnOpen_clicked();
    });

    connect(ui->imageView, &ImageView::imageDropped, this, [this](QString path){

        currentImage = cv::imread(path.toStdString());
        if(currentImage.empty()) return;

        originalImage = currentImage.clone();
        baseImage = currentImage.clone();
        previewImage = currentImage.clone();

        undoStack = std::stack<cv::Mat>();
        redoStack = std::stack<cv::Mat>();

        showImage(currentImage);
    });

    // Apply preview on release
    connect(ui->sliderBrightness, &QSlider::sliderReleased, this, &MainWindow::applyPreview);
    connect(ui->sliderContrast, &QSlider::sliderReleased, this, &MainWindow::applyPreview);
    connect(ui->sliderR, &QSlider::sliderReleased, this, &MainWindow::applyPreview);
    connect(ui->sliderG, &QSlider::sliderReleased, this, &MainWindow::applyPreview);
    connect(ui->sliderB, &QSlider::sliderReleased, this, &MainWindow::applyPreview);

    // Crop
    connect(ui->imageView, &ImageView::cropFinished, this,
            [this](cv::Rect roi){
                if(currentImage.empty()) return;

                undoStack.push(currentImage.clone());
                redoStack = std::stack<cv::Mat>();

                currentImage = currentImage(roi).clone();
                showImage(currentImage);
            });
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ---------- SHOW ----------
void MainWindow::showImage(const cv::Mat &img)
{
    ui->imageView->setImage(img);
}

// ---------- OPEN ----------
void MainWindow::on_btnOpen_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Open Image");
    if(path.isEmpty()) return;

    currentImage = cv::imread(path.toStdString());
    if(currentImage.empty()) return;

    originalImage = currentImage.clone();
    previewImage = currentImage.clone();
    baseImage = currentImage.clone();

    undoStack = std::stack<cv::Mat>();
    redoStack = std::stack<cv::Mat>();

    showImage(currentImage);
}

// ---------- SAVE ----------
void MainWindow::on_btnSave_clicked()
{
    ensureApplied();
    QString path = QFileDialog::getSaveFileName(
        this, "Save Image", "", "PNG (*.png);;JPG (*.jpg);;BMP (*.bmp)");

    if(path.isEmpty()) return;

    cv::imwrite(path.toStdString(), currentImage);
}

// ---------- RESET ----------
void MainWindow::on_btnReset_clicked()
{
    if(originalImage.empty()) return;

    currentImage = originalImage.clone();
    previewImage = currentImage.clone();
    baseImage = currentImage.clone();

    undoStack = std::stack<cv::Mat>();
    redoStack = std::stack<cv::Mat>();

    showImage(currentImage);
}

// ---------- EXIT ----------
void MainWindow::on_btnExit_clicked()
{
    close();
}

// ---------- GRAY ----------
void MainWindow::on_btnGray_clicked()
{
    ensureApplied();
    if(currentImage.empty()) return;

    undoStack.push(currentImage.clone());
    redoStack = std::stack<cv::Mat>();

    if(currentImage.channels() == 3)
        cv::cvtColor(currentImage, currentImage, cv::COLOR_BGR2GRAY);

    baseImage = currentImage.clone();

    showImage(currentImage);
}

// ---------- BLUR ----------
void MainWindow::on_btnBlur_clicked()
{
    ensureApplied();
    if(currentImage.empty()) return;

    undoStack.push(currentImage.clone());
    redoStack = std::stack<cv::Mat>();

    cv::GaussianBlur(currentImage, currentImage, cv::Size(15,15), 0);
    baseImage = currentImage.clone();
    showImage(currentImage);
}

// ---------- SHARPEN ----------
void MainWindow::on_btnSharpen_clicked()
{
    ensureApplied();
    if(currentImage.empty()) return;

    undoStack.push(currentImage.clone());
    redoStack = std::stack<cv::Mat>();

    cv::Mat k = (cv::Mat_<float>(3,3) <<
                     0,-1,0,
                 -1,5,-1,
                 0,-1,0);

    cv::filter2D(currentImage,currentImage,-1,k);
    baseImage = currentImage.clone();
    showImage(currentImage);
}

// ---------- RESIZE ----------
void MainWindow::on_btnResize_clicked()
{
    ensureApplied();
    if(currentImage.empty()) return;

    int w = QInputDialog::getInt(this,"Width","Width:", currentImage.cols);
    int h = QInputDialog::getInt(this,"Height","Height:", currentImage.rows);

    undoStack.push(currentImage.clone());
    redoStack = std::stack<cv::Mat>();

    cv::resize(currentImage,currentImage,{w,h});
    baseImage = currentImage.clone();
    showImage(currentImage);
}

// ---------- ROTATE ----------
void MainWindow::on_btnRotate_clicked()
{
    ensureApplied();
    if(currentImage.empty()) return;

    int angle = QInputDialog::getInt(this,"Rotate","Angle:");

    undoStack.push(currentImage.clone());
    redoStack = std::stack<cv::Mat>();

    cv::Point2f c(currentImage.cols/2,currentImage.rows/2);
    cv::Mat m=cv::getRotationMatrix2D(c,angle,1.0);

    cv::warpAffine(currentImage,currentImage,m,currentImage.size());
    baseImage = currentImage.clone();
    showImage(currentImage);
}

// ---------- FLIP ----------
void MainWindow::on_btnFlipH_clicked()
{
    ensureApplied();
    if(currentImage.empty()) return;

    undoStack.push(currentImage.clone());
    redoStack = std::stack<cv::Mat>();

    cv::flip(currentImage,currentImage,1);
    baseImage = currentImage.clone();
    showImage(currentImage);
}

void MainWindow::on_btnFlipV_clicked()
{
    ensureApplied();
    if(currentImage.empty()) return;

    undoStack.push(currentImage.clone());
    redoStack = std::stack<cv::Mat>();

    cv::flip(currentImage,currentImage,0);
    baseImage = currentImage.clone();
    showImage(currentImage);
}

// ---------- EDGE ----------
void MainWindow::on_btnEdge_clicked()
{
    ensureApplied();
    if(currentImage.empty()) return;

    undoStack.push(currentImage.clone());
    redoStack = std::stack<cv::Mat>();

    cv::Mat gray, edges;

    if(currentImage.channels()==3)
        cv::cvtColor(currentImage,gray,cv::COLOR_BGR2GRAY);
    else
        gray=currentImage.clone();

    cv::Canny(gray,edges,100,200);

    currentImage = edges;
    baseImage = currentImage.clone();
    showImage(currentImage);
}

// ---------- MANUAL CROP ----------
void MainWindow::on_btnCropManual_clicked()
{
    ensureApplied();
    if(currentImage.empty()) return;

    int x = QInputDialog::getInt(this,"X","X:");
    int y = QInputDialog::getInt(this,"Y","Y:");
    int w = QInputDialog::getInt(this,"W","Width:");
    int h = QInputDialog::getInt(this,"H","Height:");

    undoStack.push(currentImage.clone());
    redoStack = std::stack<cv::Mat>();

    cv::Rect roi(x,y,w,h);
    roi &= cv::Rect(0,0,currentImage.cols,currentImage.rows);

    currentImage = currentImage(roi);
    baseImage = currentImage.clone();
    showImage(currentImage);
}

// ---------- UNDO ----------
void MainWindow::on_btnUndo_clicked()
{
    if(!undoStack.empty()){
        redoStack.push(currentImage);
        currentImage = undoStack.top();
        undoStack.pop();
        baseImage = currentImage.clone();
        showImage(currentImage);
    }
}

// ---------- REDO ----------
void MainWindow::on_btnRedo_clicked()
{
    if(!redoStack.empty()){
        undoStack.push(currentImage);
        currentImage = redoStack.top();
        redoStack.pop();
        baseImage = currentImage.clone();
        showImage(currentImage);
    }
}

// ---------- BRIGHTNESS ----------
void MainWindow::on_sliderBrightness_valueChanged(int)
{
    updatePreview();
}

// ---------- CONTRAST ----------
void MainWindow::on_sliderContrast_valueChanged(int)
{
    updatePreview();
}

// ---------- RGB ----------
void MainWindow::adjustColor()
{
    updatePreview();
}

void MainWindow::applyPreview()
{
    if(!isPreviewing || previewImage.empty()) return;

    undoStack.push(currentImage.clone());
    redoStack = std::stack<cv::Mat>();

    currentImage = previewImage.clone();
    baseImage = currentImage.clone();

    isPreviewing = false;

    showImage(currentImage);
}
void MainWindow::ensureApplied()
{
    if(isPreviewing)
        applyPreview();
}

void MainWindow::updatePreview()
{
    if(baseImage.empty()) return;

    isPreviewing = true;

    previewImage = baseImage.clone();

    // -------- BRIGHTNESS + CONTRAST --------
    double alpha = ui->sliderContrast->value() / 50.0;
    int beta = ui->sliderBrightness->value() - 50;

    previewImage.convertTo(previewImage, -1, alpha, beta);

    // -------- RGB (CINEMATIC / REALISTIC) --------
    if(previewImage.channels() == 3)
    {
        cv::Mat floatImg;
        previewImage.convertTo(floatImg, CV_32F, 1.0/255.0);

        std::vector<cv::Mat> ch;
        cv::split(floatImg, ch);

        // slider → smooth gain (non-linear)
        auto smoothGain = [](int val) {
            float x = (val - 50) / 50.0f;
            return std::pow(2.0f, x);
        };

        float rGain = smoothGain(ui->sliderR->value());
        float gGain = smoothGain(ui->sliderG->value());
        float bGain = smoothGain(ui->sliderB->value());

        // apply gain
        ch[2] *= rGain; // R
        ch[1] *= gGain; // G
        ch[0] *= bGain; // B

        // soft clip (avoid blown highlights)
        for(auto &c : ch)
            cv::min(c, 1.0, c);

        cv::merge(ch, floatImg);

        // convert back
        floatImg.convertTo(previewImage, CV_8U, 255.0);
    }
    showImage(previewImage);
}