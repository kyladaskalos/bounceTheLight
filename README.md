# Bounce the Light

## Description

This will be a pong style game. The objective is to bounce the led light back and forth, bouncing it before it reaches the edge leds, and bouncing it while in a specific color. Every 3 points, the color the led needs to be in will get smaller, increasing the challenge. The point total will be visible the entire game. Each bounce will earn the player 1 point. Button B will be used to bounce the led back and forth, and the switch will be used to choose to play in easy or hard mode. Hard mode will move faster than easy mode. For each successful hit, there will be a sound to resemble hitting a ball, if time allows. It time allows, Button A will be used to start the game. Otherwise the player will have a 60 second window to get ready.

## Rules

1. Using the switch, choose whether to play in hard or easy mode.
2. Press button a to start, it time allows for it to be implemented. Otherwise wait to be prompted on screen.
3. Hit button a when the moving led is in the green region, but before it reaches the end of the leds.
4. Each bounce earns 1 point, so try to score as many points as possible.
5. As points are earned, the green region decreases, so pay attention.
6. To win the game, bounce the led 4 times once the green region is down to one on both sides, for a total of 13 points
7. If the player fails to bounce the led in time, the game is over.

## Inputs and Outputs

Button B: Switches direction of LED

Switch: Changes from easy to hard mode

LED: Simulate ball moving back and forth, as well as the "bounce zone"

Serial Monitor: Prints score, and win/loss

**IF TIME ALLOWS:**

Button A: Starts the game when pressed

Speaker: Sounds when ball is hit
