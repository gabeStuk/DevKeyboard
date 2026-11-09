#include "devkeyboard.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

using std::string;

DevKeyboard::DevKeyboard(fcitx::Instance* instance) {}

void DevKeyboard::keyEvent(const fcitx::InputMethodEntry& entry, fcitx::KeyEvent& keyEvent)
{
    if (keyEvent.isRelease())
    {
        return;
    }

    if (keyEvent.key().check(FcitxKey_F1))
    {
        auto *ic = keyEvent.inputContext();
        string text = toUppercase(ic->surroundingText().selectedText());
        ic->deleteSurroundingText(-text.length(), text.length());
        ic->commitString(text);
        return keyEvent.filterAndAccept();
    } else if (keyEvent.key().check(FcitxKey_F2))
    {
        auto *ic = keyEvent.inputContext();
        string text = toLowercase(ic->surroundingText().selectedText());
        ic->deleteSurroundingText(-text.length(), text.length());
        ic->commitString(text);
        return keyEvent.filterAndAccept();
    } else if (keyEvent.key().check(FcitxKey_F3))
    {
        auto *ic = keyEvent.inputContext();
        string text = toSnakeCase(ic->surroundingText().selectedText());
        ic->deleteSurroundingText(-text.length(), text.length());
        ic->commitString(text);
        return keyEvent.filterAndAccept();
    } else if (keyEvent.key().check(FcitxKey_F4))
    {
        auto *ic = keyEvent.inputContext();
        string text = toTitleSnakeCase(ic->surroundingText().selectedText());
        ic->deleteSurroundingText(-text.length(), text.length());
        ic->commitString(text);
        return keyEvent.filterAndAccept();
    } else if (keyEvent.key().check(FcitxKey_F5))
    {
        auto *ic = keyEvent.inputContext();
        string text = toCamelCase(ic->surroundingText().selectedText());
        ic->deleteSurroundingText(-text.length(), text.length());
        ic->commitString(text);
        return keyEvent.filterAndAccept();
    } else if (keyEvent.key().check(FcitxKey_F6))
    {
        auto *ic = keyEvent.inputContext();
        string text = toTitleCase(ic->surroundingText().selectedText());
        ic->deleteSurroundingText(-text.length(), text.length());
        ic->commitString(text);
        return keyEvent.filterAndAccept();
    } else if (keyEvent.key().check(FcitxKey_F7))
    {
        auto *ic = keyEvent.inputContext();
        string text = toSha256(ic->surroundingText().selectedText());
        ic->deleteSurroundingText(-text.length(), text.length());
        ic->commitString(text);
        return keyEvent.filterAndAccept();
    } else if (keyEvent.key().check(FcitxKey_F8))
    {
        auto *ic = keyEvent.inputContext();
        string text = toBase64(ic->surroundingText().selectedText());
        ic->deleteSurroundingText(-text.length(), text.length());
        ic->commitString(text);
        return keyEvent.filterAndAccept();
    } else if (keyEvent.key().check(FcitxKey_F9))
    {
        auto *ic = keyEvent.inputContext();
        string text = fromBase64(ic->surroundingText().selectedText());
        ic->deleteSurroundingText(-text.length(), text.length());
        ic->commitString(text);
        return keyEvent.filterAndAccept();
    }
}

string DevKeyboard::toUppercase(const string &str) {
    string result;
    for (size_t i = 0; i < str.size(); ++i) {
        unsigned char c = str[i];
        if (c == static_cast<unsigned char>('_')) {
            result += ' ';
        } else {
            result += static_cast<char>(std::toupper(str[i]));
        }
    }
    return result;
}

string DevKeyboard::toLowercase(const string &str) {
    string result;
    for (size_t i = 0; i < str.size(); ++i) {
        result += static_cast<char>(std::tolower(str[i]));
    }
    return result;
}

