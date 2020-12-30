cmake_policy(VERSION 3.9)
cmake_minimum_required(VERSION 3.9)

project(cf10Cv310DevProClaffifyV1)

if(1)
    set (PclVision_VERSION_MAJOR 2)
    set (PclVision_VERSION_MINOR 202006261423)
endif()

set(CMAKE_CXX_STANDARD 11 )
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
message(${CMAKE_CXX_FLAGS})

#------------------------------------------qt5 must -----------------------------------
#注意，在一个大工程里，这几个开关一定要尽量放在前面打开，否则有可能会报无法生成ui文件的错误
set(CMAKE_AUTOMOC ON)#自动翻译信号与槽
set(CMAKE_AUTORCC ON)#自动翻译资源文件为cpp文件
set(CMAKE_AUTOUIC ON)#自动翻译界面文件为cpp文件
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#-------------------------------version---------------------------------------
#############################################
#option(USE_MYMATH "Use tutorial provided math implementation" ON)
##configure_file(TutorialConfig.h.in TutorialConfig.h)

#-----------------------------------------qt5-------------------------------
message( "(0)(lk)________ Qt5 _______:  ")
FIND_PACKAGE (QT5 REQUIRED)
INCLUDE_DIRECTORIES (${CMAKE_CURRENT_BINARY_DIR})
ADD_DEFINITIONS (${QT_DEFINITIONS})

find_package(Qt5Widgets)
set(CMAKE_PREFIX_PATH $ENV{QTDIR594})
find_package(Qt5 COMPONENTS Core Gui  Widgets Qml Quick REQUIRED)
find_package(Qt5Core)
find_package(Qt5Widgets)
find_package(Qt5Gui)
find_package(Qt5OpenGL)
find_package(Qt5Xml)
message( "  find   qt5   finish.\n\n")

#----------------------------------------header soruces -------------------------------
#set(HEADERS##    mainwindow.h    )
set(SOURCES    main.cpp    )
set(RESOURCES    VGRibbonWindow.qrc    )
#set(QMLS    main.qml )

# 搜集指定目录 . 和./MyClass 下的源文件，将输出结果列表储存到变量ALL_SOURCE中   MainApp
aux_source_directory(. vision_SOURCE)
aux_source_directory(${PROJECT_SOURCE_DIR}/QRibbon     vision_SOURCE)
aux_source_directory(${PROJECT_SOURCE_DIR}/Classify     vision_SOURCE)
aux_source_directory(${PROJECT_SOURCE_DIR}/CoreFunctions     vision_SOURCE)
aux_source_directory(${PROJECT_SOURCE_DIR}/UISet     vision_SOURCE)
message( "\n\n\n __________________ vision_SOURCE ____________________" )
message(  ${vision_SOURCE}  )
message( "\n\n\n" )

INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}
    "${PROJECT_SOURCE_DIR}/UISet"
    "${PROJECT_SOURCE_DIR}/CoreFunctions"
    "${PROJECT_SOURCE_DIR}/Classify"
    )

# 包含进目录 gen_pcd/
include_directories("${PROJECT_BINARY_DIR}")
#ui_mainwindow.h
link_directories("${PROJECT_BINARY_DIR}/lib")

include_directories("${PROJECT_SOURCE_DIR}/VisionUI")
message( "\n\n\n __________________PROJECT_SOURCE_DIR____________________" )
message(  ${PROJECT_SOURCE_DIR}  )
message( "\n\n\n")

message( "\n\n\n _________________ PROJECT_BINARY_DIR  __________________" )
message(  ${PROJECT_BINARY_DIR}  )
message("\n\n\n" )

#--------------------------------------------qt5 relate-------------------------------------------------
qt5_wrap_ui(ui_FILES *.ui   )
file(GLOB_RECURSE FORMS "./*.ui"   "./UISet/*.ui"   )


