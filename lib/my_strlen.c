/*
** my_strlen.c for my_strlen in /home/dong_n/rendu/Piscine-C-Jour_04
** 
** Made by david$
** Login   <dong_n@epitech.net>
** 
** Started on  Thu Oct  3 16:04:01 2013 david$
** Last update Fri Oct  4 20:08:57 2013 david$
*/

int	my_strlen(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
      i = i + 1;
  return (i);
}
