// TestPtut.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#define PY_SSIZE_T_CLEAN
#include <boost/interprocess/windows_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <Python.h>
#include <string>
using namespace boost::interprocess;
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

void testSharedMemory() {

    //Create a native windows shared memory object.
    windows_shared_memory shmem(create_only, "shm", read_write, sizeof(unsigned int[16]));

    //Map the whole shared memory in this process
    mapped_region region(shmem, read_write);

    //Write all the memory to 1
    std::memset(region.get_address(), 1, region.get_size());

    launchMediapipe("ptut.py");
    unsigned int* tab = static_cast<unsigned int*>(region.get_address());


    cout << region.get_address() << endl << sizeof(unsigned int[16]) << endl;

   

    for (size_t i = 0; i < 8; i++)
    {
        cout << tab[i] << " " << tab[i+8] << endl;
    }
}
    

void launchOpenCV(const char* pyFileName, wchar_t* program = Py_DecodeLocale("python_instance", NULL)) {
    if (program == NULL) {
        cout << "wchar_t erro\n";
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
    //testSharedMemory();
    launchOpenCV("image_capture.py");
    return 0;

}




    
        
