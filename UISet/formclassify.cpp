#include "formclassify.h"
#include "ui_formclassify.h"

#pragma execution_character_set("utf-8")

FormClassify * FormClassify::instance=NULL;

FormClassify::FormClassify(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormClassify)
{
    ui->setupUi(this);
}

FormClassify::~FormClassify()
{
    delete ui;
}


#include "vgribbonwindow.h"
#include <QFileDialog>
//----------------------------------------------------------
void FormClassify::on_selClass01Dir_clicked()
{
    //getExistingDirectory
    QString dirpath = QFileDialog::getExistingDirectory(this, "选择目录", "./", QFileDialog::ShowDirsOnly) ;
    this->ui->lineEdit->setText( dirpath ) ;

    VGRibbonWindow*  pwin = VGRibbonWindow::getInstance();
    pwin->printLogToTextBox_q(dirpath  );
}

void FormClassify::on_selClass02Dir_clicked()
{
    QString dirpath = QFileDialog::getExistingDirectory(this, "选择目录", "./", QFileDialog::ShowDirsOnly) ;
    this->ui->lineEdit_2->setText( dirpath ) ;
}


#include  <iostream>
#include  <string>
#include <boost/filesystem.hpp>
int  getFiles(QString& rootPath,
              std::vector<std::string> &ret,
              std::vector<std::string> &name)
{
    if( rootPath.isEmpty()) return   -1;
    namespace fs = boost::filesystem;
    fs::path fullpath (rootPath.toLocal8Bit().data());
    fs::recursive_directory_iterator end_iter;
    for(fs::recursive_directory_iterator iter(fullpath);iter!=end_iter;iter++)
    {
        try
        {
            if (fs::is_directory( *iter ) )
            {
                std::cout<<*iter << "is dir" << std::endl;
                ret.push_back(iter->path().string());
            }
            else
            {
                std:: string file = iter->path().string();
                ret.push_back(iter->path().string());
                fs::path filePath(file);
                name.push_back(filePath.stem().string());
            }
        }
        catch ( const std::exception & ex )
        {
            std::cerr << ex.what() << std::endl;
            continue;
        }
    }
    return  0;
}

#include "vgribbonwindow.h"
#include  "opencv2/opencv.hpp"
void testLocal(QString imgPath)
{
    std:: cout<<"imgPath = "<<  imgPath.toStdString()<< std::endl;
    std::vector<std::string> nameWithPath;//绝对路径
    std::  vector<std::string> imgName;//文件名字
    int res =   getFiles(imgPath, nameWithPath, imgName);
    if(res<0) return  ;
    std:: cout<<"nameWithPath.size() = "<<  nameWithPath.size() << std::endl;
    for(int i = 0; i < nameWithPath.size(); i++)
    {
         std:: cout  <<  nameWithPath[i]<<"," ;// std::endl;
//         continue;
        cv:: Mat image =  cv::  imread(nameWithPath[i]);
        if( !image.data )  {
             std:: cout  <<   "(读图错误，没有数据.)" << std::endl;
            continue;
        }
        VGRibbonWindow*  pwin = VGRibbonWindow::getInstance();
        pwin->m_cv_img = image;
        pwin->repaint( ) ;
    }
    std:: cout<<  std::endl;
}


//train
void FormClassify::on_train_clicked()
{
//    std::string dirClass01 = this->ui->lineEdit->text().toStdString();
//    testLocal(dirClass01);

    QString dirClass01 = this->ui->lineEdit->text();//.toStdString();
    testLocal(dirClass01);
}


//----------------------------------------------------------
void FormClassify::on_selTestDir_clicked()
{
    QString dirpath = QFileDialog::getExistingDirectory(this, "选择目录", "./", QFileDialog::ShowDirsOnly) ;
    this->ui->lineEdit_3->setText( dirpath ) ;
}

//test
void FormClassify::on_test_clicked()
{

}
