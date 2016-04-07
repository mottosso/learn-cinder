#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/TriMesh.h"
#include "cinder/ObjLoader.h"

using namespace ci;
using namespace ci::app;
using namespace std;


class MyApp : public App {
  public:
    void setup();
    void draw();

    CameraPersp mCam;
    TriMeshRef mMesh;
    gl::Texture2dRef mTex;
    gl::BatchRef mBatch;
    gl::GlslProgRef mGlsl;
};

void MyApp::setup()
{
    gl::enableDepthWrite();
    gl::enableDepthRead();
    gl::enable(GL_PRIMITIVE_RESTART);
    glPrimitiveRestartIndex(0xffff);

    auto img = loadImage(loadAsset("texture.jpg"));
    mTex = gl::Texture2d::create(img);

    // create data buffers
    vector<vec3> normals;
    vector<vec3> positions;
    vector<vec2> texCoords;
    vector<uint16_t> indices;

    /*      up
        0___|_____1
        /   |    /|
       /        / |
     2/________/3 --- right
      |        |  /
      |        | /
      |________|/

    */

    vec3 up    { 0, 1, 0 };
    vec3 down  { 0,-1, 0 };
    vec3 right { 1, 0, 0 };
    vec3 left  {-1, 0, 0 };
    vec3 front { 0, 0, 1 };
    vec3 back  { 0, 0,-1 };

    // Top plane
    positions.push_back(vec3(-100, -100, -100));   // 0
    positions.push_back(vec3(100, -100, -100));    // 1
    positions.push_back(vec3(-100, -100, 100));    // 2
    positions.push_back(vec3(100, -100, 100));     // 3
    normals.push_back(up);
    normals.push_back(up);
    normals.push_back(up);
    normals.push_back(up);
    normals.push_back(up);
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(3);

    indices.push_back(0xffff); // restart

    // Bottom plane
    positions.push_back(vec3(-100, 100, -100));   // 4
    positions.push_back(vec3(100, 100, -100));    // 5
    positions.push_back(vec3(-100, 100, 100));    // 6
    positions.push_back(vec3(100, 100, 100));     // 7
    normals.push_back(down);
    normals.push_back(down);
    normals.push_back(down);
    normals.push_back(down);
    indices.push_back(4);
    indices.push_back(5);
    indices.push_back(6);
    indices.push_back(5);
    indices.push_back(6);
    indices.push_back(7);

    indices.push_back(0xffff); // restart

    auto vboMesh = gl::VboMesh::create(
        positions.size(),
        GL_TRIANGLE_STRIP,
        {
            gl::VboMesh::Layout()
                .usage(GL_STATIC_DRAW)
                .attrib(geom::POSITION, 3)
                .attrib(geom::NORMAL, 3)
        },
        indices.size(),
        GL_UNSIGNED_SHORT
   );

    vboMesh->bufferAttrib(geom::POSITION, positions);
    vboMesh->bufferAttrib(geom::NORMAL, normals);
    vboMesh->bufferIndices(indices.size() * sizeof(uint16_t), indices.data());

    auto shader = gl::context()->getStockShader(
        gl::ShaderDef()
            .lambert()
            .color()
   );

    mBatch = gl::Batch::create(vboMesh, shader);

    mCam.lookAt(vec3(800, 0, 0), vec3(0));
}

void MyApp::draw()
{
    gl::clear(Color::gray(0.2f));

    gl::setMatrices(mCam);

    // Add spinning motion
    gl::rotate(angleAxis(getElapsedFrames() * 0.01f, vec3(0, 1, 0)));

    // gl::ScopedTextureBind tex0 { mTex };
    gl::ScopedColor color { Color::gray(0.5) };

    mBatch->draw();
}


CINDER_APP(MyApp, RendererGl, [](App::Settings *settings) {
    settings->setWindowSize(640, 480);
})