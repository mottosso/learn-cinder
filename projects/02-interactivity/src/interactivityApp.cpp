#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/CameraUi.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class interactivityApp : public App {
  public:
	void setup() override;
	void mouseDown(MouseEvent event) override;
	void mouseDrag(MouseEvent event) override;
	void keyDown(KeyEvent event) override;
	void draw() override;

	gl::BatchRef mCube;
	CameraPersp mCam;
	CameraUi mCamUi;
};

void interactivityApp::keyDown(KeyEvent event)
{
	if (event.getCode() == KeyEvent::KEY_ESCAPE) quit();
}

void interactivityApp::setup()
{
	gl::enableDepthRead();
	gl::enableDepthWrite();

	auto lambert = gl::ShaderDef().lambert();
	gl::GlslProgRef shader = gl::getStockShader(lambert);
	mCube = gl::Batch::create(geom::Cube(), shader);

	mCam.setEyePoint(vec3(3.0f, 2.0f, 1.5f));
	mCam.setPerspective(60, getWindowWidth() / getWindowHeight(), 1, 1000);
	mCam.lookAt(vec3(0));

	mCamUi = CameraUi(&mCam);
}

void interactivityApp::mouseDown( MouseEvent event )
{
	mCamUi.mouseDown(event);
}

void interactivityApp::mouseDrag(MouseEvent event)
{
	mCamUi.mouseDrag(event);
}

void interactivityApp::draw()
{
	gl::clear( Color( 0.25f, 0.25f, 0.25f ) ); 

	gl::setMatrices(mCam);
	gl::color(Color(CM_HSV, 0.1, 1, 1));
	mCube->draw();
}

CINDER_APP( interactivityApp, RendererGl )
