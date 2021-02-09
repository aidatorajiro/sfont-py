#define SFTOOLS_NOXML

#include "sfont.h"
#include "sfont.cpp"

extern "C" SfTools::SoundFont * read_sound_font (char * path) {
    const QString &qs = QString(path);
    SfTools::SoundFont *sf = new SfTools::SoundFont(qs);
    sf->read();
    return sf;
}

struct VerySimpleList {
    int size;
    void * pointer;
};

extern "C" VerySimpleList qlist_size_first (QList<QString> in_obj) {
    VerySimpleList r = {in_obj.size(), &in_obj.first()};
    return r;
}