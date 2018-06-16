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

class CTrayIcon : public CCmdTarget
{
protected:
	DECLARE_DYNAMIC(CTrayIcon)

public:
	NOTIFYICONDATA m_nid;

public:
	CTrayIcon(UINT uID);
	~CTrayIcon();

	BOOL SetIcon(UINT uID, LPCTSTR lpTip = nullptr);
	BOOL SetIcon(HICON hicon, LPCTSTR lpTip = nullptr);

	BOOL SetIcon(LPCTSTR lpResName, LPCTSTR lpTip)
	{
		return SetIcon(lpResName ? ::AfxGetApp()->LoadIcon(lpResName) : (HICON)nullptr, lpTip);
	}

	BOOL SetStandardIcon(LPCTSTR lpszIconName, LPCTSTR lpTip)
	{
		return SetIcon(::LoadIcon(nullptr, lpszIconName), lpTip);
	}

	void SetNotificationWnd(CWnd* pNotifyWnd, UINT uCbMsg);

	virtual LRESULT OnDefaultTrayNotification(WPARAM uID, LPARAM lEvent);
};

