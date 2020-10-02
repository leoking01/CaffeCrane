#pragma once

#include <QMainWindow>

#include <opencv2/opencv.hpp>

//---------------------------------------qt-------------------------------------------
#include  "QPixmap"
#include  "QLabel"
#include  "QPainter"
#include  "QLabel"
#include  "QTextCodec"


namespace Ui { class VGRibbonWindow; };

class VGRibbonWindow : public QMainWindow
{
    Q_OBJECT
private:
    explicit VGRibbonWindow(QWidget *parent = nullptr);
    ~VGRibbonWindow();
public :
    static VGRibbonWindow *instance;
public:
    static VGRibbonWindow *getInstance() {
        if (instance) {
            return instance;
        } else {
            instance = new VGRibbonWindow();
        }
    }

private slots:
    void on_actionOpen_triggered();
    void on_actionclassify_triggered();

private:
    Ui::VGRibbonWindow *ui;

private:
    void VGRibbonWindow::paintEvent(QPaintEvent *event);

    void VGRibbonWindow::tool_selectFile(std::string title, const QString &p_filter, std::string nameFunc,
                                         std::string &fileNamefull, std::string &filePath, QString &qFileNameFull) ;
    void VGRibbonWindow::tool_selectFile_save_path(std::string title, const QString &p_filter, std::string nameFunc,
                                                   std::string &fileNamefull, std::string &filePath, QString &qFileNameFull);
    void VGRibbonWindow::closeEvent(QCloseEvent *event)  ;

public:
    void VGRibbonWindow::printLogToTextBox(std::string words);
    void VGRibbonWindow::printLogToTextBox_q(QString qWds) ;

public:
    cv::Mat   m_cv_img;
      std::string m_fileDir;
};
