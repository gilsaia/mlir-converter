#include <python3.8/Python.h>
#include <string>

void test_python() {
  Py_Initialize();
  PyRun_SimpleString("print('Find useful')");
  Py_Finalize();
}

char *get_simple_net() {
  std::string path = "predefined/predefined_model.py";
  FILE *fp = fopen(path.c_str(), "r");

  Py_Initialize();
  PyRun_SimpleFile(fp, path.c_str());
  PyObject *key = PyUnicode_FromString("__main__");
  PyObject *m = PyImport_GetModule(key);

  PyObject *pFunc = PyObject_GetAttrString(m, "GetPredefinedModel");
  PyObject *pRet = PyObject_CallObject(pFunc, NULL);

  char *parse_res = NULL;

  PyArg_Parse(pRet, "s", &parse_res);

  Py_XDECREF(key);
  Py_DECREF(pFunc);
  Py_DECREF(pRet);
  Py_Finalize();
  fclose(fp);
  return parse_res;
}