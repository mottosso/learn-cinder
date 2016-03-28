### ShaderDef

| Namespace |
|-----------|
| [`ci::gl::ShaderDef`](https://libcinder.org/docs/branch/master/classcinder_1_1app_1_1_app_base.html)

Generate common [`gl::GlslProg`](GlslProg.md)'s.

<br>
<br>
<br>

### Description

A convenience function for generating common shaders.

<br>
<br>
<br>

### Public Members
| Output      | Method
|------------:|:----------------
|             | ShaderDef() 
| ShaderDef & | color ()
| ShaderDef & | texture (const TextureRef &tex=TextureRef())
| ShaderDef & | texture (GLenum target)
| ShaderDef & | lambert ()
| ShaderDef & | uniformBasedPosAndTexCoord ()
| bool        | isTextureSwizzleDefault () const
| std::string | getTextureSwizzleString () const
| bool operator< | (const ShaderDef &rhs) const

<br>
<br>
<br>

### Example

![image](https://cloud.githubusercontent.com/assets/2152766/14055677/a8f82880-f2db-11e5-8703-b38393bd5911.png)

```cpp
# Draw a solid white circle.
gl::bindStockShader(gl::ShaderDef().color());
gl::drawSolidCircle(vec2(100, 100), 50);
```

Note the [named parameter idiom](https://isocpp.org/wiki/faq/ctors#named-parameter-idiom).

```cpp
gl::bindStockShader(
  gl::ShaderDef()
    .lambert()
    .color()
);
gl::drawSolidCircle(vec2(100, 100), 50);
```