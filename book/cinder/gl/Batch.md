### `Batch`

Baseclass to platform specific App subclasses.

| Namespace                | Include   
|--------------------------|-----------
| [`cinder::gl::Batch`]    | [`#include "cinder/gl/gl.h"`]

[`cinder::gl::Batch`]: https://libcinder.org/docs/branch/master/classcinder_1_1gl_1_1_batch.html
[`#include "cinder/gl/gl.h"`]: https://github.com/cinder/Cinder/blob/master/include/cinder/gl/gl.h

<br>
<br>
<br>

### Description

Pair geometry with a GLSL program.

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

![image](https://cloud.githubusercontent.com/assets/2152766/14059781/5c44d68e-f30b-11e5-849c-3e9b24ba1fca.png)


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
	
	CameraPersp		mCam;
	gl::BatchRef	mBox;
};

void MyApp::setup()
{
	auto lambert = gl::ShaderDef().lambert().color();
	gl::GlslProgRef shader = gl::getStockShader(lambert);	
	mBox = gl::Batch::create(geom::Cube(), shader);
	
	mCam.lookAt(vec3(3, 4.5, 4.5), vec3(0, 1, 0));
}

void MyApp::draw()
{
	gl::clear();
	gl::enableDepthRead();
	gl::enableDepthWrite();

	gl::setMatrices(mCam);

	int numSpheres = 64;
	float maxAngle = M_PI * 7;
	float spiralRadius = 1;
	float height = 2;
	float boxSize = 0.05f;
	float anim = getElapsedFrames() / 30.0f;

	for(int s = 0; s < numSpheres; ++s) {
		float rel = s / (float)numSpheres;
		float angle = rel * maxAngle;
		float y = fabs(cos(rel * M_PI + anim)) * height;
		float r = rel * spiralRadius;
		vec3 offset(r * cos(angle), y / 2, r * sin(angle));
		
		gl::pushModelMatrix();
		gl::translate(offset);
		gl::scale(vec3(boxSize, y, boxSize));
		gl::color(Color(CM_HSV, rel, 1, 1));
		mBox->draw();
		gl::popModelMatrix();
	}
}

CINDER_APP(MyApp, RendererGl)

```
