#include "windows.h"
#include "mmdeviceapi.h"
#include "mmsystem.h"
#include "endpointvolume.h"
#include "Functiondiscoverykeys_devpkey.h"
#include "PolicyConfig.h"

#include "../AudioFunctions.h"

#include <locale>
#include <codecvt>

namespace {
	std::string WCharPtrToString(LPWSTR in) {
		return std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t>{}.to_bytes(in);
	}

	std::wstring Utf8StrToWString(const std::string& in) {
		return std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t>{}.from_bytes(in);
	}
}

std::map<std::string, std::string> GetAudioDeviceList()
{
	IMMDeviceEnumerator* de;
	CoCreateInstance(
		__uuidof(MMDeviceEnumerator), NULL,
		CLSCTX_ALL, __uuidof(IMMDeviceEnumerator),
		(void**)&de
	);

	IMMDeviceCollection* devices;
	de->EnumAudioEndpoints(EDataFlow::eRender, DEVICE_STATE_ACTIVE, &devices);

	UINT deviceCount;
	devices->GetCount(&deviceCount);
	std::map<std::string, std::string> out;
	
	for (UINT i = 0; i < deviceCount; ++i) {
		IMMDevice* device;
		devices->Item(i, &device);
		LPWSTR deviceID;
		device->GetId(&deviceID);
		IPropertyStore* properties;
		device->OpenPropertyStore(STGM_READ, &properties);
		PROPVARIANT name;
		properties->GetValue(PKEY_Device_FriendlyName, &name);
		out[WCharPtrToString(deviceID)] = WCharPtrToString(name.pwszVal);
		properties->Release();
		device->Release();
	}
	devices->Release();
	de->Release();
	return out;
}

std::string GetDefaultAudioDeviceID() {
	IMMDeviceEnumerator* de;
	CoCreateInstance(
		__uuidof(MMDeviceEnumerator), NULL,
		CLSCTX_ALL, __uuidof(IMMDeviceEnumerator),
		(void**)&de
	);
	IMMDevice* device;
	de->GetDefaultAudioEndpoint(EDataFlow::eRender, ERole::eConsole, &device);
	LPWSTR deviceID;
	device->GetId(&deviceID);
	const auto ret = WCharPtrToString(deviceID);
	device->Release();
	de->Release();
	return ret;
}

void SetDefaultAudioDeviceID(const std::string& desiredID) {
	if (desiredID == GetDefaultAudioDeviceID()) {
		return;
	}

	IPolicyConfigVista *pPolicyConfig;

	CoCreateInstance(__uuidof(CPolicyConfigVistaClient),
		NULL, CLSCTX_ALL, __uuidof(IPolicyConfigVista), (LPVOID *)&pPolicyConfig);
	pPolicyConfig->SetDefaultEndpoint(Utf8StrToWString(desiredID).c_str(), ERole::eConsole);
	pPolicyConfig->Release();
}