# BattleshipsSDL
##Installing SDL2 & SDL_TTF on Windows with Visual Studio

1) download the VC.zip files from these URLs
https://github.com/libsdl-org/SDL/releases/tag/release-2.28.4
https://github.com/libsdl-org/SDL_ttf/releases
2) Unzip them and put them in some directory where you usually keep external libraries
3) In visual studio, go to Project->Settings->VC++ Directories, and click on Include Directories. Add new entries for the include folders found in each of the libraries you just unzipped
4) In Project->Settings->VC++ Directories again, add the lib/x64 folders to the Library Directories section
5) In Project->Settings->Linker->Input, add SDL2.lib; SDL2main.lib; SDL2_ttf.lib;
6) You now need to add the .dll files to your environment variables. Do this by going to the Windows settings page, and in the 'find a setting' search bar, search 'environment variables'. Click 'edit environment variables' and then the environment variables button.
Edit the 'path' section to include the lib/x64 folders in the two library folders you unzipped earlier. 

##Game Controls
W/I - accelerate

A/J - turn left

D/L - turn right

Q/U - fire left

E/O - fire right
