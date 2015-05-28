CEF MinGW Qt
===================

A very simple web client built using in [Chromium Embedded
Framework](https://bitbucket.org/chromiumembedded/cef) & Qt with MinGW.
The Cef events are processed by the Qt Application object. Sub-processes are spawned using a separate executable.

About
-----

The project was sucessfully compiled and tested using the following components :
- Qt 5.3.1 for Win32 (MinGW)
- MinGW (4.8.2 Dwarf)
- CEF 3.2272.2077 Win32
- CMake 3.1.0

Building
-----

* Download https://cefbuilds.com/#branch_2272 (CEF 3.2272.2077)
* Extract and copy **only** the following directories to your local git repository :

```
Debug/
Release/
Resources/
```

Do not replace "include" and "libcef_dll" directories, they have been patched by myself to allow the compilation with MinGW (see "MinGW Compilation" section).

* Run cmake on the root CMakeLists.txt
* Run "make install" on the generated MakeFile

Project
-----

* cefqtclient
    - main browser process and ui
* cefsubprocess
    - separate sub-process executable
* libcef_dll
    - cef3's c++ wrapper

MinGW Compilation
-----



Thanks to
-----

The guys from the Cef forum for their direct/indirect help.

The main CMakeLists.txt was widely built based on the Cef SimpleClient example.

Navigation icons picked from "Iconic" pack (http://somerandomdude.com/work/iconic/), under CC License.