# ShrVN

![builds](https://github.com/ShrayzzDev/ShrVN/actions/workflows/builds.yml/badge.svg)

A small Visual Novel type games engine. Not meant to be a serious nor commercial project. Not affiliated with any other engine. Name of the project may change in the future.

------------------------------------

## How to use it ?

For the moment, only command line is available to execute a project.

You have 2 options:

* ShrVN -i/--interpret 'path_to_project'. Launch the interpretor of the engine.  
* ShrVN --init 'path' 'new_project_name'. Create an empty project at the given path.

For example let's make a test project.

`ShrVN --init Scripts/ test_project`

Here we have created a empty project named test_project in the *Scripts/* folder (relative to the current path)

NOTE : The path given must exists, as this program won't create it for you, but the project folder must NOT already exists.

Now you have creared a small script follow the documentation, and you want to test it, then you run this command :

`ShrVN -i Scripts/test_project`

And your game will launch !

------------------------------------

## What can it do ?

For now, there is no menu and only the in game. You can show text, switch between ADV and NVL and that's pretty much all.

All the files needed for the initialisation of the menus are already here, but they are very likely to change when i'm gonna actually do them. (for the moment they're useless)

If you wan't more details on what it can, check official documentation [here](http://shrayzz.fr)

------------------------------------

## Dependencies

This project use SDL2 libraries (SDL, SDL_image and SDL_ttf).

This project also uses qmake to build.

--------------

## Plans for the future :

Later the option to compile those games will be available (compile to c++ then into binary). But this ins't a priority for the moment, since a lot of important feature aren't implmented yet.

Later, the program will also have a GUI (so it will be easier to do basic things, and you won't need command line), but it's even less important than the compile option, so probably will be the last thing before the 1.0 update

And obviously, keep in mind that for now, this is a very early beta and it can't do much. Like there's no menu and no saves. So you may not want to start big projects for now and wait a bit. I plan 1.0 to be out by the end of the year at the very least, but will probably earlier. 

1.0 will have all the basic things to do basic games. You won't be able to do big projects with a lot of effects and all, there will be saves, menus, and you will be able to compile games (runs faster than interpreted, and it will just be an executable, the *images/* folder and the few libraries needed). It will also guarantee compatibility with Windows and Linux. I Also plan to have mac os compatibility, but it won't be for 1.0 as I don't own a mac device, so testing is a tad harder.
