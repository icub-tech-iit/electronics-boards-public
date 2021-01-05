Electronics Boards Public
=========================

This repository mirrors our internal private repository `electronics-boards`,
exposing only a subset of the material and documentation that we aim to make public.

Each board has an own folder where there are schematic, layout, firmware, simulations, documents, photos, configuration files, etc.

The board folders follow these rules:
- foldername **name of the board** 
- admitted subfolders:
   - **config** folder contains configuration files
   - **docs** folder contains documents
      - **datasheet** folder contains useful datasheet
   - **mech** folder contains mechanical parts related to the board
   - **orcad** folder contains the OrCad project
   - **output** folder contains files for the production of the PCB and board (Gerber files, BOM, PCB Notes, etc.)
   - **pads** folder contains the PADS project
   - **pics** folder contains useful photos and videos of pcb, board, setup
   - **sims** folder contains simulations and results
   - **sw** folder contains the firmware useful for the board (test, normal operation, etc)
   - **test** folder contains test equipment, tests and results
      - **gulp** folder contains files useful for visualization with GULP
   - **wiring** folder contains logic and harness schematics for wiring

## Git LFS remark
This repository exploits the Git Large File Support ([LFS][1]) to handle the binary files.
To download the binary files, follow the GitHub [instructions][2]. To configure Git LFS, follow these [instructions][3].

[1]: https://git-lfs.github.com/
[2]: https://help.github.com/articles/installing-git-large-file-storage/
[3]: https://help.github.com/en/github/managing-large-files/configuring-git-large-file-storage
