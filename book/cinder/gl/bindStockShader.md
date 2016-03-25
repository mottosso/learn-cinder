### `bindStockShader()`

| Output      | Function
|------------:|:-------------------------
| void        | bindStockShader (const class ShaderDef &shader)

Bind and cache instance of [`gl::GlslProg`](GlslProg.md) generated via [`gl::ShaderDef()`](ShaderDef.md).

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
    gl::color(1.0f, 1.0f, 1.0f); // default
    gl::drawSolidCircle(getWindowCenter(), 20.0f);
}

CINDER_APP(MyApp, RendererGl)
```