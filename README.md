# Study Project (T3_3101)

## Developers

- [Lars Lehmann](https://github.com/nichtLehdev)
- [Yannick Kirschen](https://github.com/yannickkirschen)

## Building the project

**Tip: Open `mini-rail` as its own project in CLion.**

The project is made up of several parts:

- `mini-rail/modules`: a set of libraries containing the business logic
- `mini-rail/embedded`: a set of binaries containing code specific for the Pico
- `mini-rail/apps`: a set of binaries containing the code for the host platform
- `mini-rail/include`: public header files of the modules
- `mini-rail/lib`: third-party libraries (via git modules)

For an easy build, just execute `build.sh`. If you want to build the project
manually, read on.

There is also the Pico SDK which is required to build the embedded code. You
need to download the SDK by running `git submodule update --init`. Then set
the environment variable `PICO_SDK_PATH` to the path of the SDK
(`$(pwd)/rail/lib/pico-sdk`).

### Building for the host computer

If you want to test your code on your normal computer (and not flashing it to
the Pico), pass `TARGET_ARCH=host` to `cmake`:

```shell
cmake -D TARGET_ARCH=host -B mini-rail/build/host -S mini-rail
make -C mini-rail/host
```

All libraries and binaries are compiled to `mini-rail/build/host` using your
computers' architecture. You can now execute a binary to test some stuff.

### Building the embedded software

If you want to flash your code to the Pico, you need to build the embedded code
by passing `TARGET_ARCH=pico` to `cmake`:

```shell
cmake -D TARGET_ARCH=pico -B mini-rail/build/embedded -S mini-rail
make -C mini-rail/embedded
```

Now connect the Pico to your computer while pressing the `bootsel` button. A
drive should appear. Drag and drop the uf2 file to that drive to flash the
firmware.
