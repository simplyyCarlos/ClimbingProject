// TestPtut.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <Python.h>
#include <vector>
#include <pybind11/embed.h>
#include <pybind11/pybind11.h>
#include <pybind11/attr.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <pybind11/pytypes.h>
#include <sstream>

//using namespace boost::interprocess;
using namespace std;
namespace py = pybind11;
static char* URL;



/*
void launchMediapipe(const char* pyFileName,wchar_t* program = Py_DecodeLocale("python_instance", NULL)) {
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

}*/
/*
void testSharedMemory() {

    //Create a native windows shared memory object.
    windows_shared_memory shmem(create_only, "shm", read_write, sizeof(unsigned int[16]));

    //Map the whole shared memory in this process
    mapped_region region(shmem, read_write);

    //Write all the memory to 1
    std::memset(region.get_address(), 1, region.get_size());

    //launchMediapipe("ptut.py");
    unsigned int* tab = static_cast<unsigned int*>(region.get_address());


    cout << region.get_address() << endl << sizeof(unsigned int[16]) << endl;

    float x = 0.0f;
    float y = 0.0f;

    for (size_t i = 0; i < 8; i++)
    {
        x = tab[i] *= 10 ^ -8;
        y = tab[i + 8] *= 10 ^ -8;
        cout << x << " " << y;
    }
}
*/  
/*
int launchOpenCV(const char * programName) {
   
    

    int res = PyRun_SimpleFile(f, programName);
    Py_Finalize();
    
    status = _Py_InitializeMain();
    if (PyStatus_Exception(status)) {
        Py_ExitStatusException(status);
    }
    
}
*/




void set_url( char* py_url) {
    URL = py_url;
    std::cout << URL;
}

void set_float(py::dict& f) {
    vector<double> l;
    for (auto i : f) {
        double index = stof(string(py::str(i.first)));
        double value = stof(string(py::str(i.second)));
        l.push_back(index);
        l.push_back(value);
    }
    for (auto i : l) {
        cout << i << endl;
    }
    
    
}

void set_matrix(py::array_t<double>& mat) {
    long double d;
    vector<double> tab;
    string a =(string)py::str(mat);
    cout << a << endl;
    a.erase(remove(a.begin(), a.end(), '['),a.end());
    a.erase(remove(a.begin(), a.end(), ']'), a.end());
    stringstream ss(a);
    for (size_t i = 0; i < 9; i++)
    {
        ss >> d;
        cout << i << " " << d << endl;
        d = 0.0f;
    }
    ss >> d;
    cout << d << endl;
}

PYBIND11_EMBEDDED_MODULE(embeddedmodule, module)
{
    module.doc() = "Embedded module";
    module.def("set_url", &set_url);
    module.def("set_float", &set_float);
    module.def("set_matrix", &set_matrix);
}

class Matrix {
public:
    Matrix(size_t rows, size_t cols) : m_rows(rows), m_cols(cols) {
        m_data = new float[rows * cols];
    }
    float* data() { return m_data; }
    size_t rows() const { return m_rows; }
    size_t cols() const { return m_cols; }
private:
    size_t m_rows, m_cols;
    float* m_data;
};


void main() {
    py::scoped_interpreter guard{};
    
    
    /*auto mediapipe = py::module::import("ptut");
    auto main_mediapipe = mediapipe.attr("main");
    main_mediapipe();

    auto screenshot = py::module::import("image_capture");
    auto main_screenshot = screenshot.attr("main");
    main_screenshot();*/
    

    
    auto matrix = py::module::import("testCalibrage");
    auto main_matrix = matrix.attr("main");
    main_matrix();
    printf("end\n");
    
}





        
