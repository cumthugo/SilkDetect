#include "License.h"
#include <Iphlpapi.h>

#include "md5.h"
#pragma comment(lib,"Iphlpapi.lib")

string GetLicenseCodeImpl()
{
	PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO();
	unsigned long stSize = sizeof(IP_ADAPTER_INFO);
	int nRel = GetAdaptersInfo(pIpAdapterInfo,&stSize);
	if (ERROR_BUFFER_OVERFLOW==nRel)
	{
		delete pIpAdapterInfo;
		pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];
		nRel=GetAdaptersInfo(pIpAdapterInfo,&stSize);    
	}
	if (ERROR_SUCCESS==nRel && pIpAdapterInfo)
	{
		MD5 md5;
		md5.update((void*)pIpAdapterInfo->Address,6);
		md5.update(md5.toString());
		return md5.toString();
	}
	else
		return string();
}

string GetLicenseCode()
{
	static string code = GetLicenseCodeImpl();
	return code;
}
