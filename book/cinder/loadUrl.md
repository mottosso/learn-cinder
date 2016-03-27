### `loadUrl()`

Passed to [`loadImage()`] to load an image from a URL.

[`loadImage()`]: loadImage.md

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
    
        gl::Texture2dRef mTex;
};

void MyApp::setup()
{
    auto img = loadImage(loadUrl(
        "https://www.cs.cmu.edu/~chuck/lennapg/len_std.jpg"
    ));
    mTex = gl::Texture2d::create(img);
}

void MyApp::draw()
{
    gl::clear();
    gl::draw(mTex);
}

CINDER_APP(MyApp, RendererGl)

```