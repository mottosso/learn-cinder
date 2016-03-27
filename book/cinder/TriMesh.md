### `TriMesh`

Construct a triangle mesh from `vec3` and `Color` objects.

| Namespace      | Include
|----------------|----------------
| `cinder::TriMesh` | `#include "cinder/gl/gl.h"`

<br>
<br>
<br>

### Description

> This object is pre-Cinder 0.9. Prefer [`gl::Batch`].

Use the `TriMesh` when explicitly defining each position and color, but take care about performance; the `TriMesh` is implicitly converted to a [`VboMesh`] which in turn converts to a [`gl::Batch`].

When performance is important, always use [`gl::Batch`].

[`VboMesh`]: VboMesh.md
[`gl::Batch`]: gl/Batch.md

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
| const VECDIM< DIM, float >::TYPE * | getPositions () const
| std::vector< vec3 > & | getNormals ()
| std::vector< vec3 > & | getTangents ()
| std::vector< vec3 > & | getBitangents ()
| COLORDIM< DIM, float >::TYPE * |  getColors ()
| void           | subdivide (int division=2, bool normalize=false)

<br>
<br>
<br>


### Example

![image](https://cloud.githubusercontent.com/assets/2152766/14067075/c1b9a7bc-f453-11e5-86b1-162c4a6099ff.png)

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

     mesh.appendPosition(vec3(200, 500, 0));
     mesh.appendColorRgb(Color(1, 0, 1));
     mesh.appendPosition(vec3(500, 200, 0));
     mesh.appendColorRgb(Color(1, 0, 0));
     mesh.appendPosition(vec3(500, 500, 0));
     mesh.appendColorRgb(Color(0, 0, 1));
     mesh.appendTriangle(0, 1, 2);
}

void MyApp::draw()
{
    gl::clear(); 
    gl::draw(mesh);
}

CINDER_APP(MyApp, RendererGl)
```