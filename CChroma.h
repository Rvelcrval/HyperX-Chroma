#pragma once
#include "HXChroma.h"
#include "Color.h"

namespace HXChroma {
	const char* hid_bus_name ( hid_bus_type bus_type );
	void print_device ( hid_device_info* cur_dev );
	void print_devices ( hid_device_info* cur_dev );
}

class CChroma { 
public:
	CChroma ( ) {

	}

	bool Send ( );
	void WriteKey ( BYTE Key, Color color );
	void Clear ( );

	void SetDevice ( hid_device* device );
	bool SetDevice ( unsigned short Vend, unsigned short Prod, const wchar_t* Serial = NULL );
	bool SetDeviceWithUsage ( unsigned short Vend, unsigned short Prod, USAGE usage );
	void Close ( );

	void PrintInfo ( );

	unsigned char Buf[ 64 * 9 + 1 ] = { 0 };
	hid_device* hDevice = nullptr;
};

extern CChroma* g_pChroma;