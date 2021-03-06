/*
** instructions_tab.c for qdf in /home/tovazm/rendu/corewar/VM
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Tue Apr  8 20:16:41 2014 chalie_a
** Last update Sun Apr 13 22:23:04 2014 chalie_a
*/

#include "corewar.h"
#include "vm.h"
#include "my.h"

static void	pure_copy(const char *src, char *dest,
			  const unsigned int size)
{
  int		i;

  i = -1;
  while (++i < size)
    dest[i] = src[i];
}

static int	champ_dup(t_champ *champ, t_champ *fork)
{
  fork->code = my_calloc(champ->header->prog_size + 4, sizeof(char));
  if (!fork)
    return (FAILURE);
  fork->champ_nbr = champ->champ_nbr;
  fork->carry = 0;
  my_memset(fork->reg, 0, 16);
  my_memset(fork->cmd->args_type, 0, 4);
  my_memset(fork->cmd->args_value, 0, 4);
  fork->reg[0] = champ->reg[0];
  fork->header->prog_size = champ->header->prog_size;
  fork->cycle_to_die = champ->cycle_to_die;
  fork->cycle =  champ->cycle;
  fork->line->filename = champ->line->filename;
  fork->header->prog_size = champ->header->prog_size;
  return (SUCCESS);
}

int			ins_fork(t_champ *champ, t_arena *arena)
{
   t_champ		*fork;
   int			op1;
   int			mod;
   int			i;

   i = -1;
   mod = champ->cmd->op == 15 ? arena->mem_size : IDX_MOD;
   op1 = champ->cmd->args_value[0];
   if (!(fork = init_champ()))
     return (FAILURE);
   champ_dup(champ, fork);
   champ->pc = op1 % arena->mem_size;
   while (++i < arena->nbr_live)
     champ = champ->next;
   fork->prev = champ->prev;
   fork->next = champ;
   champ->prev->next = fork;
   champ->prev = fork;
   champ->carry = (mod != IDX_MOD && op1 ? 1 : 0);
   return (SUCCESS);
}
