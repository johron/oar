# Ø (oslash)
- Modern shell and scripting language

## Syntax idea
```ø
$ program
$ if condition == true { program }; printnl "hi\n" // print i, print("hi", also hi, another hi)
$ fn do_something() {
    program
}
```
* All programs are functions (with variadic unlimited aruments signature: `fn program(...)`)
* all functions are programs.

## Ideas
* Noe support med nix, direnv?, auto nix-develop hvis flake.nix? ...
* support for en root.ø fil, eller ".ø" som auto importeres når man kommer inni en mappe med den, og so då du går ut av den mappen so skrus det av?