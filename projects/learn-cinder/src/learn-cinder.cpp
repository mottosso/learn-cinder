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
	gl::BatchRef mRect;
	gl::GlslProgRef mGlsl;
	gl::Texture2dRef mTex;
};


void BasicApp::setup()
{
	mCam.lookAt(vec3(3, 2, 4), vec3(0));

	//auto img = loadImage(loadAsset("texture.jpg"));

	mGlsl = gl::GlslProg::create(gl::GlslProg::Format()
	.vertex(CI_GLSL(150,
		uniform mat4 ciModelViewProjection;
		in vec4 ciPosition;
		in vec2 ciTexCoord0;
		out vec2 TexCoord0;

		float offset(vec2 uv)
		{
			return (sin(uv.x * 15.0) +
					cos(uv.y * 7.0f + uv.x * 13.0f)) * 0.1f;
		}

		void main(void)
		{
			vec4 pos = ciPosition;
			pos.y = offset(ciTexCoord0);
			gl_Position = ciModelViewProjection * pos;
			TexCoord0 = ciTexCoord0;
		}
	))
	.fragment(CI_GLSL(150,
		uniform float uCheckSize;

		in vec2 TexCoord0;
		out vec4 oColor;

		vec4 checker(vec2 uv)
		{
			float v = floor(uCheckSize * uv.x) + floor(uCheckSize * uv.y);
			if (mod(v, 2.0) < 1.0)
				return vec4(1, 1, 1, 1);
			else
				return vec4(0, 0, 0, 1);
		}

		void main(void)
		{
			oColor = checker(TexCoord0);
		}
	)));

	auto plane = geom::Plane().subdivisions(ivec2(30));
	mRect = gl::Batch::create(plane, mGlsl);

	gl::enableDepthWrite();
	gl::enableDepthRead();
}

void BasicApp::draw()
{
    gl::clear(Color(0.2f, 0.2f, 0.2f));
	gl::setMatrices(mCam);

	mGlsl->uniform("uCheckSize", 30.0f);
	float anim = -1.0f * getElapsedFrames() / 30.0f;
	gl::rotate(angleAxis(anim, vec3(0, 1, 0)));
	mRect->draw();
}

CINDER_APP( BasicApp, RendererGl )
