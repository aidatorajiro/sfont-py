/*
    Copyright (C) 2021 Torajiro Aida

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#define SFTOOLS_NOXML

#include <Python.h>
#include "sfont.h"
#include "sfont.cpp"

typedef struct {
    PyObject_HEAD
    SoundFont * sf;
} PySoundFont;

static PyObject * SoundFont_new (PyTypeObject *type, PyObject *args, PyObject *kwds) {
  PySoundFont *self;
  
  self = (PySoundFont *) type->tp_alloc(type, 0);
  
  const char *path;

  if(!PyArg_ParseTuple(args, "s", &path)){
    return NULL;
  }

  const QString &qs = QString(path);

  SfTools::SoundFont *sf = new SfTools::SoundFont(qs);
  
  if (sf->read() == false) {
      PyErr_SetString(PyExc_RuntimeError, "error in read() at sfont.cpp");
      return NULL;
  }
  
  self->sf = sf;

  return (PyObject*)self;
}

static PyTypeObject PySoundFontType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "sfont.SoundFont",
    .tp_doc = "SoundFont in sfont.h",
    .tp_basicsize = sizeof(PySoundFont),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = SoundFont_new,
};

static PyMethodDef SfontMethods[] = {
  {NULL, NULL, 0, NULL}
};

static PyModuleDef sfontmodule = {
  PyModuleDef_HEAD_INIT, "sfont", "sfont.h wrapper", -1, SfontMethods
};

PyMODINIT_FUNC PyInit_sfont (void) {
  if (PyType_Ready(&PySoundFontType) < 0) {
    return NULL;
  }
  PyObject *m = PyModule_Create(&sfontmodule);
  if (m == NULL) {
    return NULL;
  }
  Py_INCREF(&PySoundFontType);
  if (PyModule_AddObject(m, "SoundFont", (PyObject *) &PySoundFontType) < 0) {
    Py_DECREF(&PySoundFontType);
    Py_DECREF(m);
    return NULL;
  }
  return m;
}

int main(int argc, char *argv[]){
  wchar_t *program = Py_DecodeLocale(argv[0], NULL);
  if (program == NULL) {
    fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
    exit(1);
  }
  PyImport_AppendInittab("sfont", PyInit_sfont);
  Py_SetProgramName(program);
  Py_Initialize();
  PyImport_ImportModule("sfont");
  PyMem_RawFree(program);
  return 0;
}
