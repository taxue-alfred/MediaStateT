import QtQuick
import QtQuick.Window
import QtCharts
import QtQuick.Layouts

Window{
    width:640
    height:480
    id:root_window

    //设置一个标志，以免多次被调用showWindow函数
    property int sign : 0

    GridLayout{
        anchors.centerIn:parent
        columns:2
        rows:2
        ChartView{
            id:left_shake
            title: qsTr("左声道")
            Layout.minimumWidth:320
            Layout.minimumHeight:240
            antialiasing:true
            legend.visible:false

            ValueAxis{
                id:left_shake_value_X
                visible:false
                min:0
                max:500
            }

            ValueAxis{
                id:left_shake_value_Y
                labelsVisible:false
                gridVisible:false
                visible:false
                min:-3000
                max:3000
            }

            SplineSeries{
                id:line1
                axisX:left_shake_value_X
                axisY:left_shake_value_Y
            }
        }

        ChartView{
            id:right_shake
            title: qsTr("右声道")
            Layout.minimumWidth:320
            Layout.minimumHeight:240
            antialiasing:true
            legend.visible:false

            ValueAxis{
                id:right_shake_value_X
                visible:false
                min:0
                max:500
            }

            ValueAxis{
                id:right_shake_value_Y
                labelsVisible:false
                gridVisible:false
                visible:false
                min:-3000
                max:3000
            }

            SplineSeries{
                id:line2
                axisX:right_shake_value_X
                axisY:right_shake_value_Y
            }
        }

        ChartView{
            id:left_bar
//            title: qsTr("左声道")
            Layout.minimumWidth:320
            Layout.minimumHeight:240
            antialiasing:true
            legend.visible:false

            BarCategoryAxis{
                id:left_bar_value_X
                labelsVisible:false
                gridVisible:false
                //这里添加下标，到时候隐藏，不然到时候进行数据替换没法替换，数量一定要和想要显示的个数一致
                categories: ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10"]
            }

            ValueAxis{
                id:left_bar_value_Y
                visible:false
                min:0
                max:1000
            }

            BarSeries{
                axisX:left_bar_value_X
                axisY:left_bar_value_Y

                BarSet {
                    id:bar1
                    label: "Bob";
                    //这里对应数值，到时候隐藏，不然到时候进行数据替换没法替换，数量一定要和想要显示的个数一致
                    values: [2, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]
                }
            }
        }

        ChartView{
            id:right_bar
//            title: qsTr("右声道")
            Layout.minimumWidth:320
            Layout.minimumHeight:240
            antialiasing:true
            legend.visible:false

            BarCategoryAxis{
                id:right_bar_value_X
                gridVisible:false
                labelsVisible:false
                categories: ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10"]
            }

            ValueAxis{
                id:right_bar_value_Y
                min:0
                max:1000
                visible:false
            }

            BarSeries{
                axisX:right_bar_value_X
                axisY:right_bar_value_Y

                BarSet {
                    id:bar2
                    color:"green"
                    label: "Bob";
                    values: [2, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]
                }
            }
        }
    }
    onClosing:root_window.closingWindow()

    Timer{
        id:update_value
        repeat:true
        running:true
        interval:45
        onTriggered:{
            //检测窗口是否处于活跃状态
            if(root_window.visible === true && mtFrequency.dataReady){
                line1.clear()
                line2.clear()

                var available_num = mtFrequency.get_available_num()
                var shake_left_value = mtFrequency.shake_left_value()
                var shake_right_value = mtFrequency.shake_right_value()
                var bar_left_value = mtFrequency.bar_left_value()
                var bar_right_value = mtFrequency.bar_right_value()

                for(var i = 0; i < available_num; i = i + 10){
                    line1.append(i, shake_left_value[i])
                    line2.append(i, shake_right_value[i])
                }

                for(var j = 0; j <= 10; j++){
                    bar1.replace(j, bar_left_value[j+1])
                    bar2.replace(j, bar_right_value[j+1])
                }
            }
        }
    }

    function closingWindow(){
        if(sign === 1){
            sign = 0
            mtFrequency.destroyVarious()
        }
    }

    function showWindow(){
        if(sign === 0){
            mtFrequency.init()
            root_window.show()
            root_window.raise()
            sign = 1
        }
    }
}