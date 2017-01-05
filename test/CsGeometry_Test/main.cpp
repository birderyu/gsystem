#include "CsGeometryFactory.h"
#include "CsGeometryHelper.h"

int main(int argc, char *argv[])
{
	CsGeometryFactory factory;
	CsGeometryP geo = factory.CreatePoint3D(1, 2, 3);
	CsPointP poi = CsGeometryHelper::ConvertTo<CsPoint>(geo);

	cs_real x = poi->X();
	cs_real y = poi->Y();
	cs_real z = poi->Z();

	poi->SetX(200);
	x = poi->X();

	system("pause");
}