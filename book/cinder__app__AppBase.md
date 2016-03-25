### App

Alias for an appropriate superclass for the current platform.

E.g.

- [AppMsw](cinder__app__AppMsw.md)
- [AppMac](cinder__app__AppMac.md)
- [AppWinRt](cinder__app__AppMsw.md)


| Namespace |
|------------
| `cinder::app::BaseApp`

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
	void	setup() override;
	void	draw() override;
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