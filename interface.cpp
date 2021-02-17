#include "xml.h"
#include "xml.cpp"
#include "sfont.h"
#include "sfont.cpp"

bool smallSf = false;

extern "C" SoundFont * read_sound_font (char * path) {
    const QString &qs = QString(path);
    SoundFont *sf = new SoundFont(qs);
    sf->read();
    return sf;
}

extern "C" SoundFont * new_sound_font () {
    const QString &qs = QString("");
    SoundFont *sf = new SoundFont(qs);
    return sf;
}

extern "C" bool write_sound_font (SoundFont *sf, char * path) {
    /*
    const QString &qs = QString(path);
    QFile f(qs);
    if (!f.open(QIODevice::ReadWrite)) {
        fprintf(stderr, "cannot open %s\n", f.fileName().toLocal8Bit().data());
        return false;
    }
    sf->file = &f;
    if (!sf->write()) {
        fprintf(stderr, "cannot write successfully\n");
        f.close();
        return false;
    }
    f.close();*/
    return true;
}

extern "C" int qlist_size (QList<void *> *in) {
    return in->size();
}

extern "C" void ** qlist_first (QList<void *> *in) {
    return &in->first();
}

extern "C" QList<void *> * qlist_new (int size, void ** simple_list) {
    QList<void *> * qlist = new QList<void *>;
    for (int i = 0; i < size; i++) {
        qlist->append(simple_list[i]);
    }
    return qlist;
}