#set( Lib_dep_root    "D:/AwsOneDriver/aStudioLk/caffe10Cv310DevProClaffifyV1/dependence")
#set( Lib_dep_root    "D:/tmp/cf10Cv310DevProClaffifyV1/dependence")
set( Lib_dep_root    "D:/caffeBundle")
#                     D:\AwsOneDriver\AStudioLk\caffe10DevProClaffifyV1\dependence

#if( 0 )
#    ### ---[ 3rd party libraries
#    macro(find_boost)
#        if(PCL_ALL_IN_ONE_INSTALLER)
#            set(BOOST_ROOT "${PCL_ROOT}/3rdParty/Boost")
#        elseif(NOT BOOST_INCLUDEDIR)
#            set(BOOST_INCLUDEDIR "D:/win10/aspDepBig/Boost168/include/boost-1_68")
#        endif(PCL_ALL_IN_ONE_INSTALLER)
#        set(BOOST_ROOT "D:/win10/aspDepBig/Boost168")
#        set(BOOST_INCLUDEDIR "D:/win10/aspDepBig/Boost168/include/boost-1_68")
#        # use static Boost in Windows
#        if(WIN32)
#            set(Boost_USE_STATIC_LIBS ON)
#            set(Boost_USE_STATIC ON)
#            set(Boost_USE_MULTITHREAD )
#        endif(WIN32)
#        if(${CMAKE_VERSION} VERSION_LESS 2.8.5)
#            set(Boost_ADDITIONAL_VERSIONS
#                "1.47.0" "1.47" "1.46.1"
#                "1.46.0" "1.46" "1.45.0" "1.45" "1.44.0" "1.44" "1.43.0" "1.43")
#        else(${CMAKE_VERSION} VERSION_LESS 2.8.5)
#            set(Boost_ADDITIONAL_VERSIONS
#                "1.68.0" "1.68"
#                "1.68.0" "1.68" "1.67.0" "1.67" "1.66.0" "1.66" "1.65.1" "1.65.0" "1.65"
#                "1.64.0" "1.64" "1.63.0" "1.63" "1.62.0" "1.62" "1.61.0" "1.61" "1.60.0" "1.60"
#                "1.59.0" "1.59" "1.58.0" "1.58" "1.57.0" "1.57" "1.56.0" "1.56" "1.55.0" "1.55"
#                "1.54.0" "1.54" "1.53.0" "1.53" "1.52.0" "1.52" "1.51.0" "1.51"
#                "1.50.0" "1.50" "1.49.0" "1.49" "1.48.0" "1.48" "1.47.0" "1.47")
#        endif(${CMAKE_VERSION} VERSION_LESS 2.8.5)
#        # Disable the config mode of find_package(Boost)
#        set(Boost_NO_BOOST_CMAKE ON)
#        #    find_package(Boost 1.40.0 ${QUIET_} COMPONENTS system filesystem thread date_time iostreams serialization chrono)
#        find_package(Boost 1.68.0 ${QUIET_}  REQUIRED COMPONENTS system filesystem thread date_time iostreams serialization chrono)
#        set(BOOST_FOUND ${Boost_FOUND})
#        set(BOOST_INCLUDE_DIRS "${Boost_INCLUDE_DIR}")
#        set(BOOST_LIBRARY_DIRS "${Boost_LIBRARY_DIRS}")
#        set(BOOST_LIBRARIES ${Boost_LIBRARIES})
#        if(WIN32 AND NOT MINGW)
#            set(BOOST_DEFINITIONS ${BOOST_DEFINITIONS} -DBOOST_ALL_NO_LIB)
#        endif(WIN32 AND NOT MINGW)
#    endmacro(find_boost)
#    find_boost()
#    message( "\n_____________________________\n")
#    #message( ${BOOST_LIBRARIES})
#    INCLUDE_DIRECTORIES( ${BOOST_INCLUDEDIR}  )
#    #INCLUDE_DIRECTORIES( ${BOOST_INCLUDEDIR}  )
#    LINK_DIRECTORIES("D:/win10/aspDepBig/Boost168/lib")
#endif()


