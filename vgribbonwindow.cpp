#include "vgribbonwindow.h"
#include "ui_vgribbonwindow.h"

#include <QShortcut>

#include "QRibbon/QRibbon.h"
#pragma execution_character_set("utf-8")
VGRibbonWindow *  VGRibbonWindow::instance = NULL;

VGRibbonWindow::VGRibbonWindow(QWidget *parent)
    : QMainWindow(parent){
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
        if ( full )        {
            maximized = isMaximized();
        }
        else if ( maximized && isMaximized() )        {
            return;
        }

        if ( full && !isMaximized() || !full && isMaximized() )        {
            if (isMaximized())            {
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

    QString  imgFile = "D:\\images/我的.jpg";  //  "D:\\images/a1.jpg"
    m_cv_img = cv::imread( imgFile.toLocal8Bit().data(),  cv::IMREAD_UNCHANGED  );
    repaint();
}

VGRibbonWindow::~VGRibbonWindow(){
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
        displayResult(this->m_cv_img, this->ui->label);

        //--------------------------
        if( 0 )
        {
            QPainter painter(this);
            QPixmap pix;
            painter.translate(0, 0);   if(0)
                pix.load("D:\imageHeben/hb (1).jpg");//加载图片地址 可以是资源文件
            pix =  cvMatToQPixmap(this->m_cv_img);
            if(0) painter.drawPixmap(0, 0, width(), height(), pix);//绘制图片 横坐标、纵坐标、宽度、高度
            painter.drawPixmap(0, 0,   pix);
        }

        //--------------  openGLWidget
        if( 1 )
        {
            QPainter painter(this->ui->openGLWidget );
            QPixmap pix;
            painter.translate(0, 0);
            if(0)             pix.load("D:\\dataImages--/3.jpg");//加载图片地址 可以是资源文件
            pix =  cvMatToQPixmap(this->m_cv_img);
            if( 0 ) painter.drawPixmap(0, 0, width(), height(), pix);//绘制图片 横坐标、纵坐标、宽度、高度


            int with =  this->ui->openGLWidget->width ();//要显示的宽度
            int height = this->ui->openGLWidget->height ();  // IgnoreAspectRatio
            QPixmap fitpixmap = pix.scaled(with, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 饱满填充
            //QPixmap fitpixmap = pixmap.scaled(with, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放



            painter.drawPixmap(0, 0,   fitpixmap);
            //            painter.set
            //            this->ui->openGLWidget->
            if(0)          this->ui->openGLWidget->resize( this->ui->openGLWidget ->size());
        }

        if( 0 )
        {
            QImage img =     cvMatToQImage(this->m_cv_img);

            QPainter painter(this->ui->openGLWidget );
            //    QPixmap pix;
            painter.translate(0, 0);
            //    if(0)             pix.load("D:\\dataImages--/3.jpg");//加载图片地址 可以是资源文件
            //    pix =  cvMatToQPixmap(this->m_cv_img);
            //      if( 0 ) painter.drawPixmap(0, 0, width(), height(), pix);//绘制图片 横坐标、纵坐标、宽度、高度
            //    painter.drawPixmap(0, 0,   pix);
            //            painter.set
            //            this->ui->openGLWidget->
            //if(0)          this->ui->openGLWidget->resize( this->ui->openGLWidget ->size());
            painter.drawImage(0,0, img );
        }
    }
}

//---------------------------------------小工具------------------------------------------------------
#include <QFileInfo>
#include <QFileDialog>
#if 0
void VGRibbonWindow::tool_selectFile(std::string title, const QString &p_filter, std::string nameFunc,
                                     std::string &fileNamefull, std::string & fileDir, QString &qFileNameFull) {
    printLogToTextBox("\n\n\n\n\n-------------------------------><--------------------------------");
    //    QPushButton *btn = (QPushButton *) sender();  // 获取到了发送该信号按钮的指针
    //    this->printLogToTextBox(("you clicked button : " + btn->text()).toStdString());
    //    nameFunc = btn->text().toStdString();
    std::string pathPast;
    if (fileDir.empty()) {
        printLogToTextBox("tool_selectFile: failure to get filePath from ini file.");
        fileDir = "C:/Users/";
    } else {
        this->ui->textBrowser->append(fileDir.c_str());
    }
    pathPast = fileDir  ;
    QString file_name;
    QString file_path = QString::fromStdString(pathPast);
    QFileInfo fi;
    QString fileName = QFileDialog::getOpenFileName(this,  QString::fromStdString(title),
                                                    file_path,   p_filter);
    if (fileName.isNull() || fileName.isEmpty())
        return;
    qFileNameFull = fileName;
    QTextCodec *code = QTextCodec::codecForName("utf-8");//解决中文路径问题  "GB2312"
    fileNamefull = code->fromUnicode(fileName).data();
    fi = QFileInfo(fileName);
    file_name = fi.fileName();
    file_path = fi.absolutePath();
    fileDir = code->fromUnicode(file_path).data();
    this->printLogToTextBox("tool_selectFile: fileNamefull = " + fileNamefull);

    this->printLogToTextBox("tool_selectFile: fileName.toStdString() = " + fileName.toStdString());
    this->printLogToTextBox(fileName.toStdString().c_str());
    this->printLogToTextBox("tool_selectFile: file_path.toStdString() = " + file_path.toStdString());
    this->printLogToTextBox("tool_selectFile: qFileNameFull.toStdString() = " + qFileNameFull.toStdString());
}
#endif



//---------------------------------------小工具------------------------------------------------------
void VGRibbonWindow::tool_selectFile(std::string title, const QString &p_filter, std::string nameFunc,
                                     std::string &fileNamefull, std::string &filePath, QString &qFileNameFull) {
    printLogToTextBox("\n\n\n\n\n-------------------------------><--------------------------------");
    //    QPushButton *btn = (QPushButton *) sender();  // 获取到了发送该信号按钮的指针
    //    this->printLogToTextBox(("you clicked button : " + btn->text()).toStdString());
    //    nameFunc = btn->text().toStdString();
    std::string pathPast;
    //    pathPast = ini_global.GetString("kernel", nameFunc, pathPast);     //   printLogToTextBox("tool_selectFile: pathPast = " + pathPast);
    if (filePath.empty()) {
        printLogToTextBox("tool_selectFile: failure to get filePath from ini file.");
        filePath = "C:/Users/";
    } else {
        this->ui->textBrowser->append(filePath.c_str());
        //printLogToTextBox("tool_selectFile: get filePath from ini file: " + pathPast);
    }
    pathPast = filePath ;
    QString file_name;
    QString file_path;// = QString::fromStdString(pathPast);
    QFileInfo fi;
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    QString::fromStdString(title), file_path,  p_filter);
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
    //    log4cplus::tcout << "log4cplus-tcout-  tool_selectFile: fileNamefull = " << fileNamefull << std::endl;
    //    log4cplus::tcout << "log4cplus-tcout-  tool_selectFile: fileName.toStdString() = " << fileName.toStdString()
    //                     << std::endl;
    //    ini_global.SetString("kernel", nameFunc, file_path.toStdString());
    //    ini_global.SetString("kernel", nameFunc + std::string("Full"), fileName.toStdString());
    //    ini_global.WriteINI(ini_global_path);
    //printLogToTextBox("select file fileNamefull = " + fileNamefull);
}



void VGRibbonWindow::tool_selectFile_save_path(std::string title, const QString &p_filter, std::string nameFunc,
                                               std::string &fileNamefull, std::string &fileDIR, QString &qFileNameFull) {
    printLogToTextBox("\n\n\n\n\n-------------------------------><--------------------------------");
    if (fileDIR.empty()) {
        printLogToTextBox("tool_selectFile: failure to get filePath from ini file.");
        fileDIR = "C:/Users/";
    } else {
        this->ui->textBrowser->append(fileDIR.c_str());
        // printLogToTextBox("tool_selectFile: get filePath from ini file: " + pathPast);
    }
    std::string pastDir;
    pastDir =  fileDIR ;
    QString file_name;
    QString file_path = QString::fromStdString(pastDir);
    QFileInfo fi;
    QString fileName = QFileDialog::getSaveFileName(this,  QString::fromStdString(title), file_path,  p_filter);

    if (fileName.isNull() || fileName.isEmpty())
        return;
    qFileNameFull = fileName;
    QTextCodec *code = QTextCodec::codecForName("utf-8");//解决中文路径问题
    fileNamefull = code->fromUnicode(fileName).data();
    fi = QFileInfo(fileName);
    file_name = fi.fileName();
    file_path = fi.absolutePath();
    fileDIR = code->fromUnicode(file_path).data();

    this->printLogToTextBox("tool_selectFile: fileNamefull = " + fileNamefull);
    this->printLogToTextBox("tool_selectFile: fileName.toStdString() = " + fileName.toStdString());
    this->printLogToTextBox(fileName.toStdString().c_str());
    this->printLogToTextBox("tool_selectFile: qFileNameFull.toStdString() = " + qFileNameFull.toStdString());
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
    std:: cout<<  words <<    std::endl;
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
    return;
#endif
}

#include "QDebug"
#include "QDebug"
void VGRibbonWindow::on_actionOpen_triggered(){
#if 1
    std::string filePathFull;
    QString fileName;
    tool_selectFile(("select range iamge file."),tr("allfileType(*);;图片文件(*png *jpg *pcd *ply *png);;pcd文件(*pcd *ply *png);;"
                                                    "本本文件(*txt)"),  "path_rangeImage", filePathFull, this->m_fileDir, fileName  );
    if (filePathFull.empty())
        return;
#endif
    //------------------
#if 0
    //    QString file_name;
    QString file_path;// = QString::fromStdString(pathPast);
    //    QFileInfo fi;
    QString fileName = QFileDialog::getOpenFileName(this,  tr("select range iamge file请选择图片"), file_path,
                                                    tr("allfileType(*);;图片文件(*png *jpg *pcd *ply *png);;pcd文件(*pcd *ply *png);;本本文件(*txt)")
                                                    //  , ReadOnly
                                                    );
    qDebug()<< "qDebug--fileName = "<<   fileName   ;
    qDebug()<< "qDebug--file_path = "<<   file_path   ;
#endif
    this->printLogToTextBox_q(  QString("QString---on_actionOpen_triggered--fileName = ")+fileName  );
    this->printLogToTextBox( "on_actionOpen_triggered--fileName = "+ fileName.toStdString() );

    cv::Mat depthImage ;//= cv::imread(fileName.toStdString(), cv::IMREAD_UNCHANGED);//读取图片数据
    //    if ( depthImage.data) {
    //        this->printLogToTextBox( QString::fromUtf8("read ok.001").toStdString());
    //    }
    //    QString::fromUtf8(file_name.data()).toStdString() ;
    //    depthImage = cv::imread( fileName.toUtf8().data() , cv::IMREAD_UNCHANGED);//读取图片数据
    depthImage = cv::imread( fileName.toLocal8Bit().data() , cv::IMREAD_UNCHANGED);//读取图片数据
    if ( depthImage.data) {
        this->printLogToTextBox( QString::fromUtf8("read ok.002").toStdString());
    }

    //    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    //    //    QTextCodec::setCodecForTr(codec);
    //    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale()); //设置GBK到本地
    //        QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    //    codec->fromUnicode(qFileNameFull ).data();
    //    depthImage = cv::imread(codec->fromUnicode(fileName ).data() , cv::IMREAD_UNCHANGED);//读取图片数据
    //    depthImage = cv::imread(fileName.toLocal8Bit().data() , cv::IMREAD_UNCHANGED);//读取图片数据
    //    if ( depthImage.data) {
    //        this->printLogToTextBox( QString::fromUtf8("read ok.003").toStdString());
    //    }
    //    depthImage = cv::imread(fileName.toLatin1().data() , cv::IMREAD_UNCHANGED);//读取图片数据
    if ( depthImage.data) {
        this->printLogToTextBox( QString::fromUtf8("read ok.004").toStdString());
    }
    if (depthImage.cols <= 0 || !depthImage.data) {
        this->printLogToTextBox( QString::fromUtf8("read iamge failure.").toStdString());
        return;
    } else {
        m_cv_img = depthImage;
        //print
        this->printLogToTextBox(QString::fromUtf8("read image ok.").toStdString());
        print_cvMat_info(depthImage);
        repaint();
    }
}

//打开分类对话框
#include "formclassify.h"
void VGRibbonWindow::on_actionclassify_triggered()
{
    QWidget *pWid =  FormClassify::getInstance();//new FormClassify( );
    //pWid->setAttribute(Qt::WA_ShowModal, true);
    if( pWid->isVisible() ) return ;
    else     pWid->show();
}
