### AppBase

Baseclass to platform specific App subclasses.

| Namespace                | Include
|--------------------------|-------------|
| [`ci::app::AppBase`] | `#include "cinder/app.h"`


[`ci::app::AppBase`]: https://libcinder.org/docs/branch/master/classcinder_1_1app_1_1_app_base.html

<br>
<br>
<br>

### Description

Use `ci::app::App` which is a [typedef] for an appropriate baseclass [relative the current platform][platform].

- [AppMsw](AppMsw.md) on Windows
- [AppMac](AppMac.md) on Osx
- [AppLinux](AppLinux.md) on Linux

[typedef]: http://en.cppreference.com/w/cpp/language/typedef
[platform]: https://github.com/cinder/Cinder/blob/e50d9d206824617b2833d89865ee48e06a0e8cfb/include/cinder/app/App.h

<br>
<br>
<br>

### Public Methods


| Output        | Method                                                      |
|--------------:|:------------------------------------------------------------|
|      WindowRef| [createWindow]() (const Window::Format &format=Window::Format()) override
|          void | [quit]() () override
|         float | [getFrameRate]() () const override
|          void | [setFrameRate]() (float frameRate) override
|          void | [disableFrameRate]() () override
|          bool | [isFrameRateEnabled]() () const override
|     WindowRef | [getWindow]() () const override
|     WindowRef | [getWindowIndex]() (size_t index) const override
|        size_t | [getNumWindows]() () const override
|     WindowRef | [getForegroundWindow]() () const override
| void          | [setup]() ()
| void          | [update]() ()
| void          | [draw]() ()
| void          | [mouseDown]() (MouseEvent event)
| void          | [mouseUp]() (MouseEvent event)
| void          | [mouseWheel]() (MouseEvent event)
| void          | [mouseMove]() (MouseEvent event)
| void          | [mouseDrag]() (MouseEvent event)
| void          | [touchesBegan]() (TouchEvent event)
| void          | [touchesMoved]() (TouchEvent event)
| void          | [touchesEnded]() (TouchEvent event)
| void          | [keyDown]() (KeyEvent event)
| void          | [keyUp]() (KeyEvent event)
| void          | [resize]() ()
| void          | [fileDrop]() (FileDropEvent event)
| void          | [cleanup]() ()
| void          | [quit]() ()=0
| signals::Signal< [void]()()> & | [getSignalUpdate]() ()
| EventSignalShouldQuit &    | [getSignalShouldQuit]() ()
| signals::Signal< [void]()()> & | [getSignalCleanup]() ()
| void          | [emitCleanup]() ()
| signals::Signal< [void]()()> & | [getSignalWillResignActive]() ()
| void          | [emitWillResignActive]() ()
| signals::Signal< [void]()()> & | [getSignalDidBecomeActive]() ()
| void          | [emitDidBecomeActive]() ()
| signals::Signal< [void]()(const DisplayRef &display)> & | [getSignalDisplayConnected]() ()
| void          | [emitDisplayConnected]() (const DisplayRef &display)
| signals::Signal< [void]()(const DisplayRef &display)> & | [getSignalDisplayDisconnected]() ()
| void          | [emitDisplayDisconnected]() (const DisplayRef &display)
| signals::Signal< [void]()(const DisplayRef &display)> & | [getSignalDisplayChanged]() ()
| void          | [emitDisplayChanged]() (const DisplayRef &display)
| const std::vector< TouchEvent::Touch > & | [getActiveTouches]() () const
| RendererRef   | [getRenderer]() () const
| DisplayRef   | [getDisplay]() () const
| WindowRef   | [createWindow]() (const Window::Format &format=Window::[Format]()())=0
| WindowRef   | [getWindow]() () const =0
| WindowRef   | [getForegroundWindow]() () const =0
| size_t   | [getNumWindows]() () const =0
| WindowRef   | [getWindowIndex]() (size_t index) const =0
| ivec2   | [getMousePos]() () const =0
| void   | [hideCursor]() ()=0
| void   | [showCursor]() ()=0
| void   | [enablePowerManagement]() (bool powerManagement=true)
| bool   | [isPowerManagementEnabled]() () const
| int   | [getWindowWidth]() () const
| int   | [getWindowHeight]() () const
| void   | [setWindowSize]() (int windowWidth, int windowHeight)
| void   | [setWindowSize]() (const ivec2 &size)
| vec2   | [getWindowCenter]() () const
| ivec2   | [getWindowSize]() () const
| float   | [getWindowAspectRatio]() () const
| Area   | [getWindowBounds]() () const
| float   | [getWindowContentScale]() () const
| ivec2   | [getWindowPos]() () const
| int   | [getWindowPosX]() () const
| int   | [getWindowPosY]() () const
| void   | [setWindowPos]() (int x, int y)
| void   | [setWindowPos]() (const ivec2 &windowPos)
| float   | [getFrameRate]() () const =0
| void   | [setFrameRate]() (float frameRate)=0
| void   | [disableFrameRate]() ()=0
| bool   | [isFrameRateEnabled]() () const =0
| float   | [getAverageFps]() () const
| double   | [getFpsSampleInterval]() () const
| void   | [setFpsSampleInterval]() (double sampleInterval)
| bool   | [isFullScreen]() () const
| void   | [setFullScreen]() (bool fullScreen, const FullScreenOptions &options=[FullScreenOptions]()())
| double   | [getElapsedSeconds]() () const
| uint32_t   | [getElapsedFrames]() () const
| bool   | [isMultiTouchEnabled]() () const
| bool   | [isHighDensityDisplayEnabled]() () const
| DataSourceRef   | [loadResource]() (const fs::path &resourcePath, int mswID, const std::string &mswType) const

<br>
<br>
<br>

### Example

```cpp
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;

class MyApp : public App {
  public:
	void setup() override;
	void draw() override;
};

void MyApp::setup()
{
	gl::enableDepthWrite();
	gl::enableDepthRead();
}

void MyApp::draw()
{
	gl::clear(
		Color(0.25f, 0.25f, 0.25f)  // Gray
	);
}

CINDER_APP(MyApp, RendererGl)

```