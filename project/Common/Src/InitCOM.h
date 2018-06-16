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

#ifndef _WIN32_WINNT			// ����ʹ�� Windows NT 4 ����߰汾���ض����ܡ�
#define _WIN32_WINNT 0x0500		//Ϊ Windows98 �� Windows 2000 �����°汾�ı�Ϊ�ʵ���ֵ��
#endif	

#ifndef _AFX
	#include <windows.h>
	#include <objbase.h>
#endif

class CInitCOM
{
public:
	CInitCOM(DWORD dwCoInit = COINIT_APARTMENTTHREADED, void * pvReserved = nullptr)
		{::CoInitializeEx(pvReserved, dwCoInit);}
	~CInitCOM()
		{::CoUninitialize();}
};
