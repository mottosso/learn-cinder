### CINDER_APP

Main application macro.

<br>
<br>
<br>

### Description

This macro wraps the native `main()` function for the currently running platform.

For example, this is the [macro for Linux](https://github.com/cinder/Cinder/blob/1010367c4da00347717cd89f513f9b047ec3c02f/include/cinder/app/linux/AppLinux.h).

```txt
#define CINDER_APP_LINUX( APP, RENDERER, ... )                                \
int main( int argc, char* argv[] )                                            \
{                                                                             \
    cinder::app::RendererRef renderer( new RENDERER );                        \
    cinder::app::AppLinux::main<APP>( renderer, #APP, argc, argv, ##__VA_ARGS__ ); \
    return 0;                                                                 \
}
```

The decision about which macro to use is located in [`App.h`]

[`App.h`]: https://github.com/cinder/Cinder/blob/1010367c4da00347717cd89f513f9b047ec3c02f/include/cinder/app/App.h

<br>
<br>
<br>

### Examples

Macro is at the bottom.

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
};

void MyApp::setup()
{
    gl::enableDepthWrite();
    gl::enableDepthRead();
}

void MyApp::draw()
{
    gl::clear(Color::gray(0.2));
}

CINDER_APP(MyApp, RendererGl)
```