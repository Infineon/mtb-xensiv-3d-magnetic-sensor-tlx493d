# mtb-xensiv-3d-magnetic-sensor-tlx493d
This repository contains several examples for the XENSIV™ 3D Magnetic Sensor family. It not only includes the sensors core library, which can be found [here](https://github.com/Infineon/xensiv-3d-magnetic-sensor-tlx493d), but also provides the necessary low level wrappers to use the core library within the ModusToolbox™.

> [!IMPORTANT]
> This is not an official example of the ModusToolbox™ and will therefore not be available through the ModusToolbox™ project creation tool. Also the necessary wrappers cannot be obtained through the library manager of the ModusToolbox™. You will find detailed instructions on how to use this repository in the following sections.

## How to get started
The repository contains all necessary files, which are required to setup a working project in the ModusToolbox™. Therefore, the first step is to clone this repository into the desired location on your computer. To make things easier you can simply clone the repository in your default project folder of the ModusToolbox™. On a windows machine it is usually the following location:
```
C:\Users\yourUsername\mtw
```

If you have configured any other default location you can use it instead. You can clone the repository with the following command:

```
git clone https://github.com/Infineon/mtb-xensiv-3d-magnetic-sensor-tlx493d.git
```

Or get a .ZIP-file directly from Github and put it in the corresponding folder.
With that done, you can now open the ModusToolbox™ and click on *"Import Existing Application In-Place"* in the lower, left corner:

![](docs/img/MTB-Import-Existing-Project.png)

Now you should she the following window. Here you have to click on *"Browse ..."*:

![](docs/img/MTB-Project-Information.png)

Now you should see you file explorer. Here, you have to select the repository folder and click on *"Select Folder"*. After a few seconds the project should be included and you should be able to see it in the "Project Explorer" of the ModusToolbox™. If everything worked out so far you just have to do a double-click on the folder in the "Project Explorer". This will set the project as active project. With that you should be able to build the project with the *"Build Project"* button of the ModusToolbox™ in the *"Quick Panel"*:

![](docs/img/MTB-Build-Project.png)

This will build your project and will also gather all necessary resources, for example the core library of the XENSIV™ 3D Magnetic sensors. After you have successfully build the project you should now the see the options to "Program" or "Debug" the selected project in the "Quick Panel" tab of the ModusToolbox™:

![](docs/img/MTB-Program-Debug.png)

Now you can connect your PSoC® to your PC and choose either of the two options to deploy the code to the hardware.

## Integrate library into existing ModusToolbox™ project
If you already have an existing ModusToolbox™ project and want to add the library to it, then you have to do the following steps:

- First of all clone the repository into your desired location.
- Then you have to copy the complete folder *framework* from the cloned repository into your project, here it is not important where you put it.
- In order to use the ModusToolbox™ drivers we need to add the core library of the XENSIV™ 3D Magnetic Sensor family to the project. This can easily done by creating the necessary file in the *deps* folder of your project. 

## Choose a different example
With the steps mentioned in the "How to get started" section you will build the default example, which is a very simple I2C example for the TLE493D-P3B6 of the third generation. Following, is an explanation on how you can change the example to your desired one. In order to do that, you simply have to change the value of the `#define EXAMPLE` to the desired example. You can see a list of all available examples in the enumeration ` examples_t `. The documentation of each example can be found the in corresponding folders directly in the code.

Whenever you have decided for a desired example and changed the code accordingly, you can simply re-build the project and program your connect hardware again.