### AppBase

Baseclass to platform specific App subclasses.

| Namespace |
|-----------|
| [`cinder::app::BaseApp`](https://libcinder.org/docs/branch/master/classcinder_1_1app_1_1_app_base.html)

<br>
<br>
<br>

### Description

Use `cinder::app::App` which is a [typedef] for an appropriate baseclass relative the current platform.

- [AppMsw](cinder__app__AppMsw.md) on Windows
- [AppMac](cinder__app__AppMac.md) on Osx

[typedef]: http://en.cppreference.com/w/cpp/language/typedef

<br>
<br>
<br>

### Public Methods


| Output        | Method                                                      |
|--------------:|:------------------------------------------------------------|
|      WindowRef| [createWindow](cinder__app__AppMsw.createWindow.md) (const Window::Format &format=Window::Format()) override
|          void | [quit](cinder__app__AppMsw.quit.md) () override
|         float | [getFrameRate](cinder__app__AppMsw.getFrameRate.md) () const override
|          void | [setFrameRate](cinder__app__AppMsw.setFrameRate.md) (float frameRate) override
|          void | [disableFrameRate](cinder__app__AppMsw.disableFrameRate.md) () override
|          bool | [isFrameRateEnabled](cinder__app__AppMsw.isFrameRateEnabled.md) () const override
|     WindowRef | [getWindow](cinder__app__AppMsw.getWindow.md) () const override
|     WindowRef | [getWindowIndex](cinder__app__AppMsw.getWindowIndex.md) (size_t index) const override
|        size_t | [getNumWindows](cinder__app__AppMsw.getNumWindows.md) () const override
|     WindowRef | [getForegroundWindow](cinder__app__AppMsw.getForegroundWindow.md) () const override
| void          | [setup](cinder__app__AppBase.setup.md) ()
| void          | [update](cinder__app__AppBase.update.md) ()
| void          | [draw](cinder__app__AppBase.draw.md) ()
| void          | [mouseDown](cinder__app__AppBase.mouseDown.md) (MouseEvent event)
| void          | [mouseUp](cinder__app__AppBase.mouseUp.md) (MouseEvent event)
| void          | [mouseWheel](cinder__app__AppBase.mouseWheel.md) (MouseEvent event)
| void          | [mouseMove](cinder__app__AppBase.mouseMove.md) (MouseEvent event)
| void          | [mouseDrag](cinder__app__AppBase.mouseDrag.md) (MouseEvent event)
| void          | [touchesBegan](cinder__app__AppBase.touchesBegan.md) (TouchEvent event)
| void          | [touchesMoved](cinder__app__AppBase.touchesMoved.md) (TouchEvent event)
| void          | [touchesEnded](cinder__app__AppBase.touchesEnded.md) (TouchEvent event)
| void          | [keyDown](cinder__app__AppBase.keyDown.md) (KeyEvent event)
| void          | [keyUp](cinder__app__AppBase.keyUp.md) (KeyEvent event)
| void          | [resize](cinder__app__AppBase.resize.md) ()
| void          | [fileDrop](cinder__app__AppBase.fileDrop.md) (FileDropEvent event)
| void          | [cleanup](cinder__app__AppBase.cleanup.md) ()
| void          | [quit](cinder__app__AppBase.quit.md) ()=0
| signals::Signal< [void](cinder__app__AppBase.void.md)()> & | [getSignalUpdate](cinder__app__AppBase.getSignalUpdate.md) ()
| EventSignalShouldQuit &    | [getSignalShouldQuit](cinder__app__AppBase.getSignalShouldQuit.md) ()
| signals::Signal< [void](cinder__app__AppBase.void.md)()> & | [getSignalCleanup](cinder__app__AppBase.getSignalCleanup.md) ()
| void          | [emitCleanup](cinder__app__AppBase.emitCleanup.md) ()
| signals::Signal< [void](cinder__app__AppBase.void.md)()> & | [getSignalWillResignActive](cinder__app__AppBase.getSignalWillResignActive.md) ()
| void          | [emitWillResignActive](cinder__app__AppBase.emitWillResignActive.md) ()
| signals::Signal< [void](cinder__app__AppBase.void.md)()> & | [getSignalDidBecomeActive](cinder__app__AppBase.getSignalDidBecomeActive.md) ()
| void          | [emitDidBecomeActive](cinder__app__AppBase.emitDidBecomeActive.md) ()
| signals::Signal< [void](cinder__app__AppBase.void.md)(const DisplayRef &display)> & | [getSignalDisplayConnected](cinder__app__AppBase.getSignalDisplayConnected.md) ()
| void          | [emitDisplayConnected](cinder__app__AppBase.emitDisplayConnected.md) (const DisplayRef &display)
| signals::Signal< [void](cinder__app__AppBase.void.md)(const DisplayRef &display)> & | [getSignalDisplayDisconnected](cinder__app__AppBase.getSignalDisplayDisconnected.md) ()
| void          | [emitDisplayDisconnected](cinder__app__AppBase.emitDisplayDisconnected.md) (const DisplayRef &display)
| signals::Signal< [void](cinder__app__AppBase.void.md)(const DisplayRef &display)> & | [getSignalDisplayChanged](cinder__app__AppBase.getSignalDisplayChanged.md) ()
| void          | [emitDisplayChanged](cinder__app__AppBase.emitDisplayChanged.md) (const DisplayRef &display)
| const std::vector< TouchEvent::Touch > & | [getActiveTouches](cinder__app__AppBase.getActiveTouches.md) () const
| RendererRef   | [getRenderer](cinder__app__AppBase.getRenderer.md) () const
| DisplayRef   | [getDisplay](cinder__app__AppBase.getDisplay.md) () const
| WindowRef   | [createWindow](cinder__app__AppBase.createWindow.md) (const Window::Format &format=Window::[Format](cinder__app__AppBase.Format.md)())=0
| WindowRef   | [getWindow](cinder__app__AppBase.getWindow.md) () const =0
| WindowRef   | [getForegroundWindow](cinder__app__AppBase.getForegroundWindow.md) () const =0
| size_t   | [getNumWindows](cinder__app__AppBase.getNumWindows.md) () const =0
| WindowRef   | [getWindowIndex](cinder__app__AppBase.getWindowIndex.md) (size_t index) const =0
| ivec2   | [getMousePos](cinder__app__AppBase.getMousePos.md) () const =0
| void   | [hideCursor](cinder__app__AppBase.hideCursor.md) ()=0
| void   | [showCursor](cinder__app__AppBase.showCursor.md) ()=0
| void   | [enablePowerManagement](cinder__app__AppBase.enablePowerManagement.md) (bool powerManagement=true)
| bool   | [isPowerManagementEnabled](cinder__app__AppBase.isPowerManagementEnabled.md) () const
| int   | [getWindowWidth](cinder__app__AppBase.getWindowWidth.md) () const
| int   | [getWindowHeight](cinder__app__AppBase.getWindowHeight.md) () const
| void   | [setWindowSize](cinder__app__AppBase.setWindowSize.md) (int windowWidth, int windowHeight)
| void   | [setWindowSize](cinder__app__AppBase.setWindowSize.md) (const ivec2 &size)
| vec2   | [getWindowCenter](cinder__app__AppBase.getWindowCenter.md) () const
| ivec2   | [getWindowSize](cinder__app__AppBase.getWindowSize.md) () const
| float   | [getWindowAspectRatio](cinder__app__AppBase.getWindowAspectRatio.md) () const
| Area   | [getWindowBounds](cinder__app__AppBase.getWindowBounds.md) () const
| float   | [getWindowContentScale](cinder__app__AppBase.getWindowContentScale.md) () const
| ivec2   | [getWindowPos](cinder__app__AppBase.getWindowPos.md) () const
| int   | [getWindowPosX](cinder__app__AppBase.getWindowPosX.md) () const
| int   | [getWindowPosY](cinder__app__AppBase.getWindowPosY.md) () const
| void   | [setWindowPos](cinder__app__AppBase.setWindowPos.md) (int x, int y)
| void   | [setWindowPos](cinder__app__AppBase.setWindowPos.md) (const ivec2 &windowPos)
| float   | [getFrameRate](cinder__app__AppBase.getFrameRate.md) () const =0
| void   | [setFrameRate](cinder__app__AppBase.setFrameRate.md) (float frameRate)=0
| void   | [disableFrameRate](cinder__app__AppBase.disableFrameRate.md) ()=0
| bool   | [isFrameRateEnabled](cinder__app__AppBase.isFrameRateEnabled.md) () const =0
| float   | [getAverageFps](cinder__app__AppBase.getAverageFps.md) () const
| double   | [getFpsSampleInterval](cinder__app__AppBase.getFpsSampleInterval.md) () const
| void   | [setFpsSampleInterval](cinder__app__AppBase.setFpsSampleInterval.md) (double sampleInterval)
| bool   | [isFullScreen](cinder__app__AppBase.isFullScreen.md) () const
| void   | [setFullScreen](cinder__app__AppBase.setFullScreen.md) (bool fullScreen, const FullScreenOptions &options=[FullScreenOptions](cinder__app__AppBase.FullScreenOptions.md)())
| double   | [getElapsedSeconds](cinder__app__AppBase.getElapsedSeconds.md) () const
| uint32_t   | [getElapsedFrames](cinder__app__AppBase.getElapsedFrames.md) () const
| bool   | [isMultiTouchEnabled](cinder__app__AppBase.isMultiTouchEnabled.md) () const
| bool   | [isHighDensityDisplayEnabled](cinder__app__AppBase.isHighDensityDisplayEnabled.md) () const
| DataSourceRef   | [loadResource](cinder__app__AppBase.loadResource.md) (const fs::path &resourcePath, int mswID, const std::string &mswType) const

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