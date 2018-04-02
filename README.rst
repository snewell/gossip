gossip
======
Gossip is a generic multiplexer; it takes input from many sources and sends it
to many destinations (where many is defined as a number larger than 0).  If
data is received before there are destinations available, gossip will keep it
queued until a destination is available to receive the data.


Building
--------
Gossip uses CMake_ as its build system.  In general, you'll need to perform
something like this:

.. code:: bash

    $ mkdir build-dir
    $ cd build-dir
    $ cmake /path/to/gossip
    $ make

Check CMake_'s documentation for additional arguments and flags.


.. _CMake: https://www.cmake.org
