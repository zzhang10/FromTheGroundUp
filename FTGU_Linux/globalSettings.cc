#include "globalSettings.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

//see header file for description

// Game config
const int global__totalLevels = 5;
const string global__moveS = "so";
const string global__moveN = "no";
const string global__moveW = "we";
const string global__moveE = "ea";
const string global__moveSW = "sw";
const string global__moveSE = "se";
const string global__moveNW = "nw";
const string global__moveNE = "ne";
const vector<char>global__walkableChar = {global__displayNormalCell, '+', '#'};

//Player selection:
const string global__selectMiddleman = "i";
const string global__selectMannequin = "a";
const string global__selectMeatshield = "e";
const string global__selectMaddude = "d";
const string global__selectHacker = "1337";

// Graphics display:
const char global__displayPotion = 'P';
const char global__displayGold = 'G';
const char global__displayForceShield = 'F';
const char global__displayDefender = 'D';
const char global__displayWarlock = 'W';
const char global__displayXenosite = 'X';
const char global__displayVindicator = 'V';
const char global__displayNinja = 'N';
const char global__displayMercenary = 'M';
const char global__displayTankmaster = 'T';
const char global__displaySmartPtr = 'S';
const char global__displayNormalCell = '.';
const char global__displayWizard = 'Z';
const char global__displayPlayer = '@';
const char global__displayStair = '\\';

//In-game messages
const string global__mapDirectory ="./maps/";
const string global__restartMsg ="Restarting game...";
const string global__quitMsg = "You have quit the game.";
const string global__goldProtected =
        "The defender is guarding the gold. You may not take it.";
const string global__goldProtectedModded =
        "\033[0;31mThe Defender was like, \"Dude, that's my gold.\"\033[0m";
const string global__FSProtected =
        "The defender is guarding the Force Shield. You may not take it.";
const string global__FSProtectedModded =
        "\033[0;31mThe Defender was like, \"you can't take that ForceShield from me!\"\033[0m";
const string global__playerUFS = "You put on the FS that you just found.";
const string global__noWalk = "Seems like you cannot walk that way.";
const string global__noWalkModded1 =
        "\033[0;31mBruh, people don't just walk inside stuff like that.\033[0m";
const string global__noWalkModded2 =
        "\033[0;31mNo no no no no, you can't go there, that's not how the game works.\033[0m";
const string global__noWalkModded3 =
        "\033[0;31mWalking that way is like a baby seal walking into a club.\033[0m";
const string global__noUse = "There is nothing to use.";
const string global__noUseModded =
        "\033[0;31m\"Watch this!\" you said, trying to use nothing and failing miserably.\033[0m";
const string global__move = "You walked ";
const string global__noAtk = "There is nothing to attack.";
const string global__noAtkModded =
        "\033[0;31mYou made a fool out of yourself by frenziedly attacking at air.\033[0m";
const string global__mercenaryHostile =
        "All Mercenaries are now hostile because you have attacked one.";
const string global__mercenaryHostileModded =
        "\033[0;31mOh boy, all the Mercenaries just got triggered.\033[0m";
const string global__playerSeeG = " and saw some gold";
const string global__playerSeeFS = " and saw a Force Shield";
const string global__playerSeeP = " and saw a random potion";
const string global__playerSeeAll = " and saw a bunch of stuff";
const string global__defenderMadDH =
        "The Defender is hostile when your are near its Stash.";
const string global__defenderMadFS =
        "The Defender is hostile when your are near the Force Shield.";
const string global__defenderMadDHModded =
        "\033[0;31mThat defender is REAL mad when you are near its Stash.\033[0m";
const string global__defenderMadFSModded =
        "\033[0;31mThat defender got no chill as long as you are near the Force Shield.\033[0m";
const string global__moddedMsg =
        "Would you like to add some mods to the game?\n\n"
        "   \033[4;37mSTANDARD FEATURES\033[0m                   \033[4;37mMODDED FEATURES\033[0m\n\n"
        "   Black and white Display             Full colour display\n"
        "   Default map                         Choose from 5 different maps\n"
        "   Standard in-game messages           Randomized funny in-game messages\n"
        "   Default enemies                     Additional enemies\n"
        "   Normal difficulty                   Selectable difficulty\n"
        "   Damage displayed as message         Player/enemy health bars\n"
        "                                       Rebalanced player stats\n"
        "                                       Reworked potion mechanics\n"
        "                                       \n\n\n"
        "    [Y] Yes      [N] No\n";
const string global__moddedYes =
        "Hope you enjoy the extra contents!";
const string global__moddedNo =
        "You will be playing with standard features. Enjoy!";
const string global__moddedInvalid =
        "Invalid entry. Please enter Y or N.";
const string global__raceMsg1 =
        "Please choose from one of the following races:\n";
