#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/CameraUi.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class BasicsApp : public App {
  public:
	void setup() override;
	void mouseDown(MouseEvent event) override;
	void mouseDrag(MouseEvent event) override;
	void keyDown(KeyEvent event) override;
	void draw() override;

	gl::BatchRef mCube;
	CameraPersp mCam;
	CameraUi mCamUi;
	gl::GlslProgRef mGlsl;
};

void BasicsApp::keyDown(KeyEvent event)
{
	if (event.getCode() == KeyEvent::KEY_ESCAPE) quit();
}

void BasicsApp::setup()
{
	gl::enableDepthRead();
	gl::enableDepthWrite();

	mGlsl = gl::GlslProg::create(
		loadAsset( "shader.vert" ),
		loadAsset( "shader.frag" ) 
	);
	mCube = gl::Batch::create(geom::Cube(), mGlsl);

	mCam.setEyePoint(vec3(3.0f, 2.0f, 1.5f));
	mCam.setPerspective(60, getWindowWidth() / getWindowHeight(), 1, 1000);
	mCam.lookAt(vec3(0));

	mCamUi = CameraUi(&mCam);
}

void BasicsApp::mouseDown( MouseEvent event )
{
	mCamUi.mouseDown(event);
}

void BasicsApp::mouseDrag(MouseEvent event)
{
	mCamUi.mouseDrag(event);
}

void BasicsApp::draw()
{
	gl::clear( Color( 0.25f, 0.25f, 0.25f ) ); 

	gl::setMatrices(mCam);
	gl::color(Color(CM_HSV, 0.1, 1, 1));
	mCube->draw();
}

CINDER_APP( BasicsApp, RendererGl )
