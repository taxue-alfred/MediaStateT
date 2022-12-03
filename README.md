# MediaStateT

#### 特性：

- 从Qt5升级到Qt6+QML混合编程，前后端分离，界面逻辑更清晰， 动画更流畅
- 现代化风格UI设计

#### 功能：

- 音乐切歌显示弹窗动画

  ![动画.gif](https://s2.loli.net/2022/01/14/BKi2yHuTq8aoSEl.gif)

- 实时的音乐频谱与音乐波形显示

  ![动画2.gif](https://s2.loli.net/2022/01/21/i7gmIjtZe8GK6vl.gif)

- 与MediaStateBoard配合的实时音乐频谱显示(TCP传输方式)

  ![动画2.gif](https://s2.loli.net/2022/02/09/TcXd1WFztxK4JNZ.gif)
  
- 与MediaStateBoard配合的多媒体控制（暂未实现）

#### 使用介绍：

1. 配置文件介绍(config.txt)：
   - 第一行为MediaStateBoard IP地址，MediaStateBoard连接后会在主屏幕显示IP地址（获得到IP地址需要自行修改配置文件）
   - 第二行为MediaStateBoard通信的端口（一般不需要更改，如果发现端口占用则需要进行修改）

2. 托盘使用：

   - 左键单双击弹出窗口

   - 右键呼出右键菜单

     ![动画.gif](https://s2.loli.net/2022/01/21/FoKDbALBVjZvRhg.gif)

3. 快捷键使用：

   - `Ctrl + 1`显示弹窗

   - `Ctrl + 2`显示实时频谱

   - `Ctrl + 3`连接MediaStateBoard（连接后显示为灰白色）
