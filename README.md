# Dependencies:
libsdl2
libsdl2-ttf
libsdl2-image
libsdl2-mixer

Install the dev dependencies of these as well and you should be good.

- Remove -mwindows
- Add nnb headers

# Windows
- Build de static zlib version in nutsnbolts
	- cmake ..
	- open solution
	- select zlib/zlib static, release, build
	- it should be in your build folder
	- I also did the install taregt. This installs it to your program files (lol). Install needs administrator rights
- Build libpng in nutsnbolts
	- I used:
		- cmake -DZLIB_LIBRARY='C:\Program Files (x86)\zlib\lib\zlibstatic.lib' -DZLIB_INCLUDE_DIR='C:\Program Files (x86)\zlib\include' ..
	- open solution
	- select release, build
	- should be in build folder
	- or do install and it'll end up in program files :D
- Install libjpeg somewhere
	- This page seemed to work: http://gnuwin32.sourceforge.net/packages/jpeg.htm

- compiler unknown: https://stackoverflow.com/questions/14372706/visual-studio-cant-build-due-to-rc-exe/14373113#14373113

cmake -DZLIB_INCLUDE="C:\Program Files (x86)\zlib\include" -DZLIB_STATIC_LIBRARY="C:\Program Files (x86)\zlib\lib\zlibstatic.lib" -DLIBPNG_INCLUDE="C:\Program Files (x86)\libpng\include" -DLIBPNG_STATIC_LIBRARY="C:\Program Files (x86)\libpng\lib\libpng16_static.lib" ..