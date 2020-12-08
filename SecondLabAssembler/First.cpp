#include <iostream>

using namespace std;
using byte = unsigned char;

int main() 
{
	setlocale(LC_ALL, "Russian");					// русский язык
	unsigned short int newMassive[24];			// экономим память

	int choice = 1;

	// пока не 0 продолжаем работу.
	while (choice != 0) {
		for (int i = 0; i < sizeof(newMassive) / sizeof(unsigned short int); i++) {
			newMassive[i] = rand() % 100;
			cout << newMassive[i];
			cout << " ";
		}

		unsigned short int  result = 0;
		// бит сбрасывает and 110111101b

		__asm
		{
			mov cx, 0							// счётчик
			xor dx, dx							// обнуление dx
			lea si, newMassive			// заносим массив в si

			cykle1 :							// цикл 1
			cmp cx, 24						// сравниваем cx с 24
				je ending						// если =, переходим в конец
				xor ax, ax						// обнуляем AX
				xor bx, bx						// обнуляем bx
				mov ax, [esi]				// ставим в ax элемент из массива
				mov bx, ax					// заносим в bx значение ax
				and ax, 00100010b		// если ax имеет 1 и 5 биты с 1.
				inc cx							// cx++
				cmp ax, 00100010b		// имеет ли ax 1 и 5 биты с 1?
				je odd							// если ax имеет 1 и 5 биты с 1
				add si, 2						// добавляем адрес массива +2
				jne cykle1					// если ax не имеет 1 и 5 биты с 1 возвр. к началу цикла 1.


				odd : add dx, 1				// dx++
				test bx, 1						// является ли число чётным
				jz evenas						// если чётн
				jnz noteven					// если нечётн


				noteven :						// нечётн
			and bx, 11011111b			// обнуляем 5-ый элемент
				jmp anyway					// прыгаем в энивей


				evenas :						// чётн
			and bx, 11111101b			// обнуляем 1-ый элемент
				jmp anyway					// прыгаем в энивей


				anyway :						// энивей
			mov[esi], bx						// заменяем элемент в массиве с адресом si значением bx
				add si, 2						// добавляем адрес массива +2
				jmp cykle1					// прыгаем к началу цикла 1.

				ending :						// конец программы
			mov result, dx					// заполняем result dx'ом, тем самым находим количество изм. элементов
		}

		// вывод элементов: 
		cout << "" << endl;
		for (int i = 0; i < sizeof(newMassive) / sizeof(unsigned short int); i++) {
			cout << newMassive[i];
			cout << " ";
		}
		cout << endl << "Количество элементов, удовлетворяющих условиям: " << result << endl;
		cout << "" << endl;

		// вывод пользователю
		cout << "Введите 0 для выхода" << endl;

		// 0 для выхода, остальное проходим далее
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