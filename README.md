## AlgServer-ex4

Our goal is to host a client at our server and find the "quickest path" for the matrix that the client will input to the program.

Our program is a specific implementation of our Server and Client Handler interfaces.

The Server handling various clients at any given moment.

The requests given to the Server are pathfinding in a graph (more precisley a matrix Graph when you give the start and goal matrix with costs to "step" into defined 
by the data you are sending to the server at the specific index), which is sent line by line (creating the matrix of costs) by the client.

The algorithm we chose to use is A*, but implementations for BEST FIRST SEARCH (in the Dijkstra context of shortest path...) and classic DFS and BFS are also implemented.


## Running

When running our server using the main supllied by us (for example using our makefile), it expects a command line argument indicating the port number the server will be
opened on (in our makefile's run target we pass 5400). After that point, the server will wait infinitly for the first client, and there after wait for a client no longer
than the 2 minutes.

## Versions

We used [Github](https://github.com/michaeltern/ex4.git) for version control.


## IDE

Clion - Ide by JetBrains

## Authors

- Michael Ternovsky
- Ofir Ben Ezra
