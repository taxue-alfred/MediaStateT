#include "include/QQ_Music_info.h"

bool QQ_Music_info::GetInfoContent(const std::string &inFilePath) {

}

size_t QQ_Music_info::write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}