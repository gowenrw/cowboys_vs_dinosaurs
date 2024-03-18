# cowboys_vs_dinosaurs

Cowboys vs Dinosaurs Badge Artifacts

This is a DEFCON Indie badge created for DC32.

This is where all the files for the Badge will be stored.

This includes code and art and cad and fab files.  All the things.

## File Structure

This is the file structure of this repository

* [/](/README.md) - YOU ARE HERE
* [/art/](./art/) - Artwork and other graphics created by this project
  * [/art/inspiration/](./art/inspiration/) - Art and graphics pulled f6 other sources used as inspiration for this project
  * [/art/fonts/](./art/fonts/) - Fonts used in art and graphics
* [/code/](./code/) - All project related Code / Firmware
* [/docs/](./docs/) - Documentation created by this project including web pages
* [/eda/](./eda/) - Electronic Design Automation files (i.e. KiCad)
  * [/eda/cowboys_vs_dinos/](./eda/cowboys_vs_dinos/) - KiCad 7.x project folder for the cowboys_vs_dinos PCB
* [/reference_parts/](./reference_parts/) - Documentation pulled from other sources related to components
* [/README.md](/README.md) - This File
* [/LICENSE](/LICENSE) - Currently set to MIT

Note: the reference_parts directory is a link to a submodule repository.
To add it use the following cmd after cloning this:
```
git submodule add https://github.com/gowenrw/reference_parts reference_parts
```
This will make a link to the current commit of that repo.
To update it to a newer commit after its been added use this cmd:
```
git submodule update --remote
```
