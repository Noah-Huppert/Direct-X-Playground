#ifndef LOG_DEF
#define LOG_DEF
#include "DXApp.h"

class Log{
public:
	Log(){

	}

	Log(LPCSTR sPrefix){
		Log::prefix = sPrefix;
	}

	void Ouput(LPCSTR message, float var = NULL){
		char buffer[8192]; // sufficently large buffer
		if (!var){
			sprintf_s(buffer, message);
		}
		else{
			sprintf_s(buffer, "%d", var);
		}
		MessageBox(NULL, buffer, Log::prefix, MB_OK);
	}
private:
	LPCSTR prefix;
};

#endif