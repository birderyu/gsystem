#include "ggeometryfactory.h"
#include "ggeometryhelper.h"

int main(int argc, char *argv[])
{
	GGeometryFactory factory;
	GGeometryP geo = factory.CreatePoint3D(1, 2, 3);
	GPointP poi = GGeometryHelper::ConvertTo<GPoint>(geo);

	greal x = poi->X();
	greal y = poi->Y();
	greal z = poi->Z();

	poi->SetX(200);
	x = poi->X();

	system("pause");
}