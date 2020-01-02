# FromTheGroundUp
A customizable text-based RPG game

#### Introduction
In this game you are an adventurer on a quest to reach the top of a multi-layered tower, hence the name “From the Ground Up”. Throughout your adventures, you will roam through dungeons connected by walkways, combat many different enemies and collect treasures. In order to reach the next level on the tower, you must find stairway which is only revealed when you defeat the enemy who has the SmartPointer (mind the c++ reference). The game ends if your health reaches 0 or if you finish the last level. 

#### Attack and Defense
You and your enemies have three major statistics: Health(HP), Attack (Atk) and Defense (Def). When you and an enemy are within 1 block radius of each other horizontally, vertically or diagonally, you may attack each other. The amount of damage dealt is dependent upon the attacker’s Atk, the defender’s Def and a randomized multiplier between 0.8 to 1.2. The damage dealt is subtracted from the defender’s HP. If the defender’s HP reaches 0, it dies. 

#### Gold
Gold is the way to keep track of your score. You may pick up gold naturally found in the dungeons, or kill an enemy to obtain some gold. Different gold piles may be worth different amounts, and the player class may affect the value of gold as well.

#### Helpful Items
Randomly scattered through the dungeons are mysterious potions. You may drink one if you are within 1 block radius of it. These potions may help you by increasing your HP, Atk and Def, or they may hurt you by decreasing them. To suit the playstyle of each class, the probability distribution of potion effects is different for different player classes. If the potion affect HP, its effect lasts until the end of the game; if the potion affects Atk or Def, its effects wear off at the end of each level. 
Once per game you will also find the ForceShield, which decreases the damage you take from enemies. This will also last until the end of the game.

#### Enemies
Enemies spawn randomly throughout the dungeon. Most enemies move around randomly until it encounters you, in which case it will stand still to attack you. Some enemies, such as the Defender, will not move at all. Other enemies, such as the Mercenary, are not hostile until provoked. When an enemy attacks you, you have a chance of dodging the attack and mitigating its damage completely; when you attack an enemy, your attack always lands. 


#### Turns
Each turn you may choose to move, attack or pick up a helpful item. You may pick up gold or the ForceShield by walking on top of it; you may attack enemies within a block of you, and you may drink potions within a block of you as well. You may not walk on top of potions or enemies. If your action is invalid or if you have entered an unrecognize command, you will be prompted again and will not lose your turn. Once your turn is complete, your enemies will make their moves.

#### Defenders
Important items like a high-valued gold pile or the ForceShield are defended by an enemy. The Defender has high HP, high Def and low Atk. You will not be able to take an important item without killing its defender. The Defender does not move and will not attack you if you are not near the item that it is protecting.

#### Display
Any enemy, gold or helpful items will be represented by a different character, as are map boundaries, walkways and walls. See GlobalSettings.cc for details.

#### But why stop there?
We have developed custom mods to bring your gameplay onto the next level (pun intended)! These mods grant you access to map selections, multiple difficulties, diversified in-game messages and more potions and enemies. You can even hack the game by entering “1337” (LEET) during player selection, which completely breaks the game mechanics mentioned above. 

#### So you want to customize the game itself?
This requires a little more work, but we have made it easier for you. Most gameplay-related settings, such as how each entity is displayed, action commands, in-game messages and number of levels are in the file GlobalSettings.cc. Just be careful to not use the same display characters/commands for different entities/actions, or the game may produce confusing and/or undefined behavior. You may also make your own maps, as long as they are rectangular and do not contain excessively small rooms that may cause randomized enemy generation to fail (you will get a custom error message when this happens). 
A few settings are deliberately hard-coded throughout the game code and are left out from GlobalSettings.cc, because changing them can be game-breaking (as we have experienced throughout developmental stages of the game). 

#### Disclaimer 
FTGU is inspired by Chamber Crawler, a final project offering for the CS246 course. While some features are visually similar, FTGU has seen extensive backend modifications from the original Chamber Crawler. A few changes have also been made to the fundamental structure of the game. 
 




