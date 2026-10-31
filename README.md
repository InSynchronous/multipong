# multipong
A multiplayer pong game written from scratch in C++ and SDL3.

[Watch demo](media/compressed.mp4)

## Technical details
 - From scratch with no true graphics API. Software rendered(mostly)
 - Custom Socket based multiplayer
 - LAN Only; or just use a port forwarding service (such as `bore`)

## Installation
There is an appimage provided for both the server and the client. You need to have the server running before you join the game.

### From Linux x86-64 Appimage
Launch a server on a given port:
```
./multipong-server.appimage --port 8080
```

If playing with someone not on your LAN, use a port forwarding tool of your choice:
- Port forward your router(get hacked speedrun wr any%)
- Use Ngrok
- Use Bore
- Use Cloudflare Tunnels

`ngrok tcp 8080`

`bore local 8080 --to bore.pub`

`cloudflared tunnel --url tcp://localhost:8080`

Join a match as either the left or right player:
```
./multipong.appimage left --server localhost:8080
```

If playing on your LAN, replace localhost with the local IP, if playing with port forwarding, put the server it's forwarded to(s) IP/Domain.

### Building from scratch
Ensure the following dependencies and tools are installed:

- `CMake`
- `g++` or `clang++`. MSVC experimental only(untested because I don't own a windows machine)
    - must support c++ 17 minimum
- `SDL3`, `SDL3-ttf`

## PLAY THE GAME
Use WASD to move around, and press F to block. When the ball approaches you, if you aren't blocking, you die.

## AI Use, Credits
I used a lot of SDL3 Tutorials and referenced the documentation some times. I did end up using a LLM Chatbot tool to help debug some compilation errors regarding to SDL3-TTF, as I had a very hard time setting that up. Other than that, the code is written entirely by myself.
