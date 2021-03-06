/*
** main.c for trul in /home/tovazm/rendu/corewar/VM
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Fri Mar 28 12:20:06 2014 chalie_a
** Last update Mon Apr 14 00:37:46 2014 chalie_a
*/

#include <stdlib.h>
#include "vm.h"

static t_champ		*init_root()
{
  t_champ		*init;

  if (!(init = malloc(sizeof(*init))))
    return (NULL);
  init->prev = init;
  init->next = init;
  return (init);
}

static t_settings	*init_sets()
{
  t_settings		*init;

  if (!(init = malloc(sizeof(t_settings))) == FAILURE)
    return (NULL);
  init->dump = -1;
  init->mem_size = MEM_SIZE;
  init->ctmo = -1;
  return (init);
}

static t_champ		*parse_commandline(char **cmd, t_settings *sets)
{
  t_champ		*champ;
  int			status;

  champ = init_root();
  while ((status = add_champs_in_list(champ, cmd, sets)) != SUCCESS)
    if (status == FAILURE)
      return (NULL);
    else
      if (fill_champs(champ->prev) == FAILURE)
	return (NULL);
  return (champ);
}

int			main(int ac, char **av)
{
  t_champ		*champ;
  t_arena		*arena;
  t_settings		*sets;

  if (!(sets = init_sets()))
    return (FAILURE);
  champ = parse_commandline(&av[1], sets);
  if (!champ)
    return (FAILURE);
  arena = init_arena(champ, sets->mem_size);
  if (arena == NULL)
    return (FAILURE);
  if (start_battle(champ, arena, sets) != DUMP)
    the_game_is_over(champ, arena, sets);
  return (SUCCESS);
}
