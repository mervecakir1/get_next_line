/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mervcaki <mervcaki@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:36:03 by mervcaki          #+#    #+#             */
/*   Updated: 2024/12/13 16:36:03 by mervcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_to_buffer(char *text, int fd)
{
	char	*buffer;
	ssize_t	bytes_read;

	bytes_read = 1;
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (!ft_strchr(text, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(text);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		text = ft_strjoin(text, buffer);
	}
	free(buffer);
	return (text);
}

char	*extract_line(char *text)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!text[0])
		return (NULL);
	while (text[i] != '\0' && text[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	while (text[j] != '\0' && text[j] != '\n')
	{
		line[j] = text[j];
		j++;
	}
	if (text[j] == '\n')
	{
		line[j] = text[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*keep_and_save_text(char *text)
{
	char	*remainder;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (text[i] != '\0' && text[i] != '\n')
		i++;
	if (text[i] == '\0')
	{
		free(text);
		return (NULL);
	}
	remainder = malloc(sizeof(char) * (ft_strlen(text) - i));
	if (!remainder)
		return (NULL);
	i++;
	while (text[i] != '\0')
		remainder[j++] = text[i++];
	remainder[j] = '\0';
	free(text);
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char	*text;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	text = read_to_buffer(text, fd);
	if (!text)
		return (NULL);
	line = extract_line(text);
	text = keep_and_save_text(text);
	return (line);
}
