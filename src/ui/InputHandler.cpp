#include "InputHandler.hpp"
#include <dsp_library/Modulators/Env/Env.hpp>

void InputHandler::initInputs() {
    inputs_["shift"] = false;
}

bool InputHandler::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

        if (keyEvent->isAutoRepeat()) // ignorer la répétition clavier
            return false;

        if (keyEvent->key() == SHIFT && inputs_["shift"] == false) {
            inputs_["shift"] = true;
        }

        if (keyEvent->key() == 65) {
            std::vector<std::shared_ptr<AudioModule>> &modules = synth_.getAudioModules();
            std::shared_ptr<Env> env = nullptr;

            for (auto &module : modules) {
                env = std::dynamic_pointer_cast<Env>(module);
                if (env)
                    break;
            }
            if (env)
                env->gateIn = true;
            // return *this;
        }

        // std::cout << keyEvent->key() << std::endl;
        // std::cout << keyEvent->text().toStdString() << std::endl;
        return true;
    }
    else if (event->type() == QEvent::KeyRelease) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

        if (keyEvent->isAutoRepeat()) // ignorer la répétition clavier
            return false;

        if (keyEvent->key() == SHIFT && inputs_["shift"] == true)
            inputs_["shift"] = false;

        if (keyEvent->key() == 65) {
            std::vector<std::shared_ptr<AudioModule>> &modules = synth_.getAudioModules();
            std::shared_ptr<Env> env = nullptr;

            for (auto &module : modules) {
                env = std::dynamic_pointer_cast<Env>(module);
                if (env)
                    break;
            }
            if (env)
                env->gateIn = false;
            // return *this;
        }

        return true;
    }

    return QObject::eventFilter(obj, event);
}