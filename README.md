# Temperature logging component

## Overview

This component uses the [temperature library](https://github.com/hdpr-rover/drivers-temperature) to show/log timestamped temperature values. It can accept an arbitrary number of temperature sensors, the only requirement is that the device itself would comply with the data protocol described in the [library](https://github.com/hdpr-rover/drivers-temperature).

**Authors: Karl Kangur  
Contact: Martin Azkarate  
Affiliation: Automation and Robotics Laboratories, ESTEC, ESA**


## Installation

### Dependencies

This package depends on the following packages:

* [drivers/temperature](https://github.com/hdpr-rover/drivers-temperature)

### Building

In order to install, clone the latest version from this repository into your workspace under `drivers/orogen/temperature`, add the following line to `autoproj/manifest` under `layout:`

    - drivers/orogen/temperature

Execute the following to build the package:

    $ autoproj build


## Basic Usage

### temperature

#### Inputs

None

#### Outputs

* **`temperature_samples`** (/temperature/samples/Temperature)

Timestamped temperature reading samples.

#### Parameters

* **`port`** (/std/string)

The device port, by default: `/dev/ttyACM0`.

* **`baudrate`** (/int)

The device baudrate, by default: `9600`.

* **`sensor_names`** (/std/vector\</std/string\>)

Temperature sensor names, also defines the number of logged sensors.

