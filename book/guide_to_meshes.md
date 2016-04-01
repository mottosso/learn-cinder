![image](https://cloud.githubusercontent.com/assets/2152766/14066057/68f254d2-f438-11e5-9883-e4fc48054099.png)

<br>
<br>
<br>

## Guide to Meshes

> Source: [creativeapplications.net](http://www.creativeapplications.net/tutorials/guide-to-meshes-in-cinder-cinder-tutorials/)

This article is going to cover two things in great detail: **vertices** and **meshes** and how they are handled in Cinder.

There are a few different names for things that may be new to you in this tutorial which I’ll lay out for you right at the beginning: vertices, mesh, [`TriMesh`], [`VboMesh`], and VBOs. If any of those are already familiar to you and you simply want implementation details on how they work, feel free to skip ahead or around, I won’t be offended. For those of you who want more background, we’ll proceed in an orderly fashion.

So, let’s begin at the beginning: the vertex.

In Cinder we use the OpenGL coordinate system which is a right-handed system. Initially the world is oriented at the upper left hand corner of your screen, so the x Axis points right, y Axis points downward, z Axis points into the screen (away from the user). A vertex is a point in geometrical shape, or, a vertex is a point in 3D space that has x, y, and z properties that determine where it is in relation to the 0, 0, 0 point (you can think of this as the center) of the world. For instance, a vertex with the values 100, 100, 100, describes a location 100 pixels to the right on the x axis, down on the y axis, and back on the z axis from the origin of the world in which it is located. In your Cinder application, unless you change it, the world is oriented at the upper left hand corner of your screen. All shapes are the result of the connections between vertices. So, a line is made up of the connections between two vertices, a pyramid is a construction made of the connections between five vertices, a cube is made up of the connections between eight vertices.

![image](https://cloud.githubusercontent.com/assets/2152766/14066062/7744ee78-f438-11e5-96ec-137235424e19.png)

What do these vertices look like in code? Something like this:

```cpp
gl::vertex(vec3(300, 100, 0)); // creates an OpenGL vertex from a vec3
```

Those vertices are passed to your graphics card and your graphics card fill in the spaces in between them in a processing usually called “the rendering pipeline”. The rendering pipeline goes more or less like this:  

1. Say how you’re going to connect all the points.  
2. Make some points.  
3. Say that you’re done making points.  

Saying it in code, and more specficially in Cinder code, looks like this:

```cpp
glBegin(GL_QUAD_STRIP);       // start drawing
gl::vertex(vec3(20, 20, 0));  // repeated a lot of times with different positions
glEnd();                      // stop drawing
```

You may be thinking: “I’ll just make eight vertices and voila: a cube.” Not so quick. There’s a hitch and that hitch is that the OpenGL renderer has different ways of connecting the vertices that you pass to it and none are as efficient as to only need eight vertices to create a cube. You’ve probably seen a version of the following image somewhere before:  

![image](https://cloud.githubusercontent.com/assets/2152766/14066065/816c5d5a-f438-11e5-8601-45354b60fe4c.png)

Creating eight vertices and expecting the `GL_QUAD_STRIP` to connect them is going to lead to something looking like this:  

![image](https://cloud.githubusercontent.com/assets/2152766/14066066/87100bd0-f438-11e5-8b3e-3902d23faafc.png)

Why is that you ask?

Well, first off because we used the `GL_QUAD_STRIP` but it’s also because there isn’t an easy way to tell your graphics card that you want to connect all those points into a cube. Generally you have to create your points to fit the drawing mode that you’ve selected because of what’s called “winding”.

A vertex gets connected to another vertex in the order that the mode does it’s winding and this means that you might need multiple vertices in a given location to create the shape you want. The cube, for example, requires eighteen vertices, not the eight that you would expect. If you note the order of vertices in the GL chart above you’ll see that all of them use their vertices slightly differently (in particular you should make note of the `GL_TRIANGLE_STRIP` example).

Drawing a shape requires that you keep track of which drawing mode is being used and which order your vertices are declared in. If you’re thinking: “it would be nice if there were an abstraction layer for this” you’re thinking right. Enter the mesh, which is really just an abstraction of the vertex and drawing mode that we started with but which has the added bonus of managing the draw order for you. That may seem insignificant at first, but it provides some real benefits when working with complex geometry.

<br>
<br>
<br>

## TriMesh

The TriMesh represents a series of vertices connected with the same connection algorithm as the `GL_TRIANGLE_STRIP`. It’s a convienent way to keep track of multiple complex objects, draw and scale them easily, and manage which vertices create which faces of a model. Let’s get the simplest example out the way first, drawing a square consisting of two triangles. This requires, as you’d imagine, four vertices that represent the vertices of each triangle.

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

![image](https://cloud.githubusercontent.com/assets/2152766/14066071/accbc24c-f438-11e5-8cea-11bfd200beb5.png)

So far, so good. Now, let’s extend that a little further and build something in 3D. A simple cube should suffice to demonstrate how the mesh connects all the vertices that it contains. At first glance, the next block of code (140 lines) might seem daunting, but all we are doing is repeating the previous code block 6 times, once per side. Since each side is comprised of 2 triangles, we draw a total of 12 triangles.  

![image](https://cloud.githubusercontent.com/assets/2152766/14066072/b142302c-f438-11e5-84dd-005699ad5cb4.png)

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
    gl::clear(Color::white());

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

![image](https://cloud.githubusercontent.com/assets/2152766/14066077/bd0c73a4-f438-11e5-8b2a-d5b5d324abfe.png)

Accessing the vertices in the TriMesh is a little different than you might imagine it at first, because you can’t directly access the vertices of the mesh and then alter them. Instead, you make a copy of the vertices using `getVertices()`, which returns a Vector of the vertices contained by the [`TriMesh`] as `vec3` objects and then modifying the values in that vector.

To update the vertices in the mesh itself you then need to clear the mesh and append all the vertices again. The same goes for any modifications to the RGB color array as well. 

Look at the following:

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
    void update();

    CameraPersp mCam;
    TriMesh mMesh;
};

void MyApp::setup()
{
    gl::enableDepthWrite();
    gl::enableDepthRead();

    mCam.lookAt(vec3(250, 200, 500), vec3(0));
}

void MyApp::update()
{
    if (mMesh.getNumVertices() == 0)
    {
        return;   
    }

    // Store all the mesh information
    Color* col = mMesh.getColors<3>();
    vec3* vec = mMesh.getPositions<3>();

    int i, j;
    i = mMesh.getNumVertices();
    j = 0;

    mMesh.clear();

    // Something to add a little movement
    float sinInc = sin(getElapsedSeconds());
    float cosInc = cos(getElapsedSeconds());
    
    while(j < i)
    {
        // Alter the positions array to get a little dynamism
        int mult = 30;
        vec[j].x -= sinInc;
        vec[j+1].x += sinInc;
        vec[j+2].x += sinInc * mult;
        vec[j+3].x -= sinInc * mult;
        vec[j].y -= cosInc;
        vec[j+1].y += cosInc;
        vec[j+2].y += cosInc * mult;
        vec[j+3].y -= cosInc * mult;

        // Now replace it in the mesh
        mMesh.appendPosition(vec[j]);
        mMesh.appendColorRgb(col[j]);
        mMesh.appendPosition(vec[j + 1]);
        mMesh.appendColorRgb(col[j + 1]);
        mMesh.appendPosition(vec[j + 2]);
        mMesh.appendColorRgb(col[j + 2]);
        mMesh.appendPosition(vec[j + 3]);
        mMesh.appendColorRgb(col[j + 3]);

        int vIdx0 = mMesh.getNumVertices() - 4;
        int vIdx1 = mMesh.getNumVertices() - 3;
        int vIdx2 = mMesh.getNumVertices() - 2;
        int vIdx3 = mMesh.getNumVertices() - 1;

        mMesh.appendTriangle(vIdx0, vIdx1, vIdx2);
        mMesh.appendTriangle(vIdx0, vIdx2, vIdx3);

        // go to the next triangle pair
        j += 4;
    }
}

void MyApp::draw()
{
    gl::clear(Color::white());

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

    Color colors[6][4] = { /* Colors for each vertex of the cube. */
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

    update();

    gl::setMatrices(mCam);
    gl::pushModelView();
    gl::draw(mMesh);
    gl::popModelView();

}


CINDER_APP(MyApp, RendererGl, [](App::Settings *settings) {
    settings->setWindowSize(640, 480);
})
```

The result?  

![image](https://cloud.githubusercontent.com/assets/2152766/14076646/8efa864c-f4db-11e5-97ac-778ee7e69d52.png)

Want to use a [`gl::Texture`] to texture the cube? Not so difficult. First, you need to set the texture coordinates of each vertex in the [`TriMesh`].

This requires that you use texture coordinates, not space coordinates or pixel coordinates. So, you may think your image is 500 pixels high and 500 pixels wide, but texture coordinates say that your texture is 1×1 with what you think of as upper-left corner (0, 0), still being (0, 0), but the bottom-right corner being (1, 1).

All the values between the 0, 0 and 1,1 points are scalar, meaning that 0.5 will be the midpoint of the image. So if you assign the texture coordinate 0.5, 0.5 to a vertex, the middle of the image will appear at that point. The picture below will hopefully help clarify this:  

![image](https://cloud.githubusercontent.com/assets/2152766/14066080/c87bcba4-f438-11e5-9706-9dad491ecf26.png)

So, now, how to put our [`TriMesh`] and [`gl::Texture`] together?

When creating the vertices using the `appendPosition()` and `appendColorRgb()` methods, use the `appendTexCoord()` method to create a texture coordinate. This indicates the location in the texture that you want to appear at that location in space.

For example..

```cpp
mMesh.appendPosition(vec3(1, 0, 0));
mMesh.appendTexCoord(vec2(1, 0));
mMesh.appendPosition(vec3(0, 1, 0));
mMesh.appendTexCoord(vec2(1, 1));
mMesh.appendPosition(vec3(0, 0, 1));
mMesh.appendTexCoord(vec2(0, 1));
```

Now, to apply a [`gl::Texture`] to this [`TriMesh`], call [`gl::Texture`] bind(), draw your [`TriMesh`] and then call [`gl::Texture`] unbind().

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

> Note the additional parameter `.texCoords(2)`

![image](https://cloud.githubusercontent.com/assets/2152766/14077815/aa9d5f26-f4e7-11e5-9010-45b11c2631dc.png)

You can even animate the positions of the texture coordinates by copying, modifying, and then re-appending them in the same way that the vertices and RGB coordinates were updated.

<br>
<br>
<br>

### The Outside World

But there’s more to the [`TriMesh`] than just a nice way to store all the vertices that you create because, let’s face it, lining up vertices is a drag and there are better and more fun ways to make vertices. For instance, using a 3d modeling program. To that end, you can import and export OBJ files.

![image](https://cloud.githubusercontent.com/assets/2152766/14066082/cedd9d74-f438-11e5-94f0-bb7cd7a77ce1.png)

For completeness, here is an OBJ file in ASCII format.

**icosahedron.obj**

```text
# This file uses centimeters as units for non-parametric coordinates.

v 0.850651 0.000000 -0.525731
v 0.850651 -0.000000 0.525731
v -0.850651 -0.000000 0.525731
v -0.850651 0.000000 -0.525731
v 0.000000 -0.525731 0.850651
v 0.000000 0.525731 0.850651
v 0.000000 0.525731 -0.850651
v 0.000000 -0.525731 -0.850651
v -0.525731 -0.850651 -0.000000
v 0.525731 -0.850651 -0.000000
v 0.525731 0.850651 0.000000
v -0.525731 0.850651 0.000000
vt 0.181818 0.250000
vt 0.363636 0.250000
vt 0.545455 0.250000
vt 0.727273 0.250000
vt 0.909091 0.250000
vt 0.090909 0.416667
vt 0.272727 0.416667
vt 0.454545 0.416667
vt 0.636364 0.416667
vt 0.818182 0.416667
vt 1.000000 0.416667
vt 0.000000 0.583333
vt 0.181818 0.583333
vt 0.363636 0.583333
vt 0.545455 0.583333
vt 0.727273 0.583333
vt 0.909091 0.583333
vt 0.090909 0.750000
vt 0.272727 0.750000
vt 0.454545 0.750000
vt 0.636364 0.750000
vt 0.818182 0.750000
f 2/17 10/22 1/16
f 1/16 11/10 2/17
f 1/16 8/15 7/9
f 1/16 7/9 11/10
f 1/16 10/21 8/15
f 5/13 2/12 6/6
f 10/18 2/12 5/13
f 2/17 11/10 6/11
f 4/8 9/14 3/7
f 3/7 12/2 4/8
f 5/13 6/6 3/7
f 3/7 9/14 5/13
f 6/6 12/1 3/7
f 7/9 8/15 4/8
f 4/8 12/3 7/9
f 4/8 8/15 9/14
f 5/13 9/14 10/19
f 6/11 11/10 12/5
f 7/9 12/4 11/10
f 8/15 10/20 9/14
v 0.850651 0.000000 -0.525731
v 0.850651 -0.000000 0.525731
v -0.850651 -0.000000 0.525731
v -0.850651 0.000000 -0.525731
v 0.000000 -0.525731 0.850651
v 0.000000 0.525731 0.850651
v 0.000000 0.525731 -0.850651
v 0.000000 -0.525731 -0.850651
v -0.525731 -0.850651 -0.000000
v 0.525731 -0.850651 -0.000000
v 0.525731 0.850651 0.000000
v -0.525731 0.850651 0.000000
vt 0.181818 0.250000
vt 0.363636 0.250000
vt 0.545455 0.250000
vt 0.727273 0.250000
vt 0.909091 0.250000
vt 0.090909 0.416667
vt 0.272727 0.416667
vt 0.454545 0.416667
vt 0.636364 0.416667
vt 0.818182 0.416667
vt 1.000000 0.416667
vt 0.000000 0.583333
vt 0.181818 0.583333
vt 0.363636 0.583333
vt 0.545455 0.583333
vt 0.727273 0.583333
vt 0.909091 0.583333
vt 0.090909 0.750000
vt 0.272727 0.750000
vt 0.454545 0.750000
vt 0.636364 0.750000
vt 0.818182 0.750000
f 14/39 22/44 13/38
f 13/38 23/32 14/39
f 13/38 20/37 19/31
f 13/38 19/31 23/32
f 13/38 22/43 20/37
f 17/35 14/34 18/28
f 22/40 14/34 17/35
f 14/39 23/32 18/33
f 16/30 21/36 15/29
f 15/29 24/24 16/30
f 17/35 18/28 15/29
f 15/29 21/36 17/35
f 18/28 24/23 15/29
f 19/31 20/37 16/30
f 16/30 24/25 19/31
f 16/30 20/37 21/36
f 17/35 21/36 22/41
f 18/33 23/32 24/27
f 19/31 24/26 23/32
f 20/37 22/42 21/36
```

Now I can import it using an instance of the [`ObjLoader`] class like so..

```cpp
ObjLoader loader { loadAsset("icosahedron.obj") };
mMesh = TriMesh::create(loader);
```

..and draw it to the screen by passing it to [`gl::Batch()`]:

```cpp
auto lambert = gl::ShaderDef().lambert();
mGlsl = gl::getStockShader(lambert);
mBatch = gl::Batch::create(*mMesh, mGlsl);
mBatch->draw();
```

![image](https://cloud.githubusercontent.com/assets/2152766/14080090/af8689d2-f4fa-11e5-9904-a8a32f0739e2.png)

Here is the full example.

```cpp
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/TriMesh.h"
#include "cinder/ObjLoader.h"

using namespace ci;
using namespace ci::app;


class MyApp : public App {
  public:
    void setup();
    void draw();

    CameraPersp mCam;
    TriMeshRef mMesh;
    gl::BatchRef mBatch;
    gl::GlslProgRef mGlsl;
};

void MyApp::setup()
{
    gl::enableDepthWrite();
    gl::enableDepthRead();

    mCam.lookAt(vec3(2.5, 2.0, 3.0), vec3(0));
}

void MyApp::draw()
{
    gl::clear(Color::gray(0.2f));

    ObjLoader loader { loadAsset("icosahedron.obj") };
    mMesh = TriMesh::create(loader);

    // If mesh doesn't have pre-defined normals, it's important
    // to recompute them. Otherwise you won't get any shading.
    if (!loader.getAvailableAttribs().count(geom::NORMAL))
        mMesh->recalculateNormals();

    // Associate a generic shader and stuff it in a Batch
    auto lambert = gl::ShaderDef().lambert();
    mGlsl = gl::getStockShader(lambert);
    mBatch = gl::Batch::create(*mMesh, mGlsl);

    gl::setMatrices(mCam);

    // Add spinning motion
    gl::rotate(angleAxis(getElapsedFrames() * 0.01f, vec3(0, 1, 0)));

    mBatch->draw();
}


CINDER_APP(MyApp, RendererGl, [](App::Settings *settings) {
    settings->setWindowSize(640, 480);
})
```

And here it is with some random colors applied to it:  

![image](https://cloud.githubusercontent.com/assets/2152766/14066085/d430fb86-f438-11e5-8cfa-250f54bc59fd.png)

Now, if you thought that was all there was to working with meshes in Cinder you would be wrong.

As mentioned earlier, the way that geometry is drawn on the graphics card is by sending points and telling the card how to connect those points. This might remind you a little of how the Textures work in OpenGL - load some data up there, draw it by referring to it using its TextureId.

So then, naturally you might wonder, what if we just stored the points on the card? Introducing the Vertex Buffer Object, aka VBO.

<br>
<br>
<br>

### VBO

A [VBO] is a way of storing all of the data of vertex data on the graphics card.

You’ve perhaps heard of [Vertex Array] and [Display List]. The [VBO] is similiar to both of these, but with a few advantages that we’ll go over very quickly.

A [Vertex Array] just let you store all the vertex data in an array on the client side, that is, on the CPU side and then send it to the graphics card when you’re ready to draw it. The downside of that is that you’re still storing the data on the client side and sending it over to the graphics card. 

So, instead of making all of our vertex data in what’s called “immediate mode”, which means between a glBegin() and glEnd() pair, you can just store vertex data in an arrays and you can draw geometric primitives by dereferencing the array elements with array indices.

The [Display List] is a similar technique, using an array to store the created geometry, with the crucial difference that a [Display List] lives solely on the graphics card. This means that once you’ve created the vertex data for geometry, you can send it the graphics card and draw it simply by referencing the id of the stored data.

The downside is that display lists can’t be modified. Once they’ve been sent to the card, you need to load them from the card, modify them, and then resend them to the card to see your changes applied.

One of the conveniences of moving things to the graphics card is reducing the amount of traffic between the graphics card and the rest of your system. The [VBO] operates quite similarly to the [Display List], with the advantage of allowing you to modify the geometry data on the graphics card without downloading all of it at once.

[Display List]: https://en.wikipedia.org/wiki/Display_list
[Vertex Array]: https://www.opengl.org/wiki/Vertex_Specification#Vertex_Array_Object
[VBO]: https://www.opengl.org/wiki/Vertex_Specification#Vertex_Buffer_Object

<br>
<br>
<br>

### VboMesh

Now, since we’re focusing on Cinder, we’ll be focusing on the [`VboMesh`] class that Cinder uses to wrap the core OpenGL functionality.

When you create a [`VboMesh`], much like in the [`TriMesh`], you need to decide whether the mesh is going to contain color information and/or texture coordinate information. But, there is another element to the VboMesh: whether the data is *dynamic*.

This is particularly important because it determines whether you're able to manipulate vertices in the mesh after creating it and it matters because using dynamic data means that the [`VboMesh`] will generate two copies of the data: one on the graphics card and one in the memory of your application.

If you don’t need to update the data after it’s been loaded then you don’t need to do anything special. If on the other hand you do want to create dynamic data, you’ll need to create a [`gl::VboMesh::Layout`] object and pass it to the [`VboMesh`].

For instance, if you want static positions and static colors you would create a [`gl::VboMesh::Layout`] object with those properties set on it, declare a [`VboMesh`] and then assign it to the result of a call to the [`VboMesh`] constructor.

```cpp
auto vboMesh = gl::VboMesh::create(
    positions.size(),
    GL_TRIANGLE_STRIP,
    {
        gl::VboMesh::Layout()
            .usage(GL_STATIC_DRAW)
            .attrib(geom::POSITION, 3)
            .attrib(geom::TEX_COORD_0, 2)
            .attrib(geom::NORMAL, 3)
    },
    indices.size(),
    GL_UNSIGNED_SHORT
);
```

This is because the [`VboMesh`], like so many other things in Cinder, is a shared pointer, which means that it has to be created before you can use it. You can return it from a method without problems, and also that you don’t have to worry about deallocating the [`VboMesh`] once you’ve created it. 

Here's one of the constructors for the [`VboMesh`]:

```cpp
VboMesh(
  size_t numVertices,
  size_t numIndices,
  Layout layout,
  GLenum primitiveType
);
```

Now, the `numVertices` and `numIndices` need a little explanantion.

You’ll recall from the [`TriMesh`] that the number of indices and the number of vertices aren’t directly correlated. You’ll almost always need to create more indices than vertices because there are more indices than discrete locations required for most geometry, but that depends on what kind of geometry you’re creating.

This brings us to one of the more confusing elements of working with [`gl::VboMesh::Layout`], which is the idea of indices; dynamic indices in particular.

The indices set the location of a `vec3` in the order of drawing elements. Remember how in the first example before introducing the [`TriMesh`], you saw how the order that the vertices were created in the order they were connected?

Well, the index for a vertex in the [`VboMesh`] works much the same way, indicating where the vertex is in relation to the other vertices and how it should be connected to them. 

In the graphic below the ways to draw a square using `GL_QUADS` is shown at the top and left and using `GL_TRIANGLE_STRIP` at the bottom and right.  

![image](https://cloud.githubusercontent.com/assets/2152766/14066089/e089c6e2-f438-11e5-93eb-67512f213eb3.png)

Cinder always requires that you create the indices for a mesh before you create the positions for that mesh, because conceptually a vertice without a index can't be properly integrated into the mesh and vice versa.

The two modes of storing positions means that the process for working with a [`VboMesh`] with dynamic positions versus one that have static positions is slightly different. 

We’ll do the static first:

```cpp
gl::VboMesh::Layout layout;
layout.setStaticIndices();
layout.setDynamicColorsRGBA();
layout.setStaticPositions();

int vertCount = 24;
int quadCount = 6;
mesh = gl::VboMesh(vertCount, quadCount * 4, layout, GL_QUADS);
```

When you're using static positions you can simply assign positions using a vector of `vec3` objects and calling `VboMesh::bufferPositions()`. So our [`VboMesh`] creation code looks like this.

> Note the indices being assigned before the positions.

```cpp
vector indices;
int i = 0;
while (i < 24)
{
  i
  i++;
}

mesh.bufferIndices(indices);

positions.push_back(vec3(100, 200, 1));
positions.push_back(vec3(200, 200, 1));
positions.push_back(vec3(200, 100, 1));
positions.push_back(vec3(100, 100, 1));

positions.push_back(vec3(200, 200, 1));
positions.push_back(vec3(200, 200, 100));
positions.push_back(vec3(200, 100, 100));
positions.push_back(vec3(200, 100, 1));

positions.push_back(vec3(200, 200, 100));
positions.push_back(vec3(100, 200, 100));
positions.push_back(vec3(100, 100, 100));
positions.push_back(vec3(200, 100, 100));

positions.push_back(vec3(100, 200, 100));
positions.push_back(vec3(100, 200, 1));
positions.push_back(vec3(100, 100, 1));
positions.push_back(vec3(100, 100, 100));

positions.push_back(vec3(100, 200, 100));
positions.push_back(vec3(200, 200, 100));
positions.push_back(vec3(200, 200, 1));
positions.push_back(vec3(100, 200, 1));

positions.push_back(vec3(100, 100, 100));
positions.push_back(vec3(200, 100, 100));
positions.push_back(vec3(200, 100, 1));
positions.push_back(vec3(100, 100, 1));

// now we can buffer positions
mesh.bufferPositions(positions);
```

This creates the same old boring looking white cube. Until we update the colors. This requires retrieving the color values from the mesh and using an iterator to examine the values, which is a familiar pattern in Cinder.

The [`VertexIter`] object is created to iterate over all the values in the mesh, you assign to the result of `VboMesh::mapVertexBuffer()` like so:

```cpp
void VboTutorial::update()
{
	float g = sin(getElapsedSeconds());
	float b = cos(getElapsedSeconds());
	gl::VboMesh::VertexIter iter = mesh.mapVertexBuffer();
	for (int x = 0; x < 24; ++x)
	{
		//positions.at(x) *= 1.001;
		iter.setColorRGBA(ColorA(1 - (g+b/3), g, b, 0.5));
		++iter;
	}
}
```

Dynamic positions are handled in the same way as dynamic colors. To create the dynamic positions for the simple cube in the [`VboMesh`], setting up the [`VboMesh`] is going to look familiar, assigning the indices via a vector of uints, but the actual updating of the positions is going to look quite different because you can’t pass a position values into the VboMesh by using `VboMesh::bufferPositions()`. Instead, you create an VertexIter to iterate over and modify the positions:

```cpp
void VboTutorialApp::setup()
{
	gl::VboMesh::Layout layout;

	layout.setStaticIndices();
	layout.setDynamicColorsRGBA();
	layout.setDynamicPositions();

	int vertCount = 24;
	int quadCount = 6;

	mesh = gl::VboMesh(vertCount, quadCount * 4, layout, GL_QUADS);
	vector indices;

	int i = 0;
	while (i < 24)
	{
		indices.push_back(i);
		i++;
	}

	mesh.bufferIndices(indices);
}
```

Note that creating the [`VboMesh`] only buffers the indices and not any positions. Creating position data is done via a [`VertexIter`], for instance, in the `update()` of the application:

```cpp
void VboTutorialApp::update()
{
	gl::VboMesh::VertexIter iter = mesh.mapVertexBuffer();
	for (int idx = 0; idx < numberOfVertices; ++idx)
	{
		iter.setPosition(vec3( xVal, yVal, zVal));
		++iter;
	}
}
```

The positions are automatically generated to be unit vector values, stored both on the graphics card and in the application memory. When you modify the [`VertexIter`] you mark a certain range of data as needing to be uploaded to the graphics card.

For those interested in the underlying functionality, this uses the stored local copy of the vertex and index information to pass to `glBufferDataARB()`. The values are only uploaded to the card when index, color, or position data is modified saving time and space on any draw operation when changes haven’t been made.

This is an important nuance because the idea of keeping records both on the graphics card and in the application memory is used throughout the [`VboMesh`], color data, texture positions and even indices.

If you create dynamic texture positions using either `setDynamicTexCoords2d()` if you’re using 2d coordinates or `setDynamicTexCoords3d()` if you’re using 3d coordinates, you can reposition a texture on a mesh dynamically. There are some key differences between 2d textures and 3d textures that you can read up more on here.

To move a texture around the x axis of the mesh, create a [`VertexIter`] and then modify the texture using `setTexCoord3d2()` or `setTexCoord2d2()` depending on the texture type that you’re using. For instance, shifting a 2d texture around:

```cpp
// dynmaically generate our new positions based on a simple sine wave for mesh
gl::VboMesh::VertexIter iter2 = mVboMesh2.mapVertexBuffer();
for (int x = 0; x < VERTICES_X; ++x)
{
	for (int z = 0; z < VERTICES_Z; ++z)
	{
		float height = sin(
			z / (float)VERTICES_Z * zFreq
			+ x / (float)VERTICES_X * xFreq
			+ offset
		) / 5.0f;

		
		iter2.setPosition(
			vec3(x / (float)VERTICES_X, height, z / (float)VERTICES_Z)
			+ vec3(0, 0.5, 0)
		);
		
		iter.setTexCoord2d2(
			vec2(x / (float)VERTICES_X, z / (float)VERTICES_Z)
		);

		++iter2;
	}
}
```

You can also copy the values from one VboMesh to another, retrieving values from a mesh using the `VboMesh::getIndexVbo()` to get the indices from a mesh and `VboMesh::getStaticVbo()` to get the vertex data from the mesh. The [`VboMesh`] can be constructed like so assuming that there's another [`VboMesh`] called `otherMesh`:

```cpp
mesh = gl::VboMesh(
  numberVertices,              // size_t numVertices,
  numberQuads * 4,             // size_t numIndices,
  otherMesh.getLayout(),       // Layout layout,
  GL_QUADS,                    // GLenum primitiveType,
  &otherMesh.getIndexVbo(),    // Vbo *indexBuffer,
  NULL,                        // Vbo *staticBuffer,
  &otherMesh.getDynamicVbo()   // Vbo *dynamicBuffer
);
```

You may be noticing the last two parameters, which are pointers to either the static or dynamic VBO data from the source VBO.

Which you use will depend on how the source has been created, using the dynamic properties from a source VBO requires that the source has dynamic positionsVBO with dynamic properties.

Using the static values from a buffer means copying the values over so that they can be manipulated independently. This means that the target mesh will have the same properties as the source mesh until they are altered.

Using the dynamic properties of a mesh means that the target mesh is using the same data as the source and changes to the source will be reflected in the target mesh. This makes it easy to reflect changes across meshes, for instance color effects or textures, but makes your meshes dependent on the source mesh.

For the last trick of interoperation between the mesh types in Cinder, a [`VboMesh`] can load a mesh from a [`TriMesh`] instance, which means that you can import and export an `.obj` file to a VBO.

For instance:

```cpp
ObjLoader loader(loadResource(OBJ_FILE_RESOURCE));
loader.load(&trimesh);
gl::VboMesh mesh = gl::VboMesh(trimesh);
```

And that gets you from a modeling tool to a VBO quite painlessly.

<br>
<br>
<br>

### Final Demonstration

As a final demonstration of how much is built into the VBO and mesh handling in Cinder, you can easily create and set the normals for a VBO using the [`VertexIter`] object and its `setNormal()` method.

A normal is simply a vector that's perpendicular to the face of a triangle or quad in a mesh or other piece of OpenGL geometry. They're quite important if you plan to use lighting of any kind when rendering a [`TriMesh`] or VBO to the screen.

The normal essentially tells OpenGL how any light is to be reflected off of a particular face. This allows you to create shading, depth, and other real world lighting effects. It's also a little out of the scope of this guide, so I'll point you to a chapter from OpenGL Programming aka “The Red Book”.

Using the [`VertexIter`] allows you set the normal position for each vertex in a VBO (or in a [`TriMesh`] for that matter) by iterating through the vertices of the VBO and setting each normal with an appropriate value.

The algorithm here was taken from the [OpenGL Wiki](http://www.opengl.org/wiki/Calculating_a_Surface_Normal) OpenGL wiki and explains the algorithm in a little bit greater detail, as well as providing an alternative algorithm.

```cpp
vec3 v0, v1, v2;

// dynmaically generate our new positions based on a simple sine wave
gl::VboMesh::VertexIter iter = mVboMesh.mapVertexBuffer();

for (int x = 0; x < VERTICES_X; ++x)
{
	for (int z = 0; z < VERTICES_Z ; ++z)
	{
		float height = sin(z / (float)VERTICES_Z * zFreq + x / (float)VERTICES_X * xFreq + offset) / 2.0f;
		if (currentVert == 0)
		{
			v0.set(x / (float)VERTICES_X, height, z / (float)VERTICES_Z);
			++currentVert;
			} else if (currentVert == 1) {
			v1.set(x / (float)VERTICES_X, height, z / (float)VERTICES_Z);
			++currentVert;
		} else {

			//v3.set(x / (float)VERTICES_X, height, z / (float)VERTICES_Z);
			v2.set(x / (float)VERTICES_X, height, z / (float)VERTICES_Z);

			vec3 uu = v2 - v0;
			vec3 vv = v1 - v0;
			vec3 n = uu.cross(vv).normalized();

			iter.setPosition(v0);
			iter.setNormal(n);
			++iter;
			iter.setPosition(v1);
			iter.setNormal(n);
			++iter;
			iter.setPosition(v2);
			iter.setNormal(n);
			++iter;
			currentVert = 0;
		}
	}
}
```

<br>
<br>
<br>

### Conclusion

Hopefully you're feeling a little more comfortable not only with creating and manipulating meshes in Cinder, but also with underestanding what some of the underlying mechanics of a mesh and OpenGL geometry are as well. This guide has barely scratched the surface, but it should be enough to get you started. For more information you can check the excellent references at [songho](http://songho.ca/opengl/gl_vbo.html) or to the reference for the [`TriMesh`] and [`VboMesh`].

Have fun and make something beautiful.

[`TriMesh`]: cinder/TriMesh.md
[`VboMesh`]: cinder/VboMesh.md
[`gl::VboMesh::Layout`]: cinder/gl/VboMesh/Layout.md
[`gl::Texture`]: cinder/gl/Texture.md
[`ObjLoader`]: cinder/ObjLoader.md
[`TriMesh::writeObject()`]: cinder/TriMesh.md
[`VertexIter`]: cinder/VboMesh/VertexIter.md

