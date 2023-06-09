# Bounce the Light

## Description

This will be a pong style game. The objective is to bounce the led light back and forth, bouncing it before it reaches the edge leds, and bouncing it while in a specific color. Every 3 points, the color the led needs to be in will get smaller, increasing the challenge. The point total will be visible the entire game. Each bounce will earn the player 1 point. Button B will be used to bounce the led back and forth, and the switch will be used to choose to play in easy or hard mode. Hard mode will move faster than easy mode. For each successful hit, there will be a sound to resemble hitting a ball, if time allows. Button A will be used to start the game.

## Rules

1. Using the switch, choose whether to play in hard or easy mode. Do this before you start every time to make sure it's in the right mode.
2. Press Button A to start.
3. Hit Button B when the moving LED is in the blue region, but before it reaches the end of the LEDs.
4. Each bounce earns 1 point.
5. As points are earned, the blue region decreases, so pay attention.
6. To win the game, bounce the LED 4 times once the blue region is down to one on both sides, for a total of 13 points
7. If the player fails to bounce the LED in time, the game is over.

## Inputs and Outputs

Button B: Switches direction of LED

Switch: Changes from easy to hard mode

LED: Simulate ball moving back and forth, as well as the "bounce zone" and plays pattern upon victory

Serial Monitor: Prints score, and win/loss

Button A: Starts the game when pressed

Speaker: Plays sound when button b is pressed
