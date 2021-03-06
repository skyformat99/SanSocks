#include "Cipher.h"

namespace cipher
{ 
  Cipher ::Cipher()
  {
    base64_helper_ = std::make_shared<Base64>();
    int i = 0;
    i = 0;
    for(int i = 0;i < 256;i++)
      encryption_[i] = i;
    std::random_shuffle(encryption_.begin(), encryption_.end());
    for(int i = 0;i < 256;i++)
      decryption_[encryption_[i]] = i;
  }

  std::string Cipher ::encode(std::string wait_encode)
  {
    for (auto &ele : wait_encode)
      ele = decryption_[ele];
    size_t out_sz = 0;
    char *after_encode = nullptr;
    after_encode = base64_helper_->base64_encode(reinterpret_cast<const unsigned char*> (wait_encode.c_str()), static_cast<size_t>(wait_encode.size()), &out_sz);
    std::string ans(after_encode, after_encode + out_sz);
    delete after_encode;
    return std::move(ans);
  }

  std::string Cipher ::decode(std::string wait_decode)
  {
    for (auto &ele : wait_decode)
      ele = decryption_[ele];
    size_t out_sz = 0;
    unsigned char *after_decode = nullptr;
    after_decode = base64_helper_->base64_decode(wait_decode.c_str(), static_cast<size_t>(wait_decode.size()), &out_sz);
    std::string ans(after_decode, after_decode + out_sz);
    delete after_decode;
    return std::move(ans);
  }

  
}