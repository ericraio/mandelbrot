#include <Python.h>

int iterate_point(double x0, double y0, int max_iterations)
{
  int iteration = 0;
  double x = x0, y = y0, x2 = x * x, y2 = y * y;

  while (x2 + y2 < 4 && iteration < max_iterations) {
    y = 2 * x * y + y0;
    x = x2 - y2 + x0;
    x2 = x * x;
    y2 = y * y;
    iteration++;
  }

  return iteration;
}

PyDoc_STRVAR(mandelbrot__doc__, "Mandelbrot point evaluation kernel");

PyDoc_STRVAR(iterate_point__doc__, "x,y,max_iterations -> iteration count at that point, up to max_iterations");

static PyObject *py_iterate_point(PyObject *self, PyObject *args)
{
  double x = 0, y = 0;
  int iterations, max_iterations = 1000;
  if (!PyArg_ParseTuple(args, "dd|i:iterate_point", &x, &y, &max_iterations)) return NULL;
  if (max_iterations < 0) max_iterations = 0;

  iterations = iterate_point(x, y, max_iterations);
  return PyInt_FromLong((long) iterations);
}

static PyMethodDef mandelbrot_methods[] = {
  {"iterate_point", py_iterate_point, METH_VARARGS, iterate_point__doc__},
  {NULL, NULL}  // sentinel
};

PyMODINIT_FUNC initmandelbrot(void)
{
  Py_InitModule3("mandelbrot", mandelbrot_methods, mandelbrot__doc__);
}
