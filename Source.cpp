#include "HXChroma.h"
#include "KeyTools.h"
#include "CChroma.h"

static hid_device* GetDeviceWithUsage ( unsigned short Vend, unsigned short Prod, USAGE usage, USAGE page ) {
	auto device_inf = hid_enumerate ( Vend, Prod );
	for ( ; device_inf; device_inf = device_inf->next ) {
		if ( device_inf->usage == usage && device_inf->usage_page == page ) {
			auto device = hid_open_path ( device_inf->path );
			return device;
		}
	}
	return nullptr;
}

std::unordered_map< KeyTools::KEY_INDEX, bool> MapKeys;

void KeyPressEvent ( KeyTools::KEY_INDEX key, bool pressed ) {

	MapKeys[ key ] = pressed;
	printf ( "Key event 0x%02x %s\n", key, pressed ? "pressed" : "released" );
}

hid_device* hKeyboard = nullptr;
bool KillThreads = false;
void KeyInputThread ( ) {
	unsigned char buf[ 8 ] = { 0 };
	while ( !KillThreads ) {
		auto ret = hid_read ( hKeyboard, buf, 8 );
		if ( ret == 0 ) continue;
		KeyPressEvent ( (KeyTools::KEY_INDEX)buf[ 2 ], buf[ 3 ] );
		
		std::this_thread::sleep_for ( std::chrono::milliseconds ( 10 ) );
	}
}

void dbgEnum(){
	auto v = hid_enumerate ( 0x03f0, 0x0591 );
	HXChroma::print_devices ( v );

	g_pChroma->PrintInfo ( );
}

int main ( int argc, char* argv[] ) {
	hKeyboard = GetDeviceWithUsage ( 0x03f0, 0x0591, HID_USAGE_PAGE_GENERIC, HID_USAGE_PAGE_VENDOR_DEFINED_END );

	if ( !hKeyboard ) {
		printf ( "Error: Keyboard not found.\n" );
		return 1;
	}

	g_pChroma->SetDevice ( 0x03f0, 0x0591 );

	auto InputThread = std::thread ( KeyInputThread );

	unsigned long long i = 0;
	while ( !(GetAsyncKeyState ( VK_HOME ) & 0x8000) || !(GetAsyncKeyState ( VK_END ) & 0x8000) ) {
		//for ( auto k : KeyTools::Row2Keys[ 2 ] )
		//	g_pChroma->WriteKey ( k, Color::hsv2rgb ( k * 5 + i * 10, 1, 1 ) );
		//for ( auto k : KeyTools::Col2Keys[ 10 ] )
		//	g_pChroma->WriteKey ( k, Color::hsv2rgb ( k * 5 + i * 10, 1, 1 ) );
		
		for ( auto k : MapKeys ) {
			if ( !k.second ) continue;
			auto key = KeyTools::VirtualKeyToEnum[ k.first ];
			g_pChroma->WriteKey ( key, Color::hsv2rgb ( key * 5 + i * 10, 1, 1 ) );
		}

		g_pChroma->Send ( );
	
		i++;

		std::this_thread::sleep_for ( std::chrono::milliseconds ( 10 ) );
	}
	
	KillThreads = true;
	InputThread.join ( );

	g_pChroma->Close ( );

	return 0;
}