#!/bin/bash

FILES=(
    "basment.c"
    "stuff.c"
    "gfx.c"
    "map.c"
    "player.c"
    "drinking.c"
    "popup.c"
    "pause.c"
    "monster.c"
    "game.c"
    "weapon.c"
    "combat.c"
    "interact.c"
    "armor.c"
    "generate.c"
    "shops.c"
    "books.c"
    "decorate.c"
    "automap.c"
    "traps.c"
    "hiscore.c"
    "title.c"
    "conf.c"
    "doors.c"
    "water.c"
    "bridge.c"
    "hell.c"
)

if [ $# -ne 1 ]; then

  gcc \
      -Wall \
      -Wmissing-prototypes -Wmissing-declarations \
      -Wnested-externs \
      -std=c99 -ggdb \
      -lncurses \
      -DFORCENAME \
      ${FILES[*]} \
      -o basment

#-Wextra -Wshadow \
#-Wredundant-decls -Wstrict-prototypes
#-pedantic 

else

  FILES+=("basment.h"
          "map.h" 
	  "mob.h"
	  "rules.h"
	  "LICENSE.TXT"
	  "README.TXT"
	  "CHANGES.TXT"
	  "build.sh"
          "basment.exe"
	  "basment.conf.example"
	  "xinetd.conf.example"
  )

  echo "Building distribution .tar.gz for \"$1\"..."
  echo "Setting up temporary folder..."
  mkdir "$1"

  for F in ${FILES[@]}
  do
    echo "Adding $F to distribution..."
    cp $F "$1"
  done

  tar -cvvf "$1.tar" "$1"
  gzip "$1.tar"

  exit 0

fi

