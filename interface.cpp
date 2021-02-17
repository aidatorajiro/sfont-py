#define SFTOOLS_NOXML

#include "sfont.h"
#include "sfont.cpp"

extern "C" SfTools::SoundFont * read_sound_font (char * path) {
    const QString &qs = QString(path);
    SfTools::SoundFont *sf = new SfTools::SoundFont(qs);
    sf->read();
    return sf;
}

extern "C" SfTools::SoundFont * new_sound_font () {
    const QString &qs = QString("");
    SfTools::SoundFont *sf = new SfTools::SoundFont(qs);
    return sf;
}

extern "C" int qlist_size (QList<void *> *in) {
    return in->size();
}

extern "C" void ** qlist_first (QList<void *> *in) {
    return &in->first();
}