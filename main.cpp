#include "vgribbonwindow.h"

#include <QApplication>

#include <iomanip>
#include <thread>
#include <mutex>
#include <iomanip>
#include <chrono>
#include <time.h>

/*
 * 判断是否是当天，时区问题内部已考虑
 * @param    timeStamp        当前时间戳(单位s)
 * @return   0                今天
 *           >0               过去几天
 *           <0               将来几天
 */
int
checkTimestamp(const std::time_t timeStamp)
{
    static std::time_t sLastTimestamp = 0;
    if (sLastTimestamp == 0) {
        static std::once_flag oc;
        std::call_once(oc, [&]()
        {
            tzset();//刷新时区
            sLastTimestamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        });
    }
    std::time_t   timezone = 1970;
    const int lastDay = (sLastTimestamp -  timezone)/86400;//转换到当前时区，自1970年来的天数
    const int curDay = (timeStamp - timezone)/86400;
    sLastTimestamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    return (curDay - lastDay);
}

time_t NowTime()
{
    time_t t_Now = time(0);
    struct tm* tm_Now = localtime(&t_Now);
    tm_Now->tm_hour =0;
    tm_Now->tm_min = 0;
    tm_Now->tm_sec = 0;
    return  mktime(tm_Now);
}

bool IsValidTime(const time_t& AEndTime, const time_t& ANowTime )
{
    return (AEndTime >= ANowTime);
}


time_t str_to_time_t(const  std:: string& ATime, const  std::string& AFormat="%d-%d-%d")
{
    struct tm tm_Temp;
    time_t time_Ret;
    try
    {
        int i = sscanf(
                    ATime.c_str(), AFormat.c_str(),// "%d/%d/%d %d:%d:%d" ,
                    &(tm_Temp.tm_year),
                    &(tm_Temp.tm_mon),
                    &(tm_Temp.tm_mday),
                    &(tm_Temp.tm_hour),
                    &(tm_Temp.tm_min),
                    &(tm_Temp.tm_sec),
                    &(tm_Temp.tm_wday),
                    &(tm_Temp.tm_yday)
                    );

        tm_Temp.tm_year -= 1900;
        tm_Temp.tm_mon --;
        tm_Temp.tm_hour=0;
        tm_Temp.tm_min=0;
        tm_Temp.tm_sec=0;
        tm_Temp.tm_isdst = 0;
        time_Ret = mktime(&tm_Temp);
        return time_Ret;
    } catch(...) {
        return 0;
    }
}


bool  ifValideCheck(std::  string sEndTime)
{
    //    std::  string sEndTime ="2020-08-24";
    std::   string sTemp;
    time_t t_Now = NowTime();
    time_t t_End = str_to_time_t(sEndTime);
    if (IsValidTime(t_End, t_Now)) {
        sTemp = "有效日期";
    } else {
        sTemp = "时间过期";
        return  false;
    }
    return  true ;
}

#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>
#include <QTextCodec>

#pragma execution_character_set("utf-8")


int main(int argc, char *argv[])
{
    //----------------------------------------------
    std:: time_t myt=time(NULL);
    std:: time_t t;
    time( &t );
    checkTimestamp( t ) ;
    if(  !  ifValideCheck("2022-09-28"))
    {
        std::cout<< "product has been out of valid date.please contact to the server provider."<<std::endl;
        return  -1;
    }
    //----------------------------------------------
    //中文支持
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QFont font;
    font.setPointSize(16); //实际上是16的字号，但设成16却不行
    font.setFamily(("wenquanyi"));
    font.setBold(false);

#ifdef  onlyRunOnWindows
    AllocConsole();//为当前的窗口程序申请一个Console窗口
    freopen("CONOUT$", "a+", stdout);
#endif



    // Initialize Google's logging library.
    google::InitGoogleLogging(argv[0]);
    google::SetLogDestination(google::GLOG_INFO ,"D:/out/a_QRibbonMasterDemoModyCMakeClassify.txt");
    FLAGS_log_dir = "D:/out";
    FLAGS_logtostderr  = false;
    FLAGS_alsologtostderr = false;// //打印到日志同时是否打印到控制台
    LOG(INFO) <<"a_QRibbonMasterDemoModyCMakeClassify start.  " << std::endl;



    QApplication a(argc, argv);
#if 0
    VGRibbonWindow w;
    w.show();
#endif

    VGRibbonWindow *pw = VGRibbonWindow::getInstance();
    pw->show();

    return a.exec();
}
