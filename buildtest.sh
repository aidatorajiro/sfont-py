clang++ -dynamiclib -L/usr/local/lib -logg -lvorbis -lvorbisfile -lvorbisenc -I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include -F/usr/local/opt/qt/lib -framework QtCore -std=c++11 main.cpp -o sfont.dylib
python3 test.py