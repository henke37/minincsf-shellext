#include "guids.h"
#include <propkey.h>
#include <string>
#include "extCl.h"
#include <Propvarutil.h>
#include "pkeys.h"
#include "string2int_t.h"


#define DURATIONSCALE 10000

HRESULT PropExtCL::storeTagAsProp(const std::string &tagName, const std::string &tagValue) {

	if(tagName=="title") {
		return SetValue(PKEY_Title,tagValue);
	} else if(tagName=="artist") {
		return SetValue(PKEY_Music_Artist,tagValue);
	} else if(tagName=="game") {
		return SetValue(PKEY_Software_ProductName,tagValue);
	} else if(tagName=="genre") {
		return SetValue(PKEY_Music_Genre,tagValue);
	} else if(tagName=="comment") {
		return SetValue(PKEY_Comment,tagValue);
	} else if(tagName=="copyright") {
		return SetValue(PKEY_Copyright,tagValue);
	} else if(tagName=="length") {
		return SetValue(PKEY_Media_Duration,str2uint64_t(tagValue)*DURATIONSCALE);
	} else if(tagName=="year") {
		return SetValue(PKEY_Media_Year,str2uint32_t(tagValue));
	} else if(tagName=="track") {
		return SetValue(PKEY_Music_TrackNumber,str2uint32_t(tagValue));
	}

	return E_FAIL;

}



HRESULT PropExtCL::storePropAsTag(REFPROPERTYKEY key) {
#define StringProp(pkey, tag) if(key==pkey) { \
	return SetTagFromStringProp(pkey, tag); \
	}

#define IntProp(pkey, tag, scale) if(key==pkey) { \
	return SetTagFromIntProp(pkey, tag, scale); \
	}

	StringProp(PKEY_Title,"title")
	else StringProp(PKEY_Music_Artist,"artist")
	else StringProp(PKEY_Software_ProductName,"game")
	else StringProp(PKEY_Music_Genre,"genre")
	else StringProp(PKEY_Comment,"comment")
	else StringProp(PKEY_Copyright,"copyright")
	else StringProp(PKEY_PSF_Mini_Library,"_lib") //TODO: deal with multiple values
	else IntProp(PKEY_Media_Duration,"length",DURATIONSCALE)
	else IntProp(PKEY_Media_Year,"year",1)

#undef StringProp
#undef IntProp

	return E_FAIL;
}