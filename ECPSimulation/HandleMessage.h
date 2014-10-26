#pragma once
#include "Lon2S4230.h"
#include "VirtualCCDManage.h"
	
class CHandleMessage
	{
	private:
		CLon2S4230 lonOP;
	
	public:
		CHandleMessage(void);
		~CHandleMessage(void);
		void Handle_Message_3();
		void Handle_Message_4();
		void Handle_Message_13();

	};