##D:/win10/pcl181Orig/3rdParty/Boost/include/boost-1_64
#SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")
#set(BOOST_INCLUDEDIR "${Lib_dep_root}/libraries_v140_x64_py35_1.1.0/libraries/include/boost-1_61")
#set(BOOST_DIR "${Lib_dep_root}/libraries_v140_x64_py35_1.1.0/libraries")
#set(Boost_LIBRARY_DIR "${Lib_dep_root}/libraries_v140_x64_py35_1.1.0/libraries/lib")
##find_package(Boost REQUIRED COMPONENTS       filesystem       thread      )
#find_package(Boost   COMPONENTS       filesystem       thread      )
#if(NOT Boost_FOUND)
#    message("Not found Boost")
#endif()
#INCLUDE_DIRECTORIES( ${BOOST_INCLUDEDIR}  )
#LINK_DIRECTORIES(  "${Boost_LIBRARY_DIR}")
##LINK_LIBRARIES
#LINK_DIRECTORIES(  "D:/AwsOneDriver/AStudioLk/caffe10DevProClaffifyV1/dependence/libraries_v140_x64_py35_1.1.0/libraries/lib")
#message( "__________________________________________" )
#message( "BOOST_LIBRARIES: " )
##message( ${BOOST_LIBRARIES} )


#F:\win10\pcl191X64\thirdpartx64\jsoncpp-master\x64
#------------------- jsoncpp ----------------------------------
message( "(5.01)(lk)________ jsoncpp _______:  ")
find_package(jsoncpp   REQUIRED PATHS "${Lib_dep_root}/jsoncpp-master/x64"
    NO_DEFAULT_PATH
             NO_PACKAGE_ROOT_PATH
             NO_CMAKE_PATH
             NO_CMAKE_ENVIRONMENT_PATH
             NO_SYSTEM_ENVIRONMENT_PATH
             NO_CMAKE_PACKAGE_REGISTRY
             NO_CMAKE_BUILDS_PATH # Deprecated; does nothing.
             NO_CMAKE_SYSTEM_PATH
             NO_CMAKE_SYSTEM_PACKAGE_REGISTRY
    )
set( jsoncpp_INCLUDE_DIRS    "${Lib_dep_root}/jsoncpp-master/x64/include" )
link_directories(   "${Lib_dep_root}/jsoncpp-master/x64/lib"  )
include_directories(${jsoncpp_INCLUDE_DIRS})
message( "jsoncpp info(lk):  ")
message( ${jsoncpp_INCLUDE_DIRS})
#message( ${jsoncpp_LIBRARY_DIRS})
message( "jsoncpp find finish.\n\n")


####################################################################################
# zlib
##D:/caffeBundle/libraries_v140_x64_py35_1.1.0/libraries/lib/caffezlib.lib
#set(ZLIB_LIBRARY  "D:/caffeBundle/libraries_v140_x64_py35_1.1.0/libraries/lib/caffezlib.lib" )
#set(zlib_DIR   "D:/caffeBundle/libraries_v140_x64_py35_1.1.0/libraries/cmake" )
#find_package(  zlib   PATHS "D:/caffeBundle/libraries_v140_x64_py35_1.1.0/libraries/cmake" )

# boost
find_package(  boost REQUIRED
#    PATHS "${Lib_dep_root}/libraries_v140_x64_py35_1.1.0/libraries"
#        NO_DEFAULT_PATH
#                 NO_PACKAGE_ROOT_PATH
#                 NO_CMAKE_PATH
#                 NO_CMAKE_ENVIRONMENT_PATH
#                 NO_SYSTEM_ENVIRONMENT_PATH
#                 NO_CMAKE_PACKAGE_REGISTRY
#                 NO_CMAKE_BUILDS_PATH # Deprecated; does nothing.
#                 NO_CMAKE_SYSTEM_PATH
#                 NO_CMAKE_SYSTEM_PACKAGE_REGISTRY
    )
