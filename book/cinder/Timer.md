### Timer

Time a block of code.

<br>
<br>
<br>

### Examples

```cpp
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace std;
using namespace ci;
using namespace ci::app;


class MyApp : public App {
public:
  void setup() override;
  void draw() override;

  gl::Texture2dRef mTexture;

};

void MyApp::setup()
{
    ci::Timer timer;

    string url = "https://www.cs.cmu.edu/~chuck/lennapg/len_std.jpg";

    timer.start();
    auto image = loadImage(loadUrl(url));
    timer.stop();

    mTexture = gl::Texture2d::create(image);

    // E.g. 1-2 seconds.
    app::console() << "Downloading texture took "
                   << timer.getSeconds()
                   << " seconds."
                   << endl;
}

void MyApp::draw()
{
    gl::clear(Color::gray(0.2));
}

CINDER_APP(MyApp, RendererGl);
```