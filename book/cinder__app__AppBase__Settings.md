### Settings

Startup settings, used during App construction. They are modified before the app is created by passing a `SettingsFn` to the app instantiation macros.

| Namespace |
|------------
| `cinder::app::BaseApp::Settings`

<br>
<br>
<br>

### Example

```cpp
#include "cinder/app/App.h"

// Create it as an anonymous function..
auto settingsFunc = []( App::Settings *settings ) {
	settings->setConsoleWindowEnabled();
	settings->setMultiTouchEnabled( false );
};

// And pass to instanatiation macro.
CINDER_APP(SimpleReceiverApp, RendererGl, settingsFunc)
```
