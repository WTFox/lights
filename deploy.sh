#!/bin/bash

echo "Flashing all devices to latest firmware"

echo "Flashing to a1"
particle flash a1 --target "5.5.0" .

echo "Flashing to p1"
particle flash p1 --target "3.3.1" .

echo "Flashing to p2_1"
particle flash p2_1 --target "5.5.0" .

echo "Flashing to patio"
particle flash patio --target "2.3.1" .
