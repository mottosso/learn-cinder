### Settings

Startup settings, used during [`App`] construction.

| Namespace |
|------------
| [`cinder::app::BaseApp::Settings`](https://libcinder.org/docs/branch/master/classcinder_1_1app_1_1_app_base_1_1_settings.html)

[`app`]: AppBase.md

<br>
<br>
<br>

### Public Methods

| Output        | Method                                                      |
|--------------:|:------------------------------------------------------------|
|        | Settings ()
|        | ~Settings ()
| void   | [setWindowSize]() (int windowSizeX, int windowSizeY)
| void   | [setWindowSize]() (const ivec2 &size)
| ivec2  | [getWindowSize]() () const
| ivec2  | [getWindowPos]() () const
| void   | [setWindowPos]() (int windowPosX, int windowPosY)
| void   | [setWindowPos]() (const ivec2 &windowPos)
| bool   | [isWindowPosSpecified]() () const
| void   | [setWindowPosUnspecified]() ()
| void   | [setQuitOnLastWindowCloseEnabled]() (bool enable=true)
| bool   | [isQuitOnLastWindowCloseEnabled]() () const
| bool   | [isFullScreen]() ()
| void   | [setFullScreen]() (bool fullScreen=true, const FullScreenOptions &options=[FullScreenOption]()s())
| bool   | [isResizable]() () const
| void   | [setResizable]() (bool resizable=true)
| bool   | [isBorderless]() () const
| void   | [setBorderless]() (bool borderless=true)
| bool   | [isAlwaysOnTop]() () const
| void   | [setAlwaysOnTop]() (bool alwaysOnTop=true)
| DisplayRef   | [getDisplay]() () const
| void   | [setDisplay]() (DisplayRef display)
| Window::Format   | [getDefaultWindowFormat]() () const
| void   | [setDefaultWindowFormat]() (const Window::Format &format)
| void   | [setDefaultRenderer]() (const RendererRef &renderer)
| RendererRef   | [getDefaultRenderer]() () const
| void | [prepareWindow]() (const Window::Format &format)
| std::vector< Window::Format > & | [getWindowFormats]() ()
| const std::vector< Window::Format > & | [getWindowFormats]() () const
| const std::string &   | [getTitle]() () const
| void   | [setTitle]() (const std::string &title)
| void   | [setHighDensityDisplayEnabled]() (bool enable=true)
| bool   | [isHighDensityDisplayEnabled]() () const
| void   | [setMultiTouchEnabled]() (bool enable=true)
| bool   | [isMultiTouchEnabled]() () const
| void   | [setPowerManagementEnabled]() (bool enable=true)
| bool   | [isPowerManagementEnabled]() () const
| void   | [setFrameRate]() (float frameRate)
| void   | [disableFrameRate]() ()
| bool   | [isFrameRateEnabled]() () const
| float   | [getFrameRate]() () const
| const std::vector< std::string > &   | [getCommandLineArgs]() () const
| void   | [setShouldQuit]() (bool shouldQuit=true)
| bool   | [getShouldQuit]() () const

### Example

```cpp
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;

class BasicApp : public App {};

// Pass settings as lambda
CINDER_APP(BasicApp, RendererGl, [&](App::Settings *settings) {
    settings->setWindowSize(1280, 720);
    settings->setTitle("My App");
})
```