INCLUDE_DIRECTORIES("${Lib_dep_root}/libraries_v140_x64_py35_1.1.0/libraries/include/boost-1_61")
LINK_DIRECTORIES("${Lib_dep_root}/libraries_v140_x64_py35_1.1.0/libraries/lib")


## gflags
#find_package(   gflags REQUIRED PATHS  "D:/win10/aspDep14/gflags-2.2.2/x64Vs14"    )
#INCLUDE_DIRECTORIES("D:/win10/aspDep14/gflags-2.2.2/x64Vs14/include")
#LINK_DIRECTORIES("D:/win10/aspDep14/gflags-2.2.2/x64Vs14Shared/lib")

find_package(   gflags REQUIRED PATHS  "${Lib_dep_root}/libraries_v140_x64_py35_1.1.0/libraries"
    NO_DEFAULT_PATH
             NO_PACKAGE_ROOT_PATH
             NO_CMAKE_PATH
             NO_CMAKE_ENVIRONMENT_PATH
             NO_SYSTEM_ENVIRONMENT_PATH
             NO_CMAKE_PACKAGE_REGISTRY
             NO_CMAKE_BUILDS_PATH # Deprecated; does nothing.
             NO_CMAKE_SYSTEM_PATH
             NO_CMAKE_SYSTEM_PACKAGE_REGISTRY
    )
INCLUDE_DIRECTORIES("${Lib_dep_root}/libraries_v140_x64_py35_1.1.0/libraries/include")
LINK_DIRECTORIES("${Lib_dep_root}/libraries_v140_x64_py35_1.1.0/libraries/lib")


## glog
#find_package(   glog REQUIRED PATHS  "D:/win10/aspDep14/glog-0.4.0/x64Vs14Shared"    )
#INCLUDE_DIRECTORIES("D:/win10/aspDep14/glog-0.4.0/x64Vs14Shared/include")
#LINK_DIRECTORIES("D:/win10/aspDep14/glog-0.4.0/x64Vs14Shared/lib")


find_package(   glog REQUIRED PATHS  "${Lib_dep_root}/libraries_v140_x64_py35_1.1.0/libraries"
    NO_PACKAGE_ROOT_PATH
    NO_CMAKE_PATH
    NO_CMAKE_ENVIRONMENT_PATH
    NO_SYSTEM_ENVIRONMENT_PATH
    NO_CMAKE_PACKAGE_REGISTRY
    NO_CMAKE_BUILDS_PATH # Deprecated; does nothing.
    NO_CMAKE_SYSTEM_PATH
    NO_CMAKE_SYSTEM_PACKAGE_REGISTRY
    )
INCLUDE_DIRECTORIES("${Lib_dep_root}/libraries_v140_x64_py35_1.1.0/libraries/include")
LINK_DIRECTORIES("${Lib_dep_root}/libraries_v140_x64_py35_1.1.0/libraries/lib")


#// cuad
find_package(   cuda  REQUIRED
#    PATHS  "${Lib_dep_root}/CUDA/v8.0"
#    NO_PACKAGE_ROOT_PATH
#    NO_CMAKE_PATH
#    NO_CMAKE_ENVIRONMENT_PATH
#    NO_SYSTEM_ENVIRONMENT_PATH
#    NO_CMAKE_PACKAGE_REGISTRY
#    NO_CMAKE_BUILDS_PATH # Deprecated; does nothing.
#    NO_CMAKE_SYSTEM_PATH
#    NO_CMAKE_SYSTEM_PACKAGE_REGISTRY
    )
