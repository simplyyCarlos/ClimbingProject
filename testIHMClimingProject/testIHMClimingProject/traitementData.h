#pragma once
#include "Data.h"
#pragma push_macro("slots")
#undef slots
#include "Python.h"
#pragma pop_macro("slots")
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <iostream>
using namespace std;
namespace py = pybind11;

class TraitementData
{
public:
	TraitementData(Data*);
	~TraitementData();
	void set_matrix(py::array_t<double>);
private:
	Data* dt;
};


