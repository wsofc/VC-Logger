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
#include "Service.h"
#include "GeneralHelper.h"

BOOL IsServiceExist(LPCTSTR pszServiceName)
{
	BOOL bExist = FALSE;
	SC_HANDLE scm = ::OpenSCManager(NULL, NULL, GENERIC_READ);
	if(scm)
	{
		SC_HANDLE sv = ::OpenService(scm, pszServiceName, GENERIC_READ);
		if(sv)
		{
			bExist = TRUE;
			::CloseServiceHandle(sv);
		}
		::CloseServiceHandle(scm);
	}

	return bExist;
}

BOOL GetServiceStatus(LPCTSTR pszServiceName, DWORD* pStatus)
{
	BOOL bIsOK = FALSE;
	SC_HANDLE scm = ::OpenSCManager(NULL, NULL, GENERIC_READ);
	if(scm)
	{
		SC_HANDLE sv = ::OpenService(scm, pszServiceName, GENERIC_READ);
		if(sv)
		{
			SERVICE_STATUS ss;
			bIsOK		= ::QueryServiceStatus(sv, &ss);
			*pStatus	= ss.dwCurrentState;
			::CloseServiceHandle(sv);
		}
		::CloseServiceHandle(scm);
	}

	return bIsOK;
}

BOOL GetServiceImagePath(LPCTSTR pszServiceName, CString& strImagePath)
{
	BOOL bIsOK = FALSE;
	strImagePath.Empty();
	SC_HANDLE scm = ::OpenSCManager(NULL, NULL, GENERIC_READ);
	if(scm)
	{
		SC_HANDLE sv = ::OpenService(scm, pszServiceName, GENERIC_READ);
		if(sv)
		{
			DWORD dwBytes;
			::QueryServiceConfig(sv, NULL, 0, &dwBytes);
			LPQUERY_SERVICE_CONFIG pConf = (LPQUERY_SERVICE_CONFIG) new BYTE[dwBytes];

			if(::QueryServiceConfig(sv, pConf, dwBytes, &dwBytes))
			{
				CString strCmd = pConf->lpBinaryPathName;
				strCmd.MakeLower();
				int iPos = strCmd.Find(_T(".exe"));
				if(iPos != -1)
				{
					strImagePath = pConf->lpBinaryPathName;
					strImagePath.GetBufferSetLength(iPos + 4);
					strImagePath.Trim(_T("\" "));

					bIsOK = TRUE;
				}
			}

			delete[] pConf;
			::CloseServiceHandle(sv);
		}
		::CloseServiceHandle(scm);
	}

	return bIsOK;
}

BOOL UnInstallService(LPCTSTR pszServiceName, LPCTSTR pszParam, DWORD dwWaitTime)
{
	BOOL	bIsOK = TRUE;

	CString strPath;
	if(GetServiceImagePath(pszServiceName, strPath))
	{
		TCHAR szcmd[MAX_PATH] = {0};
		_stprintf(szcmd,_T("%s %s"),strPath,pszParam);
	
		bIsOK = RunProcess(NULL, szcmd, TRUE, NULL, TRUE, dwWaitTime);
		if(bIsOK)
			bIsOK = !IsServiceExist(pszServiceName);
	}

	return bIsOK;
}
