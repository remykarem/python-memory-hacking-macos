import ctypes

def print_bytes(pybytes):
    libinfo = ctypes.CDLL("libinfo.so")
    libinfo.print_python_bytes.argtypes = [ctypes.py_object]
    libinfo.print_python_bytes(bytesstring)

def print_int(pyint):
    libinfo = ctypes.CDLL("libinfopylong.so")
    libinfo.print_python_long.argtypes = [ctypes.py_object]
    libinfo.print_python_long(pyint)

