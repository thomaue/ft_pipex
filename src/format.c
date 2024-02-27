/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:46:31 by tauer             #+#    #+#             */
/*   Updated: 2024/02/27 09:59:28 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*result;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	result = str;
	while (*s1)
		*str++ = *s1++;
	while (*s2)
		*str++ = *s2++;
	*str = '\0';
	return (result);
}

char	*path_maker(const char *path, const char *exec_name)
{
	if (!path || !exec_name)
		return (NULL);
	return (ft_strjoin(path, exec_name));
}

char	**ft_split(char *str, char *charset)
{
	char	**tab_split;

	if (!(str))
		return (NULL);
	tab_split = inoutput_split(str, charset);
	return (tab_split);
}

char	*clear_quote(char *arg)
{
	char	*ret;
	size_t	i;

	i = 0;
	ret = (char *)malloc(sizeof(char) * ft_strlen(arg) + 1);
	if (!ret)
		return (NULL);
	while (arg[i])
	{
		ret[i] = arg[i];
		i++;
	}
	ret[i] = '\0';
	// printf("[CLEAR QUOTE] : [%s]\n", ret);
	return (ret);
}
