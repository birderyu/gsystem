#include "CsGeometryFactory.h"

int main(int argc, char *argv[])
{
	CsGeometryFactory factory;
	CsPointP poi = factory.CreatePoint(1, 2);
	cs_real x = poi->X();
	cs_real y = poi->Y();

	poi->SetX(200);
	x = poi->X();

	system("pause");
}