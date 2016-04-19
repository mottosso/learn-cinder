### TriMesh

Construct a triangle mesh from `vec3` and `Color` objects.

| Namespace      | Include
|----------------|----------------
| `ci::TriMesh` | `#include "cinder/gl/gl.h"`

<br>
<br>
<br>

### Description

> Superseded by [`gl::Batch`].

Use the `TriMesh` when explicitly defining each position and color, but take care about performance; the `TriMesh` is implicitly converted to a [`VboMesh`] which in turn converts to a [`gl::Batch`].

When performance is important, always use [`gl::Batch`].

[`VboMesh`]: VboMesh.md
[`gl::Batch`]: gl/Batch.md
[`Surface`]: Surface.md

<br>
<br>
<br>

### VboMesh versus TriMesh

> Source: [VboMesh vs TriMesh](https://forum.libcinder.org/topic/vbomesh-vs-trimesh)

The difference between `TriMesh` and [`gl::VboMesh`] is similar to the difference between [`Surface`] and [`gl::Texture`]. The `TriMesh` is designed to be an in-memory representation for software, and [`gl::VboMesh`] is an OpenGL-specific hardware representation. The [`VboMesh`] is the fastest option, particularly if you are not modifying your geometry.

It can be a bit tricky to get it right however - check out the **VboMesh** sample.

- [samples/VboMesh][VboMesh]

[VboMesh]: https://github.com/cinder/Cinder/tree/master/samples/_opengl/VboMesh

[`gl::VboMesh`]: gl/VboMesh.md
[`gl::Texture`]: gl/Texture.md

<br>
<br>
<br>

### Comparing TriMesh and VboMesh

> Source: [VboMesh vs TriMesh](https://drewish.com/2014/08/16/comparing-the-trimesh-and-vbomesh-in-cinder/)

> This section is not yet compatible with Cinder 0.9.x

Comparing the TriMesh and VboMesh in Cinder   16 August 2014
I’ve been playing around with Cinder trying to make a simple app for drawing isometric images with triangles. I’m still learning my way around OpenGL and the wrapper classes Cinder offers but I like what I’ve seen so far. It’s been a lot of fun doing C++ again after a long time with Ruby and JavaScript.

I kept running into a random segfault when trying to draw anything using the VboMesh so I went looking for some super basic sample code. The closest thing I found was this slightly broken example. So I spent a little time cleaning it up, then got it drawing equilateral triangles:

![]()

I started wondering if I should be using the TriMesh instead, so I decided to try implementing the drawing that way so I could compare the code. It ended up a little cleaner, but since my goal is to have colors change when you touch a triangle, I’ll probably stick with the VboMesh so I can use dynamic colors.

Here’s the code in case it’s helpful for anyone else:

```cpp
// Simple demo to compare drawing 2D triangles with Cinder's VBO and TriMesh wrappers.
// https://drewish.com/2014/08/16/comparing-the-trimesh-and-vbomesh-in-cinder/

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Vbo.h"
#include "cinder/Trimesh.h"
#include "cinder/params/Params.h"

using namespace ci;
using namespace ci::app;
using namespace std;

// sqrt(3) / 2
#define M_SQRT_3_2 0.8660254037844386

class MeshTestApp : public AppBasic {
public:
    void prepareSettings( Settings *settings ) override;
    void setup();
    void recalculate();
    void buildVBOMesh();
    void buildTriMesh();
    void draw();

    gl::VboMesh mMesh;
    TriMesh mTriangles;
    params::InterfaceGl mParams;

    int  mCols = 10;
    int  mRows = 10;
    int  mScale = 30;
    bool mWireframe = false;
    bool useTriMesh = false;
};

void MeshTestApp::prepareSettings( Settings *settings )
{
    settings->enableHighDensityDisplay();
    settings->enableMultiTouch( false );
}

void MeshTestApp::setup()
{
    mParams = params::InterfaceGl( "Parameters", Vec2i( 220, 170 ) );
    mParams.addParam( "Scale", &mScale )
        .keyIncr( "s" ).keyDecr( "S" )
        .min( 1 ).max( 100 ).step( 1 )
        .updateFn( [this] { recalculate(); } );
    mParams.addParam( "Columns", &mCols )
        .keyIncr( "d" ).keyDecr( "D" )
        .min( 1 ).max( 100 ).step( 1 )
        .updateFn( [this] { recalculate(); } );
    mParams.addParam( "Rows", &mRows )
        .keyIncr( "f" ).keyDecr( "F" )
        .min( 1 ).max( 100 ).step( 1 )
        .updateFn( [this] { recalculate(); } );

    mParams.addParam( "Wireframe", &mWireframe )
        .key( "w" );
    mParams.addParam( "TriMesh/VBO", &useTriMesh )
        .updateFn( [this] { recalculate(); } )
        .key( "t" );

    recalculate();
}

void MeshTestApp::recalculate()
{
    if (useTriMesh) buildTriMesh();
    else buildVBOMesh();
}

void MeshTestApp::buildVBOMesh()
{
    gl::VboMesh::Layout layout;
    layout.setStaticIndices();
    layout.setStaticPositions();
    layout.setStaticColorsRGB();

    mMesh = gl::VboMesh(mCols * mRows * 3, mCols * mRows * 3, layout, GL_TRIANGLES);
    vector<uint32_t> indices;
    vector<Vec3f> positions;
    vector<Color> colors;

    float w = M_SQRT_3_2 * mScale;
    float h = 1.0 * mScale;
    int index = -1;
    Color8u color;

    for (int col = 0; col < mCols; col++) {
        float x = col * 2 * w;
        int direction = (col % 2) ? 1 : -1;
        for (int row = 0; row < mRows; row++) {
            direction *= -1;
            float y = row * h;

            positions.push_back( Vec3f( x - w * direction, y - h, 0 ) );
            positions.push_back( Vec3f( x + w * direction, y + 0, 0 ) );
            positions.push_back( Vec3f( x - w * direction, y + h, 0 ) );

            // #69D2E7 and #A7DBD8
            color = (direction > 0) ? Color8u( 105,210,231 ) : Color8u( 224,228,204 );
            colors.push_back( color );
            colors.push_back( color );
            colors.push_back( color );

            index += 3;
            indices.push_back( index - 2 );
            indices.push_back( index - 1 );
            indices.push_back( index );
        }
    }
    mMesh.bufferIndices( indices );
    mMesh.bufferPositions( positions );
    mMesh.bufferColorsRGB( colors );
}

void MeshTestApp::buildTriMesh()
{
    float w = M_SQRT_3_2 * mScale;
    float h = 1.0 * mScale;
    int index = -1;
    Color color;

    mTriangles.clear();

    for (int col = 0; col < mCols; col++) {
        float x = col * 2 * w;
        int direction = (col % 2) ? 1 : -1;
        for (int row = 0; row < mRows; row++) {
            direction *= -1;
            float y = row * h;

            mTriangles.appendVertex( Vec3f( x - w * direction, y - h, 0 ) );
            mTriangles.appendVertex( Vec3f( x + w * direction, y + 0, 0 ) );
            mTriangles.appendVertex( Vec3f( x - w * direction, y + h, 0 ) );

            // #69D2E7 and #A7DBD8
            color = (direction > 0) ? Color8u( 250,105,0 ) : Color8u( 105,210,231 );
            mTriangles.appendColorRgb( color );
            mTriangles.appendColorRgb( color );
            mTriangles.appendColorRgb( color );

            index += 3;
            mTriangles.appendTriangle( index - 2, index - 1, index );
        }
    }
}

void MeshTestApp::draw()
{
    gl::pushModelView();
    gl::clear( Color::white() );

    if (mWireframe) gl::enableWireframe();

    if (useTriMesh)
        gl::draw( mTriangles );
    else
        gl::draw( mMesh );

    if (mWireframe) gl::disableWireframe();

    gl::popModelView();

    mParams.draw();
}

CINDER_APP_BASIC( MeshTestApp, RendererGl )
```

<br>
<br>
<br>

### Optimisation

> Source: [Are Vbo binds expensive?](https://forum.libcinder.org/topic/are-vbo-binds-expensive)

A `TriMesh` is stored in system memory (closer to CPU) and a VboMesh is stored in device memory (closer to GPU), a VboMesh will always render faster than a `TriMesh`. What's more, in order to draw a `TriMesh` it is converted to [`VboMesh`] under the hood by Cinder anyway. To avoid overhead, it's better to do this only once instead of every frame.

Binding a [`VboMesh`] is relatively expensive because OpenGL is a state machine and it involves quite a lot of states to change. Compared to using a `TriMesh`, however, it is trivial. 

Step 1 of your optimizations should be to have all objects in device memory by creating a VboMesh from them. It's even better to create a [`gl::Batch`] which combines the mesh with the shader you use to draw it. Batches are faster than a VboMesh, for the same reason a [`VboMesh`] is faster than a `TriMesh`: the [`VboMesh`] is converted to a [`gl::Batch`] under the hood.

Next, you might want to have a look at instancing. Are you drawing 100's of instances of the same object? It's a lot faster to render all your objects with a single draw call. 

Next, make sure to apply some form of culling. Objects that are not visible (e.g. behind the camera) should not be sent to the GPU at all. Look at the frustum culling sample for more information.

Next, and a bit harder to implement, is sorting. Sort the objects from front (close to the camera) to back (further away). This avoids overdraw, where the same pixel is changed several times in a single frame. 

Finally, optimize your shader to run as fast as possible. And try to do as much in the shader as possible. You say you're using a dynamic mesh. Are you sure you have to update it on the CPU? You could also use a vertex shader to deform a static mesh, which in general is much faster.

<br>
<br>
<br>

### Public Members

| Output         | Member
|---------------:|-----------------
| void           | appendPosition (const vec3 &position)
| void           | appendPositions (const vec3 *positions, size_t num)
| void           | appendColorRgb (const Color &color)
| void           | appendColors (const Color *rgbs, size_t num)
| const VECDIM< DIM, float >::TYPE * | getPositions () const
| std::vector< vec3 > & | getNormals ()
| std::vector< vec3 > & | getTangents ()
| std::vector< vec3 > & | getBitangents ()
| COLORDIM< DIM, float >::TYPE * |  getColors ()
| void           | subdivide (int division=2, bool normalize=false)

<br>
<br>
<br>


### Examples

#### Basic

The shortest possible example.

![image](https://cloud.githubusercontent.com/assets/2152766/14067563/ff660762-f45e-11e5-9d72-9fd2b975ede1.png)

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

      TriMesh mesh;
};

void MyApp::setup()
{
    mesh = TriMesh(
        TriMesh::Format()
            .positions()
            .colors(3)
    );

    mesh.appendPosition(vec3(10, 100, 0));
    mesh.appendColorRgb(Color(0, 0, 0));
    mesh.appendPosition(vec3(100, 100, 0));
    mesh.appendColorRgb(Color(1, 0, 0));
    mesh.appendPosition(vec3(100, 10, 0));
    mesh.appendColorRgb(Color(1, 1, 0));
    mesh.appendPosition(vec3(10, 10, 0));
    mesh.appendColorRgb(Color(0, 1, 0));

    mesh.appendTriangle(0, 1, 2);
    mesh.appendTriangle(0, 2, 3);
}

void MyApp::draw()
{
    gl::clear();
    gl::draw(mesh);
}

CINDER_APP(MyApp, RendererGl, [](App::Settings *settings) {
    settings->setWindowSize(240, 160);
})
```

<br>
<br>
<br>

#### With camera

The above example assumed a default camera, which only renderes triangles at `z=0`. To render vertices in depth, you will need to establish a point of view.

![image](https://cloud.githubusercontent.com/assets/2152766/14067766/370cc3d6-f464-11e5-945c-a9e24f4ba0ef.png)


```cpp
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;


class MyApp : public App {
  public:
    void setup();
    void draw();

    CameraPersp mCam;
    TriMesh mMesh;
};

void MyApp::setup()
{
    mCam.lookAt(vec3(0, 0, 500), vec3(0));
}

void MyApp::draw()
{
    gl::clear();

    mMesh = TriMesh(
        TriMesh::Format()
            .positions()
            .colors(3)
    );

    mMesh.appendPosition(vec3(-100, 100, 0));
    mMesh.appendColorRgb(Color(0, 0, 0));
    mMesh.appendPosition(vec3(100, 100, 0));
    mMesh.appendColorRgb(Color(1, 0, 0));
    mMesh.appendPosition(vec3(100, -100, 0));
    mMesh.appendColorRgb(Color(1, 1, 0));
    mMesh.appendPosition(vec3(-100, -100, 0));
    mMesh.appendColorRgb(Color(0, 1, 0));

    mMesh.appendTriangle(0, 1, 2);
    mMesh.appendTriangle(0, 2, 3);

    gl::setMatrices(mCam);
    gl::pushModelView();
    gl::draw(mMesh);
    gl::popModelView();
}


CINDER_APP(MyApp, RendererGl, [](App::Settings *settings) {
    settings->setWindowSize(360, 240);
})

```

<br>
<br>
<br>

#### Sierpinski Triangle

> Source: [TriMesh HelloWorld](https://forum.libcinder.org/topic/trimesh-helloworld)

A more interesting example involving time.

![untitled](https://cloud.githubusercontent.com/assets/2152766/14067723/3bdcfe4a-f463-11e5-9a0b-cfbc0686c47b.gif)


```cpp
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

int sierpinski(TriMesh& mesh,
               const vec3& centre,
               float size,
               int tri_mesh_index,
               int num_iterations);

class MyApp : public App {
  public:
    void setup();
    void draw();

    CameraPersp mCam;
};

void MyApp::setup()
{
    mCam.lookAt(vec3(0, 0, 200), vec3(0), vec3(0, 1, 0));
}

void MyApp::draw()
{
    gl::clear();

    TriMesh mesh;
    int iterations = (int)((1 + sin(getElapsedSeconds())) * 4);
    sierpinski(mesh, vec3(0), 50, 0, iterations);

    gl::setMatrices(mCam);
    gl::pushModelView();
    gl::draw(mesh);
    gl::popModelView();
}


CINDER_APP(MyApp, RendererGl, [](App::Settings *settings) {
    settings->setWindowSize(640, 480);
})


/** Sierpinski Triangle
 *
 * Reference:
 *      https://en.wikipedia.org/wiki/Sierpinski_triangle
 *
*/
int sierpinski(TriMesh& mesh,
               const vec3& centre,
               float size,
               int tri_mesh_index,
               int num_iterations)
{
    if(num_iterations > 0)
    {
        num_iterations -= 1;
        float new_size = size * 0.5f;
        tri_mesh_index = sierpinski(mesh,
                                    centre + vec3(0, 1, 0) * new_size,
                                    new_size,
                                    tri_mesh_index,
                                    num_iterations);
        tri_mesh_index = sierpinski(mesh,
                                    centre + vec3(-1, -1, 0) * new_size,
                                    new_size,
                                    tri_mesh_index,
                                    num_iterations);
        tri_mesh_index = sierpinski(mesh,
                                    centre + vec3(1, -1, 0) * new_size,
                                    new_size,
                                    tri_mesh_index,
                                    num_iterations);
        return tri_mesh_index;
    }
    else
    {
        mesh.appendPosition(centre + vec3(0, 1, 0) * size);
        mesh.appendPosition(centre + vec3(-1, -1, 0) * size);
        mesh.appendPosition(centre + vec3(1, -1, 0) * size);
        mesh.appendTriangle(tri_mesh_index,
                            tri_mesh_index + 1,
                            tri_mesh_index + 2);

        return tri_mesh_index + 3;
    }
}
```

<br>
<br>
<br>

#### 3D

This is how you can draw triangles with depth.

![image](https://cloud.githubusercontent.com/assets/2152766/14067835/8c0fad92-f466-11e5-9764-ab69799b0d9a.png)

```cpp
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;


class MyApp : public App {
  public:
    void setup();
    void draw();

    CameraPersp mCam;
    TriMesh mMesh;
};

void MyApp::setup()
{
    gl::enableDepthWrite();
    gl::enableDepthRead();

    mCam.lookAt(vec3(250, 200, 500), vec3(0));
}

void MyApp::draw()
{
    gl::clear();

    mMesh = TriMesh(
        TriMesh::Format()
            .positions()
            .colors(3)
    );

    // Create the points of our cube
    vec3 v0 { -100, -100, -100 };
    vec3 v1 {  100, -100, -100 };
    vec3 v2 {  100,  100, -100 };
    vec3 v3 { -100,  100, -100 };
    vec3 v4 { -100, -100,  100 };
    vec3 v5 {  100, -100,  100 };
    vec3 v6 {  100,  100,  100 };
    vec3 v7 { -100,  100,  100 };

    // Create the colors for each vertex
    Color c0 { 0, 0, 0 };
    Color c1 { 1, 0, 0 };
    Color c2 { 1, 1, 0 };
    Color c3 { 0, 1, 0 };
    Color c4 { 0, 0, 1 };
    Color c5 { 1, 0, 1 };
    Color c6 { 1, 1, 1 };
    Color c7 { 0, 1, 1 };

    vec3 faces[6][4] = { /* Vertices for the 6 faces of a cube. */
        {v0, v1, v2, v3}, {v3, v2, v6, v7}, {v7, v6, v5, v4},
        {v4, v5, v1, v0}, {v5, v6, v2, v1}, {v7, v4, v0, v3}
    };

    Color colors[6][4] = { /* colors for each vertex of the cube. */
        {c0, c1, c2, c3}, {c3, c2, c6, c7}, {c7, c6, c5, c4},
        {c4, c5, c1, c0}, {c5, c6, c2, c1}, {c7, c4, c0, c3}
    };

    for (int i = 0; i < 6; i++)
    {
        mMesh.appendPosition(faces[i][0]);
        mMesh.appendColorRgb(colors[i][0]);
        mMesh.appendPosition(faces[i][1]);
        mMesh.appendColorRgb(colors[i][1]);
        mMesh.appendPosition(faces[i][2]);
        mMesh.appendColorRgb(colors[i][2]);
        mMesh.appendPosition(faces[i][3]);
        mMesh.appendColorRgb(colors[i][3]);

        int numberVertices = mMesh.getNumVertices();

        mMesh.appendTriangle(numberVertices - 4,
                             numberVertices - 3,
                             numberVertices - 2);

        mMesh.appendTriangle(numberVertices - 4,
                             numberVertices - 2,
                             numberVertices - 1);
    }

    gl::setMatrices(mCam);
    gl::pushModelView();
    gl::draw(mMesh);
    gl::popModelView();
}


CINDER_APP(MyApp, RendererGl, [](App::Settings *settings) {
    settings->setWindowSize(360, 240);
})
```

<br>
<br>
<br>

#### Textures

![](https://cloud.githubusercontent.com/assets/2152766/14077815/aa9d5f26-f4e7-11e5-9010-45b11c2631dc.png)

```cpp
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;


class MyApp : public App {
  public:
    void setup();
    void draw();

    CameraPersp mCam;
    TriMesh mMesh;
    gl::Texture2dRef mTex;
    gl::GlslProgRef mGlsl;
};

void MyApp::setup()
{
    gl::enableDepthWrite();
    gl::enableDepthRead();

    auto image = loadImage(loadUrl("https://www.cs.cmu.edu/~chuck/lennapg/len_std.jpg"));
    mTex = gl::Texture2d::create(image);
    mCam.lookAt(vec3(250, 200, 500), vec3(0));
}

void MyApp::draw()
{
    gl::clear();

    mMesh = TriMesh(
        TriMesh::Format()
            .positions()
            .texCoords(2)
    );

    // Create the points of our cube
    vec3 v0 { -100, -100, -100 };
    vec3 v1 {  100, -100, -100 };
    vec3 v2 {  100,  100, -100 };
    vec3 v3 { -100,  100, -100 };
    vec3 v4 { -100, -100,  100 };
    vec3 v5 {  100, -100,  100 };
    vec3 v6 {  100,  100,  100 };
    vec3 v7 { -100,  100,  100 };

    // Create the colors for each vertex
    Color c0 { 0, 0, 0 };
    Color c1 { 1, 0, 0 };
    Color c2 { 1, 1, 0 };
    Color c3 { 0, 1, 0 };
    Color c4 { 0, 0, 1 };
    Color c5 { 1, 0, 1 };
    Color c6 { 1, 1, 1 };
    Color c7 { 0, 1, 1 };

    // Create the texture coordinates for each vertex
    vec2 t0 { 0, 0 };
    vec2 t1 { 1, 0 };
    vec2 t2 { 1, 1 };
    vec2 t3 { 0, 1 };

    vec3 faces[6][4] = { /* Vertices for the 6 faces of a cube. */
        {v0, v1, v2, v3}, {v3, v2, v6, v7}, {v7, v6, v5, v4},
        {v4, v5, v1, v0}, {v5, v6, v2, v1}, {v7, v4, v0, v3}
    };

    for (int i = 0; i < 6; i++)
    {
        mMesh.appendPosition(faces[i][0]);
        mMesh.appendTexCoord(t0);
        mMesh.appendPosition(faces[i][1]);
        mMesh.appendTexCoord(t1);
        mMesh.appendPosition(faces[i][2]);
        mMesh.appendTexCoord(t2);
        mMesh.appendPosition(faces[i][3]);
        mMesh.appendTexCoord(t3);

        int numberVertices = mMesh.getNumVertices();

        mMesh.appendTriangle(numberVertices - 4,
                             numberVertices - 3,
                             numberVertices - 2);

        mMesh.appendTriangle(numberVertices - 4,
                             numberVertices - 2,
                             numberVertices - 1);
    }

    gl::setMatrices(mCam);

    // Apply shader and texture
    gl::ScopedGlslProg glslScope { gl::getStockShader(gl::ShaderDef().texture()) };
    gl::ScopedTextureBind texScope { mTex };

    gl::draw(mMesh);

}


CINDER_APP(MyApp, RendererGl, [](App::Settings *settings) {
    settings->setWindowSize(640, 480);
})
```