#include "gstring16.h"

namespace gsystem {

GString16::GString16()
	: m_tBaseString()
{

}

GString16::GString16(gchar16 c)
	: m_tBaseString(c)
{

}

GString16::GString16(gcstring16 str)
	: m_tBaseString(str)
{

}

GString16::GString16(const GString16 &str)
	: m_tBaseString(str.m_tBaseString)
{

}

GString16::GString16(GString16 &&str)
	: m_tBaseString(GMove(str.m_tBaseString))
{

}

}
