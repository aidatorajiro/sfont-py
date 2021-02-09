static PyObject * SoundFont_get_path (CustomObject *self, PyObject *args) {
  return PyBytes_FromString(self->sf->path.toLocal8Bit().data());
}
static PyObject * SoundFont_get_version (CustomObject *self, PyObject *args) {
  return self->sf->version sfVersionTag;
}
static PyObject * SoundFont_get_engine (CustomObject *self, PyObject *args) {
  return PyBytes_FromString(self->sf->engine);
}
static PyObject * SoundFont_get_name (CustomObject *self, PyObject *args) {
  return PyBytes_FromString(self->sf->name);
}
static PyObject * SoundFont_get_date (CustomObject *self, PyObject *args) {
  return PyBytes_FromString(self->sf->date);
}
static PyObject * SoundFont_get_comment (CustomObject *self, PyObject *args) {
  return PyBytes_FromString(self->sf->comment);
}
static PyObject * SoundFont_get_tools (CustomObject *self, PyObject *args) {
  return PyBytes_FromString(self->sf->tools);
}
static PyObject * SoundFont_get_creator (CustomObject *self, PyObject *args) {
  return PyBytes_FromString(self->sf->creator);
}
static PyObject * SoundFont_get_product (CustomObject *self, PyObject *args) {
  return PyBytes_FromString(self->sf->product);
}
static PyObject * SoundFont_get_copyright (CustomObject *self, PyObject *args) {
  return PyBytes_FromString(self->sf->copyright);
}
static PyObject * SoundFont_get_irom (CustomObject *self, PyObject *args) {
  return PyBytes_FromString(self->sf->irom);
}
static PyObject * SoundFont_get_iver (CustomObject *self, PyObject *args) {
  return self->sf->iver sfVersionTag;
}
static PyObject * SoundFont_get_samplePos (CustomObject *self, PyObject *args) {
  return self->sf->samplePos int;
}
static PyObject * SoundFont_get_sampleLen (CustomObject *self, PyObject *args) {
  return self->sf->sampleLen int;
}
static PyObject * SoundFont_get_presets (CustomObject *self, PyObject *args) {
  return self->sf->presets QList<Preset*>;
}
static PyObject * SoundFont_get_instruments (CustomObject *self, PyObject *args) {
  return self->sf->instruments QList<Instrument*>;
}
static PyObject * SoundFont_get_pZones (CustomObject *self, PyObject *args) {
  return self->sf->pZones QList<Zone*>;
}
static PyObject * SoundFont_get_iZones (CustomObject *self, PyObject *args) {
  return self->sf->iZones QList<Zone*>;
}
static PyObject * SoundFont_get_samples (CustomObject *self, PyObject *args) {
  return self->sf->samples QList<Sample*>;
}
static PyObject * SoundFont_get_file (CustomObject *self, PyObject *args) {
  return self->sf->file QFile*;
}
static PyObject * SoundFont_get_f (CustomObject *self, PyObject *args) {
  return self->sf->f FILE*;
}
static PyObject * SoundFont_get__compress (CustomObject *self, PyObject *args) {
  return self->sf->_compress bool;
}
static PyObject * SoundFont_get__oggQuality (CustomObject *self, PyObject *args) {
  return self->sf->_oggQuality double;
}
static PyObject * SoundFont_get__oggAmp (CustomObject *self, PyObject *args) {
  return self->sf->_oggAmp double;
}
static PyObject * SoundFont_get__oggSerial (CustomObject *self, PyObject *args) {
  return self->sf->_oggSerial qint64;
}
static PyObject * SoundFont_get__smallSf (CustomObject *self, PyObject *args) {
  return self->sf->_smallSf bool;
}