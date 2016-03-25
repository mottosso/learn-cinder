### AppBase

Baseclass to platform specific App subclasses.

| Namespace |
|-----------|
| [`cinder::app::BaseApp`](https://libcinder.org/docs/branch/master/classcinder_1_1app_1_1_app_base.html)

<br>
<br>
<br>

### Description

Use `cinder::app::App` which is an alias for an appropriate baseclass relative the current platform.

- [AppMsw](cinder__app__AppMsw.md) on Windows
- [AppMac](cinder__app__AppMac.md) on Osx


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
};

void MyApp::setup()
{
	gl::enableDepthWrite();
	gl::enableDepthRead();
}

void MyApp::draw()
{
	gl::clear(
		Color(0.25f, 0.25f, 0.25f)  // Gray
	);
}

CINDER_APP(MyApp, RendererGl)

```