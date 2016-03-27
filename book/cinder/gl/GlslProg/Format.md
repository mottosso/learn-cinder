### Format

A convenient way to write GLSL code inline with our C++ code.

| Namespace       | Include
|-----------------|-------------
| `gl::GlslProg::Format` | `#include "cinder/gl/GlslProg.h"`

<br>
<br>
<br>

### Description

This macro enables the declaration of GLSL with overall C++ code and is useful for debugging, testing, and sharing of small snippets of code on forums and mailing lists.

It serves as a simplified alternative to storing `.vert` and `.frag` files on disk and loading them via the Cinder [Asset] or [Resource] system.

[Asset]: https://libcinder.org/docs/branch/master/guides/resources/index.html
[Resource]: https://libcinder.org/docs/branch/master/guides/resources/index.html

<br>
<br>
<br>

### Example

![image](https://cloud.githubusercontent.com/assets/2152766/14060620/b90753e4-f327-11e5-9b90-a69baedb3c10.png)

```cpp
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/GlslProg.h"

using namespace ci;
using namespace ci::app;

class MyApp : public App {
  public:
    void    setup() override;
    void    draw() override;

    CameraPersp         mCam;
    gl::BatchRef        mCube;
    gl::GlslProgRef     mGlsl;
};

void MyApp::setup()
{
    mCam.lookAt(vec3(3, 2, 4), vec3(0));

    mGlsl = gl::GlslProg::create(gl::GlslProg::Format()
    .vertex(CI_GLSL(150,
        uniform mat4    ciModelViewProjection;
        in vec4         ciPosition;
        
        void main(void) {
            gl_Position = ciModelViewProjection * ciPosition;
        }
    ))
    .fragment(CI_GLSL(150,
        out vec4            oColor;
        
        void main(void) {
            oColor = vec4(1, 0.5, 0.25, 1);
        }
    )));

    mCube = gl::Batch::create(geom::Cube(), mGlsl);
    
    gl::enableDepthWrite();
    gl::enableDepthRead();
}

void MyApp::draw()
{
    gl::clear(Color(0.2f, 0.2f, 0.2f));
    gl::setMatrices(mCam);
    mCube->draw();
}

CINDER_APP(MyApp, RendererGl)
```