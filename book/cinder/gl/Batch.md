### Batch

Geometry and GLSL program combined.

| Namespace                | Include   
|--------------------------|-----------
| [`ci::gl::Batch`]    | [`#include "cinder/gl/gl.h"`]

[`ci::gl::Batch`]: https://libcinder.org/docs/branch/master/classcinder_1_1gl_1_1_batch.html
[`#include "cinder/gl/gl.h"`]: https://github.com/cinder/Cinder/blob/master/include/cinder/gl/Batch.h

<br>
<br>
<br>

### Description

Use this objet to associate geometry with a particular shader. Cinder implicitly caches and reuses the shader for each set of geometry.

- [Tutorial](https://libcinder.org/docs/branch/master/guides/opengl/part3.html)


<br>
<br>
<br>

### Public Member Functions

| Output       | Member
|-------------:|:--------------
| void         | draw (GLint first=0, GLsizei count=-1)
| void         | bind ()
| GLenum       | getPrimitive () const
| size_t       | getNumVertices () const
| size_t       | getNumIndices () const
| GLenum       | getIndexDataType () const
| const GlslProgRef & | getGlslProg () const
| void         | replaceGlslProg (const GlslProgRef &glsl)
| const VaoRef | getVao () const
| VboMeshRef   | getVboMesh () const
| void         | replaceVboMesh (const VboMeshRef &vboMesh)
| void         | reassignContext (Context *context)

<br>
<br>
<br>

### Static Public Member Functions

| Output   | Member
|---------:|:--------------
| BatchRef | create (const VboMeshRef &vboMesh, const gl::GlslProgRef &glsl, const AttributeMapping &attributeMapping=AttributeMapping())
| BatchRef | create (const geom::Source &source, const gl::GlslProgRef &glsl, const AttributeMapping &attributeMapping=AttributeMapping())

<br>
<br>
<br>

### Protected Member Functions

| Output | Member
|-------:|:--------
|        | Batch (const VboMeshRef &vboMesh, const gl::GlslProgRef &glsl, const AttributeMapping &attributeMapping)
|        | Batch (const geom::Source &source, const gl::GlslProgRef &glsl, const AttributeMapping &attributeMapping)
| void   | init (const geom::Source &source, const gl::GlslProgRef &glsl)
| void   | initVao (const AttributeMapping &attributeMapping=AttributeMapping())

<br>
<br>
<br>

### Protected Attributes

| Output | Member
|-------:|:--------------
| | VboMeshRef
| | mVboMesh
| | VaoRef
| | mVao
| | GlslProgRef
| | mGlsl
| | AttributeMapping
| | mAttribMapping

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
