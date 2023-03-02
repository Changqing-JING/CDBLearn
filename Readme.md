This repo discribes how to debug a C++ project on Windows with cdb
# Install CDB
CDB is a command line debugger by Microsoft. It can be install via Windows SDK.
There is a trick scenario that a lot of Windows C++ developers have already installed Windows SDK during installing Visual Studio, but this installation doesn't contain debugging tools. Visual Studio installer also doesn't allow to choice install debugging tools.
In this case, developers need to:
1. Open control panel
2. Open Programs and Features
3. Right click on Windows Software Development Kit
4. Click "Change"
5. Select "Change", click next, 
6. Select the check box "Debugging Tools for Windows"
7. click "Change"
8. add C:\Program Files (x86)\Windows Kits\10\Debuggers\x64 to PATH

## Build the debug target
```
mkdir build
cd build
cmake -G "Visual Studio 17 2022" -A x64 ..
cmake --build .
```
Run in "x64 Native Tools"
```
cmake -G "Ninja"  ..
```

# Start Debug
## Launch cdb and attach to a process
```
cdb -p processId
```

### Stop debugging
```
.detach
```
### Exit cdg
```
exit
```
## Often used cdb commands

| Command      | Description |Comment
| ----------- | ----------- |----------- |
| `.attach pid`      | Attach to process       |Pid must be hex number|
| `.sympath`   | List debug symbol search path        ||
| `..sympath+ DIR`   | Add debug symbol search path        ||
| `.srcpath`   | List source search path        ||
| `.srcpath+ DIR`   | Add source search path        ||
| `lm`   | list module        ||
| `x /D /f CmakeDebugTarget!`   | List functions in module        |Filter functions which name starts with 'a' in module by regex: `x /D /f CmakeDebugTarget!a*`|
| `bp CmakeDebugTarget!main`   | set breakpoint at function        ||
| `bp 00007ff6151c16a4`   | set breakpoint at address        ||
| `bc 1`   | clear breakpoint        |The 1 is index of the breakpoint|
| `g`   | Continue execution        ||
| Press Ctrl + break button   | Manual trigger break        ||
| `dyb 00007ff6151c16a4`   | dump memory at address        ||
| `u 00007ff6151c16a4`   | dump disassemble at address        ||
| `r`   | Show registers        ||

#### Reference
https://learn.microsoft.com/en-us/windows-hardware/drivers/debugger/debugging-using-cdb-and-ntsd
https://stackoverflow.com/a/51862881




