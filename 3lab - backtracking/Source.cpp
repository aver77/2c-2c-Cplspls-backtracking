#include <iostream>
#include <fstream>
#include <string>
#include <utility>

using namespace std;

bool Try(int index, int length);

const int n = 10;
int max_length = 0, n2 = 0;

pair<string, bool> basic_array[n];
string now_array[n];
string final_array[n];

void fillarr(ifstream &fin)
{
	string word;
	int i = 0;
	while (!fin.eof() && i < n)
	{
		fin >> word;
		basic_array[i].first = word;
		basic_array[i].second = false;
		i++;
	}
	fin.clear();
	fin.seekg(0);
}

void print(pair<string, bool> arr[])
{
	for (int i = 0; i < n; i++)
	{
		cout << arr[i].first << " ";
	}
	cout << endl;
}

void print()
{
	cout << "Максимальная длина кольца:" << max_length << endl;
	cout << "Полученное максимальное кольцо:" << endl;
	for (int i = 0; i < n2; i++)
	{
		cout << final_array[i] << " ";
	}
}

int main()
{
	setlocale(LC_ALL, "Ru");

	ifstream fin("Text.txt");

	if (fin.is_open())
	{
		cout << "Файл открыт\n";
		fillarr(fin);
		print(basic_array);
		int index = 0, length = 0;
		if (!Try(index,length))
			cout << "Кольцо не найдено\n";
		else
			print();
	}
	else
		cout << "Ошибка открытия файла\n";

	fin.clear();
	cin.get();
	return 0;
}

bool Try(int index, int length)
{
	bool res = false;
	if (index == 0) //установка первого элемента
	{
		for (int i = 0; i < n; i++)
		{
			string w1 = basic_array[i].first;
			basic_array[i].second = true;
			now_array[index] = w1;
			length += w1.length();
			res = Try(index + 1, length) || res; //если хоть 1раз получим res=true (при построении кольца),то true вернем
			basic_array[i].second = false;
			length -= w1.length();
		}
	}
	else
	{
		for (int j = 0; j < n; j++)
		{
			//последовательно пытаемся подбирать подходящее, перебирая слова
			string w2 = basic_array[j].first, w1 = now_array[index - 1];
			if (w2[0] == w1[w1.length() - 1] && !basic_array[j].second) //&& еще не обходили это слово
			{
				length += w2.length();
				basic_array[j].second = true;
				now_array[index] = w2; //заполнение рабочего массива + запоминается последний подходящий элемент перед заходом на рекурсию (будет хранится в w1)
				res = Try(index + 1, length) || res;
				basic_array[j].second = false; //обнуление не подходящих параметров слов на выходе из рекурсии
				length -= w2.length();
			}
		}
		//рекурсивный поиск максимального кольца из рабочего массива (результатом заполним финальный массив)
		if (now_array[0][0] == now_array[index - 1][now_array[index - 1].length() - 1] && length > max_length)
		{
			res = true;
			max_length = length;
			n2 = index; //получаем размер финального массива (количество слов в максимальном кольце)
			for (int i = 0; i < index; i++)
			{
				final_array[i] = now_array[i];
			}
		}
	}
	return res;
}