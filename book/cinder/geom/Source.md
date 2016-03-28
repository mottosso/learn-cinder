# Source

Baseclass to geometry generators.

<br>
<br>
<br>

### Description

TODO: What is this?

<br>
<br>
<br>

### Pipeline

> Source: [New geom::Source work](https://forum.libcinder.org/topic/glnext-new-geom-source-work)

Multiple [`geom::Source`] objects can form a pipeline of operations.

A simple example of that is [`geom::Transform`] taking an arbitrary [`geom::Source`] and a `mat4` and then transforms the positions and normals by it.

[`geom::Source`]: .
[`geom::Transform`]: Transform.md

```cpp     
/*               ^
              ___|___
             |   |   |
    ______   |       |
   |      |  |       |
   |      |  |       |
   |______|  |_______|

*/
mat4 stretch = scale(vec3(1, 3, 1))
mBatch = gl::Batch::create(
  geom::Transform(geom::Cube(), stretch), mGlsl)
);
```
 
This works with more complex series of transformations as well. For example, the [`geom::Twist`] class twists an arbitrary [`geom::Source`] around an axis.

```cpp
mBatch = gl::Batch::create(
  geom::Twist(geom::Cube().subdivisions(10))
    .startAngle(M_PI * 2)
    .endAngle(0), mGlsl); 
```

[`geom::Twist`]: Twist.md
[`geom::Source`]: .
[`geom::Transform`]: Transform.md

Y is the default axis but you can supply any axis as well as arbitrary starting and ending angles.

Continuing the tour, you can convert any primitive into the [`geom::Lines`] primitive.

```cpp
mBatch = gl::Batch::create(
  geom::Lines(geom::Cube().subdivisions(3)),
  mGlsl
); 
```

---

TODO

---

Another interesting addition is a geom::ColorFromAttrib() class which allows you to write a std::function which outputs a Color (or ColorA) based on some arbitrary attribute. In this example I'm coloring a Teapot based on its normals:
auto teapot = geom::Teapot().subdivisions( 11 );
auto normalsColor = []( vec3 uv ) { return Colorf( uv.x, uv.y, uv.z ); };
mBatch = gl::Batch::create( geom::ColorFromAttrib( teapot, geom::NORMAL, normalsColor ) ), mGlsl );

 

similarly, here I'm coloring a Sphere based on its UV coords piped into a simple HSV color function:
auto uvRampColor = []( vec2 uv ) { return Colorf( CM_HSV, fmod( uv.x * 3, 1.0f ),
                                                   uv.y, 1.0 ); };
auto sphere = geom::Sphere().subdivisions( 100 ).radius( 2.2f );
mBatch = gl::Batch::create( geom::ColorFromAttrib( sphere, geom::TEX_COORD_0,
                         uvRampColor ), gl::getStockShader( gl::ShaderDef().color() ) );

 

Shifting gears a bit, I also added a geom::Extrude(), which can take an arbitrary Shape2D and extrude it along the Z axis. I've made a sample for this one now in samples/Extrude :
 

This sample also shows off a final new class, VertexNormalLines, which creates a geom::Source of primitive type LINES drawn at the normals of another Source. It's used in the app like so:
mNormalsBatch = gl::Batch::create( geom::VertexNormalLines( extrudeSource, 3.0f ), gl::getStockShader( gl::ShaderDef().color() ) ); 

And its output looks like this:
 

That image also highlights an aspect of geom::Extrude which is that it's able to use Cinder's adaptive subdivision to create a minimum of vertices for an arbitrary shape. In order to make use of it I needed to add some functionality to Path2d::subdivide() to optionally calculate curve tangents along the subdivision, which has its own usefulness beyond the Extrude use case.

As a final note, I'd like to highlight the new geom::Modifier class, which several of the new geom classes make use of. It is designed to take some of the error-prone drudge work out of writing a geom::Source that modifies another source. For example usage, if we take the geom::Transform class, we see an implementation that looks like this:

void Transform::loadInto( Target *target ) const
{
    // we want to capture and then modify both positions and normals
    map<Attrib,Modifier::Access> attribAccess;
    attribAccess[POSITION] = Modifier::READ_WRITE;
    attribAccess[NORMAL] = Modifier::READ_WRITE;
    Modifier modifier( mSource, target, attribAccess, Modifier::IGNORE );
    mSource.loadInto( &modifier );
    
    ...
} 

The Modifier class is informed that we intend to Read and Write both the POSITION and NORMAL attribute of mSource. All other attributes are automatically passed through from mSource to target . In our case, we want attributes like texture coordinates, colors, etc. to be automatically copied from whatever our source is to the target, without modification. We also want to know what the current positions and normals are, and then we want to modify them based on our transformation matrix before passing them on to target . The Modifier class makes all of this monotony easier to implement. If you're intending to possibly write your own geom::Sources, particularly those that modify other Sources, the geom::Transform internals is a good example to study.

All of this is currently a branch but I'd like to merge it soon barring any modifications we want to make in advance.

-Andrew