set(CUDA_SDK_ROOT_DIR  "${Lib_dep_root}/CUDA/v8.0"   )
set(CUDA_TOOLKIT_ROOT_DIR  "${Lib_dep_root}/CUDA/v8.0"   )
INCLUDE_DIRECTORIES("${Lib_dep_root}/CUDA/v8.0/include")
LINK_DIRECTORIES("${Lib_dep_root}/CUDA/v8.0/lib/x64")


#//cv
#D:/AwsOneDriver/AStudioLk/caffe10Cv310DevProClaffifyV1/dependence/cv310Vs15Cuda8installAllFull
#find_package(  OpenCV  PATHS  "${Lib_dep_root}/libraries_v140_x64_py35_1.1.0/libraries/x64/vc14/lib"  )
find_package(  OpenCV  PATHS  "${Lib_dep_root}/cv310Vs2015DebugReleaseNoCa"
    NO_PACKAGE_ROOT_PATH
    NO_CMAKE_PATH
    NO_CMAKE_ENVIRONMENT_PATH
    NO_SYSTEM_ENVIRONMENT_PATH
    NO_CMAKE_PACKAGE_REGISTRY
    NO_CMAKE_BUILDS_PATH # Deprecated; does nothing.
    NO_CMAKE_SYSTEM_PATH
    NO_CMAKE_SYSTEM_PACKAGE_REGISTRY
    )
INCLUDE_DIRECTORIES (   ${OpenCV_INCLUDE_DIRS} )
INCLUDE_DIRECTORIES (   ${OpenCV_INSTALL_PATH} )



find_package(   HDF5  REQUIRED PATHS  "${Lib_dep_root}/libraries_v140_x64_py35_1.1.0/libraries"
    NO_PACKAGE_ROOT_PATH
    NO_CMAKE_PATH
    NO_CMAKE_ENVIRONMENT_PATH
    NO_SYSTEM_ENVIRONMENT_PATH
    NO_CMAKE_PACKAGE_REGISTRY
    NO_CMAKE_BUILDS_PATH # Deprecated; does nothing.
    NO_CMAKE_SYSTEM_PATH
    NO_CMAKE_SYSTEM_PACKAGE_REGISTRY
    )
INCLUDE_DIRECTORIES("${Lib_dep_root}/libraries_v140_x64_py35_1.1.0/libraries/include")
LINK_DIRECTORIES("${Lib_dep_root}/libraries_v140_x64_py35_1.1.0/libraries/lib")


find_package(   LMDB  REQUIRED PATHS  "${Lib_dep_root}/libraries_v140_x64_py35_1.1.0/libraries"    )
INCLUDE_DIRECTORIES("${Lib_dep_root}/libraries_v140_x64_py35_1.1.0/libraries/include")
LINK_DIRECTORIES("${Lib_dep_root}/libraries_v140_x64_py35_1.1.0/libraries/lib")


set(levelDB_DIR  "${Lib_dep_root}/libraries_v140_x64_py35_1.1.0/libraries/cmake"  )
find_package(   levelDB  REQUIRED PATHS  "${Lib_dep_root}/libraries_v140_x64_py35_1.1.0/libraries"    )
INCLUDE_DIRECTORIES("${Lib_dep_root}/libraries_v140_x64_py35_1.1.0/libraries/include")
LINK_DIRECTORIES("${Lib_dep_root}/libraries_v140_x64_py35_1.1.0/libraries/lib")


# caffe
set(caffe_DIR  "${Lib_dep_root}/installCaffeOFull/share/Caffe"
    NO_PACKAGE_ROOT_PATH
    NO_CMAKE_PATH
    NO_CMAKE_ENVIRONMENT_PATH
    NO_SYSTEM_ENVIRONMENT_PATH
    NO_CMAKE_PACKAGE_REGISTRY
    NO_CMAKE_BUILDS_PATH # Deprecated; does nothing.
    NO_CMAKE_SYSTEM_PATH
    NO_CMAKE_SYSTEM_PACKAGE_REGISTRY
    )
