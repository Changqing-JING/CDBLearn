This repo describes how to debug a C++ project on Windows with cdb
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
8. add `C:\Program Files (x86)\Windows Kits\10\Debuggers\x64` to PATH.Replace x64 with arm64 on arm64 host

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
Note: Replace x64 with arm64 on arm64 host

# Start Debug

## Launch a exe file with cdb
```
cdb -c "g" -y <path to pdb file> <exe file name>
```

## Attach mode
Launch the debug target
```
build/CmakeDebugTarget.exe
```

### Launch cdb and attach to a process
```
cdb -p processId
```
processId needs to be a hex number starts with 0x

[Parameter to avoid debugger search for symbol in system lib](https://learn.microsoft.com/en-us/windows-hardware/drivers/debugger/avoiding-debugger-searches-for-unneeded-symbols)
```
-snul
```

## Often used cdb commands

| Command      | Description |Comment
| ----------- | ----------- |----------- |
| `.attach pid`      | Attach to process       |Pid must be hex number|
| `.detach`      | detach of process       ||
| `quit`      | quit debugger       ||
| `.sympath`   | List debug symbol search path        ||
| `.sympath+ DIR`   | Add debug symbol search path        ||
| `.srcpath`   | List source search path        ||
| `.srcpath+ DIR`   | Add source search path        ||
| `lm`   | list module        ||
| `x /D /f CmakeDebugTarget!`   | List functions in module        |Filter functions which name starts with 'a' in module by regex: `x /D /f CmakeDebugTarget!a*`|
| `x CmakeDebugTarget!p`   | Show address of variable p        |[more info about x command](https://learn.microsoft.com/en-us/windows-hardware/drivers/debugger/x--examine-symbols-)|
| `bp CmakeDebugTarget!main+x`   | set breakpoint at function main line x       ||
| `bp 00007ff6151c16a4`   | set breakpoint at address        |adress can be splited like 00007ff7`9b7a3550|
| `bc 1`   | clear breakpoint        |The 1 is index of the breakpoint|
| `g`   | Continue execution        ||
| Press Ctrl + break button   | Manual trigger break        ||
| `dyb 00007ff6151c16a4`   | dump memory at address        ||
| `u 00007ff6151c16a4`   | dump disassemble at address        |`u address L8` Disassemble from address with size 8|
| `r`   | Show registers        ||
|`sx <i ignore | d disable> <exception code>`|Ignore first chance exception||
|`ba <access type><size> <memory address> `|set data break point|example `ba w4 00401000`.
<access type> is the type of access you want to monitor, such as "r" for read access or "w" for write access. |
||-g disable the break on process creationand -G disables the break on process exit.||

#### Reference
https://learn.microsoft.com/en-us/windows-hardware/drivers/debugger/debugging-using-cdb-and-ntsd
https://stackoverflow.com/a/51862881




