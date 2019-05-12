// Picture.cpp

#include "KaliLaska/Picture.hpp"
#include "logger/logger.hpp"
#include "picopng.hpp"
#include <fstream>

namespace KaliLaska {
Picture::Picture(const std::filesystem::path &file) {
  if (std::filesystem::exists(file) && std::filesystem::is_regular_file(file)) {
    LOG_DEBUG << "load file " << file;
    // load file in memory
    std::vector<unsigned char> buff;
    std::ifstream              fin{file, std::ios::binary | std::ios::in};
    std::copy(std::istreambuf_iterator<char>(fin),
              std::istreambuf_iterator<char>(),
              std::back_inserter(buff));

    // decode png by picopng
    unsigned long width{}, height{};
    if (!decodePNG(decodedPNG_, width, height, &buff[0], buff.size(), true)) {
      size_ = Size(width, height);
    } else {
      LOG_ERROR << "png can not be decoded " << file;
    }
  } else {
    LOG_WARNING << "try load not existing file " << file;
  }
}

Picture::~Picture() {
}

Size Picture::size() const {
  return size_;
}

bool Picture::isValid() const {
  return size_ != Size{};
}

const unsigned char *Picture::pixels() const {
  return decodedPNG_.data();
}
} // namespace KaliLaska
