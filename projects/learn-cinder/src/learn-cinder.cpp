#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Shader.h"
#include "cinder/Easing.h"

using namespace ci;
using namespace ci::app;

class BasicApp : public App {
public:
	void setup() override;
    void draw() override;

	CameraPersp mCam;
	gl::BatchRef mSphere;
	gl::TextureRef mTexture;
	gl::GlslProgRef mGlsl;
};

void BasicApp::setup()
{
	mCam.lookAt(vec3(3, 2, 4), vec3(0));

	auto img = loadImage(loadAsset("checkerboard.png"));
	mTexture = gl::Texture::create(img);
	mTexture->bind();

	auto shader = gl::ShaderDef().texture().lambert();
	mGlsl = gl::getStockShader(shader);
	auto sphere = geom::Sphere().subdivisions(50);
	mSphere = gl::Batch::create(sphere, mGlsl);

	gl::enableDepthWrite();
	gl::enableDepthRead();
}

void BasicApp::draw()
{
    gl::clear(Color(0.2f, 0.2f, 0.2f));
	gl::setMatrices(mCam);

	mSphere->draw();

	gl::setMatricesWindow(getWindowSize());
	Rectf drawRect(0, 0,
		mTexture->getWidth() / 3,
		mTexture->getHeight() / 3);
	gl::draw(mTexture, drawRect);
}

CINDER_APP( BasicApp, RendererGl )
