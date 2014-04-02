/*
** get_params.c for coreware in /home/tovazm/rendu/corewar/ASM
** 
** Made by 
** Login   <abel@chalier.me>
** 
** Started on  Wed Mar 19 02:14:38 2014 
** Last update Fri Mar 28 12:04:04 2014 chalie_a
*/

#include "corewar.h"
#include "op.h"
#include "x_error.h"

int	is_num(char *str)
{
  int	i;

  i = -1;
  if (str[i + 1] == '-')
    i++;
  while (str[++i])
    if (str[i] < '0' || str[i] > '9')
      return (FALSE);
  return (TRUE);
}

int     my_atoi(char *str)
{
  int   res;

  if (str[0] == ':')
    return (42);
  if (str == NULL)
    return (0);
  if (*str == '-')
    return (-my_atoi(str + 1));
  if (*str == '+')
    return (my_atoi(str + 1));
  res = 0;
  while (*str)
    {
      res = res * 10;
      res = res + *str - '0';
      str = str + 1;
    }
  return (res);
}

int		get_label_value(t_list *list, int origin, int target)
{
  int		i;
  int		final_size;
  t_list	*tmp;

  i = -1;
  final_size = 0;
  tmp = list->next;
  while (++i < origin)
    tmp = tmp->next;
  if (origin < target)
    while (++i < target)
      {
	final_size += tmp->size;
	tmp = tmp->next;
      }
  else
    return (-get_label_value(list, target - 1, origin + 1));
  return (final_size);
}

int		get_every_label_value(t_list *list)
{
  t_list	*tmp;
  int		i;
  int		j;

  i = 0;
  tmp = list->next;
  while (tmp != list)
    {
      j = -1;
      while (++j < op_tab[tmp->num - 1].nbr_args)
	{
	  if (tmp->param[j].l_flag)
	      tmp->param[j].param = get_label_value(list, i, tmp->param[j].param + 1);
	}
	  ++i;
      tmp = tmp->next;
    }
  return (SUCCESS);
}

int		get_real_size(int type, int num)
{
  if (type == T_DIR)
    if (num == OP_ZJMP || num == OP_LDI || num == OP_STI
	|| num == OP_LLDI || num == OP_FORK
	|| num == OP_LFORK || num == OP_AFF)
      return (IND_SIZE);
  if (type == T_REG)
    return (REG_SIZE);
  if (type == T_DIR)
    return (DIR_SIZE);
  if (type == T_IND)
    return (IND_SIZE);
  if (type == T_LAB)
    return (IND_SIZE);
  return (0);
}

int		get_coding_size(t_list *list, int *w_size)
{
  int		i;

  i = -1;
  list->size = (list->coding_byte == 0 ? 1 : 2);
  while (++i < MAX_ARGS_NUMBER)
    {
      *w_size = get_real_size(list->param[i].type, list->num);
      list->size += *w_size;
    }
  return (SUCCESS);
}
char		*get_l_flag(char *str, int type)
{
  if ((type == T_DIR || type == T_REG) && str[1] == ':')
    return (strdup(&str[1]));
  if (type == T_LAB)
    return (strdup(str));
  return (NULL); 
}


int		get_param_info(t_list *list, t_args *args, int i)
{
  list->param[i].type = get_type(args->args[i + 1], list->num);
  list->param[i].param = get_value(args->args[i + 1], list->param[i].type);
  list->param[i].l_flag = get_l_flag(args->args[i + 1], list->param[i].type);
  return (SUCCESS);
}

int		get_value(char *str, int type)
{ 
 if (type == T_IND || type == T_LAB)
    return (my_atoi(str));
  else
    return (my_atoi(&str[1]));
}

int		get_type(char *str, int num)
{
  if (!str)
    exit(FAILURE);
  if (str[0] == 'r')
    return (T_REG);
  else if (str[0] == '%')
    return (T_DIR); 
  else if (str[0] == ':')
      return (T_LAB);
  else if (is_num(str) == TRUE)
    return (T_IND);
  else
    return (X_ERROR(str, INV_PAR));
}
