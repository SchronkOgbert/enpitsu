# Enpitsu
Enpitsu is a rendering library built using C++
# Build instructions(via conan and CMake)
Make sure you are in the root directory<br>
This  guide shows you how to make a debug build<br>
Run the following commands in order:<br>
`conan install . -if cmake-build --build missing`<br>
`cmake -DCMAKE_BUILD_TYPE=Debug -S . -B ./cmake-build`<br>
`cmake --build ./cmake-build`<br>
The generated static library is in `cmake-build/lib/`<br>
For a release build conan install must be run with a [Release Profile](https://docs.conan.io/1/reference/profiles.html)<br>
In this case the second command changes to<br>
`cmake -DCMAKE_BUILD_TYPE=Release -S . -B ./cmake-build`<br><br>
To create a local conan package use<br>
`conan create .`
You will then be able to consume the package locally through conan install

# Conan installation instructions
The library uses conan 1.57.0<br>
You can install it via pip<br>
`pip install conan==1.57.0`<br>
! Make sure you specify the version, because conan 2.x was recently released and it won't work with the commands above
