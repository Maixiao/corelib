// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� CPPIO_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// CPPIO_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef CPPIO_EXPORTS
#define CPPIO_API __declspec(dllexport)
#else
#define CPPIO_API __declspec(dllimport)
#endif

// �����Ǵ� cpp.io.dll ������
class CPPIO_API Ccppio {
public:
	Ccppio(void);
	// TODO:  �ڴ�������ķ�����
};

extern CPPIO_API int ncppio;

CPPIO_API int fncppio(void);
