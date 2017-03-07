#include "gjsonobject.h"
#include "gjsonparsermessage.h"

#include "gtextfile.h"

gvoid Test_Json_Parse()
{
	GTextFile file("C:\\Users\\birde\\Desktop\\geojson\\roads-seoul.geojson");
	file.Open(GFile::ONLY_READ);
	GString jsonStr;
	file.ReadAll(jsonStr);

	//GString jsonStr = "{\"name\":1.1, \"key\":false, \"sex\":null, \"age\":\"12\",\"addr\":{\"street\":\"ÐÂ½Ö¿Ú\"},\"friend\":[1,2,3,4]}";
	//GString jsonStr = "{\"friend\":[1,2,3,4]}";
	std::cout << jsonStr.CString() << std::endl;

	GJsonObject json;
	gsize cursor = 0;
	GJsonParserMessage msg;
	gbool success = json.Parse(jsonStr, &cursor, &msg);
	if (!success)
	{
		gchar ec = jsonStr.GetAt(msg.ErrorCursor());
		gint stop = 1;
		stop++;
	}
	else
	{
		GString jsonStr_2 = json.ToString();
		GTextFile file_2("C:\\Users\\birde\\Desktop\\geojson\\roads-seoul.geojson.copy");
		file_2.Open(GFile::ONLY_WIRTE);
		file_2.Write(jsonStr_2);
		file_2.Close();
	}
	file.Close();

	gint stop = 1;
	stop++;
}