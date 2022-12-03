#include "Acrylic.h"

QQmlApplicationEngine* Acrylic::set_QmlEnginePointer(QQmlApplicationEngine &engine) {
    Qml_engine = &engine;
    return Qml_engine;
}

WId Acrylic::open_acrylic() {
    //获取winid第一种
    QObject* m_rootObject = Qml_engine->rootObjects().first();
    if(m_rootObject) {
        QWindow *window = qobject_cast<QWindow *>(m_rootObject);
        std::cout << window << std::endl;
        if(window) {

            WId wid = window->winId();
        }
    }

    //获取winid第二种
    //Configurations of Acrylic Effect
    hwnd = ::FindWindow(L"Qt622QWindowToolTipSaveBits", L"MediaStateT");
    std::cout << hwnd << std::endl;
    huser = GetModuleHandle(L"user32.dll");

    if(huser){
        setWindowCompositionAttribute = (pfnSetWindowCompositionAttribute)GetProcAddress(huser, "SetWindowCompositionAttribute");
        if(setWindowCompositionAttribute){
            DWORD gradientColor = DWORD(0x50F5F5F5);
            ACCENT_POLICY accent = { ACCENT_ENABLE_ACRYLICBLURBEHIND, 0, gradientColor, 0 };
            WINDOWCOMPOSITIONATTRIBDATA data;
            data.Attrib = WCA_ACCENT_POLICY;
            data.pvData = &accent;
            data.cbData = sizeof(accent);
            setWindowCompositionAttribute(hwnd, &data);
        }
    }

    return 0;
}
