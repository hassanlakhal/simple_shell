#include "main.h"

/**
 * readHistory - Reads a history file into a linked list.
 *
 * @info: Pointer to the parameter structure.
 *
 * Return: Depends on the condition.
 */

int readHistory(info_t *info)
{
	int i, last = 0, line_count = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_histo(info);

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			fill_histo(info, buf + last, line_count++);
			last = i + 1;
		}
	if (last != i)
		fill_histo(info, buf + last, line_count++);
	free(buf);
	info->hist_count = line_count;
	while (info->hist_count-- >= HIST_MAX)
		deleteNode(&(info->history), 0);
	renumberHistory(info);
	return (info->hist_count);
}
