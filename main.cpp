#define SFTOOLS_NOXML

#include "sfont.h"
#include "sfont.cpp"

extern "C" SfTools::SoundFont * read_sound_font (char * path) {
    const QString &qs = QString(path);
    SfTools::SoundFont *sf = new SfTools::SoundFont(qs);
    sf->read();
    return sf;
}

extern "C" QList<void *> qlist_new () {
    QList<void *> list;
    return list;
}

extern "C" void qlist_add (QList<void *> *in, void * elem) {
    in->append(elem);
}

extern "C" void * qlist_get (QList<void *> *in, int ind) {
    return in->operator[](ind);
}

extern "C" int qlist_size (QList<void *> *in) {
    return in->size();
}