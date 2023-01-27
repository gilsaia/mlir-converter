#include <python3.8/Python.h>

void test_python() {
  Py_Initialize();
  PyRun_SimpleString("print('Find useful')");
  Py_Finalize();
}