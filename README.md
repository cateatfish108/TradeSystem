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
����config����ִ�г���Ŀ¼��
����ctp dll����ִ�г���Ŀ¼��
�Զ�����qt dll�⵽��������Ŀ¼
cd your_qt_path\Qt\Qt5.2.0\5.2.0\msvc2012\bin
set PATH=your_qt_path\Qt\Qt5.2.0\5.2.0\msvc2012\bin;%PATH%
windeployqt.exe "yourpath\TradeSystem.exe"
# get skills
*.ui�ļ������*.h�ļ�
'''
cd your_qt_path\Qt\Qt5.2.0\5.2.0\msvc2012\bin
set PATH=your_qt_path\Qt\Qt5.2.0\5.2.0\msvc2012\bin;%PATH%
uic -o your_h_file_path\ui_TradeSystem.h your_ui_file_path\TradeSystem.ui
'''
����.pro�����ļ�
'''
your_qt_path\Qt\Qt5.2.0\5.2.0\msvc2012\bin\qmake -project
'''