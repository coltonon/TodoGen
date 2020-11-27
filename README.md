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