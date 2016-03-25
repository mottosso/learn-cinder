#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;

class AddisonApp : public App {
  public:
	void	setup() override;
	void	draw() override;
};

void AddisonApp::setup()
{
	gl::enableDepthWrite();
	gl::enableDepthRead();
}

void AddisonApp::draw()
{
	gl::clear();
}

//CINDER_APP( AddisonApp, RendererGl( RendererGl::Options().msaa( 16 ) ) )
CINDER_APP( AddisonApp, RendererGl )
