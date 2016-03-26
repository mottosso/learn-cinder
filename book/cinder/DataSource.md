### DataSource

A Cinder asset or resource.

| Namespace      | Include
|----------------|-----------------
| `DataSource`   | `#include "cinder/DataSource.h"`

<br>
<br>
<br>

### Public Members

| Output       | Member
|-------------:|--------------
| bool         | isFilePath ()=0
| bool         | isUrl ()=0
| const fs::path & | getFilePath ()
| const Url &  | getUrl ()
| const fs::path & | getFilePathHint ()
| BufferRef    | getBuffer ()
| IStreamRef   | createStream ()=0