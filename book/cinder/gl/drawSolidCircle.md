### `drawSolidCicle()`

| Namespace | Include
|-----------|-----------
| `gl::drawSolidCircle()` | `#include "cinder/gl.h"`

Draws a filled circle centered around center with a radius of radius . Default `numSegments` requests a conservative (high-quality, but slow) number based on radius.

> Using a GL convenience method should always be considered the slow path . They're fine for initial development or code that is not performance-sensitive, but [`gl::Batch`](Batch.md) should be preferred where speed counts.

<br>
<br>
<br>

### Signature

| Output      | Function
|------------:|:-------------------------
| void        | drawSolidCircle (const vec2 &center, float radius, int numSegments=-1)

<br>
<br>
<br>

### Example

![image](https://cloud.githubusercontent.com/assets/2152766/14055107/e43c3d64-f2d6-11e5-851c-9a69cefe58cb.png)

```cpp
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;

class MyApp : public App {
  public:
    void draw() override;
};

void MyApp::draw()
{
    gl::clear(Color::gray(0.1f));
    gl::bindStockShader(gl::ShaderDef().color());
    gl::drawSolidCircle(getWindowCenter(), 20.0f);
}

CINDER_APP(MyApp, RendererGl)
```