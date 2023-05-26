# Pipex

School 42 Project that consists in recreating the behavior of pipe "|".

It must behave as the following command:

```< infile cmd1 | cmd2 > outfile```


Infile is the the file that contains the input for the commands (must exist beforehand).

The output will appear in the Outfile (if does not exist, will be created).


# Bonus

- Handle multiple pipes
- 
- Support << and >> when the first parameter is "here_doc"


# Usage

## Mandatory

Use ```make``` to compile mandatory part of the project.

Then, use (for example) :

``` ./pipex infile "ls -l" "wc -l" outfile```

This command should behave the same as :

```< infile ls -l | wc -l > outfile```



## Bonus

Use ```make bonus``` to compile bonus part of the project.

To test multiple pipes, use (for example) :

``` ./pipex infile cmd1 cmd2 cmd3 ... cmdn outfile```

This command should behave the same as :

```< infile cmd1 | cmd2 | cmd3 ... | cmdn > outfile```



To test here_doc, use (for example) :

``` ./pipex here_doc LIMITER cmd cmd1 outfile```

This command should behave the same as :

```cmd << LIMITER | cmd1 >> outfile```



LIMITER is the word that will be used to exit here_doc.

It can be anything you write in the command line (LIM, STOP...).
