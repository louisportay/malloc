#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>//

void	*ft_malloc(size_t size)
{
	int ps = getpagesize();
	size_t i = size / ps;
	i = i * ps;
	if ((size % ps) > 0)
		i += ps;
	void *ptr = mmap(NULL, i, PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	return (ptr);//
}

int main(void)
{
	char *a = ft_malloc(128);
	memcpy(a, "it's a success", 15);
	printf("%s\n", a);
	munmap(a, getpagesize());
}
