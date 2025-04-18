/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_capture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:25:00 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/06 16:41:01 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/controller.h"

int	capture_output(char *buffer, int size, const char *format, ...)
{
	va_list	args;
	FILE	*fp;
	int		original_stdout;
	int		ret;
	int		bytes_read;

	va_start(args, format);
	fp = tmpfile();
	if (!fp)
	{
		perror("Failed to create temporary file");
		va_end(args);
		return (-1);
	}
	original_stdout = dup(1);
	if (dup2(fileno(fp), 1) == -1)
	{
		perror("Failed to redirect stdout");
		fclose(fp);
		va_end(args);
		return (-1);
	}
	ret = vprintf(format, args);
	fflush(stdout);
	dup2(original_stdout, 1);
	close(original_stdout);
	fseek(fp, 0, SEEK_SET);
	bytes_read = fread(buffer, 1, size - 1, fp);
	buffer[bytes_read] = '\0';
	fclose(fp);
	va_end(args);
	return (ret);
}

void	capture_formatted_output(char *actual, int *actual_ret,
		const char *format, va_list args)
{
	FILE	*fp;
	int		original_stdout;
	int		bytes_read;

	fp = tmpfile();
	if (!fp)
	{
		perror("Failed to create temporary file");
		return ;
	}
	original_stdout = dup(1);
	if (dup2(fileno(fp), 1) == -1)
	{
		perror("Failed to redirect stdout");
		fclose(fp);
		return ;
	}
	*actual_ret = vprintf(format, args);
	fflush(stdout);
	dup2(original_stdout, 1);
	close(original_stdout);
	fseek(fp, 0, SEEK_SET);
	bytes_read = fread(actual, 1, BUFFER_SIZE - 1, fp);
	actual[bytes_read] = '\0';
	fclose(fp);
}
