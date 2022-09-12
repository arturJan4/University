#!/bin/bash

while true; do
    rem_power=$((100 * $(< /sys/class/power_supply/BAT1/charge_now) / $(< /sys/class/power_supply/BAT1/charge_full)))

    echo "Battery: $rem_power%" >> /tmp/mylog.fifo
    sleep 10
done