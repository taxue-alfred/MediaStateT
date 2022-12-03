import QtQuick
import QtQuick.Controls
import QtQuick.Window

Window{
    id: pop_window
    visible: true
    visibility: Window.Windowed
    color: "transparent"
    // 透明度
    opacity: 0
    // 取消边框
    flags:Qt.FramelessWindowsHint | Qt.ToolTip
    // 设置为非模态
    modality: Qt.NonModal
    //设置初始位置(外部设置会覆盖此设置)
    x: Screen.width - content_loader.width
    y: 100
    //根据Loader设置大小
    width: content_loader.width
    height: content_loader.height

    MouseArea{
        id:content_mouse
        anchors.fill: parent
        hoverEnabled: true
    }

    // 设置出现后显示时间的计时器
    Timer{
        id:show_timer
        interval: 2500
        repeat: true
        onTriggered:{
            //这个if实现了鼠标悬停保留窗口的效果
            if(!loader_mouse.containsMouse){
                hideWindow();
            }
        }
    }

    //绘制图形的Loader，供外部使用
    property alias source_component:content_loader.sourceComponent
    Loader{
        id:content_loader
        MouseArea{
            id:loader_mouse
            anchors.fill:parent
            hoverEnabled:true
        }
    }

//---------------------------动画部分开始-------------------
    //设置出现显示动画相对于设置的x值的偏移位置，这里变量外部进行了设置
    property int x_offset: 0
    property int x_origin: 0
    //设置sign标志，防止多次showWindow调用造成多次动画显示
    property int sign: 0
    ParallelAnimation{
        id: show_anim
        // 透明度动画
        PropertyAnimation{
            target:pop_window
            property: "opacity"
            easing.type: Easing.InQuart
            from:pop_window.opacity
            to: 1
            duration:350
        }
        // 位置移动动画
        PropertyAnimation{
            target:pop_window
            property: "x"
            easing.type: Easing.OutBounce
            //从当前值开始移动
            from: pop_window.x
            to: Screen.width - content_loader.width - x_offset
            duration:800
        }
        // 大小缩放动画
        PropertyAnimation{
            target:pop_window
            property: "width"
            easing.type: Easing.OutCirc
            //从当前值开始移动
            from: 0
            to: content_loader.width
            duration:200
        }
        // 大小缩放动画
        PropertyAnimation{
            target:pop_window
            property: "height"
            easing.type: Easing.OutCirc
            //从当前值开始移动
            from: 0
            to: content_loader.height
            duration:200
        }

        onStarted:{
            pop_window.show()
        }
        //出现动画结束信号
        onFinished:{
            show_timer.restart()
        }
    }
    //设置关闭显示动画
    ParallelAnimation{
        id: hide_anim
        // 透明度动画
        PropertyAnimation{
            target:pop_window
            property: "opacity"
            easing.type: Easing.OutCubic
            from:pop_window.opacity
            to: 0
            duration:800
        }
        //位置移动动画
        PropertyAnimation{
            target:pop_window
            property: "x"
            easing.type: Easing.InExpo
            //从当前值开始移动
            from: pop_window.x
            to: x_origin
            duration:800
        }
        //大小缩放动画
        PropertyAnimation{
            target:pop_window
            property: "width"
            easing.type: Easing.InQuint
            //从当前值开始移动
            from: content_loader.width + 10
            to: 0
            duration:1000
        }
        //大小缩放动画
        PropertyAnimation{
            target:pop_window
            property: "height"
            easing.type: Easing.InQuint
            //从当前值开始移动
            from: content_loader.height + 10
            to: 0
            duration:1000
        }
        //结束动画结束之后停止定时器
        onFinished:{
            show_timer.stop()
        }
    }

    //显示弹窗
    function showWindow(){
        if(sign === 0){
            hide_anim.stop()
            show_anim.start()
            sign = 1
        }
    }

    //隐藏弹窗
    function hideWindow(){
        if(sign === 1){
            show_anim.stop()
            hide_anim.start()
            sign = 0
        }
    }
//---------------------------动画部分结束-------------------
}

