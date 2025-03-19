# Spitfire Chess Engine (Release 0.2.13)

Spitfire-v2 is a chess engine built completely from scratch in C++, using a bitboard representation and Alpha-Beta search. It's designed to be a simple, strong, fast, and easy-to-use chess engine suitable for both casual play and engine competitions. 

## Key Features

- **Bitboard Representation**
- **Negamax Alpha-Beta Search with Iterative Deepening** 
- **Quiescence Search** 
- **Move Ordering** 
- **Transposition Table with Zobrist Hashing** 
- **Handcrafted Evaluation Function** 
- **UCI Protocol Support**

## Performance

Currently, Spitfire-v2 analyzes up to **2 million nodes per second** and plays at roughly **1800 Elo**.

## How to Compile

Spitfire-v2 is straightforward to compile. Just follow these steps:

```bash
git clone https://github.com/dxwhood/spitfire-v2.git
cd spitfire-v2
mkdir build && cd build
cmake ..
make
```

After compiling, you can run the engine for terminal play with:

```bash
./spitfire-v2 --console --white
```
You can replace `--white` with `--black` to play as black.

## Using with Chess GUIs

Spitfire-v2 supports the UCI (Universal Chess Interface) standard. Just load the compiled executable in your favorite GUI (CuteChess, Arena, Chessbase, etc.), and you're ready to play.


## Future Development

Planned features include:

- NNUE evaluation for stronger positional understanding
- Parallel search (multithreading) for improved speed

## License
Spitfire-v2 is released under the **MIT License**, giving you the freedom to use, modify, and redistribute the engine however you like. Contributions and improvements are very welcome!

