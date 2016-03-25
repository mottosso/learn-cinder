### MouseEvent

Represents a mouse event.

| Namespace |
|-----------|
| [`cinder::app::MouseEvent`](https://libcinder.org/docs/branch/master/classcinder_1_1app_1_1_mouse_event.html)

<br>
<br>
<br>

### Public Methods



| Output        | Method                                                      |
|--------------:|:------------------------------------------------------------|
| 				| MouseEvent ()
| 				| MouseEvent (const WindowRef &win, int initiator, int x, int y, unsigned int modifiers, float wheelIncrement, uint32_t nativeModifiers)
| int           | [getX](cinder__app__MouseEvent.getX.md) () const
| int           | [getY](cinder__app__MouseEvent.getY.md) () const
| const ivec2 & | [getPos](cinder__app__MouseEvent.getPos.md) () const
| void          | [setPos](cinder__app__MouseEvent.setPos.md) (const ivec2 &pos)
| bool          | [isLeft](cinder__app__MouseEvent.isLeft.md) () const
| bool          | [isRight](cinder__app__MouseEvent.isRight.md) () const
| bool          | [isMiddle](cinder__app__MouseEvent.isMiddle.md) () const
| bool          | [isLeftDown](cinder__app__MouseEvent.isLeftDown.md) () const
| bool          | [isRightDown](cinder__app__MouseEvent.isRightDown.md) () const
| bool          | [isMiddleDown](cinder__app__MouseEvent.isMiddleDown.md) () const
| bool          | [isShiftDown](cinder__app__MouseEvent.isShiftDown.md) () const
| bool          | [isAltDown](cinder__app__MouseEvent.isAltDown.md) () const
| bool          | [isControlDown](cinder__app__MouseEvent.isControlDown.md) () const
| bool          | [isMetaDown](cinder__app__MouseEvent.isMetaDown.md) () const
| bool          | [isAccelDown](cinder__app__MouseEvent.isAccelDown.md) () const
| float         | [getWheelIncrement](cinder__app__MouseEvent.getWheelIncrement.md) () const
| uint32_t      | [getNativeModifiers](cinder__app__MouseEvent.getNativeModifiers.md) () const
| bool          | [isHandled](cinder__app__MouseEvent.isHandled.md) () const
| void          | [setHandled](cinder__app__MouseEvent.setHandled.md) (bool handled=true)
| WindowRef     | [getWindow](cinder__app__MouseEvent.getWindow.md) () const
| void          | [setWindow](cinder__app__MouseEvent.setWindow.md) (const WindowRef &window)

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

class BasicApp : public App {
  public:
    void mouseDrag(MouseEvent event) override;
    void keyDown(KeyEvent event) override;
    void draw() override;

  private:
    /*
     * This will maintain a list of points
     * which we will draw line segments between.
    */
    std::vector<vec2> mPoints;
};

void BasicApp::mouseDrag(MouseEvent event)
{
    /* Store the current mouse position in the list. */
    mPoints.push_back(event.getPos());
}

void BasicApp::keyDown(KeyEvent event)
{
    if(event.getCode() == KeyEvent::KEY_SPACE) {
        mPoints.clear();
    }
    else if(event.getCode() == KeyEvent::KEY_ESCAPE) {
        if(isFullScreen())
            setFullScreen(false);
        else
            quit();
    }
}

void BasicApp::draw()
{
    gl::clear(Color::gray(0.1f));

    // Set the current draw color to orange by setting values for
    // red, green and blue directly. Values range from 0 to 1.
    // See also: gl::ScopedColor
    gl::color(1.0f, 0.5f, 0.25f);

    // We're going to draw a line through all the points in the list
    // using a few convenience functions: 'begin' will tell OpenGL to
    // start constructing a line strip, 'vertex' will add a point to the
    // line strip and 'end' will execute the draw calls on the GPU.
    gl::begin(GL_LINE_STRIP);
    for(const vec2 &point : mPoints) {
        gl::vertex(point);
    }
    gl::end();
}

// This line tells Cinder to actually create and run the application.
CINDER_APP(BasicApp, RendererGl)
```