# CP411 Project: Your Project Title

Author(s): Thomas Ingram (200188260), Ben Cooney (200900760)

Date: 2023-11-27


## Introduction 

In this project we will be implementing procedural terrain generation in OpenGL and C++. procedural generation is the backbone behind many open world exploration video games in today's modern game industry. it allows for infinite and interesting worlds for players to epxlore, this technique of terrain generation can be seen in varying complexities using it to not only add interesting things to the game world but also breath life into the world. This technique can be seen in popular modern games such as Minecraft, No Mans Sky, and Terraria. for our project we will be implementing a simple version in 3D that allows the user to fly around and see the generated world that changes on each run of the program.
 
## Problem solving and algorithms

the major computing problem of procedural generation is a question of efficiency in both memory and compute time. terrain generation can be a costly system operation but using various techniques to limit what is seen and computed by the computer at a specific time we can solve these problems. one such solution is breaking the world up into chunks to allow for divide and conquer approach as we only render small pieces (3 by 3 grid of specific size around the player) of the world the player is actually in such that we arent rerendering and storing a large amount of world information. additionally we can implement view culling to stop from rendering traingles outside the users field of view.  

## Design consideration 

the general design will be one of data oriented programming as the most important consideration in this case is memory and efficiency. additionally since we arent really worried about extended functionality we dont need to handle each objects and their interactions with the interfaces of object oriented programming.

for general overview of the project we will have the main file and import different functionalities as needed through the use of different files which handle focused tasks, for example: a world file (handles world generation), a camera file (handles users current position and view), a noise file (a file to handle the noise map and considerations around it as well) as well as files for data structures such as chunks etc.

## Milestones & schedule

List of tasks/milestones/check points of your project with time schedule. For group project, it needs to provide the roles and tasks of each member.

| Task ID | Description   |  Due date | Lead   |
| :----:  | :------------ | :-----:   | :------: |
|  1      | Project research & team up | Day 7 of week 10 | Ben | 
|  2      | Project proposal | Day 6 of week 11 | Thomas/Ben |
|  3      | Project check point (Draw terrain) | 11/30/23 | Ben |
|  4      | Project check point (Transform terrain to height map) | 12/1/23 | Thomas |
|  4      | Project check point (Add Textures) | 12/2/23 | Ben |
|  5      | Project check point (Camera Movement) | 12/3/23 | Thomas |
|  6      | Project demonstration | Day 6 of week 12 | Ben |
|  7      | Project submission | Day 7 of week 12 | Thomas |

## References

A list of references you read for your project, such as papers, articles, data sources. 

- https://en.wikipedia.org/wiki/Procedural_generation

- http://www.fdg2015.org/papers/fdg2015_paper_19.pdf 

- https://www.gamedeveloper.com/design/how-to-effectively-use-procedural-generation-in-games
