### getStockShader()

Generate generic shader.

| Namespace              | Include
|:-----------------------|:----------------
| [`ci::gl::getStockShader()`] | [`#include "cinder/gl/gl.h"`]

[`gl::getStockShader()`]: https://libcinder.org/docs/branch/master/namespacecinder_1_1gl.html
[`#include "cinder/gl/gl.h"`]: https://github.com/cinder/Cinder/blob/master/include/cinder/gl/gl.h

<br>
<br>
<br>

### Signature

| Output        | Function
|--------------:|:-----------
| [`GlslProgRef`] & | getStockShader (const class ShaderDef &shader)

[`GlslProgRef`]: GlslProg.md

### Example

![image](https://cloud.githubusercontent.com/assets/2152766/14060039/a2b95e52-f313-11e5-81ef-cf9eade9120e.png)

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

    gl::BatchRef mCircleBatch;
};

void MyApp::setup()
{
    gl::enableDepthWrite();
    gl::enableDepthRead();

    auto lambert = gl::ShaderDef().lambert().color();
    gl::GlslProgRef shader = gl::getStockShader(lambert);
    mCircleBatch = gl::Batch::create(
        geom::Circle().radius(30), shader
    );
}

void MyApp::draw()
{
    gl::clear(Color::gray(0.2f));

    for (float angle = 0; angle < 2 * M_PI; angle += 0.2f) {
        gl::pushModelMatrix();
        gl::translate(
            getWindowCenter() + 200.0f * vec2(sin(angle), cos(angle))
        );
        gl::color(
            Color(CM_HSV, angle / (2 * M_PI), 1, 1)
        );
        mCircleBatch->draw();
        gl::popModelMatrix();
  }
}

CINDER_APP(MyApp, RendererGl)
```