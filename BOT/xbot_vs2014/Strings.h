#include "stdafx.h"


static const std::string base64_chars = "HNO4klm6ij9n+J2hyf0gzA8uvwDEq3X1Q7ZKeFrWcVTts/MRGYbdxSo=ILaUpPBC5";
using namespace std;
const char* base64_decode(std::string const& encoded_string) {
	int in_len = encoded_string.size();
	int i = 0;
	int j = 0;
	int in_ = 0;
	unsigned char char_array_4[4], char_array_3[3];
	std::string ret;

	while (in_len--) {
		char_array_4[i++] = encoded_string[in_]; in_++;
		if (i == 4) {
			for (i = 0; i < 4; i++)
				char_array_4[i] = base64_chars.find(char_array_4[i]);

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); i++)
				ret += char_array_3[i];
			i = 0;
		}
	}

	if (i) {
		for (j = i; j < 4; j++)
			char_array_4[j] = 0;

		for (j = 0; j < 4; j++)
			char_array_4[j] = base64_chars.find(char_array_4[j]);

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
		char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

		for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
	}
	char* preresult = new char[ret.size()];
	short lastinx = ret.size();
	strcpy(preresult, ret.c_str());
	preresult[lastinx] = 0x00;
	const char* result = preresult;
	//MessageBoxA(NULL, preresult, ret.c_str(), MB_ICONWARNING | MB_OKCANCEL);
	return result;
}

struct str
{
	const char* Kernel32dll = base64_decode(base64_decode("+mPNveAbyu+twmFJ3oSwqG55"));	// --> "Kernel32.dll"
	const char* PowrProfdll = base64_decode(base64_decode("XrSyhulmgrjlE=wJ3oSwqG55"));	// --> "PowrProf.dll"
	const char* CallNtPowerInformation = base64_decode(base64_decode("X8PsqxAtg67aEAHP3=ATDeAb3SjYqF+=+oSmzeAfJgz5"));	// --> "CallNtPowerInformation"
	const char* GetSystemInfo = base64_decode(base64_decode("wrPNX6cPfrydEzkR+47+qeA6Jgz5"));	// --> "GetSystemInfo"
}STRINGS,*PSTRINGS;