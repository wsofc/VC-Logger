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
 
#pragma once

#include <Iphlpapi.h>

#include "GeneralHelper.h"

#define INVALID_IP_ADDRESS		_T("0.0.0.0")

enum EnAdapterType
{
	//AT_UNKNOWN	= 0,
	AT_OTHER		= MIB_IF_TYPE_OTHER,
	AT_ETHERNET		= MIB_IF_TYPE_ETHERNET,
	AT_TOKENRING	= MIB_IF_TYPE_TOKENRING,
	AT_FDDI			= MIB_IF_TYPE_FDDI,
	AT_PP			= MIB_IF_TYPE_PPP,
	AT_LOOPBACK		= MIB_IF_TYPE_LOOPBACK,
	AT_SLIP			= MIB_IF_TYPE_SLIP,
};

struct TAdapterInfo
{
	CString	m_strAdapterName;
	CString	m_strCurrentIP;
	DWORD	m_dwContext;

	static const DWORD INVALID_CONTEXT	= 0xFFFFFFFF;

	TAdapterInfo(LPCTSTR lpszAdapterName = NULL, LPCTSTR lpszCurrentAddress = NULL, DWORD dwContext = INVALID_CONTEXT)
	{
		Reset(lpszAdapterName, lpszCurrentAddress, dwContext);
	}

	void Reset(LPCTSTR lpszAdapterName = NULL, LPCTSTR lpszCurrentAddress = NULL, DWORD dwContext = INVALID_CONTEXT)
	{
		m_strAdapterName	= lpszAdapterName;
		m_strCurrentIP		= lpszCurrentAddress;
		m_dwContext			= dwContext;
	}
};

typedef vector<TAdapterInfo*>				AdapterInfos;
typedef AdapterInfos::iterator				AdapterInfosI;
typedef AdapterInfos::const_iterator		AdapterInfosCI;

typedef TPtrSet<AdapterInfos>				AdapterInfoList;
typedef AdapterInfoList::iterator			AdapterInfoListListI;
typedef AdapterInfoList::const_iterator		AdapterInfoListListCI;

typedef TPtrMap<map<CString, TAdapterInfo*, uncase_string_comp_func>>	AdapterInfoMap;
typedef AdapterInfoMap::iterator			AdapterInfoMapMapI;
typedef AdapterInfoMap::const_iterator		AdapterInfoMapMapCI;


BOOL GetFirstAdapter(TAdapterInfo& adapter, EnAdapterType type);
BOOL GetFirstEthernetAdapter(TAdapterInfo& adapter);

int GetAdapterIndex(LPCWSTR lpszAdapter);
BOOL GetAdapterCurrentIP(LPCWSTR lpszAdapter, DWORD& dwContext, CString& strIP);
