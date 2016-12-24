#include "CsBinaryFile_Ex.h"
#include "CsFile.h"
#include "CsBytes.h"

#define CS_BINARY_DOCUMNET_BUFFER_SIZE 4096

CsBinaryFile_Ex::CsBinaryFile_Ex(const CsString &sFileName)
: CsFile_Ex(sFileName)
{

}

CsBinaryFile_Ex::~CsBinaryFile_Ex()
{

}

cs_byte CsBinaryFile_Ex::Format() const
{
	return CsFile::BINARY_FILE;
}

cs_bool CsBinaryFile_Ex::GetByte(cs_byte &b)
{
	if (EndOfFile() || !CanRead())
	{
		return false;
	}

	cs_int ib = fgetc(m_pFileStream);
	if (EOF == ib)
	{
		return false;
	}

	b = static_cast<cs_byte>(ib);
	return true;
}

cs_bool CsBinaryFile_Ex::PutByte(cs_byte b)
{
	if (!Valid() || !CanWrite())
	{
		return false;
	}

	if (EOF == fputc(b, m_pFileStream))
	{
		return false;
	}
	return false;
}

cs_bool CsBinaryFile_Ex::Read(cs_size_t size, CsBytes &bytes)
{
	if (EndOfFile() || !CanRead() || size <= 0)
	{
		return false;
	}
	cs_size_t bytes_old_size = bytes.Size();
	cs_size_t bytes_new_size = bytes_old_size + size;
	if (bytes_new_size > bytes.Capacity())
	{
		bytes.Reserve(bytes_new_size);
	}

	cs_size_t real_bytes_new_size = fread(bytes.Tail(), sizeof(cs_byte), size, m_pFileStream);
	if (real_bytes_new_size == 0)
	{
		return false;
	}
	return bytes.Resize(bytes_old_size + real_bytes_new_size);
}

cs_bool CsBinaryFile_Ex::ReadAll(CsBytes &bytes)
{
	if (!Valid() || !CanRead())
	{
		return false;
	}

	// 旧的文件游标备份
	cs_long old_tell = Tell();

	if (!Seek(0, CsFile::SEEK_MODE_END))
	{
		// 还原游标
		Seek(old_tell, CsFile::SEEK_MODE_START);
		return false;
	}

	cs_long all_size = Tell();
	if (all_size < 0)
	{
		// 还原游标
		Seek(old_tell, CsFile::SEEK_MODE_START);
		return false;
	}

	// 将游标设置到初始位置
	Rewind();
	if (!Read(all_size, bytes))
	{
		// 还原游标
		Seek(old_tell, CsFile::SEEK_MODE_START);
		return false;
	}

	return true;
}

cs_bool CsBinaryFile_Ex::Write(const CsBytes &bytes)
{
	if (!Valid() || !CanWrite())
	{
		return false;
	}
	if (0 == fwrite(bytes.Head(), sizeof(cs_byte), bytes.Size(), m_pFileStream))
	{
		return false;
	}
	return true;
}

cs_cstring CsBinaryFile_Ex::OpenMode() const
{
	switch(m_nOpenMode)
	{
		case CsFile::NO_OPEN:
			return NULL;
		case CsFile::ONLY_READ:
			return "rb";
		case CsFile::ONLY_WIRTE:
			return "wb";
		case CsFile::READ_WIRTE:
			return "rb+";
		case CsFile::APPEND:
			return "ab";
		default:
			break;
	}
	return NULL;
}

#undef CS_BINARY_DOCUMNET_BUFFER_SIZE
