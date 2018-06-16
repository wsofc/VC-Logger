/*
 * Copyright: JessMA Open Source (ldcsaa@gmail.com)
 *
 * Version	: 2.3.21
 * Author	: Bruce Liang
 * Website	: http://www.jessma.org
 * Project	: https://github.com/ldcsaa
 * Blog		: http://www.cnblogs.com/ldcsaa
 * Wiki		: http://www.oschina.net/p/hp-socket
 * QQ Group	: 75375912, 44636872
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#include "stdafx.h"
#include "IPHelper.h"

#pragma comment(lib, "Iphlpapi.lib")

BOOL GetFirstAdapter(TAdapterInfo& adapter, EnAdapterType type)
{
	adapter.Reset();

	BOOL bOK					= FALSE;
	ULONG size					= 1024;
	PIP_ADAPTER_INFO pAdaptInfo	= (PIP_ADAPTER_INFO)malloc(size);

	while(!bOK)
	{
		DWORD result = ::GetAdaptersInfo(pAdaptInfo, &size);

		if(result == NO_ERROR)
		{
			bOK = TRUE;
			break;
		}

		if(result == ERROR_BUFFER_OVERFLOW)
			pAdaptInfo = (PIP_ADAPTER_INFO)realloc(pAdaptInfo, size);
		else
			break;
	}

	if(bOK)
	{
		PIP_ADAPTER_INFO pItem = pAdaptInfo;

		while(pItem)
		{
			if(pItem->Type == type)
			{
				adapter.m_strAdapterName	= CA2W(pItem->AdapterName);
				PIP_ADDR_STRING pCurIP		= pItem->CurrentIpAddress;

				if(pCurIP)
				{
					ASSERT(!pCurIP->Next);

					adapter.m_dwContext		= pCurIP->Context;
					adapter.m_strCurrentIP	= CA2T(pCurIP->IpAddress.String);
				}

				return TRUE;
			}

			pItem = pItem->Next;
		}
	}

	free(pAdaptInfo);

	return FALSE;
}

BOOL GetFirstEthernetAdapter(TAdapterInfo& adapter)
{
	return GetFirstAdapter(adapter, AT_ETHERNET);
}

int GetAdapterIndex(LPCWSTR lpszAdapter)
{
	int index = -1;

	::GetAdapterIndex((LPWSTR)lpszAdapter, (PULONG)&index);

	return index;
}

BOOL GetAdapterCurrentIP(LPCWSTR lpszAdapter, DWORD& dwContext, CString& strIP)
{
	strIP.Empty();
	dwContext					= 0xFFFFFFFF;

	BOOL bOK					= FALSE;
	ULONG size					= 1024;
	PIP_ADAPTER_INFO pAdaptInfo	= (PIP_ADAPTER_INFO)malloc(size);

	while(!bOK)
	{
		DWORD result = ::GetAdaptersInfo(pAdaptInfo, &size);

		if(result == NO_ERROR)
		{
			bOK = TRUE;
			break;
		}

		if(result == ERROR_BUFFER_OVERFLOW)
			pAdaptInfo = (PIP_ADAPTER_INFO)realloc(pAdaptInfo, size);
		else
			break;
	}

	if(bOK)
	{
		PIP_ADAPTER_INFO pItem = pAdaptInfo;

		while(pItem)
		{
			if(pItem->Type == MIB_IF_TYPE_ETHERNET)
			{
				if(_wcsicmp(lpszAdapter, CA2W(pItem->AdapterName)) == 0)
				{
					PIP_ADDR_STRING pCurIP = pItem->CurrentIpAddress;

					if(pCurIP)
					{
						ASSERT(!pCurIP->Next);

						dwContext	= pCurIP->Context;
						strIP		= CA2T(pCurIP->IpAddress.String);
					}

					break;
				}
			}

			pItem = pItem->Next;
		}
	}

	free(pAdaptInfo);

	return bOK;
}
