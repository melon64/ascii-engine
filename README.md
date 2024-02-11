### Features
- MVC Architecture
- Cross-Platform Console-Based Rendering
- Event-Driven Input Handling
- Singleton-Based Core Management
- Object Management/Entity Component System
- Collision Detection
- Event Handling System
- Action Command System
- Dynamic World State:
- Multi-layered Rendering
- Resource Management
- Frame-based Animation
- State Persistence

# ascii-engine
An ASCII art game engine built in C++ from the ground up. Powered by ncurses.
## UML
![UML](https://i.ibb.co/P5z1BLN/AGE.png "UML")

## Class Documentation
### View
The view is a pure abstract class that is inherited by CursesView. It follows a singleton pattern where only 1 instance of it can exist (since we do not want multiple views). Upon instantiation, it sets up all the game window split into two separate subwindows; one for the statuses, and one for the game itself. The windows each have 2 buffers that has characters drawn on one and swapped to from the other previously shown buffer that gets cleared. The drawing is done upon being notified by the model which sends a list of objects. Based off height, it draws the objects in succession (so an object of height 1 overlaps height 0 without consequences). 

### Controller
Like the view, the controller is a pure abstract class inherited by CursesController. It also follows a singleton pattern for the same reasons. Upon instantiation, it attaches keypad and mouse action functionality to the CursesView. When the model requests an action via getAction(), it is notified and returns a std::variant of either NoAction{} (a struct that represents no action gotten) or a Keyboard/Mouse event. Game developers can then handle the respective events by retrieving the key or mouse position from the event sent to the model.

### Model
Majority of the game functionality exists in the model. It is also an abstract class with two fields for the View and Controller with each being attached via addView() and addController(). The abstract class extends two functions for its subclasses, getAction() and notifyView() in order to interact with the view and controller. Now let us go through every subclass in the model:

#### State
Another abstraction over the different states of the model, provides a start() and end() function for each singleton class that inherits it. 

#### GameState
A singleton class that provides the game loop and instantiates all the other states. The loop keeps track of game time via a clock, sending a frame refresh event per iteration of the game loop. The order of operations is as such:
- Get action from controller
- Update the world
- Notify the view
- Sleep for desired time for a constant frame rate
The engine runs on a default 33 frames per second. It provides a easy API; all game developers need to do is design their custom objects, populate the world as desired via positions, and call the go() function of the GameState.

#### WorldState
A singleton class that handles all the world logic, can be treated as the true game state. Here is a brief list of everything it does and how it does it:
##### Object movement
- All objects have their own update() function that returns a position it would move to based on its velocity and direction, the World calls update() on all the objects in its own update() function

##### Collision detection
- Following movement, the update() function calls a manageCollisions() function
- Based on the solidity (enumerated SOLID, SOFT, and FOG), it will handle it as such:
- Solid objects impede movement + send a collision event to objects collided
- Soft objects do not impede movement but sends a collision event to objects collided
- Fog objects do not collide with anything
- Any collision with the world boundary sends an event, solid objects are unable to pass though while soft/fog objects are allowed to

##### Out of bounds detection + despawning
- Each object has a out of bounds tick count - if it matches their self-defined threshold, the world will despawn and remove the object
- Note that solid objects cannot go through the world border (including player), whereas soft and fog objects can

##### Player tracking and movement
- The world takes ownership of a singular player object
- The player object is granted an observer role to mouse and keyboard input events and its view is tracked
- The player is forbidden to go past the border, collision with the border is tracked and respective events are sent

##### Event management
- Acts as the concrete subject of the observer pattern between objects and events
- New events and added and validated to the world and can be called using notifyObservers(Event)
- If objects are not registered to an event, it is not notified

##### Status tracking
- Keeps track of the 3 status lines of the view and allows modification as desired with changeStatus(status number, content)

###  Resources
A singleton class that handles custom shapes and objects. Loads custom“avatars" via a custom file format


### Example Games
- Flappy Bird
`./age -g1`
![Game 1](https://i.ibb.co/HqjZVS0/AGE1.png "Game 1")
- Space Invaders
`./age -g2`
![Game 2](https://i.ibb.co/PWG8WXG/AGE2.png "Game 2")


*Due to academic honesty reasons, the full source code cannot be provided. Please contact me at fkxie@uwaterloo.ca for info regarding implementation and compilation.*  