string DevKeyboard::toSnakeCase(const string &str) {
    string result;
    for (size_t i = 0; i < str.size(); ++i) {
        unsigned char c = str[i];
        if (std::isspace(c)) {
            result += '_';
        } else if (std::isupper(c)) {
            if (i > 0 && 
                (std::islower(static_cast<unsigned char>(str[i - 1])) ||
                 std::isdigit(static_cast<unsigned char>(str[i - 1]))  ||
                 (i + 1 < str.size() && std::islower(static_cast<unsigned char>(str[i + 1])) && !std::isspace(static_cast<unsigned char>(str[i - 1]))))) {
                result += '_';
            }
            result += static_cast<char>(std::tolower(c));
        } else {
            result += static_cast<char>(c);
        }
    }

    return result;
}

string DevKeyboard::toTitleSnakeCase(const string &str) {
    string result;
    for (size_t i = 0; i < str.size(); ++i) {
        unsigned char c = str[i];
        if (std::isspace(c)) {
            result += '_';
        } else if (std::isupper(c)) {
            if (i > 0 && 
                (std::islower(static_cast<unsigned char>(str[i - 1])) ||
                 std::isdigit(static_cast<unsigned char>(str[i - 1]))  ||
                 (i + 1 < str.size() && std::islower(static_cast<unsigned char>(str[i + 1])) && !std::isspace(static_cast<unsigned char>(str[i - 1]))))) {
                result += '_';
            }
            result += static_cast<char>(c);
        } else {
            result += static_cast<char>(std::toupper(c));
        }
    }
    return result;
}

string DevKeyboard::toCamelCase(const string &str) {
    string result;
    for (size_t i = 0; i < str.size(); ++i) {
        unsigned char c = str[i];
        if (std::isspace(static_cast<unsigned char>(str[i])) || str[i] == '_') {
            if (i < str.size())
                result += static_cast<char>(std::toupper(static_cast<unsigned char>(str[++i])));
        } else {
            result += static_cast<char>(std::tolower(c));
        }
    }
    return result;
}

string DevKeyboard::toTitleCase(const string &str) {
    string result;
    size_t start = 0;
    while (start < str.size() && std::isspace(static_cast<unsigned char>(str[start]))) ++start;
    for (size_t i = start; i < str.size(); ++i) {
        unsigned char c = str[i];
        if (i == start)
        {
            result += static_cast<char>(std::toupper(c));
        } else if (std::isspace(static_cast<unsigned char>(str[i])) || str[i] == '_') {
            if (i < str.size())
                result += static_cast<char>(std::toupper(static_cast<unsigned char>(str[++i])));
        } else {
            result += static_cast<char>(std::tolower(c));
        }
    }
    return result;
}

string DevKeyboard::toSha256(const string &str) {
    unsigned char digest[EVP_MAX_MD_SIZE];
    unsigned int len = 0;
    if (EVP_Digest(str.data(), str.size(), digest, &len, EVP_sha256(), nullptr) != 1) {
        return "";
    }


    std::stringstream ss;
    for (int i = 0; i < EVP_MAX_MD_SIZE; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(digest[i]);
    }

    return ss.str();
}

string DevKeyboard::toBase64(const string &str) {
    BIO *b64 = BIO_new(BIO_f_base64());
    BIO *mem = BIO_new(BIO_s_mem());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    BIO *bio = BIO_push(b64, mem);
    BIO_write(bio, str.data(), static_cast<int>(str.size()));
    BIO_flush(bio);

    BUF_MEM *buffer = nullptr;
    BIO_get_mem_ptr(bio, &buffer);
    string output(buffer->data, buffer->length);
    return output;
}

string DevKeyboard::fromBase64(const string &str) {
    BIO *b64 = BIO_new(BIO_f_base64());
    BIO *mem = BIO_new_mem_buf(str.data(), static_cast<int>(str.size()));
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    BIO *bio = BIO_push(b64, mem);
    std::vector<char> buffer(str.size());
    size_t decoded_size = BIO_read(bio, buffer.data(), static_cast<int>(buffer.size()));
    BIO_free_all(bio);
    if (decoded_size <= 0) {
        return "";
    }
    return string{buffer.data(), decoded_size};
}

fcitx::AddonInstance* DKFactory::create(fcitx::AddonManager* manager) {
    return new DevKeyboard(manager->instance());
}

FCITX_ADDON_FACTORY(DKFactory)