#pragma once

#include "AclLib.h"
#include "ConversationState.h"

class ACLLIB_API ConversationStateConverter
{
private:
	ConversationStateConverter(void);
	~ConversationStateConverter(void);
public:
	static ConversationState ConvertTo(CString str);
	static const char *ConvertFrom(ConversationState state);
};

