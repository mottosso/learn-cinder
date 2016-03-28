### MouseEvent

Represents a mouse event.

| Namespace |
|-----------|
| [`ci::app::MouseEvent`](https://libcinder.org/docs/branch/master/classcinder_1_1app_1_1_mouse_event.html)

<br>
<br>
<br>

### Description

Passed to window events involving the mouse.

<br>
<br>
<br>

### Public Methods



| Output        | Method                                                      |
|--------------:|:------------------------------------------------------------|
| 				| MouseEvent ()
| 				| MouseEvent (const WindowRef &win, int initiator, int x, int y, unsigned int modifiers, float wheelIncrement, uint32_t nativeModifiers)
| int           | [getX]() () const
| int           | [getY]() () const
| const ivec2 & | [getPos]() () const
| void          | [setPos]() (const ivec2 &pos)
| bool          | [isLeft]() () const
| bool          | [isRight]() () const
| bool          | [isMiddle]() () const
| bool          | [isLeftDown]() () const
| bool          | [isRightDown]() () const
| bool          | [isMiddleDown]() () const
| bool          | [isShiftDown]() () const
| bool          | [isAltDown]() () const
| bool          | [isControlDown]() () const
| bool          | [isMetaDown]() () const
| bool          | [isAccelDown]() () const
| float         | [getWheelIncrement]() () const
| uint32_t      | [getNativeModifiers]() () const
| bool          | [isHandled]() () const
| void          | [setHandled]() (bool handled=true)
| WindowRef     | [getWindow]() () const
| void          | [setWindow]() (const WindowRef &window)

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