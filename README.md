# Todo Generator

Automated project parsing to create todo-files.  Cross platform, requires C++17.

If using as a build script for github, add `todogen.exe`'s directory to your PATH, then in your script use:

```
todogen.exe -g
```

Capable of generating reports in Markdown, JSON, or plain console.  See example output [here](/docs/todo.md)

```
Todo Generator v1

Options:
Short   Long            Desc
-h      --help          Shows this help screen
-w      --write         Writes the output data to a predetermined file
-g      --git           Same as -m & -w, useful for Visual Studio build events

Generators:
Short   Long            Desc
-m      --markdown              Output results in a Markdown table
-c      --console               Output results for Console Usage
-j      --json          Output results as a JSON object
```

## Building:

### Windows:
* Clone the repo, open the .sln in Visual Studio and build.
* Edit `PATH` environment variable to include wherever you put `todogen.exe`.

### Linux:
* Clone the repo, if using GCC, you must have 8+ for `std::filesystem` to work.  Check with `G++ --version`, cmake should block you from using < 8.
* `cmake . && make`
* Move to /usr/bin/gcc if you want

### Mac
* No idea, you're on your own.