#ifndef _FCITX5_TEENGINE_H_
#define _FCITX5_TEENGINE_H_

#include <fcitx/addonfactory.h>
#include <fcitx/addonmanager.h>
#include <fcitx/instance.h>
#include <fcitx/inputcontext.h>
#include <fcitx/inputmethodengine.h>
#include <fcitx-utils/key.h>
#include <fcitx-utils/keysym.h>

class DevKeyboard : public fcitx::InputMethodEngine {
public:

    enum TextOperation {
        SHA256,
        BASE64,
        CAMELCASE,
        UPPER_CASE,
        LOWER_CASE,
        SNAKE_CASE,
        TITLE_SNAKE_CASE
    };

    DevKeyboard(fcitx::Instance* instance);
    
    void keyEvent(const fcitx::InputMethodEntry& entry, 
                  fcitx::KeyEvent& keyEvent) override;

    static std::string operateText(std::string &str, TextOperation op) {
        switch (op) {
            case TextOperation::SHA256:
                return toSha256(str);
            case TextOperation::BASE64:
                return toBase64(str);
            case TextOperation::UPPER_CASE:
                return toUppercase(str);
            case TextOperation::LOWER_CASE:
                return toLowercase(str);
            case TextOperation::SNAKE_CASE:
                return toSnakeCase(str);
            case TextOperation::TITLE_SNAKE_CASE:
                return toTitleSnakeCase(str);
        }
    }

private:
    static std::string toUppercase(const std::string &str);
    static std::string toLowercase(const std::string &str);
    static std::string toSnakeCase(const std::string &str);
    static std::string toTitleSnakeCase(const std::string &str);
    static std::string toCamelCase(const std::string &str);
    static std::string toTitleCase(const std::string &str);
    static std::string toSha256(const std::string &str);
    static std::string toBase64(const std::string &str);
    static std::string fromBase64(const std::string &str);
};

class DKFactory : public fcitx::AddonFactory {
public:
    fcitx::AddonInstance* create(fcitx::AddonManager* manager) override;
};

#endif