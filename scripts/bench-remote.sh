#!/usr/bin/env sh

set -eux

# Tune the server for benchmarking, restoring the previous state on exit.
prev_smt=$(ssh root@homelab 'cat /sys/devices/system/cpu/smt/control')
prev_governor=$(ssh root@homelab 'cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor')
prev_boost=$(ssh root@homelab 'cat /sys/devices/system/cpu/cpufreq/boost')
prev_thp=$(ssh root@homelab 'sed "s/.*\[\(.*\)\].*/\1/" /sys/kernel/mm/transparent_hugepage/enabled')
prev_aslr=$(ssh root@homelab 'cat /proc/sys/kernel/randomize_va_space')
prev_nmi=$(ssh root@homelab 'cat /proc/sys/kernel/nmi_watchdog')

trap "ssh root@homelab '
  echo $prev_smt > /sys/devices/system/cpu/smt/control
  cpupower frequency-set -g $prev_governor > /dev/null
  echo $prev_boost > /sys/devices/system/cpu/cpufreq/boost
  echo $prev_thp > /sys/kernel/mm/transparent_hugepage/enabled
  echo $prev_aslr > /proc/sys/kernel/randomize_va_space
  echo $prev_nmi > /proc/sys/kernel/nmi_watchdog'" EXIT

ssh root@homelab '
  echo off > /sys/devices/system/cpu/smt/control
  cpupower frequency-set -g performance > /dev/null
  echo 0 > /sys/devices/system/cpu/cpufreq/boost
  echo never > /sys/kernel/mm/transparent_hugepage/enabled
  echo 0 > /proc/sys/kernel/randomize_va_space
  echo 0 > /proc/sys/kernel/nmi_watchdog'

rsync -rlpc --delete --exclude build/ --exclude .git/ ./ 'homelab:~/tmp/CppPlayground/'
ssh homelab "cd ~/tmp/CppPlayground/ &&
  conan install . -of build/release -pr conan/profile --build=missing --lockfile=conan.lock &&
  cmake --preset release &&
  cmake --build --preset release --target benchmark &&
  taskset -c 0-4 ./build/release/benchmark $*"
