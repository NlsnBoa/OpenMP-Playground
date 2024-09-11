# OpenMP Personal Notes by Nelson Herrera

OpenMP stands for Open Multiprocessor. It allows you to create C/C++ and Fortran code into something that can be parallelized. Note that this is different from just concurrency. 


## Clang Installation on Mac

- **Apple’s default Clang**: No OpenMP support.
- **Homebrew’s Clang**: Has OpenMP support and is more configurable for projects that need parallelization tools like OpenMP.

Since we have a Mac the default C compiler is LLVM's Clang Compiler. However, OpenMP is not directly supported in this default version. 

Therefore, we must install a different version using Home brew:
```
brew install llvm
```

You can check which version of Clang you have by running the following:

```
clang --version
```

You know you are using the default version of Clang if your output looks like this:

```
Apple clang version 13.0.0 (clang-1300.0.29.30)
Target: x86_64-apple-darwin20.3.0
Thread model: posix
InstalledDir: /Library/Developer/CommandLineTools/usr/bin
```

Once you have Homebrew's Clang you can temporarily set it as your default clang compiler. This will be set back to the default after closing the terminal. 

```
export PATH="/opt/homebrew/opt/llvm/bin:$PATH"
```

After which if you run `clang --version` again, your output should look like this:

```
Homebrew clang version 18.1.8
Target: arm64-apple-darwin23.6.0
Thread model: posix
InstalledDir: /opt/homebrew/opt/llvm/bin
```
## Write a simple C program

We can check that everything is working by running the following program:

```
int main() {
  int ID = 0;
  printf("hello(%d)", ID);
  printf(" world(%d) \n", ID);
}
```

compile it using this:

```
clang your_file.c -o output_file
```

## OpenMP Installation on Mac

Now that we know that Clang is working we can now install OpenMP

```
brew install libomp
```

## Write a simple OpenMP Program

```
#include <stdio.h>
#include <omp.h>

int main() {
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        printf("Hello from thread %d\n", thread_id);
    }
    return 0;
}
```

To compile this program with OpenMP support, you need to use the `-fopenmp` flag and tell Clang where to find the OpenMP library.

```
clang -fopenmp -L/opt/homebrew/opt/libomp/lib -I/opt/homebrew/opt/libomp/include -o omp_program omp_program.c
```

- `-fopenmp`: Enables OpenMP support.
- `-L/opt/homebrew/opt/libomp/lib`: Specifies the library path for OpenMP.
- `-I/opt/homebrew/opt/libomp/include`: Specifies the include path for OpenMP headers.

if you are using the default Clang instead of Homebrew's clang you will probably get an output like this:
```
clang: error: unsupported option '-fopenmp'
clang: error: unsupported option '-fopenmp'
```

We can temporarily specify the library path and headers paths using:

```
export LDFLAGS="-L/opt/homebrew/opt/libomp/lib"
export CPPFLAGS="-I/opt/homebrew/opt/libomp/include"
```

And now running our program should look like this:

```
clang -fopenmp our_program.c -o our_program
```

