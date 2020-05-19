#include <stdio.h>      /* printf */
#include <string.h>     /* strcat */
#include <stdlib.h>     /* strtol */

/*
**	specifier->flags |= ast1;		sets flag for asterisk1
**	specifier->flags &= ~ast1;		cancels that flag
**	specifier->flags & ast1			checks whether it is set
**	specifier->flags = 0			obviously unsets all of the flags (resets them to zero)
*/

enum				e_flag
{
	minus = (1 << 0),
	zero = (1 << 1),
	ast1 = (1 << 2),
	dot = (1 << 3),
	ast2 = (1 << 4),
};

typedef struct		s_spec
{
	uint8_t			flags;
	char			type;
	int				crop_size;
	int				padding_size;
}					t_spec;

int main(void)
{
	static t_spec	specifier;
	uint8_t			*flags;

	//specifier = (spec_t *)malloc(sizeof(spec_t));
	printf("crop is %d\n", specifier.crop_size);
	printf("width is %d\n", specifier.padding_size);
	printf("type is %d\n", specifier.type);
	printf("flags is %d\n", specifier.flags);
	flags = &(specifier.flags);
	printf("flag is %d\n", specifier.flags);
	*flags += (minus + zero);
	if (specifier.flags)
		printf("flag is %d\n", specifier.flags);
}

//int main(void)
//{
	//printf("%0*.10d\n", 5123124);
//}