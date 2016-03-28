#### Surface

An in-memory representation of an image. Implicitly shared object.

| Namespace         | Include
|-------------------|------------
| `ci::Surface` | `#include "cinder/Surface.h"`


<br
<br>
<br>

### Description

A Surface always contains red, green and blue data, along with an optional alpha channel.

Surfaces come in two primary configurations, the traditional 8-bits per channel represented by Surface8u, and a float per channel, suitable for high dynamic range images, represented by Surface32f. Surface is a short-hand synonym for Surface8u.

Surfaces are a CPU-based image representation, and must be converted appropriately to be drawn using the GPU. For example, to be used with OpenGL the [`gl::Texture`] is a natural choice, and it can be constructed directly from a Surface.

[`gl::Texture`]: gl/Texture.md

To manipulate individual pixels of a Surface, the Surface::Iter class can be used.

To allocate a Surface that is 640x480 and has an alpha channel, use:

```cpp
Surface mySurface(640, 480, true);
```

A Surface can be created from an image file using the result of loadImage():

```cpp
auto image = loadImage("image.jpg");
Surface bitmap(image);
```

The pixels of each row of a Surface are stored in contiguous memory, and the start of each row is offset from the previous by the stride (measured in bytes) returned by getRowBytes(). Pixels can be ordered in memory in a number of configurations, specified using the SurfaceChannelOrder class.

<br>
<br>
<br>

### Example

![image](https://cloud.githubusercontent.com/assets/2152766/14065495/e60d628c-f423-11e5-865e-9fe443dbc173.png)


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
        Surface bitmap;
        Area area;
};

void MyApp::setup()
{
    auto img = loadImage(loadUrl(
        "https://www.cs.cmu.edu/~chuck/lennapg/len_std.jpg"
    ));

    Surface bitmap(img);

    Area area(0, 0, 500, 500);
    Surface::Iter iter = bitmap.getIter(area);
    while (iter.line()) {
        while (iter.pixel()) {
            iter.r() = 255 - iter.r();
            iter.g() = 255 - iter.g();
            iter.b() = 255 - iter.b();
        }
    }

    mTex = gl::Texture2d::create(bitmap);
}

void MyApp::draw()
{
    gl::clear();
    gl::draw(mTex);
}

CINDER_APP(MyApp, RendererGl)
```