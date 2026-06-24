# Oar
- Modern shell and scripting language

## Syntax idea
```oar
$ program
$ if (condition) == true { program }; printnl "hi\n" // print i, print("hi", also hi, another hi)
$ fn do_something() {
    program
}
$ (program arg1 arg 2 arg) // will run what is inside the parenthesis, does the same as `program(arg1, arg2, arg3)`
```
* All programs are functions (with variadic unlimited aruments signature: `fn program(...)`)

## Ideas
* Noe support med nix, direnv?, auto nix-develop hvis flake.nix? ...
* support for en root.oar fil, eller ".oar" som auto importeres når man kommer inni en mappe med den, og so då du går ut av den mappen so skrus det av?
* also implement some kind of stdlib, with some string manipulation stuff, to make scripting easier, +++ etc