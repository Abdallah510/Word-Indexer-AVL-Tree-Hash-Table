# Word Indexer — AVL Tree & Hash Table

A menu-driven C application. It reads a text file and indexes every word using two data structures in parallel: an AVL tree for sorted retrieval and a hash table for fast access.

## How It Was Made

Written in C. Words are read from a file, stripped of non-alphabetical characters, and treated case-insensitively. Each unique word is inserted into a self-balancing AVL tree with a frequency counter that increments on duplicates. After the tree is built, an in-order traversal populates a hash table for O(1) average-case lookups. Collision handling is implemented in the hash table.

## Features

- Load and parse text from an input file (`input.txt`), ignoring non-alphabetical characters and treating words case-insensitively
- Build an AVL tree from the loaded words, tracking frequency of each unique word
- Insert and delete words in the AVL tree
- Print all words and their frequencies in alphabetical order via in-order traversal
- Build a hash table populated from the AVL tree
- Insert, delete, and search for words in the hash table
- Word statistics: total unique word count, most frequent word, and words exceeding a user-defined frequency threshold
