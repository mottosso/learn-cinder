This project was about getting setup on Linux, through Sublime Text.

It has a Sublime project file with a build system, assuming the Cinder installation directory to be located at $CINDER. The CMakeLists.txt also depends on this environment variable.

**Usage**

```bash
cd 03-Cube/linux
./cibuild -b Debug
./Debug/ogl/Cube
```