### Resources in Cinder

Most applications need to reference data outside their own code to do anything very interesting. Cinder offers two mechanisms for including data files with your app: *assets* and *resources*. These two techniques have a lot in common. The primary difference is that resources are "baked" directly into your application, and assets are separate files living alongside your application. Assets can be easily modified separately from your code, and they take a lot less work to setup, especially on Windows. However, distribution and installation can be simpler with resources since there's no way for the data your application depends on to "go missing", and it reduces the chances that a user might modify your data unexpectedly.

<br>
<br>
<br>

### Project File Structure

TinderBox creates a project layout with separate folders for both assets and resources. Since these files are as much a part of your app as its source code, they'll generally be managed by your version control system (say, git or Subversion) just as your C++ code or anything else in your project is.

![image](https://cloud.githubusercontent.com/assets/2152766/14065863/1c5336b0-f432-11e5-9a83-432e5f05f584.png)

<br>
<br>
<br>

## Assets

Assets are quite simple to use. Simply place any file you'd like to reference from your application into the _assets_ folder that TinderBox has created for you. To access this file from your code, you'll want to call [`loadAsset()`]. This is a member function of your App, but if you'd like to call it from outside your App, call the [`loadAsset()`] variant. The function takes one parameter, which is simply the name of the file you'd like to use. For example, to load a PNG file as a gl::Texture from your assets folder, you'd do something like this:

```cpp
gl::Texture::create(loadImage(loadAsset("logo.png")));
```

Additionally, if you need to know where an asset lives in the filesystem, you can call [`getAssetPath()`].

```cpp
console() << "logo.png lives at: " << getAssetPath("logo.png") << std::endl;
// prints: "logo.png lives at /Users/andrewbell/SampleProject/assets/logo.png"
```

You can also provide additional structure to your _assets_ folder. For example, you might create a _pictures_ subfolder that contains a _photo1.jpg_. You would load that like so:

```cpp
mPhoto1 = loadImage(loadAsset("pictures/photo1.jpg"));
```

<br>
<br>
<br>

### How Assets Work

It's worth understanding a bit about how assets work under the hood. The first time you attempt to load an asset or get its path, your Cinder application automatically attempts to find its _assets_ directory. It begins by searching in the same folder in which your .app bundle or .exe lives. Next it searches its parent, on up 5 levels. The reason for such a deep search is due to the somewhat remote location where Xcode and Visual C++ can output executables, depending on their configuration. When you are ready to ship your application, make sure you include both your application (.app on OS X or .exe on Windows) and its assets folder. Note that if you are not using any assets, Cinder does not require the existence of an assets folder.

<br>
<br>
<br>

### Assets on iOS

iOS applications of course cannot require a separate folder at runtime. However TinderBox-generated iOS applications automatically include their _assets_ folder in their application's bundle, and the asset-discovery mechanism in Cinder on iOS knows to look here.

<br>
<br>
<br>

### Additional Asset Folders

While Cinder will automatically look for a specific folder as the "official" assets directory, users can use [`addAssetDirectory()`] in order to offer supplemental paths for searching for assets. [`loadAsset()`] and [`getAssetPath()`] will search the primary assets folder first, followed by any supplemental asset directories the user may have provided.

That's all there is to know about assets. If you're a beginner with Cinder, this is probably the easiest technique for including data with your application. However it's worth being aware of how to use resources as well. While they're a bit more cumbersome to use, resources allow you to create applications which are entirely self-contained.

<br>
<br>
<br>

### Resources

**OS X & iOS**

Under OS X and iOS, resources are just normal files which are contained inside the application bundle. If you haven't before, try opening up one of these bundles yourself. Context-click (right-click or control-click) an application in your *Applications* folder and choose **Show Package Contents**. Here's the results of doing this with iTunes:

![image](https://cloud.githubusercontent.com/assets/2152766/14065868/5fb7a5ee-f432-11e5-81f0-c4cdf26f56a5.png)
![image](https://cloud.githubusercontent.com/assets/2152766/14065870/61c6a272-f432-11e5-9598-554bc3d5ae09.png)

Looking around inside of the application bundle, we see a *Resources* folder inside of *Contents*. In here we can find all the data files the application depends on. As an example, the first few visible files in the screenshot are audio files iTunes plays as part of its user interface.

A similar structure is maintained for iPhone and iPad apps, and it's the one Cinder uses for these platforms as well.

<br>
<br>
<br>

### Adding a Resource

Adding a resource to your OS X or iOS application is straightforward. Let's assume you've got an image you'd like to use in your app. The first step is to add this file as a resource in Xcode. First, pull up your project window in Xcode. Now, context-click the *Resources* folder and choose **Add | Existing Files...**.

![image](https://cloud.githubusercontent.com/assets/2152766/14065874/8038654c-f432-11e5-85fd-948eabb60625.png)

Now select the file you'd like to add to your app from the Open dialog box that follows. After choosing your file, you'll see it listed in the * Resources* group of your Xcode project. The real magic happens though when Xcode copies these files into your application bundle at build time. To confirm that this will happen, select the *Targets* tab of your project inspector and reveal your application target under the *Targets* section. You'll see a build phase called *Copy Bundle Resources* and inside that will be the resource you've just added.

![image](https://cloud.githubusercontent.com/assets/2152766/14065876/85333a0e-f432-11e5-80fe-21a6d70032ef.png)

<br>
<br>
<br>

### Using a Resource

Now that we've a resource in the application, how do we actually make use of it with Cinder code? For an OS X or iOS-only application, we simply call the [`loadResource()`] function and pass it the name of the resource as a string. The result of this function (which is a [`DataSourceRef`], a class you won't generally need to use directly) can be passed to most Cinder functions and constructors that know how to do I/O. In the case of our logo image example, we would call [`loadResource()`] on that file and then pass it to [`loadImage()`]. Then the result of [`loadImage()`] can be used to create a [`gl::Texture`] or a [`Surface`] like so:

```cpp
myTexture = gl::Texture::create(loadImage(loadResource("Logo.jpg")));
Surface mySurface(loadImage(loadResource("Logo.jpg")));
```

or perhaps we want to create a QuickTime movie out of a resource called *FlyingLogo.mov*:

```cpp
myMovie = qtime::MovieGl::create(loadresource("FlyingLogo.mov"));
```

Pretty easy stuff. On the Cocoa side, that's all there is to it. In general, you can make use of the results of [`loadResource()`] about like you'd expect. However a handy function if you ever need to load a resource using a function which only accepts file paths is [`getResourcePath()`]. For example, calling this:

```cpp
console() << getResourcePath("Logo.jpg") << endl;
```

Results in something about like this: `/Users/andrewfb/Code/cinder/samples/resizeTest/xcode/build/Debug/resizeTest.app/Contents/Resources/Logo.jpg`

<br>
<br>
<br>

### Resources on Windows

Let's take a look now at how resources are handled on Microsoft Windows. The most noticeable difference relative to OS X is that resources are not stored as individual files, since an EXE does not encapsulate a directory like an OS X application bundle does. Instead, resources are baked into the EXE using a resource compiler, and are stored as binary data. However we can access this binary data in memory using the same [`loadResource()`] routine we do on OS X. Furthermore, Cinder's internal code is able to handle loading from either the flat file or in-memory representations transparently and efficiently, so in general you will not need to change application code between the platforms.


[`loadAsset()`]: cinder/app/loadAsset.md
[`getAssetPath()`]: cinder/app/getAssetPath.md
[`addAssetDirectory()`]: cinder/app/addAssetDirectory.md
[`DataSourceRef`]: cinder/DataSource.md
[`loadResource()`]: cinder/app/loadResource.md
[`loadImage()`]: cinder/loadImage.md
[`gl::Texture`]: cinder/gl/Texture.md
[`Surface`]: cinder/Surface.md
[`getResourcePath()`]: cinder/app/getResourcePath.md