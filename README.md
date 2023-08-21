
# Xist CommonGame Sample (Xcgs)

**UE 5.3+ Lyra-like HUD & Input Setup**

Official Repository: https://github.com/XistGG/XistCommonGameSample

YouTube Video: https://youtu.be/aoZKxD9NbZU

The above YT video (~16 minutes) includes a quick demo of the game
and a full look at these assets in the Unreal Editor, as well as a
code review of the interesting bits of C++ code.


### This is a SAMPLE Project

This is a **sample** repository
showing how Epic has configured and is using
**CommonUI** and **EnhancedInput** together in
[LyraStarterGame](https://x157.github.io/UE5/LyraStarterGame/).
I'm making this publicly available for educational purposes only.
Use this at your own risk.

This project is ONLY concerned with having the inputs and UI set up to closely mimic Lyra
in a single-player environment (thus, **far** simpler than Lyra).


## What doing?

- Start Game
- Click buttons in top right (Start/Pause)
- Click other buttons (+/-) to modify the global time dilation
- Keyboard `Escape` key opens/closes the main menu at any time
  - All UI on lower UI layers is explicitly hidden while the main menu is open
- Keyboard `1` and `2` keys are inputs to Start/Pause game
  - Notice UI reacts (button states change) even on keyboard inputs, not just button clicks
- Gamepad also works for menu and UI navigation

While the game is paused, it is still ticking.  DeltaTime is just
so artificially low that time is effectively stopped.

This effect is demonstrated as in
[WTF Is? Custom Time Dilation in Unreal Engine 4](https://www.youtube.com/watch?v=VeA2K1coDVw).

### Look and Feel Disclaimer

I am not an artist.  My art looks like cats may have been responsible,
but saying so is mean to cats.

The point of this project is the C++, the setup, the configs.
Not the art, which we can agree is... something.


### Interesting Code

- `AXcgsPlayerPawn`
  ( [h](./Source/XistCommonGameSample/Player/XcgsPlayerPawn.h)
  | [cpp](./Source/XistCommonGameSample/Player/XcgsPlayerPawn.cpp)
  )
  - On Possession/Unpossession:
    - Swap HUD in/out
    - Swap IMCs in/out
  - On Player Restart:
    - Bind to EnhancedInput system inputs
  - Like Lyra, you **must** provide the C++ a map of `InputAction` to `GameplayTag`
    - The C++ routes the inputs based on GameplayTags,
      it doesn't know/care what the Editor assets are named.
- `UXcgsActivatableWidget`
  ( [h](./Source/XistCommonGameSample/UI/XcgsActivatableWidget.h)
  | [cpp](./Source/XistCommonGameSample/UI/XcgsActivatableWidget.cpp)
  )
  - Custom result from `GetDesiredInputConfig`
    - You will **absolutely want to modify/customize this for your game** to set up inputs the way you want.
- `UXcgsHUDLayout`
  ( [h](./Source/XistCommonGameSample/UI/XcgsHUDLayout.h)
  | [cpp](./Source/XistCommonGameSample/UI/XcgsHUDLayout.cpp)
  )
  - More a HUD "widget" than a "layout" (because I didn't import Lyra's
    [UIExtension](https://x157.github.io/UE5/UIExtension/) plugin)
    but I kept the name compatible with Lyra so you can easily
    see the analogy.
    - I do like the idea of the `UIExtension` plugin, but not especially the implementation,
      and as implementing it significantly increases the configuration complexity,
      I opted to omit it in this educational example.
  - Your HUD should be based on this, as this installs a CommonUI Action handler for the "Main Menu" input
    to display the Main Menu when the player presses the Escape key (or Menu key on Gamepad).
- `UXcgsMainMenuWidget`
  ( [h](./Source/XistCommonGameSample/UI/Foundation/XcgsMainMenuWidget.h)
  | [cpp](./Source/XistCommonGameSample/UI/Foundation/XcgsMainMenuWidget.cpp)
  )
  - Custom type of ActivatableWidget that will explicitly hide widgets on the lower layers while active
  - Your Main Menu widget should be based on this.


### Interesting Configs

Some of the INI settings are interesting. See files: [`Config/*`](./Config/)

Some of the classes here are activated by INI.  They're not referenced by any
code anywhere, they're just in the INI.

I tried to minimize the INI files to remove stuff that didn't matter or wasn't relevant
at all to this project, to make it easier to find those gems that **really do** matter.


## Major Deviations from Lyra 5.3

Xcgs deviates from Lyra in some significant ways:

- **Xcgs is single player only**
  - A TON of Lyra's complexity comes from its multiplayer nature.
    I stripped all of that out so we can just see how the inputs work.
- There is no Character class
  - Xcgs contains only a very simple base Pawn (unused) and a Player Pawn
- Pawn Class contains its config
  - In Lyra there is a `PawnData` asset that configures Pawn stuff
  - In Xcgs all of that is just hard coded into the Player Pawn class
- All Xcgs inputs must be explicitly bound in C++
  - See `AXcgsPlayerPawn`::`SetupPlayerInputComponent`
    - All inputs must be explicitly bound here
    - There is no Lyra "Tag to Ability" mapping functionality in Xcgs
- Xcgs UI is pending awards for design in several leading mental institutions
- The concept of `UIExtension` is fantastic and something similar to it would be a great addition here as an upgrade


## Plugins Copied from Lyra 5.3

Epic [distributes some plugins with Lyra](https://x157.github.io/UE5/LyraStarterGame/Plugins/)
specifically.  I've copied some of them into this project.


### Critical Plugins

- `CommonGame`
- `CommonUser`

These plugins are absolutely critical to getting CommonUI and EnhancedInput working like Lyra.

### Amazing Plugins

- `GameplayMessageRouter`

This plugin should be distributed with UE5 Engine itself IMO.
Every game needs one of these.

In this sample, I show how the `GameState` can easily send messages to UI elements
that may or may not exist at any given time.

### Optional Plugins

- `ModularGameplayActors`

Lyra extensively uses [GameFeature Plugins](https://x157.github.io/UE5/GameFeatures/),
and `ModularGameplayActors` facilitates this.

Xcgs does not use GFPs, but I still set up everything based on `ModularGameplayActors`
and even implemented `UGameFrameworkComponentManager` in the `AXcgsHUD`.

The main reason for this is that `CommonGame` bases its classes on the
`ModularGameplayActors` bases.  So either `CommonGame` must be modified
*(no thank you)* or `ModularGameplayActors` must be used as a base.

For this project, the choice was very easy.  Your choice may differ.


## This Project is mostly Refactored Lyra

Note that the majority of this code has been refactored from Epic's
[LyraStarterGame](https://x157.github.io/UE5/LyraStarterGame/) 5.3
project.

I did make some changes to simplify things and make them easier to understand,
but in general the concepts here are all very similar to Lyra.
