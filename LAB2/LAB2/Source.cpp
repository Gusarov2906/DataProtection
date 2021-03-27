#include <iostream>
#include <Windows.h> 
#include <string>

char alphapet[45] = {"ÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÚÛÜİŞß 0123456789"};

unsigned int getNumFromAplpabet(char sym)
{
	for (int i = 0; i < 45; i++)
	{
		if (sym == alphapet[i])
			return i;
	}
	return 0;
}

bool isSimple(int n)
{
	for (int i = 2; i <= sqrt(n); i++)
	{
		if (n % i == 0)
			return false;
	}
	return true;
}

int isMatuallySimple(int x, int y)
{
	return y ? isMatuallySimple(y, x % y) : x;
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
	//setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	uint64_t p, q;
	std::cout << "Write (simple number) p: ";
	std::cin >> p;
	while (!isSimple(p))
	{
		std::cout << "Not a simple number, write again: ";
		std::cin >> p;
	}
	std::cout << "Write (simple number) q: ";
	std::cin >> q;
	while (!isSimple(q))
	{
		std::cout << "Not a simple number, write again: ";
		std::cin >> p;
	}

	uint64_t n = p * q;
	uint64_t fi = (p - 1) * (q - 1);
	std::cout << " n = " << n << " fi = " << fi << std::endl;
	uint64_t e = 0;

	while (e <= 0 || e > n)
	{
		std::cout << "Write e(0 < e < " << n << "): ";
		std::cin >> e;
	}
	while (!(isMatuallySimple(e, fi) == 1))
	{
		std::cout << "Not a matually simple numbers, write again e: ";
		std::cin >> e;
	}

	//int e = rand() % n;
	uint64_t remain = -1;
	uint64_t d = 0;
	uint64_t k = -1;
	uint64_t tmp1 = 0;
	while (remain != 0)
	{
		k++;
		remain = (k * fi + 1) % e;
		if (k == 0)
			tmp1 = remain;
		else if (tmp1 == remain)
		{
			std::cout << "(k * fi + 1) %" << e << "| never be 0";
			return 0;
		}
	}
	std::cout << std::endl;
	d = (k * fi + 1) / e;
	//d = 263; k = 21;
	std::cout << " d = " << d << " k = " << k << std::endl;
	uint64_t* encode = new uint64_t[45];

	for (int i = 0; i < 45; i++)
	{
		encode[i] = (int)mod(i + 1, e, n);
		//std::cout << encode[i] << " ";
	}

	std::cout << std::endl;
	std::cout << "Write word: ";
	std::string str;
	std::cin.ignore();
	std::getline(std::cin, str);
	std::cout << str.length();
	uint64_t* encodeRes = new uint64_t[str.length()];
	uint64_t size = str.length();

	std::cout << "Key = (" << e << "," << n << ")" << std::endl;
	std::cout << "Encode(array of Ci): " << std::endl;
	for (int i = 0; i < size; i++)
	{
		memcpy_s(&encodeRes[i], 8, &encode[getNumFromAplpabet(str[i])], 8);
		std::cout << *(encodeRes + i) << " ";
	}

	std::string decodeRes;
	uint64_t tmp;

	std::cout << std::endl << "Decode(array of Ti): " << std::endl;

	for (int i = 0; i < size; i++)
	{
		tmp = mod(*(encodeRes + i), d, n) - 1;
		decodeRes.push_back(alphapet[tmp]);
		std::cout << mod(*(encodeRes + i), d, n) << " ";
	}
	std::cout << std::endl;

	std::cout << "Result:" << std::endl << decodeRes << std::endl;
	delete[] encodeRes;
}