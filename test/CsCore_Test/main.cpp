#include "CsArray.h"
#include "CsString.h"

int main(int argc, char *argv[])
{
	CsArray<cs_int> arr;
	arr.Resize(5, 987);
	cs_int v = arr[0];
	system("pause");
}