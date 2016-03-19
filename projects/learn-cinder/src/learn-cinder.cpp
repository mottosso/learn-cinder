#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;

class BasicApp : public App {
public:
    void draw() override;
};

void BasicApp::draw()
{
    gl::clear();
}

CINDER_APP( BasicApp, RendererGl )
