# Project Name

Market order book

## Overview

This project is used to model a financial order book. It takes in orders and tries to match immedietly, if there is no match it then adds the order to a FIFO priority queue.


I have added notes for me during this process to help understand my decisions and my thinking at the time.



For the data structure that stores the Orders I dececided to use std::unordered_map as it has constant time complexity when searching for particular price buckets. Within that I used a std::list of Orders so that I could store an iterator to that order which allows O(1) for finding particular orders. Understandably list is not the most efficient container to use but as a first attempt, and with the idea of just getting it working, it will do for now.

Testing:

GTest does not support brew clang so I have built the unit tests with apple clang instead. The .vscode folder should apply all the correct settings to enable this. If you cannot build Debug then run 'brew install clang'

To get clangd to index either build, you need to change the configuration in cmake tools

To learn:

Order duration type, Fill and Kill, good till cancelled etc



TODO:

Add marketOrder queue to allow market orders to wait for ones with higher priority

Add in Users to submit market orders - Auto gen and randomly add at certain time intervals to simulate real market
