/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 11:52:55 by athonda           #+#    #+#             */
/*   Updated: 2024/08/16 11:54:08 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_count_words(char const *str, char delimiter)
{
	size_t	i;
	size_t	nbr_words;

	nbr_words = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] == delimiter && str[i] != '\0')
			i++;
		if (str[i] != delimiter && str[i] != '\0')
		{
			nbr_words++;
			while (str[i] != delimiter && str[i] != '\0')
				i++;
		}
	}
	return (nbr_words);
}

void	ft_cleanmem(unsigned int i, char **word)
{
	while (i > 0)
	{
		free(word[i - 1]);
		i--;
	}
}

int	ft_setstr(char const *s, char c, size_t nbr_words, char **word)
{
	size_t		i;
	size_t		j;
	size_t		word_len;
	const char	*word_head;

	i = -1;
	j = 0;
	while (++i < nbr_words)
	{
		while (s[j] == c && s[j] != '\0')
			j++;
		word_head = &s[j];
		if (ft_strchr(word_head, c) != NULL)
			word_len = ft_strchr(word_head, c) - word_head;
		else
			word_len = ft_strlen(word_head);
		word[i] = ft_substr(s, j, word_len);
		if (!(word[i]))
		{
			ft_cleanmem(i, word);
			return (1);
		}
		j = j + word_len;
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char			**word;
	size_t			nbr_words;

	if (s == NULL)
		return (NULL);
	nbr_words = ft_count_words(s, c);
	word = (char **)malloc(sizeof (char *) * (nbr_words + 1));
	if (word == NULL)
		return (NULL);
	if (ft_setstr(s, c, nbr_words, word))
	{
		free(word);
		return (NULL);
	}
	word[nbr_words] = NULL;
	return (word);
}
