### ShaderDef

| Namespace |
|-----------|
| [`cinder::gl::ShaderDef`](https://libcinder.org/docs/branch/master/classcinder_1_1app_1_1_app_base.html)

Generate common shaders.

<br>
<br>
<br>

### Description

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

```cpp
# Draw a solid white circle.
gl::bindStockShader(gl::ShaderDef().color());
gl::drawSolidCircle(vec2( 100, 100 ), 50);
```
```