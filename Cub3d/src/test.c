#include <stdlib.h>
#include <unistd.h>


#include <stdio.h>
#include <string.h>
int main(void)
{
	const char	*identifiers[8] = {"NO", "SO", "WE", "EA", "S ", "F ", "C ", NULL};
	int i = 0;

	while (identifiers[i])
	{
		write(1, identifiers[i++], 2);
	}
}