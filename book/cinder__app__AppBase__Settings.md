### Settings

Startup settings, used during App construction. They are modified before the app is created by passing a `SettingsFn` to the app instantiation macros.

| Namespace |
|------------
| `cinder::app::BaseApp::Settings`

<br>
<br>
<br>

### Public Methods

| Output        | Method                                                      |
|--------------:|:------------------------------------------------------------|
|        | Settings ()
|        | ~Settings ()
| void   | [setWindowSize](cinder__app__AppBase__Settings.setWindowSize.md) (int windowSizeX, int windowSizeY)
| void   | [setWindowSize](cinder__app__AppBase__Settings.setWindowSize.md) (const ivec2 &size)
| ivec2  | [getWindowSize](cinder__app__AppBase__Settings.getWindowSize.md) () const
| ivec2  | [getWindowPos](cinder__app__AppBase__Settings.getWindowPos.md) () const
| void   | [setWindowPos](cinder__app__AppBase__Settings.setWindowPos.md) (int windowPosX, int windowPosY)
| void   | [setWindowPos](cinder__app__AppBase__Settings.setWindowPos.md) (const ivec2 &windowPos)
| bool   | [isWindowPosSpecified](cinder__app__AppBase__Settings.isWindowPosSpecified.md) () const
| void   | [setWindowPosUnspecified](cinder__app__AppBase__Settings.setWindowPosUnspecified.md) ()
| void   | [setQuitOnLastWindowCloseEnabled](cinder__app__AppBase__Settings.setQuitOnLastWindowCloseEnabled.md) (bool enable=true)
| bool   | [isQuitOnLastWindowCloseEnabled](cinder__app__AppBase__Settings.isQuitOnLastWindowCloseEnabled.md) () const
| bool   | [isFullScreen](cinder__app__AppBase__Settings.isFullScreen.md) ()
| void   | [setFullScreen](cinder__app__AppBase__Settings.setFullScreen.md) (bool fullScreen=true, const FullScreenOptions &options=[FullScreenOption](cinder__app__AppBase__Settings.FullScreenOption.md)s())
| bool   | [isResizable](cinder__app__AppBase__Settings.isResizable.md) () const
| void   | [setResizable](cinder__app__AppBase__Settings.setResizable.md) (bool resizable=true)
| bool   | [isBorderless](cinder__app__AppBase__Settings.isBorderless.md) () const
| void   | [setBorderless](cinder__app__AppBase__Settings.setBorderless.md) (bool borderless=true)
| bool   | [isAlwaysOnTop](cinder__app__AppBase__Settings.isAlwaysOnTop.md) () const
| void   | [setAlwaysOnTop](cinder__app__AppBase__Settings.setAlwaysOnTop.md) (bool alwaysOnTop=true)
| DisplayRef   | [getDisplay](cinder__app__AppBase__Settings.getDisplay.md) () const
| void   | [setDisplay](cinder__app__AppBase__Settings.setDisplay.md) (DisplayRef display)
| Window::Format   | [getDefaultWindowFormat](cinder__app__AppBase__Settings.getDefaultWindowFormat.md) () const
| void   | [setDefaultWindowFormat](cinder__app__AppBase__Settings.setDefaultWindowFormat.md) (const Window::Format &format)
| void   | [setDefaultRenderer](cinder__app__AppBase__Settings.setDefaultRenderer.md) (const RendererRef &renderer)
| RendererRef   | [getDefaultRenderer](cinder__app__AppBase__Settings.getDefaultRenderer.md) () const
| void | [prepareWindow](cinder__app__AppBase__Settings.prepareWindow.md) (const Window::Format &format)
| std::vector< Window::Format > & | [getWindowFormats](cinder__app__AppBase__Settings.getWindowFormats.md) ()
| const std::vector< Window::Format > & | [getWindowFormats](cinder__app__AppBase__Settings.getWindowFormats.md) () const
| const std::string &   | [getTitle](cinder__app__AppBase__Settings.getTitle.md) () const
| void   | [setTitle](cinder__app__AppBase__Settings.setTitle.md) (const std::string &title)
| void   | [setHighDensityDisplayEnabled](cinder__app__AppBase__Settings.setHighDensityDisplayEnabled.md) (bool enable=true)
| bool   | [isHighDensityDisplayEnabled](cinder__app__AppBase__Settings.isHighDensityDisplayEnabled.md) () const
| void   | [setMultiTouchEnabled](cinder__app__AppBase__Settings.setMultiTouchEnabled.md) (bool enable=true)
| bool   | [isMultiTouchEnabled](cinder__app__AppBase__Settings.isMultiTouchEnabled.md) () const
| void   | [setPowerManagementEnabled](cinder__app__AppBase__Settings.setPowerManagementEnabled.md) (bool enable=true)
| bool   | [isPowerManagementEnabled](cinder__app__AppBase__Settings.isPowerManagementEnabled.md) () const
| void   | [setFrameRate](cinder__app__AppBase__Settings.setFrameRate.md) (float frameRate)
| void   | [disableFrameRate](cinder__app__AppBase__Settings.disableFrameRate.md) ()
| bool   | [isFrameRateEnabled](cinder__app__AppBase__Settings.isFrameRateEnabled.md) () const
| float   | [getFrameRate](cinder__app__AppBase__Settings.getFrameRate.md) () const
| const std::vector< std::string > &   | [getCommandLineArgs](cinder__app__AppBase__Settings.getCommandLineArgs.md) () const
| void   | [setShouldQuit](cinder__app__AppBase__Settings.setShouldQuit.md) (bool shouldQuit=true)
| bool   | [getShouldQuit](cinder__app__AppBase__Settings.getShouldQuit.md) () const

### Example

```cpp
#include "cinder/app/App.h"

// Pass to instanatiation macro as a lambda.
CINDER_APP(SimpleReceiverApp, RendererGl, [](App::Settings *settings) {
	settings->setConsoleWindowEnabled();
	settings->setMultiTouchEnabled( false );
})
```
