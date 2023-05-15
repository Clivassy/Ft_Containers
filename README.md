
<h1 align="center">ft_containers</h1>

# Overview

In this project, I implements my own version of some containers from the Standard Template Library (STL) using C++98. The following containers have been implemented: <br>
- vector <br>
- map <br> 
- stack <br>

The implementation aims to reproduce the behavior and features of the STL containers while following the standard constraints and requirements.<br>

# Getting Started
## Prerequisites

To run this program, you will need: <br>
A Unix-like operating system (Linux, macOS) <br>
g++ compiler <br>

## Installation
1- Clone the repository: ``git clone https://github.com/Clivassy/ft_containers`` <br>
2- ``cd ft_containers`` <br>
3- Compile the code using the provided Makefile: ``make`` <br>
4- Run test for one container : ./container (by default it will launch vector test) <br>
NB : to test other containers :  <br>
-> Open Makefile <br>
-> Decomment the test you want in this part : <br>

<img width="240" alt="Capture d’écran 2023-05-11 à 13 20 20" src="https://github.com/Clivassy/ft_containers/assets/76965602/320ff63f-eab3-4a72-a67b-46cc5bedc1e4"> <br>

## Usage

The usage of the implemented containers is similar to that of the STL containers. <br> 
For instance, to create a vector of integers and add some elements to it. <br> 
You can refer to the "tests" directory to find many tests on each container. <br>

## Code Structure
The code is organized in the following directory structure: <br>
. <br>
├── ft_vector.hpp <br>
├── ft_map.hpp <br>
├── ft_stack.hpp <br>
├── ...<br>
└── Makefile <br>

Each header file contains the implementation of a specific container. <br>
The implementation is split into two main sections: the container class definition and the container iterator definition.<br>

## General advices 
- here talk about how to begin the project 

## Vector and Stack 
- here insist on iterators + types traits + spécificités du vector

## The Red Black Tree (Map and Set)
To my mind, the important part of this project, and the real capital gain, is the implementation of the Red black Tree. <br>
So I won't go into detail about vector and stack implementation and I will focus my advices on map et set. <br> 

Here is the steps I followed to understand step by step Red Black Trees. At the end, I will provide you THE ONE AND ONLY youtube perfect teacher who helped me so much in understanding Red Black Trees and Data Structure in general. <br>

<iframe src="https://giphy.com/embed/vgUFOWBwBkziE" width="480" height="270" frameBorder="0" class="giphy-embed" allowFullScreen></iframe><p><a href="https://giphy.com/gifs/the-office-yes-nod-vgUFOWBwBkziE">via GIPHY</a></p>

# Trees <br> 
First of all, you need to understand the basic structure of a tree. 
A tree is a widely used data structure that resembles a hierarchical tree structure with a set of nodes connected by edges or branches.<br>Each node in the tree can have zero or more child nodes, except for the root node, which has no parent.<br>
Trees are a really useful way to organize data in a hierarchy. <br> They're used all the time in computer science and software engineering for things like file systems, sorting algorithms, and web page structures. <br> 
There are lots of different types of trees to choose from, like:<br> 
- Binary trees<br> 
- AVL trees<br> 
- Red-black trees<br> 
The type you choose depends on what you're trying to do and how fast you need it to be. <br> 
Have a look to this schemas to have a better understanding : <br><br>
<img width="726" alt="Capture d’écran 2023-05-11 à 13 47 45" src="https://github.com/Clivassy/ft_containers/assets/76965602/373ff567-3b8c-4591-9d06-aa9ed30f115f"> <br><br>
<img width="675" alt="Capture d’écran 2023-05-11 à 13 48 23" src="https://github.com/Clivassy/ft_containers/assets/76965602/6e57b09d-91a8-4a63-9ee1-786ddeb12d2c">
<br> 

# Binary Trees <br>
 
A binary tree is a type of tree data structure in which each node can have at most two children. The two children are commonly referred to as the left child and the right child. The structure of a binary tree is hierarchical, where each node is connected to its children nodes.

<img width="728" alt="Capture d’écran 2023-05-15 à 22 26 09" src="https://github.com/Clivassy/Ft_Containers/assets/76965602/04249676-c995-4bde-9358-08a50acb74f7">






