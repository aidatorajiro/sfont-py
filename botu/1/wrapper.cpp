#include <list>
#include <string>
#include <fstream>
using namespace std;

#define SFTOOLS_NOXML
#include <Python.h>
#include "sfont.h"
#include "sfont.cpp"

static PyObject * func_system(PyObject *self, PyObject *args){
  const char *command;
  int sts;

  if(!PyArg_ParseTuple(args, "s", &command)){
    return NULL;
  }
  sts = system(command);

  return PyLong_FromLong(sts);
}

static PyObject * func_SoundFont(PyObject *self, PyObject *args){
  const char *path;

  if(!PyArg_ParseTuple(args, "s", &path)){
    return NULL;
  }

  const string &qs = QString(path);

  new SfTools::SoundFont(qs);

  return PyBool_FromLong(1);
}

static PyMethodDef SfontMethods[] = {
  {"system", func_system, METH_VARARGS, "Execute a shell command."},
  {"SoundFont", func_SoundFont, METH_VARARGS, "Create a SoundFont instance from a file path."},
  {NULL, NULL, 0, NULL}
};

static struct PyModuleDef sfontmodule = {
  PyModuleDef_HEAD_INIT, "sfont", NULL, -1, SfontMethods
};

PyMODINIT_FUNC PyInit_sfont(void){
  return PyModule_Create(&sfontmodule);
}

int main(int argc, char *argv[]){
  wchar_t *program = Py_DecodeLocale(argv[0], NULL);
  if(program==NULL){
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
