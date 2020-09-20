#include "vgribbonwindow.h"
#include "ui_vgribbonwindow.h"

#include <QShortcut>

#include "QRibbon/QRibbon.h"

VGRibbonWindow *  VGRibbonWindow::instance = NULL;

VGRibbonWindow::VGRibbonWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui = new Ui::VGRibbonWindow();
    ui->setupUi(this);

    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

    this->addAction(ui->actionFullScreen);
    connect(ui->actionFullScreen, &QAction::triggered, [&]() {

        auto full = ui->actionFullScreen->isChecked();
        menuBar()->setVisible(!full);
        ui->actionFullScreen->setShortcut(  full ? QKeySequence("Esc") : QKeySequence("Ctrl+F"));

        static bool maximized = false;// 记录当前状态
        if ( full )
        {
            maximized = isMaximized();
        }
        else if ( maximized && isMaximized() )
        {
            return;
        }

        if ( full && !isMaximized() || !full && isMaximized() )
        {
            if (isMaximized())
            {
                showNormal();
            }
            else
                showMaximized();
        }
    });

    connect(ui->pushButton, &QPushButton::clicked, [this]() {
        QRibbon::install(this);
        this->show();
    });
}

VGRibbonWindow::~VGRibbonWindow()
{
    delete ui;
}

#include <QCloseEvent>
#include <QMessageBox>
void VGRibbonWindow::closeEvent(QCloseEvent *event) {
    QMessageBox::StandardButton button;
    button = QMessageBox::question(this, QString("..退出vision程序.."),
                                   QString("..确认退出vis程序.."),
                                   QMessageBox::Yes | QMessageBox::No);
    if (button == QMessageBox::No) {
        event->ignore(); // 忽略退出信号，程void on_pushButton_29_clicked();
    } else if (button == QMessageBox::Yes) {
        event->accept(); // 接受退出信号，程序退出
    }
}





#include "commonfunc.h"

void VGRibbonWindow::paintEvent(QPaintEvent *event) {
    // 使用at的图像 qImage 进行显示；  这里不使用这个方式；
    if (1) {
        if (m_cv_img.empty() || !m_cv_img.data)
            return;
        //        displayResult(this->m_cv_img, this->ui->label);
        //        displayResult(this->m_cv_img, this->ui->label_2);
        //        displayResult(this->m_cv_img, this->ui->label_3);
        displayResult(this->m_cv_img, this->ui->label);
    }
    //    if (1) {
    //        //        label_cv_img_coclor
    //        if (m_cv_img_color.empty() || !m_cv_img_color.data)
    //            return;
    //        displayResult(this->m_cv_img_color, this->ui->label_cv_img_coclor);
    //    }
}

//---------------------------------------小工具------------------------------------------------------
#include <QFileInfo>
#include <QFileDialog>
void VGRibbonWindow::tool_selectFile(std::string title, const QString &p_filter, std::string nameFunc,
                                     std::string &fileNamefull, std::string &filePath, QString &qFileNameFull) {
    printLogToTextBox("\n\n\n\n\n-------------------------------><--------------------------------");
    //    QPushButton *btn = (QPushButton *) sender();  // 获取到了发送该信号按钮的指针
    //    this->printLogToTextBox(("you clicked button : " + btn->text()).toStdString());
    //    nameFunc = btn->text().toStdString();
    std::string pathPast;
    //    pathPast = ini_global.GetString("kernel", nameFunc, pathPast);
    //   printLogToTextBox("tool_selectFile: pathPast = " + pathPast);
    if (pathPast.empty()) {
        printLogToTextBox("tool_selectFile: failure to get filePath from ini file.");
        pathPast = "C:/Users/";
    } else {
        this->ui->textBrowser->append(pathPast.c_str());
        //printLogToTextBox("tool_selectFile: get filePath from ini file: " + pathPast);
    }
    QString file_name;
    QString file_path = QString::fromStdString(pathPast);
    QFileInfo fi;
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    QString::fromStdString(title),
                                                    file_path,
                                                    p_filter);
    if (fileName.isNull() || fileName.isEmpty())
        return;
    qFileNameFull = fileName;
    //    QTextCodec *code = QTextCodec::codecForName("GB2312");//解决中文路径问题
    QTextCodec *code = QTextCodec::codecForName("utf-8");//解决中文路径问题
    fileNamefull = code->fromUnicode(fileName).data();
    fi = QFileInfo(fileName);
    file_name = fi.fileName();
    file_path = fi.absolutePath();
    filePath = code->fromUnicode(file_path).data();
    this->printLogToTextBox("tool_selectFile: fileNamefull = " + fileNamefull);

    this->printLogToTextBox("tool_selectFile: fileName.toStdString() = " + fileName.toStdString());
    this->printLogToTextBox(fileName.toStdString().c_str());
    this->printLogToTextBox("tool_selectFile: file_path.toStdString() = " + file_path.toStdString());
    this->printLogToTextBox("tool_selectFile: qFileNameFull.toStdString() = " + qFileNameFull.toStdString());
}

