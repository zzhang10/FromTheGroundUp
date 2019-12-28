cmake_minimum_required(VERSION 3.14)
project(FromTheGroundUp)

set(CMAKE_CXX_STANDARD 14)

add_executable(FromTheGroundUp main.cc observer.cc world.cc display/cell.cc
        display/textdisplay.cc subject.cc player/player.cc player/meatshield.cc
        player/middleman.cc player/mannequin.cc player/maddude.cc item/item.cc enemy/enemy.cc
        enemy/defender.cc enemy/ninja.cc enemy/mercenary.cc enemy/xenosite.cc
        enemy/tankmaster.cc enemy/vindicator.cc enemy/warlock.cc display/displaymsg.cc
        globalSettings.cc player/hacker.cc enemy/wizard.cc )


