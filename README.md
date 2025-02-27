<h1 align="center">FDF - A wire frame model</h1>

<p align="center"><b><i>A simplified 3D graphic representation of a landscape.</i></b><br></p>

![----------------------------------------------------------------------------------------------------------](https://github.com/hle-hena/hle-hena/blob/main/assets/aqua.png)

Need install on Linux :
```Linux
sudo apt-get install gcc make xorg libxext-dev libbsd-dev
```

To clone the project :
```bash
git clone --recursive https://github.com/hle-hena/fdf.git
cd fdf
```

To compile the program :
```bash
$ make && make clean
```

![----------------------------------------------------------------------------------------------------------](https://github.com/hle-hena/hle-hena/blob/main/assets/aqua.png)

FDF is, as shown bellow, supposed to be a simple map renderer ...
<p align="center">
	<img src="https://raw.githubusercontent.com/hle-hena/fdf/refs/heads/main/img/iso_1.png"/>
	<img src="https://raw.githubusercontent.com/hle-hena/fdf/refs/heads/main/img/iso_2.png"/>
</p>
However, I had a bit of fun, and got a bit carried away, and changed it into a first person render !
<p align="center">
	<img src="https://raw.githubusercontent.com/hle-hena/fdf/refs/heads/main/img/persp_1.png"/>
	<img src="https://raw.githubusercontent.com/hle-hena/fdf/refs/heads/main/img/persp_2.png"/>
</p>

![----------------------------------------------------------------------------------------------------------](https://github.com/hle-hena/hle-hena/blob/main/assets/aqua.png)

## BINDINGS

|KEY|ACTION|
|---|---|
|`Mouse Scroll`| Zomm In/Out|
|`WASD`| Movement|
|`Q / E`| Move up or down|
|`Mouse (Right Clicked)`| Rotation when in perspective|
|`U / J`| X axis Rotation when in isometric|
|`I / K`| Y axis Rotation when in isometric|
|`O / L`| Z axis Rotation when in isometric|
|`SPACE`| Switch between projections|
|`SHIFT`| Switch between two kinds of movement in perspective|
|`CTRL`| Switch between modes|
|`TAB`| Switch the current modifier if in CONTROL mode|
|`+ / -`| Increment or decrement the current modifier if in CONTROL mode|
|`ESC`| Quit the programm|