void VGRibbonWindow::tool_selectFile_save_path(std::string title, const QString &p_filter, std::string nameFunc,
                                               std::string &fileNamefull, std::string &filePath, QString &qFileNameFull) {
    printLogToTextBox("\n\n\n\n\n-------------------------------><--------------------------------");
    //    QPushButton *btn = (QPushButton *) sender();  // 获取到了发送该信号按钮的指针
    //    this->printLogToTextBox(("you clicked button : " + btn->text()).toStdString());
    //    nameFunc = btn->text().toStdString();
    std::string pathPast;
    //    pathPast = ini_global.GetString("kernel", nameFunc, pathPast);
    //   printLogToTextBox("tool_selectFile: pathPast = " + pathPast);
    if (pathPast.empty()) {
        printLogToTextBox("tool_selectFile: failure to get filePath from ini file.");
        pathPast = "C:/Users/";
    } else {
        this->ui->textBrowser->append(pathPast.c_str());
        // printLogToTextBox("tool_selectFile: get filePath from ini file: " + pathPast);
    }
    QString file_name;
    QString file_path = QString::fromStdString(pathPast);
    QFileInfo fi;
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    QString::fromStdString(title),
                                                    file_path,
                                                    p_filter);

    if (fileName.isNull() || fileName.isEmpty())
        return;
    qFileNameFull = fileName;
    QTextCodec *code = QTextCodec::codecForName("utf-8");//解决中文路径问题
    fileNamefull = code->fromUnicode(fileName).data();
    fi = QFileInfo(fileName);
    file_name = fi.fileName();
    file_path = fi.absolutePath();
    filePath = code->fromUnicode(file_path).data();

    this->printLogToTextBox("tool_selectFile: fileNamefull = " + fileNamefull);
    this->printLogToTextBox("tool_selectFile: fileName.toStdString() = " + fileName.toStdString());
    this->printLogToTextBox(fileName.toStdString().c_str());
    this->printLogToTextBox("tool_selectFile: qFileNameFull.toStdString() = " + qFileNameFull.toStdString());

    //    log4cplus::tcout << "log4cplus-tcout-  tool_selectFile: fileNamefull = " << fileNamefull << std::endl;
    //    log4cplus::tcout << "log4cplus-tcout-  tool_selectFile: fileName.toStdString() = " << fileName.toStdString()
    //                     << std::endl;

    //    ini_global.SetString("kernel", nameFunc, file_path.toStdString());
    //    ini_global.SetString("kernel", nameFunc + std::string("Full"), fileName.toStdString());
    //    ini_global.WriteINI(ini_global_path);
    //    // printLogToTextBox("select file fileNamefull = " + fileNamefull);
}

#define   DEBUG_PRINT_LOG_LK  1
void VGRibbonWindow::printLogToTextBox(std::string words) {
#ifdef  DEBUG_PRINT_LOG_LK
    std::string time = getDatetimeStr();
    words = time + " : " + words;
    this->ui->textBrowser->append(QString::fromStdString(words));
    QString qWds = QString::fromUtf8(words.c_str());
    QTextCodec *code = QTextCodec::codecForName("utf-8");//解决中文路径问题
    std::string std_str = code->fromUnicode(qWds).data();
    //    log4cplus::tcout << std_str << std::endl;
    std:: cout<<  words <<    std::endl;
    //print_To_Glog(words, 0);
#endif
}

void VGRibbonWindow::printLogToTextBox_q(QString qWds) {
#ifdef  DEBUG_PRINT_LOG_LK
    std::string time = getDatetimeStr();
    //    qWds = QString::fromStdString(time) + " : " + qWds;
    QTextCodec *code = QTextCodec::codecForName("GB2312");//解决中文路径问题
    std::string stdWds = code->fromUnicode(qWds).data();
    stdWds = time + ":" + stdWds;
    this->ui->textBrowser->append(QString::fromUtf8(stdWds.c_str()));
    std:: cout<<   qWds.toStdString()<<    std::endl;
    //print_To_Glog(stdWds, 0);
    return;
#endif
}



void VGRibbonWindow::on_actionOpen_triggered()
{
    std::string filePathFull;
    std::string filePath;
    QString qFileNameFull;
    tool_selectFile(("select range iamge file."),
                    tr("allfileType(*);;图片文件(*png *jpg *pcd *ply *png);;pcd文件(*pcd *ply *png);;"
                       "本本文件(*txt)"),
                    "path_rangeImage", filePathFull, filePath, qFileNameFull);

    if (filePathFull.empty())
        return;

    //    this->ui->lineEdit->setText(qFileNameFull);
    //    this->ui->comboBox->addItem(qFileNameFull);

    //show image
    cv::Mat depthImage = cv::imread(filePathFull, cv::IMREAD_UNCHANGED);//读取图片数据
    if (depthImage.cols <= 0 || !depthImage.data) {
        this->printLogToTextBox(
                    QString::fromUtf8("selectFile_rangeImage: read iamge failure .   ..").toStdString());
        return;
    } else {
        m_cv_img = depthImage;
        //print
        this->printLogToTextBox(QString::fromUtf8("selectFile_rangeImage: read image ok.   ..").toStdString());
        print_cvMat_info(depthImage);
        repaint();
    }
}


//打开分类对话框
#include "formclassify.h"
void VGRibbonWindow::on_actionclassify_triggered()
{
    QWidget *pWid =  FormClassify::getInstance();//new FormClassify( );
    //    pWid->setWindowModality(Qt::ApplicationModal);
    //    pWid->setWindowModality(Qt::applica);
    //pWid->setAttribute(Qt::WA_ShowModal, true);
    if( pWid->isVisible() ) return ;
    else
    pWid->show();
}
