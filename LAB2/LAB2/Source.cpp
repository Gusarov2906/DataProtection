#include <iostream>
#include <Windows.h> 
char alphapet[45] = {"ÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÚÛÜİŞß 0123456789"};

unsigned int getNumFromAplpabet(char sym)
{
	for (int i = 0; i < 44; i++)
	{
		if (sym == alphapet[i])
			return i;
	}
	return 0;
}
unsigned long long mod(unsigned int number, unsigned long long power, unsigned long long n)
{
	unsigned long long res = 1;
	while (power)
	{
		if (power % 2)
			res = (1ull * res * number) % n;
		number = (1ull * number * number) % n;
		power /= 2;
	}
	return res;
}
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int p, q;
	std::cout << "Write p: ";
	std::cin >> p;

	std::cout << "Write q: ";
	std::cin >> q;

	int n = p * q;
	int fi = (p - 1) * (q - 1);
	std::cout << " n = " << n << " fi = " << fi << std::endl;
	int e = 0;

	while (e <= 0 || e > n)
	{
		std::cout << "Write e(0 < e < " << n << "): ";
		std::cin >> e;
	}

	//int e = rand() % n;
	int remain = -1;
	int d = 0;
	int k = -1;

	while (remain != 0)
	{
		k++;
		remain = (k * fi + 1) % 5;
	}

	d = (k * fi + 1) / 5;
	std::cout << " d = " << d << " k = " << k << std::endl;
	int* encode = new int[45];

	for (int i = 0; i < 45; i++)
	{
		encode[i] = (int)pow(i+1, e) % n;
		//std::cout << encode[i] << " ";
	}

	std::cout << std::endl;
	std::cout  << "Write word: ";
	std::string str;
	std::cin >> str;

	int* encodeRes = new int[str.length()];
	int size = str.length();

	std::cout << "Key = (" << d <<"," << n <<")" << std::endl;
	std::cout << "Encode(array of Ci): " << std::endl;
	for (int i = 0; i < size; i++)
	{
		memcpy_s(&encodeRes[i],4,&encode[getNumFromAplpabet(str[i])],4);
		std::cout << *(encodeRes+i) << " ";
	}

	std::string decodeRes;
	uint64_t tmp;

	std::cout << std::endl << "Decode(array of Ti): " <<std::endl;

	for (int i = 0; i < size; i++)
	{
		tmp = mod(*(encodeRes+i), d, n) - 1;
		decodeRes.push_back(alphapet[tmp]);
		std::cout << mod(*(encodeRes+i), d, n) << " ";
	}
	std::cout << std::endl;

	std::cout << "Result:" << std::endl << decodeRes << std::endl;
	delete[] encodeRes;
}