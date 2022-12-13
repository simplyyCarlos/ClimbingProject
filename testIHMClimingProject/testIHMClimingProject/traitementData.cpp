#include "traitementData.h"

TraitementData::TraitementData(Data* _dt) : dt(_dt)
{
}

TraitementData::~TraitementData()
{
}

void TraitementData::set_matrix(py::array_t<double> mat)
{
	for (auto i : mat)
	{
		cout << i << endl;
	}
}
