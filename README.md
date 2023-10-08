# Study Project (T3_3101)

## Developers

- [Lars Lehmann](https://github.com/nichtLehdev)
- [Yannick Kirschen](https://github.com/yannickkirschen)

## Building the project

The project is made up of two parts:

- `rail/modules`: a set of libraries containing the business logic
- `rail/embedded`: a set of binaries containing code specific for the Pico

For an easy build, just execute `build.sh`. If you want to build the project
manually, read on.

There is also the Pico SDK which is required to build the embedded code. You
need to download the SDK by running `git submodule update --init`. Then set
the environment variable `PICO_SDK_PATH` to the path of the SDK
(`$(pwd)/rail/lib/pico-sdk`).

### Building the modules on a normal computer

If you want to test your code on your normal computer (and not flashing it to
the Pico) you can build it using `make`:

```shell
make -C rail
```

All libraries and binaries are compiled to `rail/target/{bin,lib}` using your
computers architecture. You can now execute a binary to test some stuff.

### Building the embedded software

If you want to flash your code to the Pico, you need to build the embedded code
by using `cmake`:

```shell
cmake -S rail/embedded -B rail/target/embedded
make -C rail/target/embedded
```

Now connect the Pico to your computer while pressing the `bootsel` button. A
drive should appear. Drag and drop the uf2 file to that drive to flash the
firmware.
