#include "main.h"

/**
 * inputBuf - Buffers chained commands.
 *
 * @info: Pointer to the parameter struct.
 * @buf: Address of the buffer.
 * @len: Address of the len variable.
 *
 * Return: The number of bytes read.
 */

ssize_t inputBuf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USEgetLine
		r = getLine(buf, &len_p, stdin);
#else
		r = getLine(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->line_count_flag = 1;
			removeComments(*buf);
			fill_histo(info, *buf, info->hist_count++);
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}
/**
 * readBuf - Reads a buffer.
 *
 * @info: Pointer to the parameter struct.
 * @buf: Buffer.
 * @i: Size.
 *
 * Return: The number of bytes read.
 */

ssize_t readBuf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, readBuf_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * getLine - Gets the next line of input from STDIN.
 *
 * @info: Pointer to the parameter struct.
 * @ptr: Address of the pointer to the buffer, preallocated or NULL.
 * @len: Size of preallocated ptr buffer if not NULL.
 *
 * Return: The number of bytes read.
 */

int getLine(info_t *info, char **ptr, size_t *len)
{
	static char buf[readBuf_SIZE];
	static size_t i, len1;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && len)
		s = *len;
	if (i == len1)
		i = len1 = 0;

	r = readBuf(info, buf, &len1);
	if (r == -1 || (r == 0 && *len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len1;
	new_p = reallocateMemory(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (len)
		*len = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - Blocks Ctrl-C.
 *
 * @sig_num: The signal number.
 *
 * Return: void.
 */

void sigintHandler(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("sh ->");
	_putchar(BUF_FLUSH);
}

/**
 * clearInfo - Initializes info_t struct.
 *
 * @info: Struct address.
 */

void clearInfo(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}
