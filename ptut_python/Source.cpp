// TestPtut.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#define PY_SSIZE_T_CLEAN
#include <iostream>
#include <Python.h>
#include <string>
using namespace std;

void launchMediapipe(const char* pyFileName,wchar_t* program = Py_DecodeLocale("python_instance", NULL)) {
    if (program == NULL) {
        cout << "wchar_t error\n";
    }
    FILE* f;
    errno_t err;
    err = fopen_s(&f, pyFileName, "r");
    Py_SetProgramName(program);
    Py_Initialize();
    PyRun_SimpleFile(f, pyFileName);
    if (Py_FinalizeEx() < 0) {
        return;
    }
    PyMem_RawFree(program);

}

int main() {

    launchMediapipe("ptut.py");

    return 0;

}