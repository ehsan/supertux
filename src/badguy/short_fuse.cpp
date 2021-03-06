//  SuperTux
//  Copyright (C) 2006 Matthias Braun <matze@braunis.de>
//  Copyright (C) 2010 Florian Forster <supertux at octo.it>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "audio/sound_manager.hpp"
#include "badguy/bomb.hpp"
#include "badguy/short_fuse.hpp"
#include "object/explosion.hpp"
#include "object/player.hpp"
#include "sprite/sprite.hpp"
#include "sprite/sprite_manager.hpp"
#include "supertux/object_factory.hpp"
#include "supertux/sector.hpp"
#include "util/reader.hpp"
#include "util/log.hpp"

#define EXPLOSION_FORCE 1000.0f

ShortFuse::ShortFuse(const Reader& reader) :
  WalkingBadguy(reader, "images/creatures/short_fuse/short_fuse.sprite", "left", "right")
{
  walk_speed = 100;
  max_drop_height = -1;

  //Prevent stutter when Tux jumps on Mr Bomb
  sound_manager->preload("sounds/explosion.wav");

  //Check if we need another sprite
  if( !reader.get( "sprite", sprite_name ) ){
    return;
  }
  if( sprite_name == "" ){
    sprite_name = "images/creatures/short_fuse/short_fuse.sprite";
    return;
  }
  //Replace sprite
  sprite = sprite_manager->create( sprite_name );
}

/* ShortFuse created by a dispenser always gets default sprite atm.*/
ShortFuse::ShortFuse(const Vector& pos, Direction d) :
  WalkingBadguy(pos, d, "images/creatures/short_fuse/short_fuse.sprite", "left", "right")
{
  walk_speed = 80;
  max_drop_height = 16;
  sound_manager->preload("sounds/explosion.wav");
}

void
ShortFuse::explode (void)
{
  if (!is_valid ())
    return;

  Explosion *explosion = new Explosion (get_bbox ().get_middle ());

  explosion->hurts (false);
  explosion->pushes (true);
  Sector::current()->add_object (explosion);

  remove_me ();
}

bool
ShortFuse::collision_squished(GameObject& obj)
{
  if (!is_valid ())
    return true;

  Player* player = dynamic_cast<Player*>(&obj);
  if(player)
    player->bounce(*this);

  explode ();

  return true;
}

HitResponse
ShortFuse::collision_player (Player& player, const CollisionHit&)
{
  player.bounce (*this);
  explode ();
  return ABORT_MOVE;
}

void
ShortFuse::kill_fall (void)
{
  explode ();
  run_dead_script ();
}

/* vim: set sw=2 sts=2 et : */
/* EOF */
