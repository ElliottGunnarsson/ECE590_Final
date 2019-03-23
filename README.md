- Name: Elliott Gunnarsson
- Class : ECE590
- Quater : Winter 2019
- Project: Real Time Strategy Engine

- Description :
===
This project will be a game engine for real time strategy (RTS) games. It will be based on the event loop manager but will have added features for...
1. user input (UI)
1. artificial intenigence (AI)
1. coordinates (Coords)
1. Graphical user interface (GUI)

Milestones 
===                                                        
- Timeframe         
- Completion
1. Set up tests and compile code with basic use cases               
   - 3-17-2019         
   - 20%
1. Implement UI, AI, and Coords                                     
   - 3-18-2019         
   - 40%
1. Implement GUI                                                    
   - 3-19-2019         
   - 60%
1. Document all additions with Doxygen notation                     
   - 3-20-2019         
   - 80%
1. Complete docker install guide and quickstart instruction set     
   - 3-21-2019         
   - 100%
1. Release new RTS as an executable                                 
   - 3-22-2019         
   - 110% - stretch goal


Progress report week 1
===
- made new repo as a fork of elma_project
- watched my daughter grow up.
- Put together an idea of the bare esencialls for basic use case.
- once bare essencials are working the rest is an expansive effort.
- Expecting to work heavily Wednesday Thursday Friday as I do not have work or any other oblegations those days.

Progress report week 2
===
- Milestone Progress %105
    -
1. [<span style="color:lime">
Complete</span>] Compiles Code with basic use case
    - Create minions with stats
    - test compilers, state transitions, all public functions
1. [<span style="color:lime">
Complete</span>] Implemented UI, AI, and Coords
    - UI takes keystrokes and mouse clicks
    - AI assigns randome movements in idle state
    - coordinate data used to detect colitions
1. [<span style="color:lime">
Complete</span>] Implemented GUI
    - color coded display alerts user wich minion is selected
    - ncurses is used with command prompt to detect location of mouse clicks
    - mouse clickes are used to select units and assign tasks like "travel"
1. [<span style="color:lime">
Complete</span>] Documentation Complete
    - Doxygen notation added to all include files
1. [<span style="color:lime">
Complete</span>]Quickstart guide Complete
    - install instructions added for docker, git clone, make, run
    - editors guide added for custom versions based on code.
1. [<span style="color:yellow">
Almost</span>] Release RTS as executable
    - RTS game release as docker command promt interface



docker run -v /c/Users/ellio/Documents/Embedded_Applications/ECE590_Final:/source -it klavins/elma:latest bash







Quick Start Guide
===
1. Install Docker
    ```http
     https://www.docker.com/get-started
    ```
1. Open Docker Quickstart Terminal and CD to your working directoy. Use Full screen mode for gameplay.

1. Clone repo
    ```bash
    $ git clone https://github.com/ElliottGunnarsson/ECE590_Final.git
    ```

1. Build Docker Image from latest elma image. For windows replace $PWD with full file path.
    ```docker
    $ docker run -v $PWD/ECE590_Final:/source -it klavins/elma:latest bash
    ```
1. Complie the program files.
    ```make
    $ make
    ```
1. Run the game
    ```make
    bin/overlord
    ```


Editors Guide
===







