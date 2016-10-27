NFS Carbon - Extra Options - Source Code for Build 2; Rev.01
Made by nlgzrgn
------------------------------------------------------------------------------------------------------------
Features:
(Almost every option can be edited from .ini file.)

-- (NEW!) Made some changes on Quick Race Options menu.
> COPS! Here they are! You can now enable or disable cops from where you select laps, traffic, etc.
> You can now add some traffic into your Drift or Canyon races!
! When you enable this option, "Catch Up" from Circuit menu will be removed. I had to made it to fix a crash.
! This option has a hidden mode. Try to find it out! (Tip: Look at the source code.)

-- (NEW!) You can unlock anything!
> This option uses a vanilla variable to unlock anything in the game!
! Using this one with Unlock Series Cars & Upgrades at the same time may cause unexpected results.
! Be careful. This option can mess with your save games, so don't forget to back them up.

-- (NEW!) You can save your current position on the world and load it when required.
> Press Left Shift + 1-5 to save your position.
> Press Left Ctrl + 1-5 to load it.
! Saved positions will be stored on a text file called "HotPositionL5RA.HOT" in TRACKS folder.

-- (NEW!) You can use Debug Car Customize Screen. (ONLY FOR EXPERTS)
> Enable the option from config file. It will add CAR(DEBUG) option to Main Menu.
> Press 3 to save the car you see on the screen into your save game. (Make a backup, please) (ONLY FOR EXPERTS)
> Press 1 to use the car you see on the screen on free roam.

-- (NEW!) Fixed some vanilla game bugs.
> You can use open-wheel cars now! Disappearing wheels issue is fixed.
> You can load the game without crashes now! Save game loading crash is fixed.

-- (NEW!) You can install Special Vinyls on your car now.
> You can enable VIRUS category from Xbox 360 version.
> You can enable SPECIAL category to install some fancy vinyls.
> It also removes vinyl-car dependencies, so, you can use Cross' vinyl on a Camaro!
! These vinyls will be locked. To unlock* them, use "Unlock Series Cars & Upgrades" option. (See below)

-- (NEW!) You can change the size of your car. (FOR FUN)
> RC Cars on Palmont? Yeah, it's possible now.
! Light dummies and collisions won't be affected.
! Semi trucks with trailers will look strange.

-- (NEW!) You can make some strange drifts with your handbrake. (FOR FUN)
> Enable the option, go outside and take a corner using your handbrake.
> Your car will drift like an in-game (NIS) cutscene.
! This option will not affect Drift races.

-- (NEW!) You can modify the Game Speed for races. (ONLY FOR EXPERTS)
> Use GameSpeed option from config file to set game speed. 
! It doesn't affect menus.
! Too low and high values will corrupt car physics and control responsiveness.

-- (NEW!) You can modify the World Animation Speed.
> Those tires are waving so fast? Try this option!

-- (NEW!) You can mess with Garage Camera.
> Rotate it down to flip that garage upside down.
> Zoom it out to see where you are.
> Enable camera movement on any menu, so you can rotate your car around while you're tuning it.
! When infinite zoom is enabled, your keyboard controls for In-Game Photo Mode will work too slow. (It was required to fix a bug with mouse wheel).
! Mouse wheel doesn't work in In-Game Photo Mode.

-- (NEW!) You can mess with your Smart Look Ahead Camera.
> Is that feature, which focuses your camera to turns, annoying for you? Just disable it.
> Or you want to move that useful feature to everwhere? You can do it, too.
! This option will not affect canyon races.

-- (NEW!) You can control traffic density for Quick Race.
> You can now change traffic density values (Low, Medium and High).
> See the config file!

-- Lap, pursuit time (for Pursuit Tag) and opponent count restrictions are modified.
> You can have from 0 (which makes the race unlimited) to 127 (Really long races) laps/minutes.
> You can have from 0 (forever alone) to 29* (the biggest race wars) opponents.
* The game loads maximum 29 bots in a race. Selecting more than 19 may cause crashes, be careful.
* When crew member enabled, maximum 6 opponents can be spawned.
! You can now select any number of opponents for Race Wars Circuits, too!

-- You can enable subtitles for English!
> German, French, Spanish, all have subtitles. Why not English?

-- You can add Debug and UNLOCALIZED (2?) car categories to Car Select screen.
> One category has Boss cars, one has Crew Members' cars.
> These categories may vary among save games.

-- You can enable language select screen.
> It'll appear when the game starts.
! (NEW!) Now with all the languages!

-- You can slide Autosculpt controllers infinitely!
> Make cars more riced than before!
! Some customizations will not appear on in-game world.
! Be careful while changing your game settings, getting beyond 100% may cause crashes there.

-- You can change bin index for Challenge Series. (ONLY FOR EXPERTS)
> Change the ChallengeSeriesBlacklist option from .ini and you'll get race events of any blacklist as challenge series.

-- You can change the time limit of Splash Screen.
> 30 seconds aren't enough? Make it a minute, an hour, maybe a day!

-- You can enable drift camera mode everywhere!
! Birds eye? There it is!

-- You can change the mode of your headlights now.
> Press H to change them between off (0), low beam (1) and high beam (2).
! Your latest headlight setting will be saved into the .ini file and it will be loaded from there.
> You can edit brightness settings from .ini.

--You can use the Cop Lights.
> Press O key to enable or disable them.
! Use a police car, please.
! Your latest cop lights setting will be saved into the .ini file and it will be loaded from there.
> You can edit brightness settings from .ini.

-- You can remove the barriers.
> You want to remove the neon barriers that forces you to stay on the road, or a small area? YES, YOU CAN!

-- You can unlock a strange race.
> It'll appear as Default String (Canyon Race) at Quick Race Track Select screen. Give it a try!

