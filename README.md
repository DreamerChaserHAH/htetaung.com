# Portfolio Website

> Personal Portfolio Website inspired by Nier Automata made in C++ using Raylib and compiled with Emscripten

## Motivation

As the time for my internship application comes to a close, it is finally the time for me to seriously work on a portfolio website so that potential employers can look at my skills and abilities. But as I am more of a backend person rather than a frontend person, I didn't really know how to design things well. I also wasn't sure what kind of design I should start with in the first place hence I kept procrastinating. I also wanted to make a bit more unique than others.

One day, while I was learning raylib and compiling c++ to emscripten, I had a sudden motivation.

"What if I could make a game menu like interface with C++ for my portfolio website?"

Sure, the website might be slow

Sure, SEO is bad.

But

It is unique, and different from how most people would do their portfolio website.

Hence, it's here.

I worked on this repository first in May of 2024, but I stopped due to personal things happening in life, now as of December 2024, I thought that maybe I should just go with this repo instead of starting from scratch. It is cool anyways, why not right?

## How to Build

The "website" is designed to run on both desktop and web

### Web Build

```
mkdir webbuild && cd webbuild
emcmake cmake ..
emmake make
npx serve
```