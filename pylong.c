#include "Python.h"

/**
 * print_python_bytes - prints info about a Python 3 bytes object
 * @p: a pointer to a Python 3 bytes object
 * 
 * Return: Nothing
 */
void print_python_long(PyObject *p)
{
   /* The pointer with the correct type.*/
   PyLongObject *l;
   l = (PyLongObject *)p;

   printf("  ref counts: %ld\n", p->ob_refcnt);
   /* casting the PyObject pointer to a PyBytesObject pointer */
   /* never trust anyone, check that this is actually
        a PyBytesObject object. */

   printf("Address of object %p\n", p);
   printf("Address of object %p\n", l);

   if (l && PyLong_Check(l)) {
      printf("  size: %ld\n", l->ob_base.ob_size);
      printf("  value: %d\n", *l->ob_digit);
      printf("  address: %p\n", l->ob_digit);
   }
   else
      printf("  size: %ld\n", l->ob_base.ob_size);
}