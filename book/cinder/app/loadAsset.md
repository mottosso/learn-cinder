### loadAsset()

Returns a [`DataSourceRef`] to the active App's's asset. Throws a AssetLoadExc on failure.

| Namespace         | Include
|-------------------|-------------
| `app::loadAsset()` | `#include "cinder/app/app.h"`

[`DataSourceRef`]: ../DataSource.md

<br>
<br>
<br>

### Description

External files within a Cinder project are managed by the framework via this function.

<br>
<br>
<br>

### Signature

| Output          | Function
|----------------:|--------------
| DataSourceRef   | loadAsset (const fs::path &relativePath)


<br>
<br>
<br>

### Example

![image](https://cloud.githubusercontent.com/assets/2152766/14061326/7fc3a5f8-f375-11e5-89c8-c0e1680cf2ad.png)

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
    // Download image to your /assets directory.
    // https://www.cs.cmu.edu/~chuck/lennapg/len_std.jpg
    auto img = loadImage(loadAsset("len_std.jpg"));
    mTex = gl::Texture2d::create(img);
}

void MyApp::draw()
{
    gl::clear();
    gl::draw(mTex);
}

CINDER_APP(MyApp, RendererGl)
```