### ImageSource

<br>
<br>
<br>

### Public Members

| Output         | Member
|---------------:|:---------------|
|                | ImageSource ()
|                | ~ImageSource ()
| float          | getPixelAspectRatio () const
| bool           | isPremultiplied () const
| size_t | getRowBytes () const 
| int32_t | getCount () const
| void | load (ImageTargetRef target)=0
| int32_t | getWidth () const
| int32_t | getHeight () const
| ColorModel | getColorModel () const
| DataType | getDataType () const
| ChannelOrder | getChannelOrder () const
| bool | hasAlpha () const

<br>
<br>
<br>

### Example

![](https://cloud.githubusercontent.com/assets/2152766/14061326/7fc3a5f8-f375-11e5-89c8-c0e1680cf2ad.png)

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
    ImageSourceRef img = loadImage(loadUrl(
      "https://www.cs.cmu.edu/~chuck/lennapg/len_std.jpg"));
    mTex = gl::Texture2d::create(img);
}

void MyApp::draw()
{
    gl::clear();
    gl::draw(mTex);
}

CINDER_APP(MyApp, RendererGl)
```