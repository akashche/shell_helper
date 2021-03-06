Utility for common shell tasks
==============================

Cross-platform utility created as a workaround for Windows batch scripts shortcomings.

Implements a set of command-line tasks to be used from the shell scripts. It runs fine on Linux
too, though most of the implemented tasks are easily achievable using standard *nix tools. 

Binary downloads
----------------

**Windows:**

 - [x86 for Windows XP and newer](https://bitbucket.org/akashche/downloads/downloads/shell_helper_1.0.exe)
 - 504 KB
 - sha256: `733b95f56932e2b5dd896e12ff8bba9ba31586ebceae2f60dd2ecbc44a64f9ec`
 - [VirusTotal report](https://www.virustotal.com/en/file/733b95f56932e2b5dd896e12ff8bba9ba31586ebceae2f60dd2ecbc44a64f9ec/analysis/1447610022/)

**Linux:**

 - [portable x86_64 ELF binary](https://bitbucket.org/akashche/downloads/downloads/shell_helper_1.0) (statically linked with [musl libc](http://wiki.musl-libc.org/wiki/Main_Page))
 - 4.2 MB 
 - sha256: `e565082757d49ee1094502ad28f9f983a1bde064bdf1738be4a7a6c5efe71aba`

Supported tasks
---------------

The following command-line tasks are currently supported

####uuid

Generates and prints [uuid](https://en.wikipedia.org/wiki/Universally_unique_identifier):

    ./shell_helper uuid
    > 541e2f11-c8b2-4ac7-84f7-79c81c480c9d

####time

Prints current date and time using specified format string ([iso 8601](https://xkcd.com/1179/) by default):

    ./shell_helper time -f %Y_%m_%d_%H_%M_%S
    > 2015_11_15_16_31_42

####connect

Tests TCP connection to the specified IP address and TCP port:

    ./shell_helper connect -i 127.0.0.1 -p 22
    > SUCCESS
    ./shell_helper connect -i 127.0.0.1 -p 4242
    > ERROR: Connection refused (111)

Also supports "wait mode" polling periodically for the connection until it will become available:

    ./shell_helper connect -i 127.0.0.1 -p 4242 -w 10
    # 10 seconds passed
    > ERROR: Connection timed out (-1)

####replace

Replaces placeholders in the source file using parameters from JSON file and writes results to output file:

Source file with placeholders `src.txt`:

    41 {{foo}} 43 {{bar}}

JSON file with parameters `params.json`:

    { "foo": "42", "bar": "44" }

Run `replace` task:

    ./shell_helper replace \
        --replace_source src.txt \
        --replace_params params.json \
        --replace_dest dest.txt

Result in `dest.txt`:

    41 42 43 44

####process

Starts specified process in background printing its PID and redirecting process output to the specified file

Process description JSON file `desc.json`:

    {
        "executable": "/bin/ls",
        "arguments": ["-l", "-a", "-h"],
        "out_file": "out.txt"
    }

Start process:

    ./shell_helper process -d desc.json 
    > 15623

Output file contents:

    total 136K
    drwxr-xr-x 13 alex alex 4.0K Nov 15 17:12 .
    drwxr-xr-x  9 alex alex 4.0K Nov 15 16:55 ..
    -rw-r--r--  1 alex alex  37K Nov 15 16:55 some_file
    ...

How to build
------------

[CMake](http://cmake.org/) is required for building.

    git clone --recursive https://github.com/akashche/shell_helper.git
    cd shell_helper
    mkdir build
    cd build
    cmake ..
    # on Linux and Mac
    make
    # on Windows
    msbuild shell_helper.sln

License information
-------------------

This project is released under the [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0).

Changelog
---------

**2015-11-15**

 * version 1.0.0
 * initial public version
