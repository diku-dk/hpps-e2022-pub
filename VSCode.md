# VS Code for HPPS

If you prefer an integrated development environment (IDE) for implementing and debugging the assignments in HPPS you an use the free cross-platform [VS Code](https://code.visualstudio.com/) IDE from Microsoft.

_Note_: There is another product named Visual Studio which is an entirely different product.

You can [install VS Code via Microsoft](https://code.visualstudio.com/download) or through your favorite package manager.

## Tools for C

To get syntax highlighting and debugging support for the C programming language that we use, install the [MS C/C++ extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools).

You can search for `ms-vscode.cpptools` inside VS Code's package manager to get it set up.
If you have a supported debugger set up on your system, it will work right away.
If debugging does not work, try the [guide to configuring and choosing the debugger](https://code.visualstudio.com/docs/cpp/cpp-debug).

An alternative is to use the [CodeLLDB extension](https://marketplace.visualstudio.com/items?itemName=vadimcn.vscode-lldb) which supports the LLDB debugger.

## Docker for non-Linux machines

As some of the assignments are related to the operating system details, it can be required that you use a Linux-like operating system.
For Windows that means using the [Windows Subsystem for Linux](https://docs.microsoft.com/en-us/windows/wsl/install-win10) which provides an emulation layer.

Another option, that works on all operating systems, is to use Docker to get a fully configured Linux distribution, complete with debugger and compiler.

This option can be integrated into VS Code with the [Remote Containers extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers).

There is a [guide to setting up Docker and a working VS Code integration](https://code.visualstudio.com/docs/remote/containers-tutorial) in a few steps.
Once the integration is set up, you can compile and debug entirely within the Docker instance, and not worry about installing compilers, libraries or debuggers in the host system.

## Tools for Python

Some of the assignments suggest using Python, which you can get support for by installing the [Python extension for VS Code](https://marketplace.visualstudio.com/items?itemName=ms-python.python).

## Source control and versioning

We will not cover version control system, but since you will be working in groups, you may want to use [Git](https://git-scm.com/video/what-is-version-control), which is supported by VS Code without the need for extensions.
