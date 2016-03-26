![image](https://cloud.githubusercontent.com/assets/2152766/14053112/080dd7f8-f2c7-11e5-9629-2d8211dcb2fc.png)

This guide is written with users of previous versions of Cinder in mind, and is meant to aid in the transition to Cinder’s new OpenGL API in version 0.9.x.

> Source - [forum.libcinder.org](https://forum.libcinder.org/#Topic/23286000002367065)

<br>
<br>
<br>

### History

OpenGL has evolved considerably in recent versions. And with the introduction of Core Profile  in OpenGL 3.2 (and parallel changes in OpenGL ES 2), much of the functionality of previous versions has been removed entirely. Most prominent was the removal of the fixed function pipeline,  which gave way to the fully programmable pipeline . This change allows OpenGL to more closely map to the underlying hardware, and is a significant improvement with respect to power and performance. However some of the simpler techniques for interacting with GL in previous versions are no longer available.


With version 0.9.x, Cinder attempts to expose this new power, while still maintaining a relatively easy-to-use API.  While this document is not an exhaustive tutorial on the new API, it does cover the core concepts, and should be supplemented with a look at the sample code found in samples/_opengl.

<br>
<br>
<br>

### What’s Changed in OpenGL Itself?

Quite a bit of functionality was removed with OpenGL Core Profile. One of the most significant changes is that OpenGL no longer provides a way to draw without a GLSL program (informally called a shader). Furthermore, immediate mode - functions like [`glBegin()`], [`glVertex()`] and [`glEnd()`] - are no longer available. OpenGL also no longer has the notion of a vertex normal, a color, or similar. Instead, all such data is generic per-vertex data which the user supplies in the form of GLSL attributes. This vertex data is also only made available to GLSL programs via generic buffers of vertex data called Vertex Buffer Objects  (VBOs). Additionally, OpenGL no longer has the concept of the `GL_MODELVIEW` or `GL_PROJECTION` matrices. Similar to generic attributes, such data are the responsibility of the programmer to maintain and to pass to her shaders via generic GLSL uniform variables. Much of the global state in previous versions of GL is gone entirely as well. For example, texturing is no longer enabled via `glEnable(GL_TEXTURE_2D)`. Such state is no longer state at all, but is simply implemented or not implemented in the currently bound GLSL program.

[`glBegin()`]: https://www.opengl.org/sdk/docs/man2/xhtml/glBegin.xml
[`glVertex()`]: https://www.opengl.org/sdk/docs/man2/xhtml/glVertex.xml
[`glEnd()`]: https://www.opengl.org/sdk/docs/man2/xhtml/glEnd.xml

<br>
<br>
<br>

### What’s Changed in Cinder?

As you might imagine, Cinder has changed quite a bit too in order to embrace this new philosophy in OpenGL. We’ve attempted to create an API that captures the power of this new way of working, but have also tried to maintain abstractions that are much simpler to use than pure GL. While some things have necessarily become more complex, we believe the benefits easily outweigh the costs, and that you’ll find this new approach to be not only more capable but even more enjoyable to use.

<br>
<br>
<br>

### Getting Started

In previous versions of Cinder, the easiest way to draw was to use the GL convenience methods, like [`gl::drawSolidCircle()`]. This is still true in 0.9.x, but with a minor caveat. As mentioned previously, OpenGL now requires a shader to be bound, so we’ll need to provide it one. Cinder offers a class called [`gl::ShaderDef`] for easily generating common shaders. To draw a solid white circle, this is the code:

```cpp
gl::bindStockShader(gl::ShaderDef().color());
gl::drawSolidCircle(vec2(100, 100), 50);
```

As in previous versions, [`gl::drawSolidCircle()`] takes a center point and a radius. However the preceding line is new. [`gl::bindStockShader()`] accepts a [`gl::ShaderDef`] and generates a shader (a [`gl::GlslProg`]) as is necessary. It also caches these [`gl::GlslProg`]'s to avoid unnecessary compilation. In this example, we’re using `.color()` on the [`gl::ShaderDef`] in order to request that the current color be used, which defaults to white.

To make our circle red we use the same function we’d use in previous versions, `gl::color()`:

```cpp
gl::bindStockShader(gl::ShaderDef().color());
gl::color(1, 0, 0);
gl::drawSolidCircle(vec2(100, 100), 50);
```

Essentially all GL convenience methods (`gl::drawCube()`, `gl::drawSphere()`, `gl::drawSolidRect()`, etc) still function in 0.9.x, and there are new convenience methods as well. However, using a GL convenience method should always be considered the slow path . They’re fine for initial development or code that is not performance-sensitive, but the techniques we’ll discuss next should always be preferred when speed counts.

[`gl::drawSolidCircle()`]: cinder/gl/drawSolidCircle.md

<br>
<br>
<br>

### Batches

[`gl::Batch`] is the fast path in Cinder 0.9.x for typical cases. An instance of [`gl::Batch`] represents the combination of geometry and an associated shader. To get started, let’s optimize our previous use of the convenience method [`gl::drawSolidCircle()`].

[`gl::Batch`]: cinder/gl/Batch.md


```cpp
class MyApp : public App {
  gl::BatchRef mCircleBatch;
};

void MyApp::setup()
{
   gl::GlslProgRef solidShader = gl::getStockShader(
     gl::ShaderDef().color()
   );

  mCircleBatch = gl::Batch::create(
    geom::Circle()
      .center(vec2(100, 100))
      .radius(50),
    solidShader);
}

void MyApp::draw()
{
  gl::clear();
  gl::color(1, 0, 0);
  mCircleBatch->draw();
}
```

This code touches on several different new concepts. First, we’re using our [`gl::ShaderDef`] slightly differently. Rather than binding it using [`gl::bindStockShader()`], we’re using [`gl::getStockShader()`], which returns a proper [`gl::GlslProgRef`] based on a [`gl::ShaderDef`]. Next, we construct a [`gl::Batch`]. The constructor (called via create()) accepts geometry as the first parameter and a [`gl::GlslProgRef`] as the second parameter - in our case the one we just generated with [`gl::getStockShader()`].

Let’s look at the first parameter to our Batch construction, the geometry portion..

```cpp
geom::Circle().center(100, 100).radius(50)
```

This uses [`geom::Circle()`], which is one of many classes provided with Cinder that can be used to create geometry. Other examples include [`geom::Sphere()`], [`geom::Teapot()`], [`geom::WireCone()`], and many others. The pairing of one of these [`geom::Source`]'s (or another source of geometry, such as a [`TriMesh`] or a [`VboMesh`]) with a shader (i.e. [`gl::GlslProg`]) is expressed with a [`gl::Batch`].

To draw a [`gl::Batch`] we simply use its `draw()` member method. Notice that we still set the color with [`gl::color()`]. Cinder “knows” that the Batch’s shader requires the current color, and it passes it along in a uniform automatically. We’ll look at how that machinery works later.

[`TriMesh`]: cinder/TriMesh.md
[`VboMesh`]: cinder/VboMesh.md
[`geom::Source`]: cinder/geom/Source.md
[`geom::Sphere()`]: cinder/geom/Sphere.md
[`geom::Teapot()`]: cinder/geom/Teapot.md
[`geom::WireCone()`]: cinder/geom/WireCone.md
[`geom::Circle()`]: cinder/geom/Circle.md
[`gl::GlslProgRef`]: cinder/gl/GlslProg.md
[`gl::GlslProg`]: cinder/gl/GlslProg.md
[`gl::getStockShader()`]: cinder/gl/getStockShader.md
[`gl::bindStockShader()`]: cinder/gl/bindStockShader.md
[`gl::ShaderDef`]: cinder/gl/ShaderDef.md
[`gl::color()`]: cinder/gl/color.md

<br>
<br>
<br>

### Transformations

In previous versions of OpenGL (and Cinder), there was a global stack of two matrices, one for the ModelView matrix, and one for the Projection matrix. Users manipulated these stacks with functions like [`glTranslatef()`] or in Cinder, [`gl::translate()`]. In modern GL these stacks are removed entirely. However Cinder still provides this useful functionality through the same methods - [`gl::translate()`], [`gl::scale()`], [`gl::rotate()`], etc.

One key difference is that Cinder now separates the Model and View matrices. Calls to [`gl::translate()`] et al manipulate the active Model matrix; there is no longer the concept of the matrix mode (formerly manipulated with the now defunct [`glMatrixMode()`]). Here’s an example; we can adapt the code above to draw a number of circles in a circular arrangement, all using the same [`gl::Batch`].

First a modification to our [`setup()`] routine to create our [`geom::Circle()`] at the default origin, rather than at `vec2(100, 100)` as previously. We’ll also shrink the radius a bit:

```cpp
mCircleBatch = gl::Batch::create(
  geom::Circle()
    .radius(30),
  solidShader
);
```

And now in `draw()`, we’ll do the following:

```cpp
void MyApp::draw()
{
  gl::clear();        

  for (float angle = 0; angle < 2 * M_PI; angle += 0.2f) {
    gl::pushModelMatrix();
    gl::translate(
      getWindowCenter() + 200.0f * vec2(sin(angle), cos(angle))
    );
    gl::color(
      Color(CM_HSV, angle / (2 * M_PI), 1, 1)
    );
    mCircleBatch->draw();
    gl::popModelMatrix();
  }
}
```

Let’s look at this routine.

A for-loop iterates from 0 to 2 pi radians. Within the loop we preserve the current Model matrix using [`gl::pushModelMatrix()`]. We then translate the current Model transformation to the window center plus a bit of trigonometry to arrange the circles’ centers in a larger circle of radius 200. Next we set the current color using HSV color, and then draw our [`gl::Batch`]. Note that this draw command is “aware” of the current Model matrix (not to mention View and Projection) as well as the current color automatically. Finally, we restore the Model matrix to what it was previous to this iteration of the loop, using [`gl::popModelMatrix()`].

![image](https://cloud.githubusercontent.com/assets/2152766/14053127/2591f62e-f2c7-11e5-81a3-8053670c19ff.png)

[`glMatrixMode()`]: https://www.opengl.org/sdk/docs/man2/xhtml/glMatrixMode.xml
[`glTranslatef()`]: https://www.opengl.org/sdk/docs/man2/xhtml/glTranslate.xml
[`gl::translate()`]: cinder/gl/translate.md
[`gl::rotate()`]: cinder/gl/rotate.md
[`gl::scale()`]: cinder/gl/scale.md
[`gl::pushModelMatrix()`]: cinder/gl/pushModelMatrix.md
[`gl::popModelMatrix()`]: cinder/gl/popModelMatrix.md
[`setup()`]: cinder/app/AppBase.md#setup

<br>
<br>
<br>

### Scoped Utilities and State

In Cinder 0.9.x you’ll see a number of classes which begin with gl::Scoped in the name; such as [`gl::ScopedModelMatrix`], [`gl::ScopedColor`], and [`gl::ScopedTextureBind`].

While there are other ways to achieve the same thing, these classes are efficient and easy to use. They are designed around RAII, preserving a given piece of state on instantiation and restoring it on destruction. As an example, let’s rework the previous for-loop to use a [`gl::ScopedModelMatrix`]:

```cpp
for (float angle = 0; angle < 2 * M_PI; angle += 0.2f) {
  gl::ScopedModelMatrix scpModelMtx;
  gl::translate(
    getWindowCenter() + 200.0f * vec2(sin(angle), cos(angle))
  );
  gl::color(
    Color(CM_HSV, angle / (2 * M_PI), 1, 1)
  );
  mCircleBatch->draw();
}
```

In this example, creating our variable scpModelMtx  preserves the Model matrix at its point of instantiation. We then manipulate the Model matrix using [`gl::translate()`]. And when the destructor for scpModelMtx  fires at the end of the loop iteration, it will restore the Model matrix to its value when scpModelMtx  was instantiated.


Additionally, it’s worth noting that Cinder now caches virtually all state in a class called [`gl::Context`]. This allows Cinder to save and restore state quickly without querying GL for the active values. As a result, it’s safe and fast to use these `gl:: Scoped*`  family of classes for preserving state.

[`gl::ScopedModelMatrix`]: cinder/gl/ScopedModelMatrix.md
[`gl::ScopedColor`]: cinder/gl/ScopedColor.md
[`gl::ScopedTextureBind`]: cinder/gl/ScopedTextureBind.md
[`gl::Context`]: cinder/gl/Context.md

<br>
<br>
<br>

### Writing Custom Shaders

While [`gl::ShaderDef`] is helpful for basic shaders - in addition to `.color()`, it supports `.texture()` and `.lambert()` - it’s common to write your own GLSL. Let’s look at an example of how to do that.


We’ll keep the same circle example, and write a shader that takes the place of our ShaderDef-created version. For the purposes of this example, we’ll make use of the [`CI_GLSL()`] macro, which allows writing GLSL code inline. Our setup routine looks like this now:

[`CI_GLSL()`]: cinder/gl/CI_GLSL.md

```cpp
void MyApp::setup()
{
  gl::GlslProgRef solidShader = gl::GlslProg::create(
     // vertex code
     CI_GLSL(150,
       uniform mat4        ciModelViewProjection;

       in vec4                ciPosition;
       in vec4                ciColor;

       out lowp vec4        Color;

       void main(void)
       {
         gl_Position        = ciModelViewProjection * ciPosition;
         Color              = ciColor;
       }
     ),
     // fragment code
     CI_GLSL(150,
       in vec4          Color;
       out vec4         oColor;

       void main(void)
       {
         oColor = Color;
       }
     )
  );

  mCircleBatch = gl::Batch::create(
    geom::Circle()
      .radius(30),
    solidShader
  );
}
```


And just to reiterate, if we had written files named say, `solidColor.vert`  and `solidColor.frag` and stored them as files in our assets  directory - a more common workflow - we’d see a line like this instead of the CI_GLSL macros:

```cpp
GlslProgRef solidShader = gl::GlslProg::create(
  loadAsset("solidColor.vert"),
  loadAsset("solidColor.frag")
);
```

Looking at our GLSL code above, you’ll see a few distinctive things. First, we have both uniforms and attributes with the prefix ci  - ciModelViewProjection, as well as attributes `ciPosition` and `ciColor`. These names are special, and serve as signals to Cinder to automatically fill in their values appropriately. As you might imagine, `ciModelViewProjection` is equivalent to the current Model, View and Projection matrices concatenated into a single mat4. If you have been writing GLSL shaders in prior OpenGL versions, you likely used the now defunct gl_ModelViewProjectionMatrix variable for this.

Similarly, there are automatically recognized vertex attributes; in the example above they are `ciPosition` and `ciColor`. In the case of `ciPosition`, this attribute is automatically supplied by our [`geom::Circle()`]. `ciColor` is similar but has a unique caveat. If our [`geom::Source`] had supplied a color, the shader would have used it. However Cinder automatically supplies the global current color (set via [`gl::color()`]) in the absence of a per-vertex color. As an experiment, let’s try slightly different geometry that does supply per-vertex color. If we change the Batch assignment in [`setup()`] out like this:

```cpp
ColorAf green(0, 1, 0), blue(0, 0, 1);
mBatch = gl::Batch::create(
  geom::Rect()
    .colors(green, green, blue, blue)
    .rect(Rectf(-15, -10, 15, 10)),
  solidShader
);
```

We see this:

![image](https://cloud.githubusercontent.com/assets/2152766/14053136/387b1d42-f2c7-11e5-8336-758fff591a63.png)


Here we see the global color is ignored as geom::Rect has generated per-vertex colors upon our request. For the curious, this automatic variable uploading occurs in the [`gl::Batch.draw()`](`gl::Batch`) call, and it can be invoked manually in advanced usage scenarios. Furthermore, there are mechanisms for manually configuring the mapping to attributes and uniforms in GlslProg::Format for users that have some reason to use a non - default configuration.

<br>
<br>
<br>

### Conclusion

The OpenGL API in Cinder 0.9.x is quite deep - much more so than can be captured in this post. However hopefully this serves as enough background to dig into the samples, which are the best place to learn until we have more thorough documentation.
