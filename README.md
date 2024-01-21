# TradeSystem
auto trade system
# deps
Qt_5_2_0_MSVC2012_32bit
vs2012
tinyxml
ctp
# build
mkdir build && cd build
cmake -G "Visual Studio 11 2012" -A Win32 ..
cmake --build . --config <Debug/Release> -j
# run
拷贝config到可执行程序目录下
拷贝ctp dll到可执行程序目录下
自动拷贝qt dll库到程序运行目录
cd your_qt_path\Qt\Qt5.2.0\5.2.0\msvc2012\bin
set PATH=your_qt_path\Qt\Qt5.2.0\5.2.0\msvc2012\bin;%PATH%
windeployqt.exe "yourpath\TradeSystem.exe"
# get skills
*.ui文件编译成*.h文件
'''
cd your_qt_path\Qt\Qt5.2.0\5.2.0\msvc2012\bin
set PATH=your_qt_path\Qt\Qt5.2.0\5.2.0\msvc2012\bin;%PATH%
uic -o your_h_file_path\ui_TradeSystem.h your_ui_file_path\TradeSystem.ui
'''
生成.pro工程文件
'''
your_qt_path\Qt\Qt5.2.0\5.2.0\msvc2012\bin\qmake -project
'''