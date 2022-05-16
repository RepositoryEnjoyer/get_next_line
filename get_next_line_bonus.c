/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaurici <cmaurici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 16:48:17 by cmaurici          #+#    #+#             */
/*   Updated: 2022/05/14 17:50:03 by cmaurici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*empty_store(char *store)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (store[i] && store[i] != '\n')
		i++;
	if (!store[i])
	{
		free(store);
		return (NULL);
	}
	str = malloc(sizeof(char) * (ft_strlen(store) - i + 1));
	if (!str)
	{
		free(str);
		return (NULL);
	}
	i++;
	while (store[i])
		str[j++] = store[i++];
	str[j] = '\0';
	free(store);
	return (str);
}

char	*trim_line(char *store)
{
	int		i;
	char	*rtn;

	i = 0;
	if (!store[i])
		return (NULL);
	while (store[i] && store[i] != '\n')
		i++;
	rtn = malloc(sizeof(char) * i + 2);
	if (!rtn)
		return (NULL);
	i = 0;
	while (store[i] && store[i] != '\n')
	{
		rtn[i] = store[i];
		i++;
	}
	if (store[i] == '\n')
	{
		rtn[i] = '\n';
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}

void	*free_all(char *store, char *tmp)
{
	free(tmp);
	free(store);
	return (NULL);
}

char	*read_line(int fd, char *store)
{
	char	*tmp;
	int		read_rslt;

	tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp)
		return (NULL);
	read_rslt = 1;
	while (read_rslt != 0 && !ft_strchr(store, '\n'))
	{
		read_rslt = read(fd, tmp, BUFFER_SIZE);
		if (read_rslt == -1)
			return (free_all(store, tmp));
		tmp[read_rslt] = '\0';
		if (!store)
		{
			store = malloc(sizeof(char) * 1);
			store[0] = '\0';
		}
		store = ft_strjoin(store, tmp);
	}
	free(tmp);
	return (store);
}

char	*get_next_line(int fd)
{
	static char	*store[4096];
	char		*rtn;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	store[fd] = read_line(fd, store[fd]);
	if (!store[fd])
		return (NULL);
	rtn = trim_line(store[fd]);
	store[fd] = empty_store(store[fd]);
	return (rtn);
}
