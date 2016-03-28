### VECDIM

An alias for various GLM vectors.

| Namespace    | Include
|--------------|-----------------
| `ci::VECDIM` | [`#include "cinder/Vector.h"`]

[`#include "cinder/Vector.h"`]: https://github.com/cinder/Cinder/blob/master/include/cinder/Vector.h

```cpp
template<> struct VECDIM<2,float>	  { typedef vec2	TYPE; };
template<> struct VECDIM<3,float>	  { typedef vec3	TYPE; };
template<> struct VECDIM<4,float>	  { typedef vec4	TYPE; };
template<> struct VECDIM<2,double>	 { typedef dvec2	TYPE; };
template<> struct VECDIM<3,double>	 { typedef dvec3	TYPE; };
template<> struct VECDIM<4,double>	 { typedef dvec4	TYPE; };
template<> struct VECDIM<2,int>		{ typedef ivec2	TYPE; };
template<> struct VECDIM<3,int>		{ typedef ivec3	TYPE; };
template<> struct VECDIM<4,int>		{ typedef ivec4	TYPE; };
```

<br>
<br>
<br>

### Examples

```cpp

```