const string global__raceMsg2 =
        "["+string(global__selectMiddleman,0)+"] MIDDLEMAN: 240 HP, 30 Atk, 30 Def, 150% endgame score multiplier\n"
        "["+string(global__selectMannequin,0)+"] MANNEQUIN: 160 HP, 30 Atk, 40 Def, gold is doubled in value\n"
        "["+string(global__selectMaddude,0)+"] MADDUDE: 240 HP, 40 Atk, 20 Def, negative potions have positive effects\n"
        "["+string(global__selectMeatshield,0)+"] MEATSHIELD: 350 HP, 40 Atk, 35 Def, gold is worth half in value\n";
const string global__raceMsgModded =
	"|---------------------|---------------------|----------------------|-----------------------|\n"
	"|     ["+string(global__selectMiddleman,0)+"]MIDDLEMAN    "
    "|    ["+string(global__selectMannequin,0)+"]MANNEQUIN     "
    "|      ["+string(global__selectMaddude,0)+"]MADDUDE      "
    "|     ["+string(global__selectMeatshield,0)+"]MEATSHIELD     |\n"
	"|  480HP 30Atk 40Def  |  600HP 20Atk 125Def |   350HP 80Atk 20Def  |    880HP 35Atk 5Def   |\n"
	"|                     |                     |                      |                       |\n"
	"|    150% endgame     |       Gold is       |   Negative potions   |     Gold is worth     |\n"
	"|  score multiplier   |  doubled in value   | have positive effect |     half in value     |\n"
	"|                     |                     |                      |                       |\n"
	"|  Compound Potions   |  More Defense buffs |   More Attack buffs  |   More Health buffs   |\n"
	"|---------------------|---------------------|----------------------|-----------------------|\n";
const string global__doSomething = "What would you like to do?";
const string global__failedGen =
        "The level generation failed due to randomizing too many items"
        " together and running out of space. Trying again...\n";
const string global__replayMsg =
        "Would you like to play again? [Y/N]";
const string global__modeMsg =
        "\033[1;35mPlease choose your difficulty:\n\n"
        "\033[1;32m[p] Pleb mode: Enemies' attacks will do no damage\n"
        "\033[1;33m[n] Normal mode: Regular gameplay\n"
        "\033[1;31m[b] Brutal mode: Enemies' Atk and Def increase by 10% per level "
        "rounded up to the next integer.\n"
        "                 Each level spawns 20% more enemies than the"
        " previous one.\n\033[0m";
const string global__mapMsg =
        "\033[1;35mPlease choose your map:\n\n"
        "[s] Standard: 5 rooms, medium size, single-width hallways\n"
        "[c] Close Quarters: 6 rooms, small size, free-roam walkways\n"
	    "[u] Crumple Zone: 7 rooms, large size, single-width hallways\n"
        "[r] Rotator: 5 rooms, medium size, single-width hallways\n"
	    "[i] Isolated: 6 rooms, medium size, single-width hallways\n\033[0m";

const string global__moddedIntro =
	"\033[1;33m[Extra Enemy Mod]\033[1;35m\n"
        "This mod introduces an additional type of enemy, Wizards[Z].\n"
	"3 Wizards are spawned each level, regardless of difficulty.\n"
	"Wizards have low HP, low Def and medium Atk, and their attacks miss 67% of the time.\n"
	"However, when their magic zaps do hit, they deal true damage which ignores defense!\n"
	"A Wizard drops a potion on death, and cannot hold the SmartPointer.\n\n"
	"\033[1;33m[Custom Potion Mod]\033[1;35m\n"
        "Now you have more potions in game, the DLC also improves potion mechanics.\n"
	"The Meatshield now has higher chance of getting a Regeneration potion, \n"
	"with a chance of Regeneration II which increases health by 30.\n"
	"The Maddude now has higher chance of getting a Strength potion, \n"
	"with a chance of Strength II which increases attack by 10.\n"
	"The Mannequin now has higher chance of getting a Resistance potion, \n"
	"with a chance of Resistance II which increases defense by 10.\n"
	"The Middleman now has a chance of getting a Compound potion which\n"
	"Increases health, attack and defense by 10\n\n"
	"\033[1;33m[ConvTweaks Mod]\033[1;35m\n"
	"Player statistics are re-balanced to provide better gameplay.\n"
	"w, a, s, and d are used instead of no, we, so, and ea respectively,\n"
	"and you may attack with e <direction>\n\n";

