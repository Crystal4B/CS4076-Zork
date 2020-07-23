#include "charactercursedlistener.h"

#include "eventmanager.h"
#include "game.h"
#include "curseditem.h"

CharacterCursedListener::CharacterCursedListener(Game *game)
{
    this->game = game;
}

void CharacterCursedListener::run(void *args)
{
	if (!game->is_over())
	{
		CursedItem *item = (CursedItem *) args;

		int newHP = game->getPlayer().getHealth() - item->getDamage();
		game->getPlayer().setHealth(newHP);
	}
}
