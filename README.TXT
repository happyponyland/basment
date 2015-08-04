================
BASMENT DWELLERS
================
by Ulf Åström (happyponyland.net)

This is a game about killing monsters and collecting treasure.


Building
========

./build.sh


Controls
========

LEFT, RIGHT: Move character
UP: Climb up ladders, interact with environment
DOWN: Climb down ladders
SPACE: Pass (wait) a turn, or ready shield (if you have one)
M: View map (if you have one)
Q: Quit

You can also use "hjkl" for vi-like movement.


Options
=======
Pass these on the command line.

-dvorak
Changes vi-keys to the more Dvorak-friendly "dhtn".

-demo
Activates map generator demo mode.

-hiscores, -allscores
Displays highscore table.

-scores <file>
Sets the path of the highscore table.

-forcename
Always prompt for a player name for the highscore table.
(Without forcename the players username will be used.)


Shared server
=============

You can play BASMENT DWELLERS on a multi-user machine with a shared
highscore list. If you are logged in to the machine, you only need to
change the highscore file in the site-wide options /etc/basment.conf

You can also run BASMENT DWELLERS on an external port, not requiring
players to have a login account. BASMENT does not manage any network
sockets of its own, so you will need an external program to establish
the client connection. For this purpose xinetd works reasonably well;
it can be set up to make a telnet connection and run BASMENT in place
of the "login" program.

Install xinetd and telnetd from your package mananger (or source).

Please read up on xinetd configuration to avoid unnecessary security
risks. An xinetd.conf.example file is provided but will require some
customization. If you want /etc/xinetd.d separation for services you
will need to split it in two, but you probably know how to do this.

