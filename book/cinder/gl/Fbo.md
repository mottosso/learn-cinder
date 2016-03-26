### `Fbo`

Represents an OpenGL Framebuffer Object.

| Namespace                | Include   
|--------------------------|-----------
| [`cinder::gl::Fbo`]    | [`#include "cinder/gl/gl.h"`]

[`cinder::gl::Fbo`]: https://libcinder.org/docs/branch/master/classcinder_1_1gl_1_1_fbo.html
[`#include "cinder/gl/gl.h"`]: https://github.com/cinder/Cinder/blob/master/include/cinder/gl/gl.h

<br>
<br>
<br>

### Description

In OpenGL, the results of rendering commands end up as pixels in a 2D image called a framebuffer. The default framebuffer in OpenGL is automatically drawn to the screen, but Framebuffer Objects (FBOs) provide a mechanism for users to supply an alternative, off-screen destination. Drawing off-screen enables a number of effects which are difficult or impossible otherwise. For example, imagine you want to blur the entire screen. By using an FBO, you can capture the result of your rendering commands before they hit the screen, process those pixels using an OpenGL shader, and then draw the blurred pixels instead of the originals.

A framebuffer can also encapsulate more than just red-green-blue data per pixel. In fact by default OpenGL stores depth information, as well as alpha (or coverage) values, among other things. An FBO can also represent this additional information, allowing the storage and processing of alpha and depth information. Furthermore, all of this information can be used as textures in subsequent OpenGL rendering. This technique is often called render-to-texture.
Setting up an FBO
To setup an FBO, the first step is to specify the size of the FBO in pixels.

```cpp
#include "cinder/gl/Fbo.h"
using namespace ci;
gl::FboRef mFbo = gl::Fbo::create(640, 480);
```

Because we have not specified any formatting parameters, the FBO defaults to a format that emulates the normal screen-based framebuffer, storing RGB as well as alpha and depth information. To make use of the FBO, the first step is to bind it as the current framebuffer.

```cpp
myFbo->bindFramebuffer();
<...drawing commands...>
```

Now any rendering commands we issue will render to our FBO instead of the screen. Once we are finished rendering off-screen, we will want to restore the screen as the primary framebuffer, which we'll do like this:

```cpp
myFbo->unbindFramebuffer();
```

At this point, our FBO contains the result of our rendering commands stored as a [`gl::Texture`]. We can do any number of things with these pixels. Assuming we have a shader which blurs, we might do something like this:

[`gl::Texture`]: cinder/gl/Texture.md

```cpp
#include "cinder/gl/GlslProg.h"
gl::GlslProg blurShader;
blurShader.uniform("blurRadius", 5.0f);
blurShader.bind();
// Draw the contents of the Fbo
// by using it as a texture.
gl::draw( myFbo.getTexture() );
blurShader.unbind();
```

<br>
<br>
<br>

### Advanced Formats

The Cinder FBO class also support customizing what data is stored in the FBO using the Fbo::Format object. For example to enable mip-mapping, you would write something about like this:

```cpp
gl::Fbo::Format format;
format.enableMipmapping();
gl::Fbo myFbo( 640, 480, format );
```

The `Fbo::Format` object can also be used to modify the way the data of the framebuffer is stored. For example, on implementations that support it, we can enable a high dynamic range floating point framebuffer by passing the constant GL_RGBA32F as the format for storing the color data, meaning 32-bit floating point data for red, green, blue and alpha.

```cpp
gl::Fbo::Format hdrFormat;
hdrFormat.setColorInternalFormat( GL_RGBA32F );
gl::Fbo myHdrFbo( 640, 480, hdrFormat );
```

<br>
<br>
<br>

### Antialiasing with FBOs

The Cinder [`gl::Fbo`] also supports the option to antialias FBOs on implementations that support it. The typical technique is known as multisample antialiasing (MSAA), and works simply by taking several samples per pixel and averaging them together. This averaging step must be performed after all the rendering has taken place, and the Cinder FBO class automatically takes care of it when you call Fbo::getColorTexture() or Fbo::bindTexture().

[`gl::Fbo`]: cinder/gl/Fbo.md

In order to enable MSAA, set your format to use a value greater than 1 for its samples.

```cpp
gl::Fbo::Format msaaFormat;
msaaFormat.setSamples( 4 ); // enable 4x MSAA
gl::Fbo myMsaaFbo( 640, 480, msaaFormat );
```

Additionally, though currently limited to Nvidia cards on Windows, the Cinder FBO supports an antialiasing scheme known as coverage sample antialiasing (CSAA). This technique works by determining pixel coverage information (effectively alpha) in a less expensive manner than MSAA. Per Nvidia's documentation..

> "...CSAA produces antialiased images that rival the quality of 8x or 16x MSAA, while introducing only a minimal performance hit over standard (typically 4x) MSAA."

To understand more about how CSAA works, please refer to this documentation from Nvidia. This feature can be enabled in Cinder's [`gl::Fbo`] class like so:

```cpp
gl::Fbo::Format csaaFormat;
csaaFormat.setSamples( 4 );
csaaFormat.setCoverageSamples( 8 ); // a combination which creates the "CSAA 8x" mode
gl::Fbo myCsaaFbo( 640, 480, csaaFormat );
```

**Note**

Currenty by enabling FBO multisampling, you automatically disable the depth buffer's availablility as a texture, though your FBO may still contain a depth buffer; consequently getDepthTexture() and bindDepthTexture() will fail.

<br>
<br>
<br>

### Saving FBO Contents

Saving the pixels from an FBO is quite straightforward.

```cp[
#include "cinder/ImageIo.h"
writeImage( getHomeDirectory() + "myPixels.png", myFbo.getTexture() );
```

<br>
<br>
<br>

### Example

![image](https://cloud.githubusercontent.com/assets/2152766/14059908/688c6ba6-f30f-11e5-8371-c74ad8452d5d.png)


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
    
    CameraPersp     mCam;
    gl::BatchRef    mBox;
};

void MyApp::setup()
{
    gl::enableDepthRead();
    gl::enableDepthWrite();

    auto lambert = gl::ShaderDef().lambert().color();
    gl::GlslProgRef shader = gl::getStockShader(lambert);   
    mBox = gl::Batch::create(geom::Cube(), shader);
    
    mCam.lookAt(vec3(3, 4.5, 4.5), vec3(0, 1, 0));
}

void MyApp::draw()
{
    gl::clear(Color::gray(0.2f));

    gl::setMatrices(mCam);
    gl::pushModelMatrix();

    gl::translate(vec3(0, 0, 0));
    gl::scale(vec3(1.0f, 1.0f, 1.0f));
    gl::color(Color(CM_HSV, 0.5, 1, 1));

    mBox->draw();

    gl::popModelMatrix();
}

CINDER_APP(MyApp, RendererGl)
```
