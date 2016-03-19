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

	gl::pushModelMatrix();

	// move to window center
	gl::translate(getWindowCenter());

	int numCircles = 32;
	float radius = getWindowHeight() / 2 - 30;

	for (int c = 0; c < numCircles; ++c) {
		float rel = c / (float)numCircles;
		float angle = rel * M_PI * 2;
		vec2 offset(cos(angle), sin(angle));

		// preserve the Model matrix
		gl::pushModelMatrix();

		// move to the correct position
		gl::translate(offset * radius);
		gl::rotate(angle);
		gl::scale(8, 0.25f);
		gl::color(Color(CM_HSV, rel, 1, 1));
		gl::drawSolidCircle(vec2(), 20);

		// restore matrix
		gl::popModelMatrix();
	}

	// draw a white circle at window center
	gl::color(Color(1, 1, 1));
	gl::drawSolidCircle(vec2(), 15);

	// restory the default Model matrix
	gl::popModelMatrix();
}

CINDER_APP( BasicApp, RendererGl )
