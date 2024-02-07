cmake_minimum_required(VERSION 3.21)
project(MediaStateT)

set(CMAKE_CXX_STANDARD 17)

#包含当前目录
#set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#设置qt的cmake编译目录，包含了qt模块编译需要的cmake文件
set(CMAKE_PREFIX_PATH "E:/Qt/6.6.1/mingw_64")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Quick
        Svg
        Xml
        REQUIRED)

#设置第三方头文件路径
include_directories("./include")
include_directories("./Libraries/FFMPEG/include")
include_directories("./Libraries/fftw-3.3.5-dll64")
include_directories("./Libraries/Json")
include_directories("./Libraries/Libcurl_7.78_dll_x64/include")
include_directories("./Libraries/PersonalLibraries/Netease_Music_info/include")
include_directories("Libraries/PersonalLibraries/FileBasicInformation/include")
include_directories("Libraries/QHotkey/QHotkey")
include_directories("Libraries/PersonalLibraries/StartWithSystem/include")
include_directories("Libraries/PersonalLibraries/AudioSource/include")

#引入库文件
link_directories(./Libraries/FFMPEG/lib)
link_directories(./Libraries/fftw-3.3.5-dll64)
link_directories(./Libraries/Libcurl_7.78_dll_x64/lib)

#包含需要编译的文件
set(SOURCE_FILES src/main.cpp)
set(RESOURCE_FILES qml/media_stateT.qml qml/PopWindow.qml qml/TextScroll.qml
        qml/PageAudioFrequency.qml qml/PageMenu.qml)
set(QRC_FILES media_stateT.qrc src/MtMediaInfo.cpp include/MtMediaInfo.h
        Libraries/PersonalLibraries/FileBasicInformation/FileBasicInformation.cpp
        Libraries/PersonalLibraries/Netease_Music_info/Netease_Music_info.cpp
        Libraries/PersonalLibraries/QQ_Music_info/QQ_Music_info.cpp
        Libraries/PersonalLibraries/StartWithSystem/StartWithSystem.cpp
        Libraries/PersonalLibraries/StartWithSystem/include/StartWithSystem.h
        Libraries/QHotkey/QHotkey/qhotkey.cpp
        Libraries/QHotkey/QHotkey/qhotkey_win.cpp
        Libraries/PersonalLibraries/AudioSource/AudioSource.cpp
        Libraries/PersonalLibraries/AudioSource/include/AudioSource.h src/FFTW_Call.cpp
        include/FFTW_Call.h src/MtFrequencyInfo.cpp include/MtFrequencyInfo.h src/InfoCommunication.cpp
        include/InfoCommunication.h
        src/MtBoardConnect.cpp
        include/MtBoardConnect.h
        src/MtFrequencyThreadInterface.cpp
        include/MtFrequencyThreadInterface.h
        src/InfoCommunicationThreadInterface.cpp
        include/InfoCommunicationThreadInterface.h
        src/MtFrequencyForQml.cpp
        include/MtFrequencyForQml.h
        src/Acrylic.cpp
        include/Acrylic.h
        include/WindowCompositionAttribute.h)
set(OTHER_FILES icon/icon_setting.rc)
# 加入WIN32取消显示console
add_executable(MediaStateT
        ${SOURCE_FILES} ${RESOURCE_FILES} ${QRC_FILES} ${OTHER_FILES})

target_link_libraries(MediaStateT
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Quick
        Qt6::Svg
        Qt6::Xml
        )
target_link_libraries(MediaStateT libcurl)
target_link_libraries(MediaStateT avcodec avdevice avfilter
        avformat avutil postproc swresample swscale)
target_link_libraries(MediaStateT libfftw3-3)