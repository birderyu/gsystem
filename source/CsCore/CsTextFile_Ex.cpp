#include "CsTextFile_Ex.h"
#include "CsTextFile.h"

CsTextFile_Ex::CsTextFile_Ex(const CsString &sFileName)
: CsFile_Ex(sFileName)
{

}

cs_bool CsTextFile_Ex::Open(CsFile::CS_FILE_OPEN_MODE emOpenMode)
{
	if (!Close())
	{
		return false;
	}
	if (m_sFileName.IsEmpty())
	{
		return false;
	}
	if (!CsFile_Ex::Open(emOpenMode))
	{
		return false;
	}
	errno_t errno;
	if (m_emOpenMode == CsFile::FILE_OPEN_MODE_ONLY_READ)
	{
		errno = fopen_s(&m_pFileStream, m_sFileName.CString(), "rt");
	}
	else if (m_emOpenMode == CsFile::FILE_OPEN_MODE_ONLY_WIRTE)
	{
		errno = fopen_s(&m_pFileStream, m_sFileName.CString(), "wt");
	}
	else if (m_emOpenMode == CsFile::FILE_OPEN_MODE_READ_WIRTE)
	{
		errno = fopen_s(&m_pFileStream, m_sFileName.CString(), "rt+");
	}
	else if (m_emOpenMode == CsFile::FILE_OPEN_MODE_APPEND)
	{
		errno = fopen_s(&m_pFileStream, m_sFileName.CString(), "at");
	}
	return errno != 0 && m_pFileStream != NULL;
}

cs_bool CsTextFile_Ex::ReadLine(CsString &line)
{
	if (!m_pFileStream || !CanRead(m_emOpenMode))
	{
		// 无法读取文件
		return false;
	}

	if ((bufindex >= maxbuf) && (feof(m_pFileStream)))
	{
		return false;
	}

	int complete = false;
	unsigned long j = 0, i;

	cs_char s[LINEBUFSIZE];
	do
	{
		for (i = bufindex; (i < maxbuf) && (!complete); i++)
		{
			if (buf[i] != CS_CR)
			{
				if ((j >= (LINEBUFSIZE - 1)) || (buf[i] == CS_LF))
				{
					complete = true;
					s[j++] = 0x0;
				}
				else
					s[j++] = buf[i];
			}
		}
		bufindex = i;

		if (!complete)
		{
			if (feof(m_pFileStream))
				complete = true;
			else
			{
				maxbuf = fread(buf, 1, LINEBUFSIZE, m_pFileStream);
				bufindex = 0;
			}
		}
	} while (!complete);

	s[j] = 0x0;
	return true;
}

cs_bool CsTextFile_Ex::WriteLine(const CsString &line, cs_int format)
{
	/*
	if (!m_pFileStream || !CanWrite(m_emOpenMode))
	{
		// 无法写入文件
		return false;
	}

	int complete = false;
	long len;

	while (!complete)
	{
		len = strlen(line.GetCStr());
		if (bufindex + len < LINEBUFSIZE)
		{
			memcpy((void *)&buf[bufindex], line.GetCStr(), len);
			bufindex += len;

			if ((format == CS_CR) || (format == CS_CRLF))
			{
				if (bufindex + 1 >= LINEBUFSIZE)
				{
					if (fwrite(buf, 1, bufindex, m_pFileStream) != bufindex)
						return(0);
					bufindex = 0;
				}
				buf[bufindex++] = CS_CR;
			}

			if ((format == CS_LF) || (format == CS_CRLF))
			{
				if (bufindex + 1 >= LINEBUFSIZE)
				{
					if (fwrite(buf, 1, bufindex, m_pFileStream) != bufindex)
						return(0);
					bufindex = 0;
				}
				buf[bufindex++] = CS_LF;
			}
			complete = true;
		}
		else
		{
			memcpy((void *)&buf[bufindex], line.GetCStr(), LINEBUFSIZE - bufindex);
			if (fwrite(buf, 1, LINEBUFSIZE, m_pFileStream) != LINEBUFSIZE)
				return(0);
			ptr += (LINEBUFSIZE - bufindex);
			bufindex = 0;
		}
	}
	return(1);
	*/
	return false;
}