find_package(  caffe REQUIRED PATHS  "${Lib_dep_root}/installCaffeOFull"    )
include_directories(  "${Lib_dep_root}/installCaffeOFull/include"  )
LINK_DIRECTORIES (  "${Lib_dep_root}/installCaffeOFull/lib" )
# ${Caffe_LIBRARIES}


####################################################################################
####################################################################################
####################################################################################


######################################生成exe#######################################################
if( 1  )
    set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
    add_executable(${PROJECT_NAME}    MACOSX_BUNDLE ${SOURCES}   ${vision_SOURCE}   ${FORMS}   ${RESOURCES}  ) # ${RESOURCES}
    if(  1 )
        target_link_libraries(   ${PROJECT_NAME}  PUBLIC
            Qt5::Core Qt5::Widgets Qt5::Gui Qt5::Qml Qt5::Quick
            ${PCL_LIBRARIES}            # ${VTK_LIBRARIES}
            ${BOOST_LIBRARIES}
#            D:\AwsOneDriver\cf10Cv310DevProClaffifyV1\dependence
            ${Lib_dep_root}/libraries_v140_x64_py35_1.1.0/libraries/lib/boost_date_time-vc140-mt-1_61.lib
            boost_date_time-vc140-mt-1_61.lib
            ${OpenCV_LIBRARIES}  ${OpenCV_LIBS}
            ${Caffe_LIBRARIES}
#                D:/win10/aspDep14/gflags-2.2.2/x64Vs14/lib/gflags.lib
#                   glog

            ${Lib_dep_root}/libraries_v140_x64_py35_1.1.0/libraries/lib/gflags.lib
           ${Lib_dep_root}/libraries_v140_x64_py35_1.1.0/libraries/lib/glog.lib

            boost_atomic-vc140-mt-1_61     boost_chrono-vc140-mt-1_61
            boost_filesystem-vc140-mt-1_61   boost_iostreams-vc140-mt-1_61

            ${EXTRA_LIBS}
            ${OpenCV_LIBRARIES}            #  ${jsoncpp_LIBRARIES}
            jsoncpp            #   ${tinyxml2_LIBRARIES}
            ${log4cplus_LIBRARIES}            ${glog_libraries}
            ${GLOG_LIB}#            camerad             #CameraLaserLine  #            ${lib_KenenceLaserLine}
            )
    endif()
endif()
message( "(6)(lk)__________ project ___________:  "  )
message(  "project info(lk):  "  )
message(   ${PROJECT_NAME}  )
#message(   ${HEADERS}  )
message(   ${SOURCES}   )
message(   ${vision_SOURCE}  )
message(   ${FORMS}   )


#------------------------------------------- version ------------------------------------------------
include_directories(${PROJECT_BINARY_DIR}    ${OpenCL_INCLUDE_DIRS}    )


#---------------------------------------------------------------------------------
set(CMAKE_INSTALL_PREFIX  "${PROJECT_BINARY_DIR}/install")
## Binaries
install (TARGETS  ${PROJECT_NAME}     DESTINATION bin)


#######################################################
#Add some multithreaded build support
MARK_AS_ADVANCED(MULTITHREADED_BUILD)
set(MULTITHREADED_BUILD   8  CACHE STRING "How many threads are used to build the project")
if(MULTITHREADED_BUILD)
    if(${CMAKE_GENERATOR} MATCHES "Unix Makefiles")
        message(STATUS ${CMAKE_BUILD_TOOL})
        set(CMAKE_MAKE_PROGRAM  "${CMAKE_MAKE_PROGRAM} -j${MULTITHREADED_BUILD}")
        message(STATUS "Added arguments to CMAKE_BUILD_TOOL: ${CMAKE_MAKE_PROGRAM}")
    elseif(MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}/MP")
        message(STATUS "Added parallel build arguments to CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
    endif()
endif()
#######################################################


