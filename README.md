ԭ�������ص�ַ: https://gitee.com/ldcsaa/VC-Logger.git

��ע��VC-Logger v2.0.3 ���� vc-common-src-2.3.2 �еĻ����������롣��ˣ����� VC-Logger v2.0.3 ʱ��Ҫͬʱ���� vc-common-src-2.2.2��

/******************************************************************************
Module:  VC-Logger

Purpose: ��¼������־��
		1. ����־��Ϣ�����ָ���ļ�
		2. ���� GUI ���򣬿��԰���־��Ϣ���͵�ָ������
		3. ����ConsoleӦ�ó��򣬿��԰���־��Ϣ������׼��� (std::cout)

Desc:
		1�����ܣ�
		--------------------------------------------------------------------------------------
		a) ����־��Ϣ�����ָ���ļ�
		b) ÿ������һ����־�ļ�
		c) ���� GUI ���򣬿��԰���־��Ϣ���͵�ָ������
		d) ����ConsoleӦ�ó��򣬿��԰���־��Ϣ������׼��� (std::cout)
		e) ֧�� MBCS / UNICODE��Console / GUI��win32 / x64 ����
		f) ֧�ֶ�̬���غ;�̬������־��� DLL
		g) ֧�� DEBUG/TRACE/INFO/WARN/ERROR/FATAL �ȶ����־����
		
		2�������ԣ�
		--------------------------------------------------------------------------------------
		a) �򵥴������������κγ�������
		b) ʹ�ýӿڼ򵥣����踴�ӵ����û����ù���
		c) �ṩ CStaticLogger �� CDynamicLogger ��װ�����ھ�̬��̬�����Լ�������־������û������ע����ϸ��
		d) �������Ҫ��¼�����־�ļ�ֻ��Ϊÿ����־�ļ�������Ӧ�� CStaticLogger �� CDynamicLogger ����
		e) ֻ����� Log()/Debug()/Trace()/Info()/Warn()/Error()/Fatal() �ȷ�����¼��־
		f) ��־��¼����֧�ֿɱ����
		g) ��־�����ʽ��<ʱ��> <�߳�ID> <��־����> <��־����>
		
		3�����ܣ�
		--------------------------------------------------------------------------------------
		a) ֧�ֶ��߳�ͬʱ����д��־����
		b) ʹ�õ����߳��ں�̨д��־����Ӱ�칤���̵߳�����ִ��
		c) ����������ʽ������¼��־

Usage:
		����һ������̬���� Logger DLL��
		--------------------------------------------------------------------------------------
		0. Ӧ�ó������ StaticLogger.h ͷ�ļ�
		1. ���� CStaticLogger ����ͨ��Ϊȫ�ֶ���
		2. ���� CStaticLogger->Init(...) ��ʼ����־���
		3. ʹ�� CStaticLogger->Log()/Debug()/Trace()/Info()/Warn()/Error()/Fatal() �ȷ���д��־
		4. ���� CStaticLogger->UnInit(...) ������־�����CStaticLogger ��������ʱҲ���Զ�������־�����

		������������̬���� Logger DLL��
		--------------------------------------------------------------------------------------
		0. Ӧ�ó������ DynamicLogger.h ͷ�ļ�
		1. ���� CDynamicLogger ����ͨ��Ϊȫ�ֶ���
		2. ���� CDynamicLogger->Init(...) ��ʼ����־���
		3. ʹ�� CDynamicLogger->Log()/Debug()/Trace()/Info()/Warn()/Error()/Fatal() �ȷ���д��־
		4. ���� CDynamicLogger->UnInit(...) ������־�����CDynamicLogger ��������ʱҲ���Զ�������־�����

		����������ֱ���õ����������� Logger DLL��
		--------------------------------------------------------------------------------------
		0. Ӧ�ó������ Logger.h ͷ�ļ�
		1. �ֹ����� ILoger_Create() �� ILoger_Create() ������������������ ILogger ���� 
		��ע������Ƕ�̬���أ����ֹ����� ::LoadLibrary()/::FreeLibrary() ϵ�� API �������غ�ж�� Logger DLL��
		
		[
			***** ����ϣ��ͨ�����ڽ�����־��Ϣ�� GUI ���� *****

			A. ��־�����ʼ���ɹ������ SetGUIWindow(HWND) ��������־�Ĵ���
			B. ��������Ӧ���� LOG_MESSAGE ��Ϣ
			C. ������ LOG_MESSAGE ��Ϣ�󣬵��� ILogger::FreeLogMsg() ���ٽ��յ��� TLogMsg 
		]

Environment:
		1. Windows 2000 or later (_WIN32_WINNT >= 0x0500)
		2. VC++ 2010 or later

Release:
		1. Logger_C.dll		- Console/MBCS/Release
		2. Logger_CD.dll	- Console/MBCS/Debug
		3. Logger_CU.dll	- Console/Unicode/Release
		4. Logger_CUD.dll	- Console/Unicode/Debug
		5. Logger.dll		- GUI/MBCS/Release
		6. Logger_D.dll		- GUI/MBCS/Debug
		7. Logger_U.dll		- GUI/Unicode/Release
		8. Logger_UD.dll	- GUI/Unicode/Debug

Examples:
		1. TestGUILogger		- GUI ����Գ���		����̬���أ�
		2. TestDynamicLogger	- GUI ����Գ���		����̬���أ�
		3. TestConsoleLogger	- Console ����Գ���	����̬���أ�

******************************************************************************/