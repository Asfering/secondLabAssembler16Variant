#include <iostream>

using namespace std;
using byte = unsigned char;

int main() 
{
	setlocale(LC_ALL, "Russian");					// ������� ����
	unsigned short int newMassive[24];			// �������� ������

	int choice = 1;

	// ���� �� 0 ���������� ������.
	while (choice != 0) {
		for (int i = 0; i < sizeof(newMassive) / sizeof(unsigned short int); i++) {
			newMassive[i] = rand() % 100;
			cout << newMassive[i];
			cout << " ";
		}

		unsigned short int  result = 0;
		// ��� ���������� and 110111101b

		__asm
		{
			mov cx, 0							// �������
			xor dx, dx							// ��������� dx
			lea si, newMassive			// ������� ������ � si

			cykle1 :							// ���� 1
			cmp cx, 24						// ���������� cx � 24
				je ending						// ���� =, ��������� � �����
				xor ax, ax						// �������� AX
				xor bx, bx						// �������� bx
				mov ax, [esi]				// ������ � ax ������� �� �������
				mov bx, ax					// ������� � bx �������� ax
				and ax, 00100010b		// ���� ax ����� 1 � 5 ���� � 1.
				inc cx							// cx++
				cmp ax, 00100010b		// ����� �� ax 1 � 5 ���� � 1?
				je odd							// ���� ax ����� 1 � 5 ���� � 1
				add si, 2						// ��������� ����� ������� +2
				jne cykle1					// ���� ax �� ����� 1 � 5 ���� � 1 �����. � ������ ����� 1.


				odd : add dx, 1				// dx++
				test bx, 1						// �������� �� ����� ������
				jz evenas						// ���� ����
				jnz noteven					// ���� ������


				noteven :						// ������
			and bx, 11011111b			// �������� 5-�� �������
				jmp anyway					// ������� � ������


				evenas :						// ����
			and bx, 11111101b			// �������� 1-�� �������
				jmp anyway					// ������� � ������


				anyway :						// ������
			mov[esi], bx						// �������� ������� � ������� � ������� si ��������� bx
				add si, 2						// ��������� ����� ������� +2
				jmp cykle1					// ������� � ������ ����� 1.

				ending :						// ����� ���������
			mov result, dx					// ��������� result dx'��, ��� ����� ������� ���������� ���. ���������
		}

		// ����� ���������: 
		cout << "" << endl;
		for (int i = 0; i < sizeof(newMassive) / sizeof(unsigned short int); i++) {
			cout << newMassive[i];
			cout << " ";
		}
		cout << endl << "���������� ���������, ��������������� ��������: " << result << endl;
		cout << "" << endl;

		// ����� ������������
		cout << "������� 0 ��� ������" << endl;

		// 0 ��� ������, ��������� �������� �����
		while (!(cin >> choice) || (cin.peek() != '\n'))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Error!" << endl;
		}
		if (choice == 0) break;

	}
	system("Pause");
	return 0;
}