-- You can now load every save game!
> You don't need to fix the checksum or CD-Key. Just copy them in and load.

-- You can unlock Series Cars & Upgrades.
> The same option from NFSC Unlocker. Use faster cars anytime you want!
> Press F8 to enable or disable it anytime in game.
! Be careful. This option can mess with your save games, so don't forget to back them up.

-- You can change Maximum Multiplier for Drift events.
> They're not enough for you? You trust your drifting? You want to multiply your drift more and more? Get your highest multipliers here!

-- You can force the game to any(?) Heat Level.
> Press F7 to enable heat level override, which will change minimum* and maximum* heat level limits and let you get up to x10!
! This option can be force-enabled from .ini file.
> Press PageUp to change your heat level if you want.
* See the config file.
! x0 doesn't appear at the HUD.
! Don't get busted while Heat Level Override is enabled. It may crash your game.

-- Added some options to edit rain!
> Open the .ini file and go to the [Weather] section. Set it as you like!

-- Added some options from MW ModLoader.
> Run the game in a window, or skip movies directly!


Also check out:
> NFS Carbon - Extra Options (Build 2; Rev.01) - Features: https://youtu.be/l0UbDGPeB94

------------------------------------------------------------------------------------------------------------
How To Compile:

! Before compiling, make sure you're using v1.4 NFSC.exe (6,88 MB (7.217.152 bytes)).
If not, just search "NFS Carbon NO DVD Crack UNLEASHED" on Google, Bing or any search engine you like.

! If your game is still on v1.2, you can find the v1.4 patch on: 
https://mega.nz/#!1BJgXJCC!U5FwMyevPg4y2mJ8FrmxVJ9QsfYDaviw1iKp4H4xtnw

Now you can compile the Extra Options. Just follow these steps:

1) Open "NFSCExtraOptions\NFSCExtraOptions.vcxproj" with Microsoft Visual Studio 2015 (If you want to use it with an older version, just change the platform toolset setting.)
2) Look for the "Solution Explorer" panel. Locate "NFSCExtraOptions" under "Solution "NFSCExtraOptions" (1 project)".
3) Right click > Build. (Or, you can open its contents by clicking the triangle at left. dllmain.cpp is the main code. Make the edits you want, you're free!)
!Make sure you're building with Release and Win32 option. See the upper toolbar for them.
4) Look for the "Output" panel. If it says "Build: 1 succeeded, 0 failed," and stuff, your .asi file has been successfully built. (It will be built into "(Project folder)\Release" folder.)
5) Now, copy it to your "NFS Carbon\scripts" folder. (Use Ctrl+C, Ctrl+V / Cmd+C, Cmd+V / Strg+C, Strg+V; Right-Click > Copy; via xcopy command on CMD; or how do you like it.)
6) Copy the NFSCExtraOptionsSettings.ini from main folder into "NFS Carbon\scripts" folder, too.
7) Run NFSC and see what happens. :)

If this is too complicated for you, or if you want to use an already complied version; just take a visit to my YouTube channel:
https://www.youtube.com/c/nlgzrgn77

------------------------------------------------------------------------------------------------------------
Changelog: (+ Addition, * Change, ! Attention, - Deletion)

Build 2; Rev.01:
+ Added "Show More Race Options" option.
+ Added "Unlock All Things" option.
+ Added Traffic Density Controllers.
+ Added an option to modiy Smart Look Ahead Camera (Drift Camera Movement).
+ Fixed disappearing wheels bug.
+ Added a fix for Save Game loading crash.
+ Added Garage Camera Hacks.
+ Added an option to change Game Speed. (ONLY FOR EXPERTS)
+ Added an option to change World Animation Speed.
+ Added car model size modifiers. (FOR FUN)
+ Added "Augmented Drift With E-Brake" option. (FOR FUN)
+ Added "Show Debug Car Customize" option.
+ Added "Hot Position Saver/Loader".
+ Added hidden vinyls to vinyl selection menu.
* Fixed overwrite issue of Misc options.
* Maximum opponent controller limit has changed from 28 to 29.
* Changed string replacement method to fix a crash with Additional Copyright Text. (Copyright will be in English.)

Build 1; Rev.02:
- Removed Crew Member fix for maximum opponents. (It limits everything to 10.)

Build 1; Rev.01: (Unreleased build)
+ Initial release.
------------------------------------------------------------------------------------------------------------
Thanks to:

samfednik; for Lights' addresses from NFSMW.
379Felipe; for testing, his great help and Portuguese (Brasil) translation.
BloodyThunderX (HGCentral); for testing.
Speedyheart; for her great help.
Xan1242; for his great help.
MWisBest; for his great help.
Aero_; for his great help.
Eclipse 72Rus (CorvetteZ06); for removing the neon barriers.
AKuHAK1; for the method I’ve used on Advanced Force Heat Level hack.
gnagna2000; for NFSC Unlocker.
ThirteenAG; for Ultimate ASI Loader, and .ini Reader.
thelink2012; for injector.
Me; for hacks & this mod.

And who I’ve forgotten to thank here. 
------------------------------------------------------------------------------------------------------------
Final Notes:

This mod is licensed under GNU/GPLv3. So, you can use the source code from it and improve it as I stay as the original creator.

If you find any issue, just post it here:
https://github.com/nlgzrgn/NFSCExOpts/issues

You can also send your improvements from GitHub as well: 
https://github.com/nlgzrgn/NFSCExOpts/pulls

Don’t try to steal my mod in any way.
If you will upload this archive somewhere else; you can add a read me and customize the .ini comments (Texts after “//”) for your language.
But please don’t delete any file from this download.
------------------------------------------------------------------------------------------------------------

See ya!
©2016 nlgzrgn - No rights reserved. ;)

