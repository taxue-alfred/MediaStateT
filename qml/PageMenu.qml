import QtQuick
import QtQuick.Window
import QtQuick.Controls

Window{
    id:root_window
    property int menu_x
    property int menu_y
    x:menu_x
    y:menu_y - height
    width: 136
    height: 180
    flags:Qt.FramelessWindowsHint | Qt.ToolTip
    modality: Qt.NonModal
    color: "transparent"

    //定义信号，发射给调用控件
    signal sws_click
    signal sw_click
    signal sf_click
    signal cm_click

    property alias sws:start_with_system
    property alias connectMSBoardState : connectMSBoard.checked

    Timer{
        id:close_timer
        interval:1000
        repeat:true
        running:true
        onTriggered:{
            root_window.show()
            close_timer.restart()
            if(!start_with_system.hovered && !showWindow.hovered &&
                !showFrequency.hovered && !connectMSBoard.hovered &&
                !exit.hovered){
                    root_window.close()
            }
        }
    }

    Rectangle{
        radius:8
        width:root_window.width
        height:root_window.height

        Column{
            anchors.centerIn: parent

        RoundButton{
                id: start_with_system
                width:root_window.width
                height:36
                radius:8
                checkable:true
                background:
                    Rectangle{
                        id:sws_bk
                        radius:8
                        color: start_with_system.checked ? "whitesmoke" :
                                (start_with_system.hovered ? "lightgrey" :
                                    "white")
                        Image{
                            id:sws_img
                            anchors.left:parent.left
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.leftMargin:12
                            smooth:true
                            width:20
                            height:20
                            source:"/icon/start.svg"
                        }
                        Text{
                            anchors.left:sws_img.left
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.leftMargin:28
                            text:"自动启动"
                            font.pointSize:9
                        }
                    }

                onClicked:root_window.sws_click()
            }

            RoundButton{
                id: showWindow
                width:root_window.width
                height:36
                radius:8
                background:
                    Rectangle{
                        radius:8
                        color: showWindow.hovered ? "lightgray": "white"
                        Image{
                            id:sw_img
                            anchors.left:parent.left
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.leftMargin:13
                            smooth:true
                            width:17
                            height:17
                            source:"/icon/window.svg"
                        }
                        Text{
                            anchors.left:sw_img.left
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.leftMargin:27
                            text:"显示窗口"
                            font.pointSize:9
                        }
                    }

                onClicked:root_window.sw_click()
            }

            RoundButton{
                id: showFrequency
                width:root_window.width
                height:36
                radius:8
                background:
                    Rectangle{
                        radius:8
                        color: showFrequency.hovered ? "lightgray": "white"
                        Image{
                            id:sf_img
                            anchors.left:parent.left
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.leftMargin:10
                            smooth:true
                            width:23
                            height:23
                            source:"/icon/frequency.svg"
                        }
                        Text{
                            anchors.left:sf_img.left
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.leftMargin:30
                            text:"显示频谱"
                            font.pointSize:9
                        }
                    }

                onClicked:root_window.sf_click()
            }

            RoundButton{
                id: connectMSBoard
                width:root_window.width
                height:36
                radius:8
                checkable : true
                background:
                    Rectangle{
                        radius:8
                        color: connectMSBoard.checked ? "whitesmoke" :
                               (connectMSBoard.hovered ? "lightgrey" :
                                   "white")
                        Image{
                            id:mtb_img
                            anchors.left:parent.left
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.leftMargin:10
                            smooth:true
                            width:23
                            height:23
                            source:"/icon/board.svg"
                        }
                        Text{
                            anchors.left:mtb_img.left
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.leftMargin:30
                            text:"连接MSBoard"
                            font.pointSize:9
                        }
                    }

                onClicked:{
                    //触发信号
                    root_window.cm_click()
                    if(connectMSBoard.checked){
                        mtBoardConnect.init()
                    }else{
                        mtBoardConnect.destroyConnect()
                    }
                }
            }

            RoundButton{
                id: exit
                width:root_window.width
                height:36
                radius:8
                background:
                    Rectangle{
                        radius:8
                        color: exit.hovered ? "crimson": "white"
                        Image{
                            id:exit_img
                            anchors.left:parent.left
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.leftMargin:12
                            smooth:true
                            width:20
                            height:20
                            source:"/icon/exit.svg"
                        }
                        Text{
                            anchors.left:exit_img.left
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.leftMargin:28
                            text:"退出"
                            font.pointSize:9
                        }
                    }
                onClicked:{
                    if(connectMSBoard.checkable){
                        mtBoardConnect.destroyConnect()
                    }
                    Qt.quit()
                }
            }
        }
    }
}