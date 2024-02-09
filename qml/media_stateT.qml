import QtQuick
import QtQuick.Controls
import QtQuick.Window
import Qt5Compat.GraphicalEffects
import Qt.labs.platform

import qt.txwh.MT_info_get 1.0

Item{
    //绘制窗口，然后传到PopWindow模块的Loader里
    Component{
        id:window_draw

        Rectangle{
            id:bk_rectangle
            width:200
            height:70
            radius:10
            color: Qt.rgba(0.8,0.8,0.8,0.95)

            Image{
                id:img_background
                width:bk_rectangle.width - 40
                height:bk_rectangle.height - 16
                source:"/icon/MtIcon.jpg"
                smooth: true
                mipmap:true
                cache:false
                visible:false
                fillMode: Image.PreserveAspectCrop
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter : parent.horizontalCenter
                anchors.right: parent.right
                anchors.rightMargin: 6
            }

            Rectangle {
                id: img_bck_mask
                width: img_background.width
                height: img_background.height
                radius: 10
                color: "red"
                visible: false
            }

            OpacityMask {
                anchors.fill: img_background
                source: img_background
                maskSource: img_bck_mask
            }

            FastBlur {
                anchors.fill: img_background
                source: img_background
                radius: 32
                transparentBorder:true
            }

            Image {
                id: img
                width: 60
                height: 60
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin:6
                source: "/icon/MtIcon.jpg"
                sourceSize.width:1024
                sourceSize.height:1024
                smooth: true
                mipmap:true
                visible: false
                cache:false
            }

            Rectangle {
                id: img_mask
                width: img.width
                height: img.height
                radius: 10
                color: "red"
                visible: false
            }

            OpacityMask {
                anchors.fill: img
                source: img
                maskSource: img_mask
            }

            TextScroll{
                id:music_name_label
                width:110
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: -16
                anchors.left:img.right
                anchors.leftMargin:10
                fontPixelSize:17
                text:qsTr("Music Name")
            }

            TextScroll{
                id:player_name_label
                width:110
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: 16
                anchors.left:img.right
                anchors.leftMargin:10
                fontPixelSize:13
                text:qsTr("Player")
            }

            //获取信息类，这是一个C++类
            MT_info_get{
                id:mt_info_get
                //这里QT6和Qt5的Quick有些不同
                //这样子加个function可以很明显的标识这是由emit传来的signal的参数
                //详细链接可以参考这个： https://www.direktembedded.com/qt5-to-qt6-qml-pyside-porting/
                onSig_qml_netease_file_changed:
                    function(){
                        //获取信息
                        mt_info_get.onQmlMusicInfoGet()
                        mt_info_get.onQmlPlayerInfoGet()
                        mt_info_get.onQmlImgDownload()
                        //显示窗口
                        pop_window.showWindow()
                }

                onSig_qml_music_info_get:
                    function(music_name){
                        music_name_label.text = music_name
                        //重新获取图片
                        mt_info_get.onQmlImgDownload()
                        //由于QtImage存在缓存机制，需要cache：false并且先置空路径再设置路径才会加载图片，不改变路径直接调用上次的缓存
                        img.source = ""
                        img.source = "file:./album.jpg"
                        img_background.source = ""
                        img_background.source = "file:./album.jpg"
                    }

                onSig_qml_player_info_get:
                    function(player_name){
                        player_name_label.text = player_name
                    }

                onSig_qml_autostart_status:
                    function(value){
                        if (value){
                            menu_right.sws.checked = true
                        }else{
                            menu_right.sws.checked = false
                        }
                    }

                onSig_qml_hot_key_activated:
                    function(value){
                        if(value === 1){
                            pop_window.showWindow()
                        }else if(value === 2){
                            mt_fre.showWindow()
                        }else if(value === 3){
                            mtBoardConnect.init();
                            menu_right.connectMSBoardState = true;
                        }
                    }

                onSig_qml_got_mouse_cursor:
                    //Qt6用法。qt5可忽略function
                    function(x,y){
                        menu_right.menu_x = x
                        menu_right.menu_y = y
                        menu_right.show()
                        //展现在最上层
                        menu_right.raise()
                    }
            }

            SystemTrayIcon{
                id:system_icon
                visible: true
                icon.source: "qrc:/icon/MtIcon.jpg"
                tooltip:"MediaStateT"

                onActivated:
                    //reason是SystemTrayIcon固有属性,不同数值对应不同的按键事件
                    //来源：https://gist.github.com/kviktor/
                    function(reason){
                        //双击，单机，2，3，右键1
                        if(reason === 2 || reason === 3){
                            //显示窗口
                            pop_window.showWindow()
                        }else if(reason === 1){
                            //定义过的槽函数，执行操作后，然后发射到on_qml_get_mouse_cursor
                            mt_info_get.on_qml_get_mouse_cursor()
                        }
                    }
            }

            PageMenu{
                id:menu_right

                onSws_click:{
                    if(menu_right.sws.checked){
                        mt_info_get.on_qml_create_sws()
                        // 再次进行状态检测确保添加成功
                        mt_info_get.on_qml_check_start_with_system()
                    }else{
                        mt_info_get.on_qml_remove_sws()
                        mt_info_get.on_qml_check_start_with_system()
                    }
                }

                Component.onCompleted: mt_info_get.on_qml_check_start_with_system()

                onSw_click:{
                    pop_window.showWindow()
                }

                onSf_click:{
                    mt_fre.showWindow()
                }
            }
        }
    }

    PopWindow{
        id:pop_window
        // 设置初始位置,对PopWindow里面的x,y进行了覆盖
        x_offset: get_screen_pixel(0.005, Screen.width)
        x: get_screen_pixel(0.94, Screen.width) //设置0.94不设置1是为了防止不同缩放下屏幕边缘乱跳的问题
        y: get_screen_pixel(0.13, Screen.height)
        x_origin: get_screen_pixel(0.94, Screen.width)
        source_component:window_draw

        // 为了适应不同的屏幕，需要使用百分比表示
        function get_screen_pixel(percent, sum_pixel){
            return percent * sum_pixel
        }
    }

    PageAudioFrequency{
        id:mt_fre
    }
}