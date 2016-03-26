### Color

A basic color.

| Namespace        | Include 
|:-----------------|:------------
| `Color`          | `#include "cinder/Color.h"`

<br>
<br>
<br>

### Static Members

| Output        | Function
|--------------:|:---------------
| ColorT< T >  | zero ()
| ColorT< T >  | black ()
| ColorT< T >  | white ()
| ColorT< T >  | gray (T value, T alpha=CHANTRAIT< T >::max())
| ColorT< T >  | hex (uint32_t hexValue)
| ColorAT< T >  | hexA (uint32_t hexValue)

<br>
<br>
<br>

### Example

![image](https://cloud.githubusercontent.com/assets/2152766/14059925/be197bae-f30f-11e5-8670-350fce5ee2ba.png)

```cpp
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;

class MyApp : public App {
  public:
    void draw() override;
};

void MyApp::draw()
{
    gl::clear(Color::gray(0.2f));
}

CINDER_APP(MyApp, RendererGl)
```