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
#include "trayicon.h"

IMPLEMENT_DYNAMIC(CTrayIcon, CCmdTarget)

CTrayIcon::CTrayIcon(UINT uID)
{
	ASSERT(uID != 0);

	memset(&m_nid, 0 , sizeof(m_nid));
	m_nid.cbSize	= sizeof(m_nid);
	m_nid.uID		= uID;
}

CTrayIcon::~CTrayIcon()
{
	SetIcon((HICON)nullptr);
}

BOOL CTrayIcon::SetIcon(UINT iconID, LPCTSTR lpTip)
{ 
	HICON hicon = nullptr;

	if(iconID)
		hicon = AfxGetApp()->LoadIcon(iconID);

	return SetIcon(hicon, lpTip);
}


BOOL CTrayIcon::SetIcon(HICON hicon, LPCTSTR lpTip) 
{
	UINT msg;

	m_nid.uFlags = 0;

	if(hicon)
	{
		msg				= m_nid.hIcon ? NIM_MODIFY : NIM_ADD;
		m_nid.hIcon		= hicon;
		m_nid.uFlags   |= NIF_ICON;
	}
	else
	{
		if(m_nid.hIcon == nullptr)
			return TRUE;

		msg = NIM_DELETE;
	}

	if(lpTip)
	{
		_tcsncpy(m_nid.szTip, lpTip, sizeof(m_nid.szTip) / sizeof(TCHAR));
		m_nid.uFlags |= NIF_TIP;
	}

	if(m_nid.uCallbackMessage && m_nid.hWnd)
		m_nid.uFlags |= NIF_MESSAGE;

	BOOL bRet = Shell_NotifyIcon(msg, &m_nid);

	if(msg == NIM_DELETE || !bRet)
		m_nid.hIcon = nullptr;

	return bRet;
}

void CTrayIcon::SetNotificationWnd(CWnd* pNotifyWnd, UINT uCbMsg)
{
	ASSERT(pNotifyWnd == nullptr || ::IsWindow(pNotifyWnd->GetSafeHwnd()));
	m_nid.hWnd = pNotifyWnd->GetSafeHwnd();

	ASSERT(uCbMsg == 0 || uCbMsg >= WM_USER);
	m_nid.uCallbackMessage = uCbMsg;
}

LRESULT CTrayIcon::OnDefaultTrayNotification(WPARAM wID, LPARAM lEvent)
{
	if(wID!=m_nid.uID || (lEvent!=WM_RBUTTONUP && lEvent!=WM_LBUTTONDBLCLK))
		return 0;

	CMenu menu;

	if(!menu.LoadMenu(m_nid.uID))
		return 0;

	CMenu* pSubMenu = menu.GetSubMenu(0);

	if (!pSubMenu) 
		return 0;

	if(lEvent == WM_RBUTTONUP)
	{
		CPoint mouse;
		::GetCursorPos(&mouse);
		::TrackPopupMenu(pSubMenu->m_hMenu, 0, mouse.x, mouse.y, 0, m_nid.hWnd, nullptr);
	}
	else
		::SendMessage(m_nid.hWnd, WM_COMMAND, pSubMenu->GetMenuItemID(0), 0);

	return 1;
}
