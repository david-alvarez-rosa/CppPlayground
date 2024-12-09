#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using DiskMap = std::vector<uint16_t>;
using Disk = std::vector<int16_t>;

namespace {
constexpr const auto kFreeBlockId{-1};
}  // namespace

auto ComputeChecksum(const Disk& disk) -> long long {
  // Pre-req disk is compacted
  auto checksum{0LL};
  auto i{-1};
  while (++i < disk.size() && disk[i] != kFreeBlockId) {
    checksum += i * disk[i];
  }
  return checksum;
}

auto CompactDisk(Disk& disk) {
  auto left{0UL}, right{disk.size()};
  while (left < right) {
    while (left < right && disk[--right] == kFreeBlockId);
    while (left < right && disk[++left] != kFreeBlockId);
    std::swap(disk[left], disk[right]);
  }
}

auto ConvertToDisk(const DiskMap& disk_map) -> Disk {
  auto disk = Disk{};
  for (auto i{0U}, id{0U}; i < disk_map.size(); i += 2, ++id) {
    auto file_blocks = disk_map[i];
    auto free_blocks = disk_map[i + 1];
    while (file_blocks--) {
      disk.push_back(id);
    }
    while (free_blocks--) {
      disk.push_back(kFreeBlockId);
    }
  }
  return disk;
};

auto ParseInputFile(const std::string& file_name) -> DiskMap {
  auto disk_map = DiskMap{};
  auto file_stream = std::ifstream{file_name};
  auto digits_raw = std::string{};
  file_stream >> digits_raw;

  for (auto digit_raw : digits_raw) {
    disk_map.push_back(digit_raw - '0');
  }

  return disk_map;
}

auto main(int argc, char* argv[]) -> int {
  auto disk_map = ParseInputFile(argv[1]);
  auto disk = ConvertToDisk(disk_map);
  CompactDisk(disk);
  std::cout << ComputeChecksum(disk) << "\n";
}
