#include <qpushbutton.h>
#include <qevent.h>
#include <qregularexpression.h>
#include "observer.cpp"
using namespace std;

class Key :public QPushButton{
private:
    friend class Keyboard;
    QString keyboard_key;
    QSet<QString> pressedKeys;
    QString last_pressed = "";
    map<string, Key*> &keys;
public: 
    Key(QString keyboard_key_con,map<string,Key*>&keys_con) : keyboard_key(keyboard_key_con),keys(keys_con) {
        this->setText(keyboard_key);
       
        setFocusPolicy(Qt::StrongFocus);
        QRegularExpression regex("^.*$");
        QRegularExpression regex_fkeys("^F[0-9]$");
        if (regex_fkeys.match(keyboard_key).hasMatch())
            keyboard_key = keyboard_key.toLower();
        else if (regex.match(keyboard_key).hasMatch())
            keyboard_key = keyboard_key.toLower();
        
           
        QObject::connect(this, &QPushButton::clicked, [&]() {
            
            QString styleSheet = this->styleSheet();
            QString blue = QString("background-color: blue;");
            QString none = QString("background-color: none;");
            for (auto& key : keys)
                key.second->last_pressed = "";
            if (keyboard_key == "↑")
                last_pressed = "uparrow";
            else if (keyboard_key == "←")
                last_pressed = "leftarrow";
            else if (keyboard_key == "→")
                last_pressed = "rightarrow";
            else if (keyboard_key == "↓")
                last_pressed = "dowmarrow";
            else if (keyboard_key == "Num/")
                last_pressed = "kp_slash";
            else if (keyboard_key == "num*")
                last_pressed = "kp_multiply";
            else if (keyboard_key == "num-")
                last_pressed = "kp_minus";
            else if (keyboard_key == "ent")
                last_pressed = "kp_enter";
            else if (keyboard_key == "num.")
                last_pressed = "kp_del";
            else if (keyboard_key == "num0")
                last_pressed = "kp_ins";
            else if (keyboard_key == "num2")
                last_pressed = "kp_downarrow";
            else if (keyboard_key == "num3")
                last_pressed = "kp_pgdn";
            else if (keyboard_key == "num4")
                last_pressed = "kp_leftarrow";
            else if (keyboard_key == "num5")
                last_pressed = "kp_5";
            else if (keyboard_key == "num6")
                last_pressed = "kp_rightarrow";
            else if (keyboard_key == "num7")
                last_pressed = "kp_home";
            else if (keyboard_key == "num8")
                last_pressed = "kp_uparrow";
            else if (keyboard_key == "num9")
                last_pressed = "kp_pgup";
            else if (keyboard_key == "num+")
                last_pressed = "kp_plus";
            else if (keyboard_key == "num1")
                last_pressed = "kp_end";
            else if (keyboard_key == "caps lock")
                last_pressed = "capslock";
            else last_pressed = keyboard_key;
            if (styleSheet.contains("blue") and keyboard_key != "\u001B" and keyboard_key != "\r")
                this->setStyleSheet(none), pressedKeys.insert(keyboard_key);
            else
            {
                for (auto& key : keys)
                    key.second->setStyleSheet(none);
                this->setStyleSheet(blue), pressedKeys.insert(keyboard_key);
            }
            });
    }
	void keyPressEvent(QKeyEvent* event) override {
        QString keyText = event->text();
        if (event->key() == Qt::Key_Tab)
        {
            event->ignore();
            return;
        }
        if (event->key() == Qt::Key_Space)
        {
            event->ignore();
            return;
        }
        if (event->key() == Qt::Key_F1)
        {
            for (auto& key : keys)
                key.second->last_pressed = "";
            last_pressed = "f1";
            if (pressedKeys.contains("f1")) {
                pressedKeys.remove("f1");
                keys["f1"]->setStyleSheet("background-color: none;");
            }
            else
            {
                for (auto& el : pressedKeys)
                    pressedKeys.remove(el);
                QString styleSheet = QString("background-color: blue;");
                if (keys["f1"])
                {
                    qDebug() << keyText.toStdString();
                    for (auto& key : keys)
                        key.second->setStyleSheet("background - color: none;");
                    keys["f1"]->setStyleSheet(styleSheet);
                    pressedKeys.insert("f1");
                }
            }

        }
        if (event->key() == Qt::Key_F2)
        {
            for (auto& key : keys)
                key.second->last_pressed = "";
            last_pressed = "f2";
            if (pressedKeys.contains("f2")) {
                pressedKeys.remove("f2");
                keys["f2"]->setStyleSheet("background-color: none;");
            }
            else
            {
                for (auto& el : pressedKeys)
                    pressedKeys.remove(el);
                QString styleSheet = QString("background-color: blue;");
                if (keys["f2"])
                {
                    qDebug() << keyText.toStdString();
                    for (auto& key : keys)
                        key.second->setStyleSheet("background - color: none;");
                    keys["f2"]->setStyleSheet(styleSheet);
                    pressedKeys.insert("f2");
                }
            }

        }
        if (event->key() == Qt::Key_F3)
        {
            for (auto& key : keys)
                key.second->last_pressed = "";
            last_pressed = "f3";
            if (pressedKeys.contains("f3")) {
                pressedKeys.remove("f3");
                keys["f3"]->setStyleSheet("background-color: none;");
            }
            else
            {
                for (auto& el : pressedKeys)
                    pressedKeys.remove(el);
                QString styleSheet = QString("background-color: blue;");
                if (keys["f3"])
                {
                    qDebug() << keyText.toStdString();
                    for (auto& key : keys)
                        key.second->setStyleSheet("background - color: none;");
                    keys["f3"]->setStyleSheet(styleSheet);
                    pressedKeys.insert("f3");
                }
            }

        }
        if (event->key() == Qt::Key_F4)
        {
            for (auto& key : keys)
                key.second->last_pressed = "";
            last_pressed = "f4";
            if (pressedKeys.contains("f4")) {
                pressedKeys.remove("f4");
                keys["f4"]->setStyleSheet("background-color: none;");
            }
            else
            {
                for (auto& el : pressedKeys)
                    pressedKeys.remove(el);
                QString styleSheet = QString("background-color: blue;");
                if (keys["f4"])
                {
                    qDebug() << keyText.toStdString();
                    for (auto& key : keys)
                        key.second->setStyleSheet("background - color: none;");
                    keys["f4"]->setStyleSheet(styleSheet);
                    pressedKeys.insert("f4");
                }
            }

        }
        if (event->key() == Qt::Key_F5)
        {
            for (auto& key : keys)
                key.second->last_pressed = "";
            last_pressed = "f5";
            if (pressedKeys.contains("f5")) {
                pressedKeys.remove("f5");
                keys["f5"]->setStyleSheet("background-color: none;");
            }
            else
            {
                for (auto& el : pressedKeys)
                    pressedKeys.remove(el);
                QString styleSheet = QString("background-color: blue;");
                if (keys["f5"])
                {
                    qDebug() << keyText.toStdString();
                    for (auto& key : keys)
                        key.second->setStyleSheet("background - color: none;");
                    keys["f5"]->setStyleSheet(styleSheet);
                    pressedKeys.insert("f5");
                }
            }

        }
        if (event->key() == Qt::Key_F6)
        {
            for (auto& key : keys)
                key.second->last_pressed = "";
            last_pressed = "f6";
            if (pressedKeys.contains("f6")) {
                pressedKeys.remove("f6");
                keys["f6"]->setStyleSheet("background-color: none;");
            }
            else
            {
                for (auto& el : pressedKeys)
                    pressedKeys.remove(el);
                QString styleSheet = QString("background-color: blue;");
                if (keys["f6"])
                {
                    qDebug() << keyText.toStdString();
                    for (auto& key : keys)
                        key.second->setStyleSheet("background - color: none;");
                    keys["f6"]->setStyleSheet(styleSheet);
                    pressedKeys.insert("f6");
                }
            }

        }
        if (event->key() == Qt::Key_F7)
        {
            for (auto& key : keys)
                key.second->last_pressed = "";
            last_pressed = "f7";
            if (pressedKeys.contains("f7")) {
                pressedKeys.remove("f7");
                keys["f7"]->setStyleSheet("background-color: none;");
            }
            else
            {
                for (auto& el : pressedKeys)
                    pressedKeys.remove(el);
                QString styleSheet = QString("background-color: blue;");
                if (keys["f7"])
                {
                    qDebug() << keyText.toStdString();
                    for (auto& key : keys)
                        key.second->setStyleSheet("background - color: none;");
                    keys["f7"]->setStyleSheet(styleSheet);
                    pressedKeys.insert("f7");
                }
            }

        }
        if (event->key() == Qt::Key_F8)
        {
            for (auto& key : keys)
                key.second->last_pressed = "";
            last_pressed = "f8";
            if (pressedKeys.contains("f8")) {
                pressedKeys.remove("f8");
                keys["f8"]->setStyleSheet("background-color: none;");
            }
            else
            {
                for (auto& el : pressedKeys)
                    pressedKeys.remove(el);
                QString styleSheet = QString("background-color: blue;");
                if (keys["f1"])
                {
                    qDebug() << keyText.toStdString();
                    for (auto& key : keys)
                        key.second->setStyleSheet("background - color: none;");
                    keys["f8"]->setStyleSheet(styleSheet);
                    pressedKeys.insert("f8");
                }
            }

        }
        if (event->key() == Qt::Key_F9)
        {
            for (auto& key : keys)
                key.second->last_pressed = "";
            last_pressed = "f9";
            if (pressedKeys.contains("f9")) {
                pressedKeys.remove("f9");
                keys["f9"]->setStyleSheet("background-color: none;");
            }
            else
            {
                for (auto& el : pressedKeys)
                    pressedKeys.remove(el);
                QString styleSheet = QString("background-color: blue;");
                if (keys["f9"])
                {
                    qDebug() << keyText.toStdString();
                    for (auto& key : keys)
                        key.second->setStyleSheet("background - color: none;");
                    keys["f9"]->setStyleSheet(styleSheet);
                    pressedKeys.insert("f9");
                }
            }

        }
        if (event->key() == Qt::Key_F10)
        {
            for (auto& key : keys)
                key.second->last_pressed = "";
            last_pressed = "f10";
            if (pressedKeys.contains("f10")) {
                pressedKeys.remove("f10");
                keys["f10"]->setStyleSheet("background-color: none;");
            }
            else
            {
                for (auto& el : pressedKeys)
                    pressedKeys.remove(el);
                QString styleSheet = QString("background-color: blue;");
                if (keys["f10"])
                {
                    qDebug() << keyText.toStdString();
                    for (auto& key : keys)
                        key.second->setStyleSheet("background - color: none;");
                    keys["f10"]->setStyleSheet(styleSheet);
                    pressedKeys.insert("f10");
                }
            }

        }
        if (event->key() == Qt::Key_F11)
        {
            for (auto& key : keys)
                key.second->last_pressed = "";
            last_pressed = "f11";
            if (pressedKeys.contains("f11")) {
                pressedKeys.remove("f11");
                keys["f11"]->setStyleSheet("background-color: none;");
            }
            else
            {
                
                for (auto& el : pressedKeys)
                    pressedKeys.remove(el);
                QString styleSheet = QString("background-color: blue;");
                if (keys["f11"])
                {
                    qDebug() << keyText.toStdString();
                    for (auto& key : keys)
                        key.second->setStyleSheet("background - color: none;");
                    keys["f11"]->setStyleSheet(styleSheet);
                    pressedKeys.insert("f11");
                }
            }

        }
        if (event->key() == Qt::Key_F12)
        {
            for (auto& key : keys)
                key.second->last_pressed = "";
            last_pressed = "f12";
            if (pressedKeys.contains("f12")) {
                pressedKeys.remove("f12");
                keys["f12"]->setStyleSheet("background-color: none;");
            }
            else
            {   
                for (auto& el : pressedKeys)
                    pressedKeys.remove(el);
                QString styleSheet = QString("background-color: blue;");
                if (keys["f12"])
                {
                    qDebug() << keyText.toStdString();
                    for (auto& key : keys)
                        key.second->setStyleSheet("background - color: none;");
                    keys["f12"]->setStyleSheet(styleSheet);
                    pressedKeys.insert("f12");
                }
            }

        }
        QRegularExpression regex("^.*$");
        if (!keyText.isEmpty() and regex.match(keyText).hasMatch() and keyText !="\u001B" and keyText != "\r") {
           
            
            for (auto& key : keys)
                key.second->last_pressed = "";
            last_pressed = keyText;
            for (auto& key : keys)
                qDebug() << key.second->last_pressed;
            if (pressedKeys.contains(keyText)) {
                pressedKeys.remove(keyText);
                keys[keyText.toStdString()]->setStyleSheet("background-color: none;");
            }
            else
            {
                for (auto& el : pressedKeys)
                    pressedKeys.remove(el);
                QString styleSheet = QString("background-color: blue;");           
                if (keys[keyText.toStdString()])
                {
                   
                    for (auto& key : keys)
                        key.second->setStyleSheet("background - color: none;");
                    keys[keyText.toStdString()]->setStyleSheet(styleSheet);
                    pressedKeys.insert(keyText);
                }
            }
       
        }
        QPushButton::keyPressEvent(event);
	    
    }
};