//Random message generator
const string global__genMessage(string type, string name, int dmgDealt) {
    if (type == "playerAttack") { //Player Attack Enemy
        if (!global__modded) {
            return "You dealt " + to_string(dmgDealt) + " damage to the "+
            name + ".";
        }
        string AM1 = "You told the " + name + " a really funny joke. It laughed"+
                " so hard and lost " + to_string(dmgDealt) + " health.";
        string AM2 = "You threw an exception at the " + name + ", but the "
                + name + " failed to catch it and received " +
                to_string(dmgDealt) + " damage.";
        string AM3 = "You grabbed your last exam paper and showed the " + name +
                " your horrendous grades. The " + name + " instantly lost " +
                to_string(dmgDealt) + " health.";
        string AM4 = "You walked up to the " + name + " and said, \"why don't" +
                " you take " + to_string(dmgDealt) + " damage?\" And it did.";
        vector<string>possibleMsg ={AM1, AM2, AM3, AM4};
        if (global__modded) {
            return "\033[0;36m" + possibleMsg[rand() % possibleMsg.size()] +"\033[0m";
        }
        return possibleMsg[rand() % possibleMsg.size()];
    } else if (type == "enemyDie") { //Enemy die
        if (!global__modded) {
            return "The " + name + " was slain.";
        }
        string KM1 = "The " + name + " had its destructor called, and it vanished.";
        string KM2 = "The " + name + " lost all its will to live, "+
                "fell flat on the ground and died.";
        string KM3 = "The " + name + " was like, \"that's enough " +
                "damage taken by me, I'm outta here\".";
        string KM4 = "The " + name + " was too busy battling and"
                + " forgot to breathe.";
        vector<string>possibleMsg ={KM1, KM2, KM3, KM4};
        if (global__modded) {
            return "\033[0;32m" + possibleMsg[rand() % possibleMsg.size()] +"\033[0m";
        }
        return possibleMsg[rand() % possibleMsg.size()];
    } else if (type == "enemyMiss") { //Enemy miss
        if (!global__modded) {
            return "The " + name + " missed its attack.";
        }
        string percent = "50%";
        if(name == "Wizard") percent = "67%";
        stringstream temp{""};
        temp << endl;
        string EM1 = "The " + name + " whiffed its attack horribly "+
                "and missed you by a mile. A mile is 1.60934 kilometers.";
        string EM2 = "You escaped the " + name + "'s attack with a swift lunge.";
        string EM3 = "The " + name + " calculated, \"according to the game rules," +
                " I'm supposed to fail my attack " + percent + " of the time,"
                + temp.str() + "so I'll fail this time I guess\".";
        string EM4 = "You gave the " + name + " a big hug and said, \"I missed "+
                "you man!\" The " + name + " was like, \"I missed you too!\"" +
                " It sure did.";
        vector<string>possibleMsg ={EM1, EM2, EM3, EM4};
        if (global__modded) {
            return "\033[0;32m" + possibleMsg[rand() % possibleMsg.size()] +"\033[0m";
        }
        return possibleMsg[rand() % possibleMsg.size()];
    } else if (type == "enemyHit") {//enemy hit
        string dmg = to_string(dmgDealt);
        if (!global__modded) {
            return "The " + name + " attacked you for " + dmg + " damage.\033[0m";
        }
      
        if (name == "Tankmaster") {
            return "\033[0;31mThe Tankmaster ran you over for " + dmg + " damage.\033[0m";
        } else if (name == "Mercenary") {
            return "\033[0;31mThe Mercenary slashed you with his rapier and did "
            +dmg+" damage.";
        } else if (name == "Vindicator") {
            return "\033[0;31mThe Vindicator bullied you for " + dmg + " damage.\033[0m";
        } else if (name == "Warlock") {
            return "\033[0;31mThe Warlock dealt " + dmg +
                " damage to you with its stone hammer.\033[0m";
        } else if (name == "Defender") {
            return "\033[0;31mThe Defender knocked you over with his heavy shield. You took "
            + dmg + " damage.\033[0m";
        } else if (name == "Ninja") {
            return "\033[0;31mThe Ninja threw a shuriken at you and did "
            +dmg +" damage.\033[0m";
        } else if (name == "Xenosite") {
            return "\033[0;31mThe Xenosite bit you fiercely for "
                + dmg + " damage.\033[0m";
        } else if (name == "Wizard") {
            return "\033[0;31mThe Wizard zapped you for " + dmg + " damage.\033[0m";
        } else {
            return "\033[0;31mThe "+ name + " hit you for " + dmg + " damage.\033[0m";
        }
    } else return "";
}

// Bonus
bool global__modded = false;
int global__mode = 1;
double global__multiplier = 1;
string global__currmap = "standard.txt";

// Hacker
bool global__hacker = false;
const string global__hackerWalkOver =
        "Normal players can't walk over that, but Hackers just don't care.\n";
const string global__hackerMapBorder =
        "As a Hacker you discovered that the world of FTGU is actually round.\n"
        "If you hit the border you'll just come out the other side!\n";
const string global__defenderHack =
        "The Defender was like, \"Nope, you can't take tha... Oh nuts, you can...\"\n";
const string global__hackerIntro =
        "You have chosen to be a Hacker[SECRET RACE]\n"
        "Enemies will still be hostile, but you have super high HP, Atk and Def..\n"
        "You can walk into walls and over potions and enemies.\n"
        "You may take anything protected by a defender.\n"
        "You also have access to a special map...\n"
        "(We pause for a few seconds to make sure you read all that)\n\n";



