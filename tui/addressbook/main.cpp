#include "addressbook.h"

int main(int argc, char **argv)
{
	if (2 != argc)
	{
		cerr << "Usage: " << argv[0] << " file_name\n";
		return 1;
	}

	AddressBook ab;

	if (ab.ReadFromFile(argv[1]))
	{
		cerr << "Can't open input file: " << argv[1] << '\n';
		return 2;
	}

	ab.Run();

	return 0;
}