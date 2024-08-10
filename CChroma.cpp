#include "CChroma.h"

#include <mutex>

CChroma* g_pChroma = new CChroma ( );

static const unsigned char report[ 65 ] = { 0x0,
	0x04, 0xf2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static std::mutex m;
bool CChroma::Send ( ) {
	std::lock_guard<std::mutex> lock ( m );

	//Buf[ 1 ] = 0x04;
	//Buf[ 2 ] = 0xF2;
	//Buf[ 9 ] = 0x9;
	if ( hid_send_feature_report ( hDevice, report, 65 ) < 0 ) {
		wprintf ( L"Unable to send a feature report.\n %s\n", hid_error ( hDevice ) );
		return false;
	}

	for ( int times = 0; times < 9; times++ )
		hid_send_feature_report ( hDevice, Buf + 64 * times, 65 );
	return true;
}

void CChroma::WriteKey ( BYTE Key, Color color ) {
	std::lock_guard<std::mutex> lock ( m );

	Buf[ 1 + Key * 4 ] = 0x81;
	Buf[ 2 + Key * 4 ] = color.r;
	Buf[ 3 + Key * 4 ] = color.g;
	Buf[ 4 + Key * 4 ] = color.b;
}

void CChroma::Clear ( ) {
	std::lock_guard<std::mutex> lock ( m );

	ZeroMemory ( Buf, sizeof Buf );
}

void CChroma::SetDevice ( hid_device* device ) {
	hDevice = device;
	hid_set_nonblocking ( hDevice, 1 );
}

bool CChroma::SetDevice ( unsigned short Vend, unsigned short Prod, const wchar_t* Serial ) {
	auto device = hid_open ( Vend, Prod, Serial );
	if ( !device ) {
		printf ( "unable to open device\n" );
		return false;
	}
	SetDevice ( device );

	return true;
}

bool CChroma::SetDeviceWithUsage ( unsigned short Vend, unsigned short Prod, USAGE usage ) {
	auto device_inf = hid_enumerate ( Vend, Prod );
	for ( ; device_inf; device_inf = device_inf->next ) {
		if ( device_inf->usage & usage ) {
			auto device = hid_open_path ( device_inf->path );
			SetDevice ( device );

			return true;
		}
	}
	return false;
}

void CChroma::Close ( ) {
	hid_close ( hDevice );
	hid_exit ( );
}

void CChroma::PrintInfo ( ) {
	if ( hid_device_info* info = hid_get_device_info ( hDevice ) )
		HXChroma::print_devices ( info );
	else
		printf ( "Unable to get device info\n" );
}

namespace HXChroma {
	const char* hid_bus_name ( hid_bus_type bus_type ) {
		static const char* const HidBusTypeName[ ] = {
			"Unknown",
			"USB",
			"Bluetooth",
			"I2C",
			"SPI",
		};

		if ( (int)bus_type < 0 )
			bus_type = HID_API_BUS_UNKNOWN;
		if ( (int)bus_type >= (int)(sizeof ( HidBusTypeName ) / sizeof ( HidBusTypeName[ 0 ] )) )
			bus_type = HID_API_BUS_UNKNOWN;

		return HidBusTypeName[ bus_type ];
	}

	void print_device ( hid_device_info* cur_dev ) {
		printf ( "Device Found\n  type: %04hx %04hx\n  path: %s\n  serial_number: %ls", cur_dev->vendor_id, cur_dev->product_id, cur_dev->path, cur_dev->serial_number );
		printf ( "\n" );
		printf ( "  Manufacturer: %ls\n", cur_dev->manufacturer_string );
		printf ( "  Product:      %ls\n", cur_dev->product_string );
		printf ( "  Release:      %hx\n", cur_dev->release_number );
		printf ( "  Interface:    %d\n", cur_dev->interface_number );
		printf ( "  Usage (page): 0x%hx (0x%hx)\n", cur_dev->usage, cur_dev->usage_page );
		printf ( "  Bus type: %u (%s)\n", (unsigned)cur_dev->bus_type, hid_bus_name ( cur_dev->bus_type ) );
		printf ( "\n" );
	}

	void print_devices ( hid_device_info* cur_dev ) {
		for ( ; cur_dev; cur_dev = cur_dev->next ) {
			print_device ( cur_dev );
		}
	}
}