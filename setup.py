import sys
import os
import subprocess

mac_build = "clang++ -dynamiclib -L/usr/local/lib -lsndfile -logg -lvorbis -lvorbisfile -lvorbisenc -I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include -F/usr/local/opt/qt/lib -framework QtCore -framework QtXml -std=c++11 interface.cpp -o sfont.dylib"
linux_build = "gcc -shared -lsndfile -logg -lvorbis -lvorbisfile -lvorbisenc -o sfont.so -fPIC interface.cpp"
win_build = "cl.exe /D_USRDLL /D_WINDLL interface.cpp sfont.h sfont.cpp /link /DLL /OUT:sfont.dll"

if sys.platform == "darwin":
    if os.path.exists("/usr/local/opt/qt/lib"):
        subprocess.run(mac_build.split(" "))
    else:
        raise RuntimeError("Please install qt under /usr/local/opt/qt via homebrew")
elif sys.platform == "linux":
    subprocess.run(linux_build.split(" "))
elif sys.platform == "win32":
    subprocess.run(win_build.split(" "))
else:
    subprocess.run(linux_build.split(" "))
